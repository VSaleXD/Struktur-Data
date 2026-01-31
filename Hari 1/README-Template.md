# Template Pengumpulan Tugas — Cara Pakai

Berikut cara menggunakan template untuk membuat PDF pengumpulan tugas.

## Langkah Cepat
- Buka file [Hari 1/Tugas-PDF-Template.html](Hari%201/Tugas-PDF-Template.html) di VS Code.
- Ganti semua placeholder (contoh: "Isi nama lengkap", "Isi NIM", dll.).
- Simpan, lalu buka file tersebut di browser (Chrome/Edge).
- Tekan `Ctrl+P` → pilih "Simpan sebagai PDF" → simpan.

## Isi yang Disarankan
- Identitas: Nama, NIM, Kelas, Mata Kuliah, Hari/Tanggal, Judul Tugas.
- Ringkasan: Tujuan dan penjelasan singkat solusi.
- Cara kompilasi/run: Perintah yang dipakai.
- Hasil eksekusi: Output penting dan analisis singkat.
- Cuplikan kode: Bagian kode relevan dari [Hari 1/LKP1.cpp](Hari%201/LKP1.cpp).
- Screenshot: Hasil run/IDE (opsional).
- Pernyataan keaslian dan tanda tangan.

## Kompilasi Program (Windows)
Jalankan perintah berikut dari folder "Hari 1":

```powershell
g++ -std=c++17 -O2 -Wall -o LKP1.exe LKP1.cpp
./LKP1.exe
```

Jika `g++` belum tersedia, install MinGW atau gunakan compiler lain yang tersedia.
