#include <bits/stdc++.h>
using namespace std;

// Struktur data produk
struct Produk {
    int id;
    string nama;
    string kategori;
    int stok;
    double harga;
    string status;
};

const int MAKS_PRODUK = 1000;
Produk daftarProduk[MAKS_PRODUK];
int jumlahProduk = 0;

// Fungsi mencari indeks produk berdasarkan ID
int cariProdukById(int id) {
    for (int i = 0; i < jumlahProduk; i++) {
        if (daftarProduk[i].id == id) return i;
    }
    return -1;
}

// Menu insert produk
void insertProduk() {
    if (jumlahProduk >= MAKS_PRODUK) {
        cout << "Kapasitas penuh!\n";
        return;
    }
    Produk p;
    cout << "ID produk: "; cin >> p.id;
    if (cariProdukById(p.id) != -1) {
        cout << "ID sudah ada!\n";
        return;
    }
    cout << "Nama: "; cin.ignore(); getline(cin, p.nama);
    cout << "Kategori: "; getline(cin, p.kategori);
    cout << "Stok: "; cin >> p.stok;
    cout << "Harga: "; cin >> p.harga;
    cout << "Status: "; cin.ignore(); getline(cin, p.status);
    daftarProduk[jumlahProduk++] = p;
    cout << "Produk berhasil ditambah!\n";
}

// Menu search produk
void searchProduk() {
    int id;
    cout << "Masukkan ID produk: "; cin >> id;
    int idx = cariProdukById(id);
    if (idx == -1) cout << "Produk tidak ditemukan!\n";
    else {
        Produk &p = daftarProduk[idx];
        cout << "ID: " << p.id << "\nNama: " << p.nama << "\nKategori: " << p.kategori << "\nStok: " << p.stok << "\nHarga: " << p.harga << "\nStatus: " << p.status << "\n";
    }
}

// Menu update stok
void updateStok() {
    int id, stokBaru;
    cout << "ID produk: "; cin >> id;
    int idx = cariProdukById(id);
    if (idx == -1) cout << "Produk tidak ditemukan!\n";
    else {
        cout << "Stok baru: "; cin >> stokBaru;
        daftarProduk[idx].stok = stokBaru;
        cout << "Stok berhasil diupdate!\n";
    }
}

// Menu delete produk
void deleteProduk() {
    int id;
    cout << "ID produk: "; cin >> id;
    int idx = cariProdukById(id);
    if (idx == -1) cout << "Produk tidak ditemukan!\n";
    else {
        for (int i = idx; i < jumlahProduk - 1; i++) {
            daftarProduk[i] = daftarProduk[i+1];
        }
        jumlahProduk--;
        cout << "Produk berhasil dihapus!\n";
    }
}

// Tampilkan semua produk
void tampilkanSemua() {
    if (jumlahProduk == 0) {
        cout << "Belum ada produk.\n";
        return;
    }
    for (int i = 0; i < jumlahProduk; i++) {
        Produk &p = daftarProduk[i];
        cout << i+1 << ". ID: " << p.id << ", Nama: " << p.nama << ", Stok: " << p.stok << ", Harga: " << p.harga << ", Status: " << p.status << "\n";
    }
}

int main() {
    int pilihan;
    do {
        cout << "\n=== Sistem Inventori Gudang (Array) ===\n";
        cout << "1. Insert produk\n2. Search produk\n3. Update stok\n4. Delete produk\n5. Tampilkan semua\n0. Keluar\nPilih menu: ";
        cin >> pilihan;
        switch(pilihan) {
            case 1: insertProduk(); break;
            case 2: searchProduk(); break;
            case 3: updateStok(); break;
            case 4: deleteProduk(); break;
            case 5: tampilkanSemua(); break;
            case 0: cout << "Keluar...\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while (pilihan != 0);
    return 0;
}
