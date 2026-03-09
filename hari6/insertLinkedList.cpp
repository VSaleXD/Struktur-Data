#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

long long compLL = 0;

Node* createNode(int data) {
    Node* newNode = new Node;
    
    newNode->data = data;
    newNode->next = nullptr;

    return newNode;
}

Node* insertLast(Node* head, int data) {
    Node* newNode = createNode(data);

    if (head == nullptr)
        return newNode;
    
    Node* temp = head;
    while (temp->next != nullptr)
        temp = temp->next;  
    
    temp->next = newNode;

    return head;
}

void printList(Node* head) {
    Node* temp = head;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

Node* insertionSortList(Node* head) {
    Node* sorted = nullptr;

    while (head != nullptr) {
        Node* current = head;
        head = head->next;

        if (sorted == nullptr || sorted->data >= current->data) {
            compLL++;
            current->next = sorted;
            sorted = current;
        } else {
            Node* temp = sorted;
            while (temp->next != nullptr && temp->next->data < current->data) {
                compLL++;
                temp = temp->next;
            }

            current->next = temp->next;
            temp->next = current;
        }
    }

    return sorted;
}
int main() {
    Node* head = nullptr;
    int n, x;

    cout << "Masukkan jumlah data: ";
    cin >> n;

    cout << "Masukkan data:\n";
        for (int i = 0; i < n; i++) {
        cin >> x;
        head = insertLast(head, x);
    }
    
    cout << "Sebelum sorting:\n";
    printList(head);

    head = insertionSortList(head);

    cout << "Setelah sorting:\n";
    printList(head);

    cout << "Jumlah perbandingan: " << compLL << endl;
    
    return 0;
}