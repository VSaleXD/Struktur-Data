#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define N 4

struct node {
    int key[N]; // Diperbesar menjadi N untuk menampung overflow sementara sebelum split
    struct node* child[N + 1]; // Diperbesar menjadi N+1 untuk menampung child overflow sementara
    int isleaf; // Menyatakan posisi node pada leaf (1) atau tidak (0)
    int n; // Jumlah key dalam suatu node
    struct node* parent; // Menyatakan node parent
};

// Fungsi pembantu untuk membuat node baru
struct node* createNewNode() {
    struct node* newNode = new struct node;
    newNode->isleaf = 1;
    newNode->n = 0;
    newNode->parent = NULL;
    for (int i = 0; i < N + 1; i++) {
        newNode->child[i] = NULL;
    }
    return newNode;
}

// Fungsi pencarian leaf bawaan yang sudah diperbaiki logic pointer-nya
struct node* searchforleaf(struct node* root, int k) {
    if (!root) return NULL;
    struct node* curr = root;
    while (curr->isleaf == 0) {
        int i = 0;
        while (i < curr->n && k > curr->key[i]) {
            i++;
        }
        curr = curr->child[i];
    }
    return curr;
}

// FUNGSI INSERT BAWAAN LKP YANG SUDAH DIPERBAIKI TOTAL
struct node* insert(struct node* root, int k) {
    if (root) {
        struct node* p = searchforleaf(root, k);
        int e = k;
        struct node* newChildRight = NULL; // Pointer untuk menampung child baru hasil split

        // Loop naik ke atas (ke parent) jika terjadi overflow
        for (; p; p = p->parent) {
            // Kasus 1: Node kosong langung insert tanpa split
            if (p->n == 0) {
                p->key[0] = e;
                p->n = 1;
                return root;
            }

            // Cari posisi insert di node p saat ini
            int i = p->n - 1;
            while (i >= 0 && p->key[i] > e) {
                p->key[i + 1] = p->key[i];
                p->child[i + 2] = p->child[i + 1]; // Geser pointer child
                i--;
            }
            p->key[i + 1] = e;
            p->child[i + 2] = newChildRight; // Pasang child baru di sisi kanan key baru
            if (newChildRight) {
                newChildRight->parent = p;
            }
            p->n++;

            // Kasus 2: Node tidak penuh 
            if (p->n < N) {
                return root;
            }

            // Kasus 3: Node Penuh (p->n == N), Harus di-SPLIT (Mekanisme pembagian 50-50 yang valid)
            struct node* r = createNewNode();
            r->isleaf = p->isleaf;

            int midIndex = N / 2; // Index median tengah (untuk N=4, midIndex = 2)
            int upKey = p->key[midIndex]; // Key yang akan dinaikkan ke parent

            // Pindahkan elemen setengah kanan ke node baru 'r'
            int m = 0;
            for (int j = midIndex + 1; j < N; j++) {
                r->key[m] = p->key[j];
                r->child[m] = p->child[j];
                if (r->child[m]) r->child[m]->parent = r;
                m++;
            }
            r->child[m] = p->child[N]; // Child terakhir
            if (r->child[m]) r->child[m]->parent = r;
            r->n = m;

            // Kurangi ukuran node lama 'p'
            p->n = midIndex;

            // Siapkan variabel untuk loop perulangan ke parent di atasnya
            e = upKey;
            newChildRight = r;

            // Jika yang di-split adalah ROOT, buat root baru (Pohon bertambah tinggi)
            if (p->parent == NULL) {
                struct node* newRoot = createNewNode();
                newRoot->isleaf = 0;
                newRoot->key[0] = upKey;
                newRoot->child[0] = p;
                newRoot->child[1] = r;
                newRoot->n = 1;
                p->parent = newRoot;
                r->parent = newRoot;
                return newRoot; // Root baru resmi menggantikan root lama
            }
        }
    } else {
        // Buat node baru jika Root masih NULL
        struct node* newRoot = createNewNode();
        newRoot->key[0] = k;
        newRoot->n = 1;
        return newRoot;
    }
    return root;
}

// Fungsi rekursif untuk mencetak struktur B-Tree agar mudah dibaca
void printTree(struct node* root, int level = 0) {
    if (root) {
        cout << "Level " << level << ": [ ";
        for (int i = 0; i < root->n; i++) {
            cout << root->key[i] << " ";
        }
        cout << "]\n";
        
        if (!root->isleaf) {
            for (int i = 0; i <= root->n; i++) {
                printTree(root->child[i], level + 1);
            }
        }
    }
}

int main() {
    struct node* root = NULL;

    // NOMOR 5
    int dataAwal[] = {14, 2, 9, 12, 21, 31, 49};     
    for (int x : dataAwal) {
        root = insert(root, x);
    }
    cout << "Original Tree " << endl;
    printTree(root);
    cout << endl;

    cout << "Setelah Menambahkan Elemen 17" << endl;
    root = insert(root, 17);
    printTree(root);

    return 0;
}