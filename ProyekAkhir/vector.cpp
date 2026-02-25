#include <bits/stdc++.h>
using namespace std;

struct data{
    int ID;
    string nama;
    int stok;
    int harga;
    string kategori;
    string status;
};

void tambahBarang(vector<data>& inventory) {
    data barang;
    cout << "Masukkan ID barang: ";
    cin >> barang.ID;
    cout << "Masukkan nama barang: ";
    cin >> barang.nama;
    cout << "Masukkan stok barang: ";
    cin >> barang.stok;
    cout << "Masukkan harga barang: ";
    cin >> barang.harga;
    cout << "Masukkan kategori barang: ";
    cin >> barang.kategori;
    cout << "Masukkan status barang (Tersedia/Tidak Tersedia): ";
    cin >> barang.status;
    inventory.push_back(barang);
    cout << "Barang berhasil ditambahkan!\n";
}

void tampilkanSemua(const vector<data>& inventory) {
    if (inventory.empty()) {
        cout << "Inventori kosong!\n";
        return;
    }
    cout << "\nData barang dalam inventori:\n";
    for (const auto& barang : inventory) {
        cout << "ID: " << barang.ID << endl;
        cout << "Nama: " << barang.nama << endl;
        cout << "Stok: " << barang.stok << endl;
        cout << "Harga: " << barang.harga << endl;
        cout << "Kategori: " << barang.kategori << endl;
        cout << "Status: " << barang.status << endl;
        cout << "-----------------------------" << endl;
    }
}

void cariBarang(const vector<data>& inventory) {
    int id;
    cout << "Masukkan ID barang yang dicari: ";
    cin >> id;
    bool ditemukan = false;
    for (const auto& barang : inventory) {
        if (barang.ID == id) {
            cout << "ID: " << barang.ID << endl;
            cout << "Nama: " << barang.nama << endl;
            cout << "Stok: " << barang.stok << endl;
            cout << "Harga: " << barang.harga << endl;
            cout << "Kategori: " << barang.kategori << endl;
            cout << "Status: " << barang.status << endl;
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) cout << "Barang tidak ditemukan!\n";
}

void updateBarang(vector<data>& inventory) {
    int id;
    cout << "Masukkan ID barang yang ingin diupdate: ";
    cin >> id;
    bool ditemukan = false;
    for (auto& barang : inventory) {
        if (barang.ID == id) {
            cout << "Data lama: Nama: " << barang.nama << ", Stok: " << barang.stok << ", Harga: " << barang.harga << ", Kategori: " << barang.kategori << ", Status: " << barang.status << endl;
            cout << "Masukkan nama baru: ";
            cin >> barang.nama;
            cout << "Masukkan stok baru: ";
            cin >> barang.stok;
            cout << "Masukkan harga baru: ";
            cin >> barang.harga;
            cout << "Masukkan kategori baru: ";
            cin >> barang.kategori;
            cout << "Masukkan status baru: ";
            cin >> barang.status;
            cout << "Barang berhasil diupdate!\n";
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) cout << "Barang tidak ditemukan!\n";
}

void hapusBarang(vector<data>& inventory) {
    int id;
    cout << "Masukkan ID barang yang ingin dihapus: ";
    cin >> id;
    bool ditemukan = false;
    for (auto it = inventory.begin(); it != inventory.end(); ++it) {
        if (it->ID == id) {
            inventory.erase(it);
            cout << "Barang berhasil dihapus!\n";
            ditemukan = true;
            break;
        }
    }
    if (!ditemukan) cout << "Barang tidak ditemukan!\n";
}

int main() {
    vector<data> inventory;
    int pilihan;
    do {
        cout << "\n=== Menu Inventori Gudang (Vector) ===\n";
        cout << "1. Tambah Barang\n";
        cout << "2. Cari Barang\n";
        cout << "3. Update Barang\n";
        cout << "4. Hapus Barang\n";
        cout << "5. Tampilkan Semua Barang\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        switch(pilihan) {
            case 1: tambahBarang(inventory); break;
            case 2: cariBarang(inventory); break;
            case 3: updateBarang(inventory); break;
            case 4: hapusBarang(inventory); break;
            case 5: tampilkanSemua(inventory); break;
            case 0: cout << "Keluar...\n"; break;
            default: cout << "Pilihan tidak valid!\n";
        }
    } while(pilihan != 0);
    return 0;
}
