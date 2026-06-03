#include <iostream>
#include <string>

using namespace std;


struct Node {
    int data;
    Node* next;
    Node* prev;

    Node(int val) {
        data = val;
        next = nullptr;
        prev = nullptr;
    }
};

class MyDeque {
private:
    Node* head; 
    Node* tail;

public:
    MyDeque() {
        head = nullptr;
        tail = nullptr;
    }

    void push_front(int val) {
        Node* newNode = new Node(val);
        if (head == nullptr) { 
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void push_back(int val) {
        Node* newNode = new Node(val);
        if (tail == nullptr) { \
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    void pop_front() {
        if (head == nullptr) return; 
        
        Node* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp; 
    }

    void pop_back() {
        if (tail == nullptr) return;

        Node* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        } else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
    }

    void display() {
        Node* curr = head;
        while (curr != nullptr) {
            cout << curr->data << "\n";
            curr = curr->next;
        }
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    cin >> N;

    MyDeque dq;
    string cmd;
    int val;

    for (int i = 0; i < N; i++) {
        cin >> cmd;
        if (cmd == "push_front") {
            cin >> val;
            dq.push_front(val);
        } else if (cmd == "push_back") {
            cin >> val;
            dq.push_back(val);
        } else if (cmd == "pop_front") {
            dq.pop_front();
        } else if (cmd == "pop_back") {
            dq.pop_back();
        }
    }

    dq.display();

    return 0;
}