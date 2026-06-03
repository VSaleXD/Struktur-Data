#include <bits/stdc++.h>
using namespace std;

struct Barang {
    int id;
    string nama;
    string kategori;
    int stok;
    int harga;
    string status;
};

static string tentukanStatus(int stok) {
    if (stok <= 0) {
        return "Habis";
    }
    if (stok < 25) {
        return "Menipis";
    }
    return "Tersedia";
}

static vector<string> splitCSV(const string& baris, char pemisah) {
    vector<string> hasil;
    string token;
    stringstream ss(baris);
    while (getline(ss, token, pemisah)) {
        hasil.push_back(token);
    }
    return hasil;
}

static int parseHargaCSV(const string& nilai) {
    string bersih;
    for (char ch : nilai) {
        if (isdigit(static_cast<unsigned char>(ch))) {
            bersih.push_back(ch);
        }
    }
    if (bersih.empty()) {
        return 0;
    }
    return stoi(bersih);
}

class strukturDataUnorderedMap {
private:
    unordered_map<string, Barang> data;

public:
    bool insert(const pair<string, Barang>& p) {
        return data.emplace(p.first, p.second).second;
    }

    bool search(const string& key, Barang& hasil) const {
        auto it = data.find(key);
        if (it == data.end()) {
            return false;
        }
        hasil = it->second;
        return true;
    }

    bool update(const string& key, int value) {
        auto it = data.find(key);
        if (it == data.end()) {
            return false;
        }
        it->second.stok = max(0, value);
        it->second.status = tentukanStatus(it->second.stok);
        return true;
    }

    bool hapus(const string& key) {
        return data.erase(key) > 0;
    }

    size_t size() const {
        return data.size();
    }

    void printAll() const {
        cout << "\nData unordered_map:\n";
        for (const auto& entry : data) {
            const Barang& b = entry.second;
            cout << b.id << " | " << b.nama << " | " << b.kategori << " | "
                 << b.stok << " | " << b.harga << " | " << b.status << '\n';
        }
    }
};

class strukturDataVector {
private:
    vector<Barang> data;

    int cariIndex(const string& key) const {
        for (size_t i = 0; i < data.size(); ++i) {
            if (data[i].nama == key) {
                return static_cast<int>(i);
            }
        }
        return -1;
    }

public:
    bool insert(const Barang& value) {
        if (cariIndex(value.nama) != -1) {
            return false;
        }
        data.push_back(value);
        return true;
    }

    bool search(const string& key, Barang& hasil) const {
        for (const auto& item : data) {
            if (item.nama == key) {
                hasil = item;
                return true;
            }
        }
        return false;
    }

    bool update(const string& key, int value) {
        int index = cariIndex(key);
        if (index == -1) {
            return false;
        }
        data[static_cast<size_t>(index)].stok = max(0, value);
        data[static_cast<size_t>(index)].status = tentukanStatus(data[static_cast<size_t>(index)].stok);
        return true;
    }

    bool hapus(const string& key) {
        int index = cariIndex(key);
        if (index == -1) {
            return false;
        }
        data.erase(data.begin() + index);
        return true;
    }

    size_t size() const {
        return data.size();
    }

    void printAll() const {
        cout << "\nData vector:\n";
        for (const auto& b : data) {
            cout << b.id << " | " << b.nama << " | " << b.kategori << " | "
                 << b.stok << " | " << b.harga << " | " << b.status << '\n';
        }
    }
};

static Barang buatBarang(int id, const string& nama, const string& kategori, int stok, int harga) {
    return Barang{id, nama, kategori, stok, harga, tentukanStatus(stok)};
}

static bool importCSV(const string& namaFile, strukturDataVector& inventoriVector, strukturDataUnorderedMap& inventoriMap) {
    ifstream file(namaFile);
    if (!file.is_open()) {
        return false;
    }

    string baris;
    bool headerDilewati = false;
    int idBerurutan = 1;

    while (getline(file, baris)) {
        if (!headerDilewati) {
            headerDilewati = true;
            continue;
        }

        if (baris.empty()) {
            continue;
        }

        vector<string> kolom = splitCSV(baris, ';');
        if (kolom.size() < 8) {
            continue;
        }

        string stockCode = kolom[1];
        string nama = kolom[2];

        int stok = 0;
        try {
            stok = stoi(kolom[3]);
        } catch (const exception&) {
            continue;
        }

        int harga = parseHargaCSV(kolom[5]);
        string kategori = kolom[7];

        Barang barang = buatBarang(idBerurutan++, nama, kategori, stok, harga);
        inventoriVector.insert(barang);
        inventoriMap.insert({stockCode, barang});
    }

    return true;
}

int main() {

    strukturDataVector inventoriVector;
    strukturDataUnorderedMap inventoriMap;

    inventoriVector.insert(buatBarang(1, "Laptop A", "Elektronik", 12, 15000000));
    inventoriVector.insert(buatBarang(2, "Mouse B", "Elektronik", 40, 175000));
    inventoriVector.insert(buatBarang(3, "Kardus C", "Packaging", 80, 25000));

    inventoriMap.insert({"1", buatBarang(1, "Laptop A", "Elektronik", 12, 15000000)});
    inventoriMap.insert({"2", buatBarang(2, "Mouse B", "Elektronik", 40, 175000)});
    inventoriMap.insert({"3", buatBarang(3, "Kardus C", "Packaging", 80, 25000)});

    Barang hasil;
    if (inventoriVector.search("Mouse B", hasil)) {
        cout << "Vector search: " << hasil.nama << " stok " << hasil.stok << '\n';
    }

    if (inventoriMap.search("2", hasil)) {
        cout << "Map search: " << hasil.nama << " stok " << hasil.stok << '\n';
    }

    inventoriVector.update("Laptop A", 9);
    inventoriMap.update("1", 9);

    inventoriVector.hapus("Kardus C");
    inventoriMap.hapus("3");

    if (importCSV("online_retail_II.csv", inventoriVector, inventoriMap)) {
        cout << "\nImport CSV berhasil.\n";
    } else {
        cout << "\nImport CSV gagal. Pastikan online_retail_II.csv ada di folder yang sama.\n";
    }

    inventoriVector.printAll();
    inventoriMap.printAll();

    cout << "\nUkuran vector   : " << inventoriVector.size() << '\n';
    cout << "Ukuran hash map : " << inventoriMap.size() << '\n';
    return 0;
}