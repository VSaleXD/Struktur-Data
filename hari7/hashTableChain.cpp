#include <bits/stdc++.h>
using namespace std;

#define TABLE_SIZE 10

struct Node {
    int key;
    Node* next;
};

Node* hashTable[TABLE_SIZE];

int hashFunction(int key) {
    return key % TABLE_SIZE;
}

Node* createNode(int key) {
    Node* newNode = new Node();
    newNode->key = key;
    newNode->next = NULL;
    return newNode;
}

void insert(int key) {
    int index = hashFunction(key);
    Node* newNode = createNode(key);

    if (hashTable[index] == NULL) {
        hashTable[index] = newNode;
    } else {
        newNode->next = hashTable[index];
        hashTable[index] = newNode;
    }
}

void display() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        cout << i << " -> ";
        Node* temp = hashTable[i];

        while (temp != NULL) {
            cout << temp->key << " -> ";
            temp = temp->next;
        }

        cout << "NULL" << endl;
    }
}

int totalCollisions() {
    int collisions = 0;

    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* temp = hashTable[i];
        int count = 0;

        while (temp != NULL) {
            count++;
            temp = temp->next;
        }

        if (count > 1) {
            collisions += (count - 1);
        }
    }

    return collisions;
}

int main() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }

    int jumlahData, nilai;
    cout << "Masukkan jumlah data: ";
    cin >> jumlahData;

    cout << "Masukkan data:" << endl;
    for (int i = 0; i < jumlahData; i++) {
        cin >> nilai;
        insert(nilai);
    }

    cout<< "Total collisions: " << totalCollisions() << endl;

    cout << "Masukkan data yang ingin dicari: ";
    cin >> nilai;

    cout << "\nHash Table:" << endl;
    display();

    return 0;
}

//input data
//50 700 76 85 92 73 101