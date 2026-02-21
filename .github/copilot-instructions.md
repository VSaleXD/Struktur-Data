# Project Guidelines

## Code Style
- Bahasa utama: C++ (lihat contoh di hari4/stack.cpp, hari4/queue.cpp, Hari3/linkedlist.cpp)
- Gunakan penamaan variabel dan fungsi yang deskriptif, konsisten dengan bahasa Indonesia/Inggris sederhana.
- Struktur data diimplementasikan dengan struct dan array, bukan STL.
- Indentasi 4 spasi, tanpa tab.

## Architecture
- Setiap file .cpp biasanya berisi satu topik/struktur data (misal: stack, queue, linked list).
- Tidak ada pemisahan file header (.h), semua kode dalam satu file.
- Program utama (main) berisi menu interaktif untuk demonstrasi operasi struktur data.

## Build and Test
- Kompilasi dengan:  
  `g++ namafile.cpp -o namafile.exe`
- Jalankan dengan:  
  `./namafile.exe` (atau klik dua kali di Windows)
- Tidak ada framework testing otomatis, pengujian manual melalui menu interaktif.

## Project Conventions
- Semua input/output menggunakan fungsi standar C/C++ (scanf/printf/cin/cout).
- GUnakan library bits/stdc++.h untuk memudahkan penggunaan fungsi standar.
- File dan folder diberi nama sesuai topik dan urutan hari praktikum.

## Integration Points
- Tidak ada integrasi eksternal, semua kode mandiri.

## Security
- Tidak ada penanganan keamanan khusus, kode hanya untuk pembelajaran struktur data dasar.
