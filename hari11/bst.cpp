#include <bits/stdc++.h>
using namespace std;

const int MAKS_NODE = 200;

struct NodeArray {
    int info;
    int kiri;
    int kanan;
    bool aktif;
};

class BSTArray {
private:
    NodeArray data[MAKS_NODE];
    int root;
    int nextKosong;

    int buatNode(int nilai) {
        if (nextKosong >= MAKS_NODE) {
            return -1;
        }

        data[nextKosong].info = nilai;
        data[nextKosong].kiri = -1;
        data[nextKosong].kanan = -1;
        data[nextKosong].aktif = true;

        return nextKosong++;
    }

    bool cariNodeDanParent(int nilai, int &idx, int &parent) {
        idx = root;
        parent = -1;

        while (idx != -1) {
            if (data[idx].info == nilai) {
                return true;
            }

            parent = idx;
            if (nilai < data[idx].info) {
                idx = data[idx].kiri;
            } else {
                idx = data[idx].kanan;
            }
        }

        return false;
    }

    void tampilMenyamping(int idx, int level) {
        if (idx == -1) {
            return;
        }

        tampilMenyamping(data[idx].kanan, level + 1);

        cout << '\n';
        if (idx == root) {
            cout << "Root-> ";
        } else {
            for (int i = 0; i < level; i++) {
                cout << ' ';
            }
        }
        cout << data[idx].info;

        tampilMenyamping(data[idx].kiri, level + 1);
    }

public:
    BSTArray() {
        root = -1;
        nextKosong = 0;
        for (int i = 0; i < MAKS_NODE; i++) {
            data[i].aktif = false;
            data[i].kiri = -1;
            data[i].kanan = -1;
            data[i].info = 0;
        }
    }

    bool kosong() {
        return root == -1;
    }

    void tambah(int nilai) {
        if (root == -1) {
            int idxBaru = buatNode(nilai);
            if (idxBaru == -1) {
                cout << "Kapasitas node penuh." << endl;
                return;
            }
            root = idxBaru;
            cout << "Node root berhasil ditambahkan." << endl;
            return;
        }

        int sekarang = root;
        int parent = -1;

        while (sekarang != -1) {
            if (data[sekarang].info == nilai) {
                cout << "Nilai sudah ada di BST." << endl;
                return;
            }

            parent = sekarang;
            if (nilai < data[sekarang].info) {
                sekarang = data[sekarang].kiri;
            } else {
                sekarang = data[sekarang].kanan;
            }
        }

        int idxBaru = buatNode(nilai);
        if (idxBaru == -1) {
            cout << "Kapasitas node penuh." << endl;
            return;
        }

        if (nilai < data[parent].info) {
            data[parent].kiri = idxBaru;
        } else {
            data[parent].kanan = idxBaru;
        }

        cout << "Node berhasil ditambahkan." << endl;
    }

    void hapus(int nilai) {
        if (kosong()) {
            cout << "Tree kosong." << endl;
            return;
        }

        int loc, par;
        if (!cariNodeDanParent(nilai, loc, par)) {
            cout << "Node tidak ditemukan." << endl;
            return;
        }

        int kiri = data[loc].kiri;
        int kanan = data[loc].kanan;

        if (kiri == -1 && kanan == -1) {
            if (par == -1) {
                root = -1;
            } else if (data[par].kiri == loc) {
                data[par].kiri = -1;
            } else {
                data[par].kanan = -1;
            }
            data[loc].aktif = false;
            cout << "Node daun berhasil dihapus." << endl;
            return;
        }

        if (kiri == -1 || kanan == -1) {
            int child = (kiri != -1) ? kiri : kanan;

            if (par == -1) {
                root = child;
            } else if (data[par].kiri == loc) {
                data[par].kiri = child;
            } else {
                data[par].kanan = child;
            }

            data[loc].aktif = false;
            cout << "Node dengan satu anak berhasil dihapus." << endl;
            return;
        }

        int parSuc = loc;
        int suc = data[loc].kanan;

        while (data[suc].kiri != -1) {
            parSuc = suc;
            suc = data[suc].kiri;
        }

        data[loc].info = data[suc].info;

        int childSuc = data[suc].kanan;
        if (data[parSuc].kiri == suc) {
            data[parSuc].kiri = childSuc;
        } else {
            data[parSuc].kanan = childSuc;
        }

        data[suc].aktif = false;
        cout << "Node dengan dua anak berhasil dihapus." << endl;
    }

    void tampil() {
        if (kosong()) {
            cout << "Tree kosong." << endl;
            return;
        }

        tampilMenyamping(root, 1);
        cout << '\n';
    }
};

int main() {
    BSTArray bst;
    int pilihan, nilai;

    while (true) {
        cout << "\n==============================" << endl;
        cout << "     MENU BST TANPA POINTER   " << endl;
        cout << "==============================" << endl;
        cout << "1. Tampilkan BST" << endl;
        cout << "2. Tambah node" << endl;
        cout << "3. Hapus node" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                bst.tampil();
                break;
            case 2:
                cout << "Masukkan nilai yang ditambahkan: ";
                cin >> nilai;
                bst.tambah(nilai);
                break;
            case 3:
                cout << "Masukkan nilai yang dihapus: ";
                cin >> nilai;
                bst.hapus(nilai);
                break;
            case 4:
                cout << "Program selesai." << endl;
                return 0;
            default:
                cout << "Pilihan tidak valid." << endl;
        }
    }
}
