#include<bits/stdc++.h>
using namespace std;

int *getValue(){
    int *arr =(int *) malloc(10 * sizeof(int));
    for(int i = 0; i < 10; i++){
        arr[i] = i + 1;
    }
    return arr;
}

vector<int> getValues(){
    vector<int> v;
    for(int i = 0; i < 10; i++){
        v.push_back(i + 1);
    }
    return v;
}

int main(){
    //program 4
    int *array = getValue();
    for(int i = 0; i < 10; i++){
        cout << "*(array + " << i << ") = " << *(array + i) << endl;
    }
    //program 5
    vector<int> get=getValues();
    vector<int>::iterator it;
    for(it = get.begin(); it != get.end(); it++){
        cout << "*it = " << *it << endl;
    }

    //1. Apa risiko penggunaan array dinamis pada PROGRAM 4? 
    //2. Mengapa PROGRAM 5 relatif lebih aman dari kesalahan memori? 
    //3. Dari sisi programmer pemula, pendekatan mana yang lebih mudah dipahami? 
    //4. Dalam proyek besar, pendekatan mana yang lebih mudah dirawat (maintainable)?
}