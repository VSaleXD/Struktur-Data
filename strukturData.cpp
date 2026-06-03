#include<bits/stdc++.h>
using namespace std;   

struct node{
    int data;
    node* next;
    node* prev;

    node(int x){
        data = x;
        next = NULL;
        prev = NULL;
    }};

class myQueue{
    node* head;
    node* tail;
    int size;

    public:
    myQueue(){
        head = NULL;
        tail = NULL;
        size = 0;
    }

    void push_back(int x){
        node* newNode = new node(x);
        if(size == 0){
            head = newNode;
            tail = newNode;
        }
        else{
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void push_front(int x){
        node* newNode = new node(x);
        if(size == 0){
            head = newNode;
            tail = newNode;
        }
        else{
            head->prev = newNode;
            newNode->next = head;
            head = newNode;
        }
        size++;
    }

    void pop_back(){
        if(size == 0){
            cout<<"Deque is empty"<<endl;
            return;
        }
        node* temp = tail;
        tail = tail->prev;
        if(tail != NULL){
            tail->next = NULL;
        }
        else{
            head = NULL;
        }
        delete temp;
        size--;
    }
    void pop_front(){
        if(size == 0){
            cout<<"Deque is empty"<<endl;
            return;
        }
        node* temp = head;
        head = head->next;
        if(head != NULL){
            head->prev = NULL;
        }
        else{
            tail = NULL;
        }
        delete temp;
        size--;
    }
    void display(){
        node* temp = head;
        while(temp != NULL){
            cout<<temp->data<<" ";
            temp = temp->next;
        }
        cout<<endl;
    }
};

class myStack{
    node* top;
    int size;

    public:
    myStack(){
        top = NULL;
        size = 0;
    }

    void push(int x){
        node* newNode = new node(x);
        if(size == 0){
            top = newNode;
        }
        else{
            newNode->next = top;
            top->prev = newNode;
            top = newNode;
        }
        size++;
    }

    void pop(){
        if(size == 0){
            cout<<"Stack is empty"<<endl;
            return;
        }
        node* temp = top;
        top = top->next;
        if(top != NULL){
            top->prev = NULL;
        }
        delete temp;
        size--;
    }

    void display(){
        node* temp = top;
        while(temp != NULL){
            cout<<temp->data<<" ";
            temp = temp->next;
        }
        cout<<endl;
    }
};

class mySort{
    public:
    void bubbleSort(int arr[], int n){
        for(int i=0; i<n-1; i++){
            for(int j=0; j<n-i-1; j++){
                if(arr[j] > arr[j+1]){
                    swap(arr[j], arr[j+1]);
                }
            }
        }
    }

    void selectionSort(int arr[], int n){
        for(int i=0; i<n-1; i++){
            int minIndex = i;
            for(int j=i+1; j<n; j++){
                if(arr[j] < arr[minIndex]){
                    minIndex = j;
                }
            }
            swap(arr[i], arr[minIndex]);
        }
    }

    void insertionSort(int arr[], int n){
        for(int i=1; i<n; i++){
            int key = arr[i];
            int j = i-1;
            while(j >= 0 && arr[j] > key){
                arr[j+1] = arr[j];
                j--;
            }
            arr[j+1] = key;
        }
    }

    void radixSort(int arr[], int n){
        int max = *max_element(arr, arr+n);
        for(int exp = 1; max/exp > 0; exp *= 10){
            countingSort(arr, n, exp);
        }
    }

    void countingSort(int arr[], int n, int exp){
        int output[n];
        int count[10] = {0};
        for(int i=0; i<n; i++){
            count[(arr[i]/exp)%10]++;
        }
        for(int i=1; i<10; i++){
            count[i] += count[i-1];
        }
        for(int i=n-1; i>=0; i--){
            output[count[(arr[i]/exp)%10]-1] = arr[i];
            count[(arr[i]/exp)%10]--;
        }
        for(int i=0; i<n; i++){
            arr[i] = output[i];
        }
    }

    void mergeSort(int arr[], int l, int r){
        if(l < r){
            int m = l + (r-l)/2;
            mergeSort(arr, l, m);
            mergeSort(arr, m+1, r);
            merge(arr, l, m, r);
        }
    }

    void merge(int arr[], int l, int m, int r){
        int n1 = m - l + 1;
        int n2 = r - m;
        int L[n1], R[n2];
        for(int i=0; i<n1; i++){
            L[i] = arr[l+i];
        }
        for(int j=0; j<n2; j++){
            R[j] = arr[m+1+j];
        }
        int i=0, j=0, k=l;
        while(i < n1 && j < n2){
            if(L[i] <= R[j]){
                arr[k] = L[i];
                i++;
            }
            else{
                arr[k] = R[j];
                j++;
            }
            k++;
        }
        while(i < n1){
            arr[k] = L[i];
            i++;
            k++;
        }
        while(j < n2){
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    int partition(int arr[], int low, int high){
        int pivot = arr[high];
        int i = low - 1;
        for(int j = low; j < high; j++){
            if(arr[j] < pivot){
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i+1], arr[high]);
        return i+1;
    }

    void quickSort(int arr[], int low, int high){
        if(low < high){
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi-1);
            quickSort(arr, pi+1, high);
        }
    }

    void display(int arr[], int n){
        for(int i=0; i<n; i++){
            cout<<arr[i]<<" ";
        }
        cout<<endl;
    }
};

class myLinkedList{
    node* head;
    int size;

    public:
    myLinkedList(){
        head = NULL;
        size = 0;
    }

    void insert(int x){
        node* newNode = new node(x);
        if(size == 0){
            head = newNode;
        }
        else{
            node* temp = head;
            while(temp->next != NULL){
                temp = temp->next;
            }
            temp->next = newNode;
            newNode->prev = temp;
        }
        size++;
    }

    void display(){
        node* temp = head;
        while(temp != NULL){
            cout<<temp->data<<" ";
            temp = temp->next;
        }
        cout<<endl;
    }
};

// Node untuk chaining hash table
struct ChainNode {
    int key;
    ChainNode* next;
    ChainNode(int k) : key(k), next(NULL) {}
};
// Hash Table dengan Linear Probing
#define TABLE_SIZE 10
#define EMPTY -1
class MyhashTableProb{
    int* hashTable;
public:
    MyhashTableProb(){
        hashTable = new int[TABLE_SIZE];
        for(int i=0; i<TABLE_SIZE; i++) hashTable[i] = EMPTY;
    }
    int hashFunction(int key) { return key % TABLE_SIZE; }
    bool insert(int key) {
        int index = hashFunction(key);
        int startIndex = index;
        while(hashTable[index] != EMPTY) {
            index = (index + 1) % TABLE_SIZE;
            if(index == startIndex) return false; // penuh
        }
        hashTable[index] = key;
        return true;
    }
    void display() {
        for(int i=0; i<TABLE_SIZE; i++) {
            if(hashTable[i] == EMPTY) cout << i << " -> kosong" << endl;
            else cout << i << " -> " << hashTable[i] << endl;
        }
    }
};

// Hash Table dengan Chaining
class MyHashTableChain{
    ChainNode** hashTable;
public:
    MyHashTableChain(){
        hashTable = new ChainNode*[TABLE_SIZE];
        for(int i=0; i<TABLE_SIZE; i++) hashTable[i] = NULL;
    }
    int hashFunction(int key) { return key % TABLE_SIZE; }
    void insert(int key) {
        int idx = hashFunction(key);
        ChainNode* n = new ChainNode(key);
        n->next = hashTable[idx];
        hashTable[idx] = n;
    }
    void display() {
        for(int i=0; i<TABLE_SIZE; i++) {
            cout << i << " -> ";
            ChainNode* temp = hashTable[i];
            while(temp) {
                cout << temp->key << " -> ";
                temp = temp->next;
            }
            cout << "NULL" << endl;
        }
    }
    int totalCollisions() {
        int collisions = 0;
        for(int i=0; i<TABLE_SIZE; i++) {
            int count = 0;
            ChainNode* temp = hashTable[i];
            while(temp) {
                count++;
                temp = temp->next;
            }
            if(count > 1) collisions += (count-1);
        }
        return collisions;
    }
};

class CircularQueue{
    int* arr;
    int front;
    int rear;
    int capacity;

    public:
    CircularQueue(int c){
        arr = new int[c];
        capacity = c;
        front = 0;
        rear = -1;
    }

    void enqueue(int x){
        if((rear + 1) % capacity == front){
            cout<<"Queue is full"<<endl;
            return;
        }
        rear = (rear + 1) % capacity;
        arr[rear] = x;
    }

    void dequeue(){
        if(front == (rear + 1) % capacity){
            cout<<"Queue is empty"<<endl;
            return;
        }
        front = (front + 1) % capacity;
    }

    void display(){
        if(front == (rear + 1) % capacity){
            cout<<"Queue is empty"<<endl;
            return;
        }
        int i = front;
        while(i != rear){
            cout<<arr[i]<<" ";
            i = (i + 1) % capacity;
        }
        cout<<arr[rear]<<endl;
    }
};

int main(){
    myQueue q;
    q.push_back(1);
    q.push_back(2);
    q.push_front(0);
    q.display();
    q.pop_back();
    q.display();
    q.pop_front();
    q.display();

    myStack s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.display();
    s.pop();
    s.display();

    mySort sort;
    int arr[] = {5, 2, 9, 1, 5, 6};
    int n = sizeof(arr)/sizeof(arr[0]);
    sort.bubbleSort(arr, n);
    sort.display(arr, n);

    int arr2[] = {5, 2, 9, 1, 5, 6};
    sort.selectionSort(arr2, n);
    sort.display(arr2, n);

    int arr3[] = {5, 2, 9, 1, 5, 6};
    sort.insertionSort(arr3, n);
    sort.display(arr3, n);

    int arr4[] = {5, 2, 9, 1, 5, 6};
    sort.radixSort(arr4, n);
    sort.display(arr4, n);

    int arr5[] = {5, 2, 9, 1, 5, 6, 3, 4, 8, 7};
    n=sizeof(arr5)/sizeof(arr5[0]);
    sort.mergeSort(arr5, 0, n-1);
    sort.display(arr5, n);


    int arr6[] = {5, 2, 9, 1, 5, 6, 3, 4, 8, 7};
    n=sizeof(arr6)/sizeof(arr6[0]);
    sort.quickSort(arr6, 0, n-1);
    sort.display(arr6, n);
    
    CircularQueue cq(5);
    cq.enqueue(10);
    cq.enqueue(20);
    cq.enqueue(30);
    cq.display();
    cq.dequeue();
    cq.display();

    MyhashTableProb ht;
    ht.insert(1);
    ht.insert(11);
    ht.insert(21);
    ht.display();
    
    MyHashTableChain htChain;
    htChain.insert(1);
    htChain.insert(11);
    htChain.insert(21);
    htChain.display();


    return 0;
}