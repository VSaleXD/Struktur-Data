#include<bits/stdc++.h>
using namespace std;

int main(){
    int n,i;
    int *a, *b;
    cin>>n;

    a = (int*) malloc(n*sizeof(int));
    b = (int*) malloc(n*sizeof(int));

    // for(i=0;i<n;i++){
    //     a[i] = rand()%10;
    //     b[n-i-1] = a[i];
    // }

    int *helpA = a;
    int *helpB = b + n - 1;
    for(i=0;i<n;i++){
        *helpA = rand()%10;
        *helpB = *helpA;
        helpA++;
        helpB--;
    }

    helpA = a;
    helpB = b;

    for(i=0;i<n;i++){
        cout<<helpA[i]<<" ";
    }
    cout<<endl;
    for(i=0;i<n;i++){
        cout<<helpB[i]<<" ";
    }

    free(a);
    free(b);
}