#include <iostream>
#include <vector>
using namespace std;

long long compIS = 0, shiftIS = 0;
long long compSS = 0, swapSS = 0;

void printArray(const vector<int>& arr) {
    for (int x : arr)
        cout << x << " ";
    cout << endl;
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0) {
            compIS++;
            if (arr[j] > key) {
                arr[j + 1] = arr[j];
                shiftIS++;
                j--;
            } else {
                break;
            }
        }
        arr[j + 1] = key;
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        
        for (int j = i + 1; j < n; j++) {
            compSS++;
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
            swapSS++;
        }
    }
}

int main() {
    int n;
    cout << "Masukkan jumlah data: ";
    cin >> n;

    vector<int> arr1(n), arr2(n);

    cout << "Masukkan data:\n";
    for (int i = 0; i < n; i++) {
        cin >> arr1[i];
        arr2[i] = arr1[i]; // copy untuk selection sort
    }


    insertionSort(arr1);
    selectionSort(arr2);

    cout << "\nHasil Insertion Sort:\n";
    printArray(arr1);
    cout << "Perbandingan: " << compIS << endl;
    cout << "Pergeseran: " << shiftIS << endl;
    cout << "\nHasil Selection Sort:\n";
    printArray(arr2);
    cout << "Perbandingan: " << compSS << endl;
    cout << "Swap: " << swapSS << endl;
    
    return 0;
}