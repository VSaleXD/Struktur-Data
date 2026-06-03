#include <bits/stdc++.h>
using namespace std;

#define TRUE 1
#define FALSE 0

typedef struct{
    vector<int> item;
    int front;
    int rear;
} Queue;

void init(Queue *q)
{
    q->front = 0;
    q->rear = -1;
}

int is_empty(Queue *q)
{
    return (q->front > q->rear);
}

int is_full(Queue *q)
{
    return (q->rear == (int)q->item.size() - 1);
}

int enqueue(Queue *q, int x)
{
    if (is_full(q))
        return FALSE;
    
    q->item.push_back(x);
    q->rear++;
    return TRUE;
}

int dequeue(Queue *q, int *value)
{
    if (is_empty(q))
        return FALSE;

    *value = q->item[(q->front)++];
    return TRUE;
}

int main(void)
{
    Queue q;
    init(&q);
    
    int x,y;
    int n;
    cin >> n;
    while(n--){
        string perintah;
        cin >> perintah;
        if(perintah == "add"){
            cin >> x >> y;
            for(int i = 0; i < y; i++){
                enqueue(&q, x);
            }
            cout << q.size() << "\n";
        }
        if(perintah == "del"){
            cin >> x;
            for(int i = 0; i < x; i++){
                if(!dequeue(&q, &y)){
                    cout << "empty\n";
                    break;
                }
            }
        }
        if(perintah == "rev"){
            reverse(q.item.begin() + q.front, q.item.begin() + q.rear + 1);
        }
    }

    return 0;
}

