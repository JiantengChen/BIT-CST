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


typedef struct LNode
{
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;


void CreateLinkList(LinkList &L, int m)
{
    L = new LNode;
    LNode *p, *r;
    L->data = 1;
    r = L;
    for (int i = 2; i <= m; ++i)
    {
        p = new LNode; //生成新结点
        p->data = i;   //输入元素值
        p->next = NULL;
        r->next = p; //插入到表尾
        r = p;       // r指向新的尾结点
    }
}

void print(LinkList &L, int m)
{
    LNode *p = L;
    for (int i = 0; i < m; i++)
    {
        cout << p->data << "\t";
        p = p->next;
    }
}



void deleteNode (LinkList &L,LinkList p,int n)
{
    LinkList q;
    while (p->data != n)
    {
        q = p;
        p = p->next;
    }
    q->next = p->next;
    p = q->next;
}




int main()
{
    int n;
    cin>>n;

}