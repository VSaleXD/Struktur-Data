#include<iostream>
using namespace std;

struct node{
    int data;
    struct node* next;
};

static void reverse(struct node** head_ref){
    struct node* prev = NULL;
    struct node* current = *head_ref;
    struct node* next;
    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head_ref = prev;
}

int main(){
 char tes[20] = "hello world";
    cout<<tes<<endl;
    return 0;
}