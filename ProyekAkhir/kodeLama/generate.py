from pathlib import Path
import random
import sys

KATEGORI_LIST = [
	"Elektronik",
	"Makanan",
	"Minuman",
	"Pakaian",
	"ATK",
	"Kebersihan",
	"Olahraga",
	"Otomotif",
]

NAMA_BARANG = {
	"Elektronik": ["Laptop", "Mouse", "Keyboard", "Monitor", "Printer"],
	"Makanan": ["Beras", "Gula", "MiInstan", "Biskuit", "Sereal"],
	"Minuman": ["AirMineral", "Kopi", "Teh", "Susu", "Jus"],
	"Pakaian": ["Kaos", "Jaket", "Celana", "Kemeja", "Topi"],
	"ATK": ["Pensil", "Pulpen", "BukuTulis", "Spidol", "Map"],
	"Kebersihan": ["Sabun", "Sampo", "Tisu", "PembersihLantai", "PastaGigi"],
	"Olahraga": ["Bola", "Raket", "Matras", "SepatuLari", "Skipping"],
	"Otomotif": ["Oli", "Helm", "Ban", "KampasRem", "Aki"],
}


def buat_status(stok):
	if stok == 0:
		return "Habis"
	if stok < 10:
		return "Menipis"
	return "Tersedia"


def buat_data_barang(jumlah_data, seed=42):
	random.seed(seed)
	data_barang = []

	for index in range(jumlah_data):
		kategori = random.choice(KATEGORI_LIST)
		nama_dasar = random.choice(NAMA_BARANG[kategori])
		stok = random.randint(0, 250)
		harga = random.randrange(5000, 500001, 5000)
		status = buat_status(stok)
		nomor = 1001 + index
		nama = f"{nama_dasar}_{nomor}"

		data_barang.append(
			{
				"id": nomor,
				"nama": nama,
				"stok": stok,
				"harga": harga,
				"kategori": kategori,
				"status": status,
			}
		)

	return data_barang


def simpan_ke_file(data_barang, output_file):
	baris = [str(len(data_barang))]

	for barang in data_barang:
		baris.append(
			f"{barang['id']} {barang['nama']} {barang['stok']} {barang['harga']} {barang['kategori']} {barang['status']}"
		)

	output_file.write_text("\n".join(baris), encoding="utf-8")


def main():
	folder_skrip = Path(__file__).resolve().parent
	output_file = folder_skrip / "data.txt"
	jumlah_data = 10
	seed = 42

	if len(sys.argv) >= 2:
		jumlah_data = int(sys.argv[1])

	if len(sys.argv) >= 3:
		seed = int(sys.argv[2])

	data_barang = buat_data_barang(jumlah_data, seed)
	simpan_ke_file(data_barang, output_file)
	print(f"Berhasil membuat {jumlah_data} data dummy di {output_file.name} dengan seed {seed}")


if __name__ == "__main__":
	main()