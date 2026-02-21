#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> v={1,5,23,90,15,35};
    make_heap(v.begin(), v.end());
    cout << is_heap(v.begin(), v.begin()+3);
    return 0;
}