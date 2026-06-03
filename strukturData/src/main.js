import Chart from 'chart.js/auto'
import './style.css'

const app = document.querySelector('#app')

const currencyFormatter = new Intl.NumberFormat('id-ID', {
  style: 'currency',
  currency: 'IDR',
  maximumFractionDigits: 0,
})

const numberFormatter = new Intl.NumberFormat('id-ID')

const kategoriList = ['Elektronik', 'ATK', 'Kebutuhan', 'Logistik', 'Sparepart', 'Packaging']

const state = {
  data: null,
  error: null,
}

const chartState = {
  timeChart: null,
  memoryChart: null,
}

function createSeededRandom(seed) {
  let value = seed % 2147483647

  if (value <= 0) {
    value += 2147483646
  }

  return () => {
    value = (value * 16807) % 2147483647
    return (value - 1) / 2147483646
  }
}

function padId(index) {
  return String(index).padStart(5, '0')
}

function getStatus(stok) {
  if (stok === 0) {
    return 'Habis'
  }

  if (stok < 25) {
    return 'Menipis'
  }

  return 'Tersedia'
}

function generateInventory(count) {
  const random = createSeededRandom(count * 97 + 13)
  const records = []

  for (let index = 1; index <= count; index += 1) {
    const kategori = kategoriList[Math.floor(random() * kategoriList.length)]
    const stok = Math.floor(random() * 160)
    const harga = Math.floor(15000 + random() * 485000)

    records.push({
      id: `BRG-${padId(index)}`,
      nama: `Barang ${padId(index)}`,
      stok,
      harga,
      kategori,
      status: getStatus(stok),
    })
  }

  return records
}

function cloneRecord(record) {
  return { ...record }
}

function formatDuration(value) {
  return `${value.toFixed(2)} ms`
}

function formatBytes(value) {
  if (value < 1024) {
    return `${Math.round(value)} B`
  }

  if (value < 1024 * 1024) {
    return `${(value / 1024).toFixed(2)} KB`
  }

  return `${(value / (1024 * 1024)).toFixed(2)} MB`
}

function estimateRecordSize(record) {
  const textSize = (record.id.length + record.nama.length + record.kategori.length + record.status.length) * 2
  const numericSize = 16
  return textSize + numericSize
}

function estimateVectorMemory(records) {
  const recordBytes = records.reduce((total, record) => total + estimateRecordSize(record), 0)
  const referenceBytes = records.length * 8
  return recordBytes + referenceBytes + 128
}

function estimateMapMemory(records) {
  const recordBytes = records.reduce((total, record) => total + estimateRecordSize(record), 0)
  const entryBytes = records.length * 32
  const keyBytes = records.reduce((total, record) => total + record.id.length * 2, 0)
  return recordBytes + entryBytes + keyBytes + 256
}

function createQueryIds(records, queryCount) {
  const random = createSeededRandom(records.length * 41 + queryCount * 17)
  const queryIds = []

  for (let index = 0; index < queryCount; index += 1) {
    const target = Math.floor(random() * records.length)
    queryIds.push(records[target].id)
  }

  return queryIds
}

function buildVector(records) {
  return records.map(cloneRecord)
}

function buildMap(records) {
  const inventoryMap = new Map()

  for (const record of records) {
    inventoryMap.set(record.id, cloneRecord(record))
  }

  return inventoryMap
}

function runVectorExperiment(records, queryIds) {
  const buildStart = performance.now()
  const vector = buildVector(records)
  const buildDuration = performance.now() - buildStart

  let searchHits = 0
  let totalNilai = 0
  const searchStart = performance.now()

  for (const id of queryIds) {
    const item = vector.find((record) => record.id === id)

    if (item) {
      searchHits += 1
      totalNilai += item.harga * item.stok
    }
  }

  const searchDuration = performance.now() - searchStart

  const updateTargetIds = queryIds.slice(0, Math.min(200, queryIds.length))
  const updateStart = performance.now()

  for (const id of updateTargetIds) {
    const item = vector.find((record) => record.id === id)

    if (item) {
      item.stok = Math.max(0, item.stok - 1)
      item.status = getStatus(item.stok)
    }
  }

  const updateDuration = performance.now() - updateStart

  const deleteTargetIds = queryIds.slice(-120)
  const deleteStart = performance.now()

  for (const id of deleteTargetIds) {
    const index = vector.findIndex((record) => record.id === id)

    if (index !== -1) {
      vector.splice(index, 1)
    }
  }

  const deleteDuration = performance.now() - deleteStart

  return {
    label: 'Vector',
    structure: vector,
    buildDuration,
    searchDuration,
    updateDuration,
    deleteDuration,
    searchHits,
    checksum: totalNilai,
    memoryBytes: estimateVectorMemory(records),
  }
}

function runMapExperiment(records, queryIds) {
  const buildStart = performance.now()
  const inventoryMap = buildMap(records)
  const buildDuration = performance.now() - buildStart

  let searchHits = 0
  let totalNilai = 0
  const searchStart = performance.now()

  for (const id of queryIds) {
    const item = inventoryMap.get(id)

    if (item) {
      searchHits += 1
      totalNilai += item.harga * item.stok
    }
  }

  const searchDuration = performance.now() - searchStart

  const updateTargetIds = queryIds.slice(0, Math.min(200, queryIds.length))
  const updateStart = performance.now()

  for (const id of updateTargetIds) {
    const item = inventoryMap.get(id)

    if (item) {
      item.stok = Math.max(0, item.stok - 1)
      item.status = getStatus(item.stok)
    }
  }

  const updateDuration = performance.now() - updateStart

  const deleteTargetIds = queryIds.slice(-120)
  const deleteStart = performance.now()

  for (const id of deleteTargetIds) {
    inventoryMap.delete(id)
  }

  const deleteDuration = performance.now() - deleteStart

  return {
    label: 'Unordered Map',
    structure: inventoryMap,
    buildDuration,
    searchDuration,
    updateDuration,
    deleteDuration,
    searchHits,
    checksum: totalNilai,
    memoryBytes: estimateMapMemory(records),
  }
}

function averageDuration(results, key) {
  const total = results.reduce((sum, result) => sum + result[key], 0)
  return total / results.length
}

function getFastestLabel(vectorValue, mapValue) {
  if (Math.abs(vectorValue - mapValue) < 0.01) {
    return 'Seri'
  }

  return vectorValue < mapValue ? 'Vector' : 'Unordered Map'
}

function renderPreviewRows(records) {
  return records
    .slice(0, 8)
    .map(
      (record) => `
        <tr>
          <td>${record.id}</td>
          <td>${record.nama}</td>
          <td>${record.kategori}</td>
          <td>${record.stok}</td>
          <td>${currencyFormatter.format(record.harga)}</td>
          <td><span class="status-chip status-${record.status.toLowerCase()}">${record.status}</span></td>
        </tr>
      `,
    )
    .join('')
}

function renderBenchmarkRows(benchmark) {
  return [`
    <tr>
      <td>Bangun struktur</td>
      <td>${formatDuration(benchmark.vector.buildDuration)}</td>
      <td>${formatDuration(benchmark.map.buildDuration)}</td>
      <td>${getFastestLabel(benchmark.vector.buildDuration, benchmark.map.buildDuration)}</td>
    </tr>
    <tr>
      <td>Pencarian ID</td>
      <td>${formatDuration(benchmark.vector.searchDuration)}</td>
      <td>${formatDuration(benchmark.map.searchDuration)}</td>
      <td>${getFastestLabel(benchmark.vector.searchDuration, benchmark.map.searchDuration)}</td>
    </tr>
    <tr>
      <td>Update stok</td>
      <td>${formatDuration(benchmark.vector.updateDuration)}</td>
      <td>${formatDuration(benchmark.map.updateDuration)}</td>
      <td>${getFastestLabel(benchmark.vector.updateDuration, benchmark.map.updateDuration)}</td>
    </tr>
    <tr>
      <td>Hapus data</td>
      <td>${formatDuration(benchmark.vector.deleteDuration)}</td>
      <td>${formatDuration(benchmark.map.deleteDuration)}</td>
      <td>${getFastestLabel(benchmark.vector.deleteDuration, benchmark.map.deleteDuration)}</td>
    </tr>
  `].join('')
}

function renderResults() {
  if (!state.data) {
    return `
      <section class="panel card benchmark-card">
        <div class="panel-head">
          <div>
            <p class="eyebrow">Memuat data</p>
            <h3>Menunggu JSON dari C++</h3>
          </div>
        </div>
        <p class="microcopy">File benchmark-data.json belum tersedia atau masih dimuat.</p>
      </section>
    `
  }

  const { benchmark, preview, summary } = state.data

  return `
    <section class="panel-grid">
      <article class="panel card">
        <div class="panel-head">
          <p class="eyebrow">Hasil ringkas</p>
          <h3>Vector</h3>
        </div>
        <div class="stat-stack">
          <div class="stat-line"><span>Record aktif</span><strong>${numberFormatter.format(benchmark.vector.activeCount)}</strong></div>
          <div class="stat-line"><span>Hit pencarian</span><strong>${numberFormatter.format(benchmark.vector.searchHits)}</strong></div>
          <div class="stat-line"><span>Total nilai sampel</span><strong>${currencyFormatter.format(benchmark.vector.checksum)}</strong></div>
          <div class="stat-line"><span>Estimasi memori</span><strong>${formatBytes(benchmark.vector.memoryBytes)}</strong></div>
        </div>
      </article>

      <article class="panel card">
        <div class="panel-head">
          <p class="eyebrow">Hasil ringkas</p>
          <h3>Unordered Map</h3>
        </div>
        <div class="stat-stack">
          <div class="stat-line"><span>Record aktif</span><strong>${numberFormatter.format(benchmark.map.activeCount)}</strong></div>
          <div class="stat-line"><span>Hit pencarian</span><strong>${numberFormatter.format(benchmark.map.searchHits)}</strong></div>
          <div class="stat-line"><span>Total nilai sampel</span><strong>${currencyFormatter.format(benchmark.map.checksum)}</strong></div>
          <div class="stat-line"><span>Estimasi memori</span><strong>${formatBytes(benchmark.map.memoryBytes)}</strong></div>
        </div>
      </article>
    </section>

    <section class="panel card benchmark-card">
      <div class="panel-head">
        <div>
          <p class="eyebrow">Perbandingan waktu</p>
          <h3>Vector vs Unordered Map</h3>
        </div>
        <p class="microcopy">Semakin kecil nilai waktu, semakin baik.</p>
      </div>
      <div class="table-wrap">
        <table>
          <thead>
            <tr>
              <th>Operasi</th>
              <th>Vector</th>
              <th>Unordered Map</th>
              <th>Paling cepat</th>
            </tr>
          </thead>
          <tbody>
            ${renderBenchmarkRows(benchmark)}
          </tbody>
        </table>
      </div>
    </section>

    <section class="panel-grid chart-grid">
      <article class="card chart-card">
        <div class="panel-head">
          <div>
            <p class="eyebrow">Grafik waktu</p>
            <h3>Perbandingan performa</h3>
          </div>
          <p class="microcopy">Nilai lebih kecil berarti lebih cepat.</p>
        </div>
        <div class="chart-frame">
          <canvas id="time-chart" aria-label="Grafik waktu vector dan unordered map" role="img"></canvas>
        </div>
      </article>

      <article class="card chart-card">
        <div class="panel-head">
          <div>
            <p class="eyebrow">Grafik memori</p>
            <h3>Estimasi penggunaan memori</h3>
          </div>
          <p class="microcopy">Semakin kecil, semakin hemat ruang.</p>
        </div>
        <div class="chart-frame">
          <canvas id="memory-chart" aria-label="Grafik estimasi memori vector dan unordered map" role="img"></canvas>
        </div>
      </article>
    </section>

    <section class="panel-grid">
      <article class="card inventory-card">
        <div class="panel-head">
          <div>
            <p class="eyebrow">Preview data</p>
            <h3>Inventori contoh</h3>
          </div>
          <span class="pill">${numberFormatter.format(preview.length)} baris awal</span>
        </div>
        <div class="table-wrap compact-table">
          <table>
            <thead>
              <tr>
                <th>ID</th>
                <th>Nama</th>
                <th>Kategori</th>
                <th>Stok</th>
                <th>Harga</th>
                <th>Status</th>
              </tr>
            </thead>
            <tbody>
              ${renderPreviewRows(preview)}
            </tbody>
          </table>
        </div>
      </article>

      <article class="card notes-card">
        <div class="panel-head">
          <div>
            <p class="eyebrow">Catatan eksperimen</p>
            <h3>Interpretasi singkat</h3>
          </div>
        </div>
        <div class="note-list">
          <div class="note-item">
            <strong>Vector</strong>
            <p>Cocok jika data dibaca berurutan dan jumlah operasi pencarian tidak dominan. Dataset: ${numberFormatter.format(summary.itemCount)} item.</p>
          </div>
          <div class="note-item">
            <strong>Unordered Map</strong>
            <p>Lebih cocok untuk pencarian dan update berdasarkan ID karena akses langsung via key.</p>
          </div>
          <div class="note-item">
            <strong>Memori</strong>
            <p>Estimasi memori menunjukkan Map cenderung lebih boros, tetapi lebih cepat untuk lookup.</p>
          </div>
        </div>
      </article>
    </section>
  `
}

function renderApp() {
  if (state.error) {
    app.innerHTML = `
      <div class="page-shell">
        <section class="card hero">
          <div class="hero-copy">
            <p class="eyebrow">Struktur Data - Proyek Inventori Gudang</p>
            <h1>Gagal memuat data benchmark dari C++.</h1>
            <p class="lede">${state.error}</p>
          </div>
        </section>
      </div>
    `
    return
  }

  if (!state.data) {
    app.innerHTML = `
      <div class="page-shell">
        <section class="card hero">
          <div class="hero-copy">
            <p class="eyebrow">Struktur Data - Proyek Inventori Gudang</p>
            <h1>Memuat hasil eksperimen dari C++.</h1>
            <p class="lede">JS hanya merender grafik batang dan tabel hasil yang sudah dihitung dari program C++.</p>
          </div>
        </section>
      </div>
    `
    return
  }

  const { summary } = state.data

  app.innerHTML = `
    <div class="page-shell">
      <div class="orb orb-left" aria-hidden="true"></div>
      <div class="orb orb-right" aria-hidden="true"></div>

      <header class="hero card">
        <div class="hero-copy">
          <p class="eyebrow">Struktur Data - Proyek Inventori Gudang</p>
          <h1>Sistem inventori gudang untuk eksperimen waktu dan memori.</h1>
          <p class="lede">
            Bandingkan pendekatan <strong>vector</strong> dan <strong>unordered_map</strong> pada data barang gudang. Data benchmark
            dihitung oleh C++ lalu dipakai JS hanya untuk visualisasi.
          </p>
        </div>

        <div class="hero-summary">
          <div class="summary-card accent-card">
            <span>Dataset</span>
            <strong>${numberFormatter.format(summary.itemCount)} barang</strong>
          </div>
          <div class="summary-card">
            <span>Query acak</span>
            <strong>${numberFormatter.format(summary.queryCount)} kali</strong>
          </div>
          <div class="summary-card">
            <span>Pengulangan</span>
            <strong>${numberFormatter.format(summary.rounds)} ronde</strong>
          </div>
          <div class="summary-card">
            <span>Basis data</span>
            <strong>Array vs Map</strong>
          </div>
        </div>
      </header>

      ${renderResults()}

      <footer class="footer-note">
        <p>
          Catatan: pengukuran waktu dan estimasi memori dihitung di C++, sementara JS hanya membaca JSON dan merender grafik.
        </p>
      </footer>
    </div>
  `

  renderCharts()
}

function destroyCharts() {
  if (chartState.timeChart) {
    chartState.timeChart.destroy()
    chartState.timeChart = null
  }

  if (chartState.memoryChart) {
    chartState.memoryChart.destroy()
    chartState.memoryChart = null
  }
}

function buildChartConfig(labels, vectorValues, mapValues, title, yLabel) {
  return {
    type: 'bar',
    data: {
      labels,
      datasets: [
        {
          label: 'Vector',
          data: vectorValues,
          backgroundColor: 'rgba(97, 212, 255, 0.75)',
          borderColor: 'rgba(97, 212, 255, 1)',
          borderWidth: 1,
          borderRadius: 10,
        },
        {
          label: 'Unordered Map',
          data: mapValues,
          backgroundColor: 'rgba(241, 180, 90, 0.75)',
          borderColor: 'rgba(241, 180, 90, 1)',
          borderWidth: 1,
          borderRadius: 10,
        },
      ],
    },
    options: {
      responsive: true,
      maintainAspectRatio: false,
      interaction: {
        mode: 'index',
        intersect: false,
      },
      plugins: {
        legend: {
          labels: {
            usePointStyle: true,
            pointStyle: 'rectRounded',
          },
        },
        title: {
          display: true,
          text: title,
        },
        tooltip: {
          callbacks: {
            label(context) {
              return `${context.dataset.label}: ${context.raw.toFixed(2)} ${yLabel}`
            },
          },
        },
      },
      scales: {
        x: {
          grid: {
            display: false,
          },
        },
        y: {
          beginAtZero: true,
          ticks: {
            callback(value) {
              return `${Number(value).toFixed(0)}`
            },
          },
        },
      },
    },
  }
}

function renderCharts() {
  destroyCharts()

  if (!state.data) {
    return
  }

  const { benchmark } = state.data
  const operations = ['Bangun', 'Cari', 'Update', 'Hapus']
  const vectorTimes = [
    benchmark.vector.buildDuration,
    benchmark.vector.searchDuration,
    benchmark.vector.updateDuration,
    benchmark.vector.deleteDuration,
  ]
  const mapTimes = [
    benchmark.map.buildDuration,
    benchmark.map.searchDuration,
    benchmark.map.updateDuration,
    benchmark.map.deleteDuration,
  ]

  const timeCanvas = document.querySelector('#time-chart')
  const memoryCanvas = document.querySelector('#memory-chart')

  if (timeCanvas) {
    chartState.timeChart = new Chart(timeCanvas, buildChartConfig(
      operations,
      vectorTimes,
      mapTimes,
      'Waktu eksekusi per operasi (ms)',
      'ms',
    ))
  }

  if (memoryCanvas) {
    chartState.memoryChart = new Chart(memoryCanvas, buildChartConfig(
      ['Estimasi memori'],
      [benchmark.vector.memoryBytes / 1024],
      [benchmark.map.memoryBytes / 1024],
      'Estimasi memori per struktur (KB)',
      'KB',
    ))
  }
}

async function loadBenchmarkData() {
  try {
    const response = await fetch('/benchmark-data.json', { cache: 'no-store' })

    if (!response.ok) {
      throw new Error(`Gagal memuat benchmark-data.json (${response.status})`)
    }

    state.data = await response.json()
    renderApp()
  } catch (error) {
    state.error = error instanceof Error ? error.message : 'Gagal memuat data benchmark.'
    renderApp()
  }
}

loadBenchmarkData()
