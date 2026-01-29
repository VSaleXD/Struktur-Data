#include <bits/stdc++.h>
using namespace std;

struct Mahasiswa {
    char nama[50];
    int nim;
    float ipk;
};

void cetak(Mahasiswa mhs[], int n){
    for(int i=0;i<n;i++){
        printf("Data Mahasiswa ke-%d:\n", i+1);
        printf("Nama: %s\n", mhs[i].nama);
        printf("NIM: %d\n", mhs[i].nim);
        printf("IPK: %.2f\n", mhs[i].ipk);
    }
}

void cari(Mahasiswa mhs[], int n, int nimCari){
    for(int i=0;i<n;i++){
        if(mhs[i].nim == nimCari){
            printf("Data Mahasiswa ditemukan:\n");
            cetak(&mhs[i], 1);
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

    cetak(mhs, 1);

    vector<Mahasiswa> vecMhs;
    vecMhs.push_back(mhs[0]);

    int idx=1;
    for(int i=1;i<3;i++){
        cin>>mhs[idx].nama>>mhs[idx].nim>>mhs[idx].ipk;
        idx++;
    }

    cari(mhs, idx, 23456);
    cari(mhs, idx, 34567);

    return 0;
}