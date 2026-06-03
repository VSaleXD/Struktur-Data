#include<bits/stdc++.h>
using namespace std;

class binaryTree{
    char tree[10];
    public:
    int root(char key){
        if(tree[0] != '\0')
            cout<<"Tree already had root"<<endl;
        else
            tree[0] = key;
        return 0;
    }
    int set_left(char key, int parent){
        if(tree[parent] == '\0'){
            cout << "\nCan't set child at index " << (parent * 2) + 1 << " , no parent found" << endl;
        }else{
            tree[(parent * 2) + 1] = key;
        }
        return 0;
    }
    int set_right(char key, int parent){
        if(tree[parent] == '\0'){
            cout << "\nCan't set child at index " << (parent * 2) + 2 << " , no parent found" << endl;
        }else{
            tree[(parent * 2) + 2] = key;
        }
        return 0;
    }

    int print_tree(){
        cout << endl;
        for(int i = 0; i < 10; i++){
            if(tree[i] != '\0')
                cout << tree[i];
            else
                cout << "-";
        }
        return 0;
    }
}; 

int main(){
    binaryTree tree;
    tree.root('A');
    tree.set_left('B', 0);
    tree.set_right('C', 0);
    tree.set_left('D', 1);
    tree.set_right('E', 1);
    tree.set_left('F', 2);
    tree.print_tree();
}
