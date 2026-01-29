#include <bits/stdc++.h>
using namespace std;

struct Mahasiswa {
    char nama[50];
    int nim;
    float ipk;
};

void print(Mahasiswa mhs[], int n){
    for(int i=0;i<n;i++){
        printf("Data Mahasiswa ke-%d:\n", i+1);
        printf("Nama: %s\n", mhs[i].nama);
        printf("NIM: %d\n", mhs[i].nim);
        printf("IPK: %.2f\n", mhs[i].ipk);
    }
}

int main() {

    Mahasiswa mhs[5];
    strcpy(mhs[0].nama, "John Doe");
    mhs[0].nim = 12345;
    mhs[0].ipk = 3.75f;

    print(mhs, 1);

    vector<Mahasiswa> vecMhs;
    vecMhs.push_back(mhs[0]);

    int idx=1;
    for(int i=0;i<2;i++){
        cin>>mhs[idx].nama>>mhs[idx].nim>>mhs[idx].ipk;
        idx++;
    }

    print(mhs, 3);


    return 0;
}