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

Status InitList_L(LinkList &L)
{
    L = new LNode;
    L->next = NULL;
    return OK;
}

void CreateLinkList(LinkList &L, int m)
{
    L = new LNode;
    LNode *p, *r;
    r = L;
    for (int i = 1; i <= m; ++i)
    {
        p = new LNode; // 生成新结点
        p->data = i;   // 输入元素值
        p->next = NULL;
        r->next = p; // 插入到表尾
        r = p;       // r指向新的尾结点
    }
}

void print(LinkList &L, int m)
{
    LNode *p = L->next;
    for (int i = 0; i < m; i++)
    {
        cout << p->data << " ";
        p = p->next;
    }
}

void List_reverse(LinkList &L)
{
    LinkList p, q;  // 初始化两个结点
    p = L->next;  // 使p指向链表头节点的下一节点
    L->next = NULL;  // 将原有头结点的下一节点置空，作为逆置后链表的尾结点
    // 通过迭代，改变链表中的指针方向，实现链表的原地逆置
    while (p != NULL)
    {
        q = p->next;
        p->next = L->next;
        L->next = p;
        p = q;
    }
}

int main(int argc, char const *argv[])
{
    LinkList L;
    CreateLinkList(L, 10);
    print(L, 10);
    List_reverse(L);
    print(L, 10);
    system("pause");
    return 0;
}
