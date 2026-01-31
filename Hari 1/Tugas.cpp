/* Export this file to PDF:

Option A: Pandoc + XeLaTeX (recommended, syntax highlight)
- PowerShell:
  "```cpp`n$(Get-Content -Raw .\Tugas.cpp)`n```" | Set-Content .\Tugas.md
  pandoc -s .\Tugas.md -o .\Tugas.pdf --pdf-engine=xelatex --highlight-style=tango
- CMD:
  echo ```cpp> Tugas.md
  type Tugas.cpp >> Tugas.md
  echo ``` >> Tugas.md
  pandoc -s Tugas.md -o Tugas.pdf --pdf-engine=xelatex --highlight-style=tango

Option B: highlight CLI (single-step to PDF)
  highlight -O pdf -o Tugas.pdf Tugas.cpp

Option C: a2ps + Ghostscript
  a2ps -Ecpp -o out.ps Tugas.cpp && gswin64c -sDEVICE=pdfwrite -o Tugas.pdf out.ps

Option D: VS Code
  Install "PrintCode" or "Code Printer" extension → Print/Export to PDF.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <vector>
using namespace std;

// Struktur data
struct Mahasiswa {
    char nama[50];
    int nim;
    float ipk;
};

int main() {
    // Menggunakan POINTER
    int angka = 10;
    int* ptrAngka = &angka;
    printf("Nilai angka: %d\n", *ptrAngka);

    // Menggunakan ARRAY
    int arrayAngka[5] = {1, 2, 3, 4, 5};
    printf("Elemen-elemen array: ");
    for (int i = 0; i < 5; ++i) {
        printf("%d ", arrayAngka[i]);
    }
    printf("\n");

    // Menggunakan STRUCT
    Mahasiswa mhs1;
    strcpy(mhs1.nama, "John Doe");
    mhs1.nim = 12345;
    mhs1.ipk = 3.75f;

    printf("Data Mahasiswa:\n");
    printf("Nama: %s\n", mhs1.nama);
    printf("NIM: %d\n", mhs1.nim);
    printf("IPK: %.2f\n", mhs1.ipk);

    // Menggunakan STL (vector)
    std::vector<int> vectorAngka;
    for (int i = 0; i < 5; ++i) {
        vectorAngka.push_back(i * 2);
    }

    printf("Elemen-elemen vector: ");
    for (std::size_t i = 0; i < vectorAngka.size(); ++i) {
        printf("%d ", vectorAngka[i]);
    }
    printf("\n");
    // Modifikasi program
    // 1. Modifikasi nilai variabel angka menggunakan pointer
    *ptrAngka = 20;

    // 2. Modifikasi IPK mahasiswa mhs1 menggunakan pointer
    float* ptrIpk = &mhs1.ipk;
    *ptrIpk = 3.90f;

    // 3. Tambahkan dua elemen baru ke dalam vectorAngka
    vectorAngka.push_back(12);
    vectorAngka.push_back(15);

    // Tampilkan hasil setelah modifikasi
    printf("Setelah dimodifikasi:\n");
    printf("Nilai angka setelah dimodifikasi: %d\n", *ptrAngka);
    printf("IPK mahasiswa setelah dimodifikasi: %.2f\n", mhs1.ipk);
    printf("Elemen-elemen vector setelah dimodifikasi: ");
    for (size_t i = 0; i < vectorAngka.size(); ++i) {
        printf("%d ", vectorAngka[i]);
    }
    printf("\n");

    return 0;
}