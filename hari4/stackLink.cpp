#include <stdio.h>
#include <stdlib.h>

#define STACKSIZE 100
#define TRUE 1
#define FALSE 0

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *top;
} Stack;

int is_empty(Stack *s);
int is_full(Stack *s);
int push(Stack *s, int x);
int pop(Stack *s, int *value);
int stack_top(Stack *s, int *value);

int main(void)
{
    int choice, value;
    Stack stack;
    stack.top = NULL;

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
                if (push(&stack, value))
                    printf("Value pushed successfully.\n");
                else
                    printf("Stack Overflow!\n");
                break;
            case 2:
                if (pop(&stack, &value))
                    printf("Popped value: %d\n", value);
                else
                    printf("Stack Underflow!\n");
                break;
            case 3:
                if (stack_top(&stack, &value))
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

    // Free all remaining nodes
    while (stack.top != NULL) {
        Node* temp = stack.top;
        stack.top = stack.top->next;
        free(temp);
    }

    return 0;
}


int is_empty(Stack *s)
{
    return (s->top == NULL);
}

int is_full(Stack *s)
{
    return FALSE; 
}

int push(Stack *s, int x)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return FALSE;
    newNode->data = x;
    newNode->next = s->top;
    s->top = newNode;
    return TRUE;
}

int pop(Stack *s, int *value)
{
    if (is_empty(s))
        return FALSE;
    Node* temp = s->top;
    *value = temp->data;
    s->top = temp->next;
    free(temp);
    return TRUE;
}

int stack_top(Stack *s, int *value)
{
    if (is_empty(s))
        return FALSE;
    *value = s->top->data;
    return TRUE;
}