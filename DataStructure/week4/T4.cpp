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
typedef int SElemType;
typedef int QElemType;

typedef struct
{
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;

Status InitStack(SqStack &S)
{
    S.base = new SElemType[MAXSIZE];
    if (!S.base)
        return OVERFLOW;
    S.top = S.base;
    S.stacksize = MAXSIZE;
    return OK;
}

Status Push(SqStack &S, char e)
{
    if (S.top - S.base == S.stacksize)
        return ERROR;
    *S.top++ = e;
    return OK;
}

Status Pop_char(SqStack &S, char &e)
{
    if (S.top == S.base)
        return ERROR;
    e = *--S.top;
    return OK;
}

Status Pop(SqStack &S, SElemType &e)
{
    if (S.top == S.base)
        return ERROR;
    e = *--S.top;
    return OK;
}

Status GetTop(SqStack S, SElemType &e)
{
    if (S.top == S.base)
        return ERROR;
    e = *(S.top - 1);
    return OK;
}

Status GetTop_char(SqStack S, char &e)
{
    if (S.top == S.base)
        return ERROR;
    e = *(S.top - 1);
    return OK;
}

bool StackEmpty(SqStack S)
{
    if (S.top == S.base)
        return true;
    else
        return false;
}

int StackLength(SqStack S)
{
    return S.top - S.base;
}

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

Status EnQueue(LinkQueue &Q, QElemType &e)
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

int QueueLength(LinkQueue &Q)
{
    return Q.rear - Q.front;
}

int main()
{

    int n;
    cin >> n;
    int input[n];
    LinkQueue Q1, Q2, Q3;
    InitQueue(Q1);
    InitQueue(Q2);
    InitQueue(Q3);
    for (int i = 0; i < n; i++)
    {
        cin >> input[i];
        if (input[i] < 60)
            EnQueue(Q1, input[i]);
        else if (input[i] < 100 && input[i] >= 60)
            EnQueue(Q2, input[i]);
        else if (input[i] >= 100)
            EnQueue(Q3, input[i]);
    }

    cout << "60>x:";
    while (!QueueEmpty(Q1))
    {
        int temp;
        DeQueue(Q1, temp);
        cout << temp << ' ';
    }
    cout << endl;

    cout << "60<=x<100:";
    while (!QueueEmpty(Q2))
    {
        int temp;
        DeQueue(Q2, temp);
        cout << temp << ' ';
    }
    cout << endl;

    cout << "x>=100:";
    while (!QueueEmpty(Q3))
    {
        int temp;
        DeQueue(Q3, temp);
        cout << temp << ' ';
    }
    cout << endl;

    system("pause");
    return 0;
}