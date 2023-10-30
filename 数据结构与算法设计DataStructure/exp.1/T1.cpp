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
        p = new LNode; //�����½��
        p->code = i;   //����Ԫ��ֵ
        p->next = NULL;
        r->next = p; //���뵽��β
        r = p;       // rָ���µ�β���
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
        // �ҵ���s�����֮��ĵ�n�����
        for (int i = 1; i < n; i++)
        {
            q = p;
            p = p->next;
        }
        // �����ǰ�ڵ㲢��������ɾ��
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
        cout << "������������m:" << endl;
        cin >> m;
        if (m <= 0)
            cout << "����������������ڵ���0�����������롣" << endl;
    } while (m <= 0);
    do
    {
        cout << "����������s:" << endl;
        cin >> s;
        if (s < 1)
            cout << "������С����С������������������롣" << endl;
        else if (s >= m)
            cout << "�����������ܽ�����������������롣" << endl;
    } while (s < 1 || s > m);
    do
    {
        cout << "����������n:" << endl;
        cin >> n;
        if (n <= 0)
            cout << "������㲻��С��0������������" << endl;
    } while (n <= 0);

    LinkList L, p;
    CreateLinkList(L, m);
    p = L;

    // ���ҵ�s�����
    for (int i = 1; i < s; i++)
    {
        p = p->next;
    }

    deleteNode(L, p, n);

    system("pause");
    return 0;
}