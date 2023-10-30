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
    ElemType code;
    struct LNode *next;
} LNode, *LinkList;

void CreateLinkList(LinkList &L, int m)
{
    L = new LNode;
    LNode *p, *r;
    L->code = 1;
    r = L;
    for (int i = 2; i <= m; ++i)
    {
        p = new LNode; //生成新结点
        p->code = i;   //输入元素值
        p->next = NULL;
        r->next = p; //插入到表尾
        r = p;       // r指向新的尾结点
    }
    r->next = L;
}

void print(LinkList &L, int m)
{
    LNode *p = L;
    for (int i = 0; i < m; i++)
    {
        cout << p->code << "\t";
        p = p->next;
    }
}

void deleteNode(LinkList &L, LinkList p, int n)
{
    LinkList q;
    while (p->next != p)
    {
        // 找到第s个结点之后的第n个结点
        for (int i = 1; i < n; i++)
        {
            q = p;
            p = p->next;
        }
        // 输出当前节点并从链表中删除
        cout << p->code << '\t';
        q->next = p->next;
        p = q->next;
    }
    cout << p->code << endl;
}

int main()
{
    int m, s, n;
    do
    {
        cout << "请输入结点数量m:" << endl;
        cin >> m;
        if (m <= 0)
            cout << "链表结点数量必须大于等于0，请重新输入。" << endl;
    } while (m <= 0);
    do
    {
        cout << "请输入整数s:" << endl;
        cin >> s;
        if (s < 1)
            cout << "结点计数小于最小结点数量，请重新输入。" << endl;
        else if (s >= m)
            cout << "结点计数超出总结点数量，请重新输入。" << endl;
    } while (s < 1 || s > m);
    do
    {
        cout << "请输入整数n:" << endl;
        cin >> n;
        if (n <= 0)
            cout << "计数结点不能小于0，请重新输入" << endl;
    } while (n <= 0);

    LinkList L, p;
    CreateLinkList(L, m);
    p = L;

    // 查找第s个结点
    for (int i = 1; i < s; i++)
    {
        p = p->next;
    }

    deleteNode(L, p, n);

    system("pause");
    return 0;
}