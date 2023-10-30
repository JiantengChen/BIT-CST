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

int main()
{
    SqStack S;

    InitStack(S);

    char input[MAXSIZE];
    cin >> input;

    for (int i = 0; i < MAXSIZE; i++)
    {
        if (input[i] == '\0' || input[i] == '\n')
            break;
        Push(S, input[i]);
    }
    int l = StackLength(S);
    char plus_re[l], minus_re[l];
    for (int i = 0; i < l; i++)
    {
        char temp;
        Pop_char(S, temp);
        plus_re[i] = temp;
        minus_re[l - 1 - i] = temp;
    }

    for (int i = 0; i < l; i++)
    {
        if (plus_re[i] != minus_re[i])
        {
            cout << "不是回文" << endl;
            system("pause");
            return 0;
        }
        else
            continue;
    }
    cout << "是回文" << endl;

    system("pause");
    return 0;
}