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

Status S_Push(SqStack &S, SElemType e)
{
    if (S.top - S.base == S.stacksize)
        return ERROR;
    *S.top++ = e;
    return OK;
}

Status S_Pop(SqStack &S, SElemType &e)
{
    if (S.top == S.base)
        return ERROR;
    e = *--S.top;
    return OK;
}

bool S_isEmpty(SqStack S)
{
    if (S.top == S.base)
        return true;
    else
        return false;
}

Status Q_En(SqStack &S1, SqStack &S2, SElemType x)
{
    if (S1.top - S1.base < S1.stacksize)  // 若栈S1未满，将入队元素入栈S1
        S_Push(S1, x);
    else if (S1.top - S1.base == S1.stacksize && S_isEmpty(S2))  // 若栈S1满，S2空，将S1元素出栈并入栈S2之后，入队元素可入栈S1
    {
        while (!S_isEmpty(S1))
        {
            S_Pop(S1, x);
            S_Push(S2, x);
        }
        S_Push(S1, x);
    }
    else  // 其余情况下无法入队
        return ERROR;
    return OK;
}

Status Q_De(SqStack &S1, SqStack &S2, SElemType x)
{
    if (!S_isEmpty(S2))  // 如果栈S2非空，直接取出栈S2的栈顶元素即可
        S_Pop(S2, x);
    else if (S_isEmpty(S1))  // 若栈S1，S2空，即队列为空
    {
        cout << "The queue is empty." << endl;
        return ERROR;
    } 
    else  // 若S2为空，S1不为空，则将S1元素出栈并入栈S2后，取S2栈顶元素
    {
        while (!S_isEmpty(S1))
        {
            S_Pop(S1, x);
            S_Push(S2, x);
        }
        S_Pop(S2, x);
    }
    return OK;
}

bool Q_isEmpty(SqStack &S1, SqStack &S2)
{
    if (S_isEmpty(S1) && S_isEmpty(S2))  // 两栈同时为空表示队列为空
        return true;
    else
        return false;
}

int main()
{

    system("pause");
    return 0;
}
