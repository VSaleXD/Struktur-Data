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

class unordered_map {
private:
    std::unordered_map<std::string, Barang> data;

public:
    bool insert(const std::pair<std::string, Barang>& p) {
        return data.emplace(p.first, p.second).second;
    }

    bool search(const std::string& key, Barang& hasil) const {
        auto it = data.find(key);
        if (it == data.end()) {
            return false;
        }
        hasil = it->second;
        return true;
    }

    bool update(const std::string& key, int value) {
        auto it = data.find(key);
        if (it == data.end()) {
            return false;
        }
        it->second.stok = std::max(0, value);
        it->second.status = tentukanStatus(it->second.stok);
        return true;
    }

    bool hapus(const std::string& key) {
        return data.erase(key) > 0;
    }

    std::size_t size() const {
        return data.size();
    }

    void printAll() const {
        std::cout << "\nData unordered_map:\n";
        for (const auto& entry : data) {
            const Barang& b = entry.second;
            std::cout << b.id << " | " << b.nama << " | " << b.kategori << " | "
                      << b.stok << " | " << b.harga << " | " << b.status << '\n';
        }
    }
};

class vector {
private:
    std::vector<Barang> data;

    int cariIndex(const std::string& key) const {
        for (std::size_t i = 0; i < data.size(); ++i) {
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

    bool search(const std::string& key, Barang& hasil) const {
        for (const auto& item : data) {
            if (item.nama == key) {
                hasil = item;
                return true;
            }
        }
        return false;
    }

    bool update(const std::string& key, int value) {
        int index = cariIndex(key);
        if (index == -1) {
            return false;
        }
        data[static_cast<std::size_t>(index)].stok = std::max(0, value);
        data[static_cast<std::size_t>(index)].status = tentukanStatus(data[static_cast<std::size_t>(index)].stok);
        return true;
    }

    bool hapus(const std::string& key) {
        int index = cariIndex(key);
        if (index == -1) {
            return false;
        }
        data.erase(data.begin() + index);
        return true;
    }

    std::size_t size() const {
        return data.size();
    }

    void printAll() const {
        std::cout << "\nData vector:\n";
        for (const auto& b : data) {
            std::cout << b.id << " | " << b.nama << " | " << b.kategori << " | "
                      << b.stok << " | " << b.harga << " | " << b.status << '\n';
        }
    }
};

static Barang buatBarang(int id, const std::string& nama, const std::string& kategori, int stok, int harga) {
    return Barang{id, nama, kategori, stok, harga, tentukanStatus(stok)};
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    vector inventoriVector;
    unordered_map inventoriMap;

    inventoriVector.insert(buatBarang(1, "Laptop A", "Elektronik", 12, 15000000));
    inventoriVector.insert(buatBarang(2, "Mouse B", "Elektronik", 40, 175000));
    inventoriVector.insert(buatBarang(3, "Kardus C", "Packaging", 80, 25000));

    inventoriMap.insert({"1", buatBarang(1, "Laptop A", "Elektronik", 12, 15000000)});
    inventoriMap.insert({"2", buatBarang(2, "Mouse B", "Elektronik", 40, 175000)});
    inventoriMap.insert({"3", buatBarang(3, "Kardus C", "Packaging", 80, 25000)});

    Barang hasil;
    if (inventoriVector.search("Mouse B", hasil)) {
        std::cout << "Vector search: " << hasil.nama << " stok " << hasil.stok << '\n';
    }

    if (inventoriMap.search("2", hasil)) {
        std::cout << "Map search: " << hasil.nama << " stok " << hasil.stok << '\n';
    }

    inventoriVector.update("Laptop A", 9);
    inventoriMap.update("1", 9);

    inventoriVector.hapus("Kardus C");
    inventoriMap.hapus("3");

    inventoriVector.printAll();
    inventoriMap.printAll();

    std::cout << "\nUkuran vector   : " << inventoriVector.size() << '\n';
    std::cout << "Ukuran hash map : " << inventoriMap.size() << '\n';
    return 0;
}