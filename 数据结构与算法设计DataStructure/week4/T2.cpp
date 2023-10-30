#include <iostream>
#include <cstdio>

using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

typedef int Status;

typedef int QElemType;

typedef struct QNode
{
    QElemType data;
    struct QNode *next;
} QNode, *QueuePtr;

typedef struct
{
    QueuePtr front;
    QueuePtr rear;
} LinkQueue;

Status InitQueue(LinkQueue &Q)
{
    Q.front = Q.rear = (QueuePtr)malloc(sizeof(QNode));
    if (!Q.front)
        exit(OVERFLOW);
    Q.front->next = NULL;
    return OK;
}

Status QueueEmpty(LinkQueue Q)
{
    return (Q.front == Q.rear);
}

Status GetHead(LinkQueue Q, QElemType &e)
{
    if (Q.front == Q.rear)
        return ERROR;
    e = Q.front->next->data;
    return OK;
}

Status EnQueue(LinkQueue &Q, QElemType e)
{
    QNode *p;
    p = (QueuePtr)malloc(sizeof(QNode));
    if (!p)
        exit(OVERFLOW);
    p->data = e;
    p->next = NULL;
    Q.rear->next = p;
    Q.rear = p;
    return OK;
}

Status DeQueue(LinkQueue &Q, QElemType &e)
{
    if (Q.front == Q.rear)
        return ERROR;
    QNode *p;
    p = Q.front->next;
    e = p->data;
    Q.front->next = p->next;
    if (Q.rear == p)
        Q.rear = Q.front;
    free(p);
    return OK;
}

int main()
{
    int n;
    cin >> n;

    LinkQueue Q_odd, Q_even;
    InitQueue(Q_odd);
    InitQueue(Q_even);

    int input[n];
    for (int i = 0; i < n; i++)
        cin >> input[i];
    for (int i = 0; i < n; i++)
    {
        if (input[i] % 2 == 0)
            EnQueue(Q_even, input[i]);
        else if (input[i] % 2 == 1)
            EnQueue(Q_odd, input[i]);
    }
    for (int i = 0; i < n / 2; i++)
    {
        if (QueueEmpty(Q_even) || QueueEmpty(Q_odd))
            break;
        int temp1, temp2;
        DeQueue(Q_even, temp2);
        DeQueue(Q_odd, temp1);
        cout << temp1 << " " << temp2 << endl;
    }

    system("pause");
    return 0;
}