#include <bits/stdc++.h>
using namespace std;

#define TABLE_SIZE 7
#define EMPTY -1

int hashTable[TABLE_SIZE];

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

bool insert(int key) {
    int index = hashFunction(key);
    int startIndex = index;

    while (hashTable[index] != EMPTY) {
        index = (index + 1) % TABLE_SIZE;
        if (index == startIndex) {
            return false;
        }
    }

    hashTable[index] = key;
    return true;
}

void display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i] == EMPTY) {
            cout << i << " -> kosong" << endl;
        } else {
            cout << i << " -> " << hashTable[i] << endl;
        }
    }
}

int main() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = EMPTY;
    }

    int jumlahData, nilai;
    cout << "Masukkan jumlah data: ";
    cin >> jumlahData;

    cout << "Masukkan data:" << endl;
    for (int i = 0; i < jumlahData; i++) {
        cin >> nilai;
        if (!insert(nilai)) {
            cout << "Tabel penuh, data " << nilai << " tidak dapat dimasukkan." << endl;
            break;
        }
    }

    cout << "\nHash Table:" << endl;
    display();

    return 0;
}