#include<bits/stdc++.h>
using namespace std;

struct node {
    int key;
    node *left;
    node *right;
    int height;
};

class AVL {
    public:
    node *root;
    node* insert(node* root, int key);
    node* rightRotate(node* y);
    node* leftRotate(node* x);
    int getBalance(node* N);
    int height(node* N);


    void inOrder(node* root){
        if(root != nullptr){
            inOrder(root->left);
            cout << root->key << " ";
            inOrder(root->right);
    };
    void postOrder(node* root);
        if(root != nullptr){
            postOrder(root->left);
            postOrder(root->right);
            cout << root->key << " ";
        }
    void preOrder(node* root);
    AVL() {
        root = nullptr;
    }
    void printPreOrder() {
        preOrder(root);
    }
};

int main(){
    AVL tree;
    tree.insert(tree.root, 10);
    tree.insert(tree.root, 20);
    tree.printPreOrder();
}