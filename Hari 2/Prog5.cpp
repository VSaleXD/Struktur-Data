#include<bits/stdc++.h>
using namespace std;

vector<int> getValues(){
    vector<int> v;
    for(int i = 0; i < 10; i++){
        v.push_back(i + 1);
    }
    return v;
}

int main(){
    vector<int> get=getValues();

    while(!get.empty()){
        get.pop_back();
    };
    get.push_back(100);
    vector<int>::iterator it;
    for(it = get.begin(); it != get.end(); it++){
        cout << "*it = " << *it << endl;
    }
}