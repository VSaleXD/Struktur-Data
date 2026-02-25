#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0


typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct {
    Node *front;
    Node *rear;
} Queue;


void init(Queue *q);
int is_empty(Queue *q);
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
        printf("4. Display Queue\n");
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
                if (scanf("%d", &value) != 1) {
                    printf("Invalid input!\n");
                    while (getchar() != '\n');
                    break;
                }
                if (enqueue(&q, value))
                    printf("Value inserted successfully.\n");
                else
                    printf("Queue Overflow! (Memory allocation failed)\n");
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
            case 4: {
                printf("Queue contents: ");
                Node *current = q.front;
                if (!current) {
                    printf("(empty)");
                }
                while (current != NULL) {
                    printf("%d ", current->data);
                    current = current->next;
                }
                printf("\n");
                break;
            }
            default:
                printf("Invalid choice!\n");
        }

        while (getchar() != '\n');

    } while (choice != 3);

    // Free all remaining nodes
    while (q.front != NULL) {
        Node *temp = q.front;
        q.front = q.front->next;
        free(temp);
    }

    return 0;
}

void init(Queue *q)
{
    q->front = NULL;
    q->rear = NULL;
}

int is_empty(Queue *q)
{
    return (q->front == NULL);
}



int enqueue(Queue *q, int x)
{
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return FALSE;
    newNode->data = x;
    newNode->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    return TRUE;
}

int dequeue(Queue *q, int *value)
{
    if (is_empty(q))
        return FALSE;
    Node *temp = q->front;
    *value = temp->data;
    q->front = temp->next;
    if (q->front == NULL)
        q->rear = NULL;
    free(temp);
    return TRUE;
}