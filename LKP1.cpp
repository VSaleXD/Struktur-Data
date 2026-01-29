#include <bits/stdc++.h>
using namespace std;

struct Mahasiswa {
    char nama[50];
    int nim;
    float ipk;
};

void cetak(Mahasiswa mhs[], int n){
    printf("Nama: %s\n", mhs[n].nama);
    printf("NIM: %d\n", mhs[n].nim);
    printf("IPK: %.2f\n", mhs[n].ipk);
}

void cari(Mahasiswa mhs[], int n, int nimCari){
    for(int i=0;i<n;i++){
        if(mhs[i].nim == nimCari){
            printf("Data Mahasiswa ditemukan:\n");
            cetak(mhs, i);
            return;
        }
    }
    printf("Data Mahasiswa dengan NIM %d tidak ditemukan.\n", nimCari);
}

int main() {

    Mahasiswa mhs[5];
    strcpy(mhs[0].nama, "John Doe");
    mhs[0].nim = 12345;
    mhs[0].ipk = 3.75f;

    cetak(mhs, 0);

    vector<Mahasiswa> vecMhs;
    vecMhs.push_back(mhs[0]);

    int idx=1;

    printf("Masukkan data 2 mahasiswa baru (nama nim ipk):\n");
    for(int i=1;i<3;i++){
        cin>>mhs[idx].nama>>mhs[idx].nim>>mhs[idx].ipk;
        idx++;
    }

    printf("Pencarian data mahasiswa berdasarkan NIM:\n");
    int nimCari;
    for(int i=0;i<2;i++){
        cin>>nimCari;
        cari(mhs, idx, nimCari);
    }

    return 0;
}