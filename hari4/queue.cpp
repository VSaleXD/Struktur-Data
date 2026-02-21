#include <stdio.h>
#include <stdlib.h>

#define MAXQUEUE 5
#define TRUE 1
#define FALSE 0

typedef struct {
    int item[MAXQUEUE];
    int front;
    int rear;
} Queue;

/* Prototypes */
void init(Queue *q);
int is_empty(Queue *q);
int is_full(Queue *q);
int enqueue(Queue *q, int x);
int dequeue(Queue *q, int *value);

int main(void)
{
    Queue q;
    int choice, value;

    init(&q);

    do {
        printf("\n===== QUEUE MENU =====\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Exit\n");
        printf("======================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                if (enqueue(&q, value))
                    printf("Value inserted successfully.\n");
                else
                    printf("Queue Overflow!\n");
                break;

            case 2:
                if (dequeue(&q, &value))
                    printf("Removed value: %d\n", value);
                else
                    printf("Queue Underflow!\n");
                break;

            case 3:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }

        while (getchar() != '\n');

    } while (choice != 3);

    return 0;
}

void init(Queue *q)
{
    q->front = 0;
    q->rear = -1;
}

int is_empty(Queue *q)
{
    return (q->front > q->rear);
    // return (q->rear - q->front + 1 == 0);
}

int is_full(Queue *q)
{
    return (q->rear == MAXQUEUE - 1);
}

int enqueue(Queue *q, int x)
{
    if (is_full(q))
        return FALSE;
    
    q->item[++(q->rear)] = x;
    return TRUE;
}

int dequeue(Queue *q, int *value)
{
    if (is_empty(q))
        return FALSE;

    *value = q->item[(q->front)++];
    return TRUE;
}