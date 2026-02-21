#include <stdio.h>
#include <stdlib.h>

#define STACKSIZE 100
#define TRUE 1
#define FALSE 0

typedef struct {
    int item[STACKSIZE];
    int top;
} Stack;

/* Function Prototypes */
void init(Stack *s);
int is_empty(Stack *s);
int is_full(Stack *s);
int push(Stack *s, int x);
int pop(Stack *s, int *value);
int stack_top(Stack *s, int *value);

int main(void)
{
    Stack s;
    int choice, value;
    char ch;

    init(&s);

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
                if (push(&s, value))
                    printf("Value pushed successfully.\n");
                else
                    printf("Stack Overflow!\n");
                break;
                
            case 2:
                if (pop(&s, &value))
                    printf("Popped value: %d\n", value);
                else
                    printf("Stack Underflow!\n");
                break;

            case 3:
                if (stack_top(&s, &value))
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

void init(Stack *s)
{
    s->top = -1;
}

int is_empty(Stack *s)
{
    return (s->top == -1);
}

int is_full(Stack *s)
{
    return (s->top == STACKSIZE - 1);
}

int push(Stack *s, int x)
{
    if (is_full(s))
        return FALSE;
    
    s->item[++(s->top)] = x;
    return TRUE;
}

int pop(Stack *s, int *value)
{
    if (is_empty(s))
        return FALSE;

    *value = s->item[(s->top)--];
    return TRUE;
}

int stack_top(Stack *s, int *value)
{
    if (is_empty(s))
        return FALSE;
    
        *value = s->item[s->top];
    return TRUE;
}