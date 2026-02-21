#include <stdio.h>
#include <stdlib.h>

#define STACKSIZE 100
#define TRUE 1
#define FALSE 0


typedef struct Node {
    int item;
    int data;
    struct Node *next;
} Node;

/* Function Prototypes */
void init(Node *s);
int is_empty(Node *s);
int is_full(Node *s);
int push(Node *s, int x);
int pop(Node *s, int *value);
int stack_top(Node *s, int *value);

int main(void)
{
    int choice, value;
    char ch;
    Node* head = nullptr;


    init(head);

    do {
        printf("\n===== STACK MENU =====\n");
        printf("1. Push\n");
        printf("2. Pop\n");
        printf("3. Stack Top\n");
        printf("4. Exit\n");
        printf("======================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n'); // clear buffer
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                if (push(head, value))
                    printf("Value pushed successfully.\n");
                else
                    printf("Stack Overflow!\n");
                break;
                
            case 2:
                if (pop(head, &value))
                    printf("Popped value: %d\n", value);
                else
                    printf("Stack Underflow!\n");
                break;

            case 3:
                if (stack_top(head, &value))
                    printf("Top value: %d\n", value);
                else
                    printf("Stack is empty.\n");
                break;

            case 4:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

        while (getchar() != '\n'); // clear buffer

    } while (choice != 4);

    return 0;
}



void insentAtEnd(Node* &head, int newData) {
    Node* newNode = new Node();
    newNode->data = newData;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;

        return;
    }
    else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void init(Node *s)
{
    s = nullptr;
}

int is_empty(Node *s)
{
    return (s == nullptr);
}

int is_full(Node *s)
{
    return FALSE; // Linked list stacks are not full in the traditional sense
}

int push(Node *s, int x)
{
    Node* newNode = new Node();
    newNode->data = x;
    newNode->next = s;
    s = newNode;

    return TRUE;
}

int pop(Node *s, int *value)
{
    if (is_empty(s))
        return FALSE;

    *value = s->data;
    Node* temp = s;
    s = s->next;
    delete temp;

    return TRUE;
}

int stack_top(Node *s, int *value)
{
    if (is_empty(s))
        return FALSE;
    
        *value = s->data;
    return TRUE;
}