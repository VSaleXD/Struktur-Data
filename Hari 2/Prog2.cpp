#include<bits/stdc++.h>
using namespace std;

int main(){
    int *dynamicArray = (int*)malloc(5 * sizeof(int));

    for(int i = 0; i < 5; i++){
        dynamicArray[i] = i + 1;
    }
    for(int i = 0; i < 5; i++){
        cout << dynamicArray[i] << " ";
    }

    int newSize = 8;
    dynamicArray = (int*)realloc(dynamicArray, newSize * sizeof(int));
    
    for(int i = 5; i < newSize; i++){
        dynamicArray[i] = i + 1;
    }

    for(int i = 0; i < newSize; i++){
        cout << dynamicArray[i] << " ";
    }

    free(dynamicArray);
}