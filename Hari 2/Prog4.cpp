#include<bits/stdc++.h>
using namespace std;

int *getValues(){
    int *arr =(int *) malloc(10 * sizeof(int));
    for(int i = 0; i < 10; i++){
        arr[i] = i + 1;
    }
    return arr;
}

int main(){
    int *array = getValues();
    for(int i = 0; i < 10; i++){
        cout << "*(array + " << i << ") = " << *(array + i) << endl;
    }
}