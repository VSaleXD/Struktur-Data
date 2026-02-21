#include<bits/stdc++.h>
using namespace std;

struct node {
    int data;
    node* next;
    node* prev;
};
node* tail = nullptr;

void insentAtEnd(node* &head, int newData) {
    node* newNode = new node();
    newNode->data = newData;
    newNode->next = nullptr;

    // Jika linked list kosong, membuat node baru menjadi head dan tail
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }
    else {
        tail->next = newNode;
        tail = newNode;
    }
}


//double linked list
void insentAtEnd(node* &head, int newData) {
    node* newNode = new node();
    newNode->data = newData;
    newNode->next = nullptr;
    newNode->prev = nullptr;

    // Jika linked list kosong, membuat node baru menjadi head dan tail
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }

    tail->next = newNode;
    newNode->prev = tail;
    tail = newNode;
}

//circular linked list
void insentAtEnd(node* &head, int newData) {
    node* newNode = new node();
    newNode->data = newData;

    // Jika linked list kosong, membuat node baru menjadi head dan tail
    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        newNode->next = head; // Menghubungkan ke diri sendiri 
        return;
    }

    tail->next = newNode;
    newNode->next = head; 
    tail = newNode;
}


int main(){
    node* head = nullptr;
    node* tail = nullptr;

    insentAtEnd(head, 10);
    insentAtEnd(head, 20);
    insentAtEnd(head, 30);
    return 0;
}