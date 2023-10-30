#include <iostream>
#include <cstdio>
using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

typedef int ElemType;
typedef int Status;

typedef struct 
{
    ElemType *elem;
    int length;
} SqList;


Status InitList_Sq(SqList &L)
{
    L.elem = new ElemType[MAXSIZE];
    if (!L.elem)
        exit(OVERFLOW);
    L.length = 0;
    return OK;
}

void print(SqList &L)
{
    for (int i = 0; i < L.length - 1; i++)
    {
        printf("%d,", L.elem[i]);
    }
    printf("%d", L.elem[L.length - 1]);
    printf("\n");
}

void List_reverse(SqList &L)
{
    int left = 0, right = L.length - 1;  // 利用左右两个标志实现线性表的原地逆置
    int count = 0;
    while (count < L.length/ 2 and right>left)  // 当循环次数到线性表长度一半时或left>=right时循环停止
    {
        int tmp = L.elem[left];
        L.elem[left] = L.elem[right];
        L.elem[right] = tmp;
        count++;
        left++;
        right--;
    }
}

int main()
{
    SqList L;
    InitList_Sq(L);
    for (int i = 0; i < 10; i++)
    {
        L.length++;
        L.elem[i] = i;
    }
    print(L);
    List_reverse(L);
    print(L);
    system("pause");
    return 0;
}