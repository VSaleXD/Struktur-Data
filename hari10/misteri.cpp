#include<bits/stdc++.h>
using namespace std;

void fun1(int arr[], int n, int i){
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    if(left < n && arr[left] > arr[largest])
        largest = left;
    if(right < n && arr[right] > arr[largest])
        largest = right;
    if(largest != i){
        swap(arr[i], arr[largest]);
        fun1(arr, n, largest);
    }
}

void fun2(int arr[], int n){
    int startIdx = (n / 2) - 1;
    for(int i = startIdx; i >= 0; i--)
    fun1(arr, n, i);
}

void fun3(int arr[], int &n){
    int lastElement = arr[n - 1];
    arr[0] = lastElement;
    n = n - 1;
    fun1(arr, n, 0);
}

void printArray(int arr[], int n){
    for(int i = 0; i < n; ++i)
        cout << arr[i] << " ";
    cout << endl;
}

int main(){
    int arr[]= { 2, 4, 5, 1, 6, 10, 13, 17, 15, 8, 9 };
    int n = sizeof(arr) / sizeof(arr[0]);
    // fun1(arr, n, 0);
    // printArray(arr, n);
    // fun2(arr, n);
    // printArray(arr, n);

    // int arr2[] = {10, 5, 3, 6, 2, 4, 17 };
    // n = sizeof(arr2) / sizeof(arr2[0]);
    // fun3(arr2, n);
    // printArray(arr2, n);

    int arr3[] = {20,16,11, 2, 4, 5, 1, 6, 10, 13};
    n = sizeof(arr3) / sizeof(arr3[0]);
    cout << n << endl;
    fun2(arr3, n);
    printArray(arr3, n);
    fun3(arr3, n);
    printArray(arr3, n);
    return 0;
}