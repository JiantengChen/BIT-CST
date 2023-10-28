#include <bits/stdc++.h>
using namespace std;

#define FALSE 0
#define OK 1
#define ERROR 0
#define MAXSIZE 100

typedef char TElemType;
typedef int Status;

typedef struct BiNode
{
    TElemType data;
    struct BiNode *lchild, *rchild;
} BiTNode, *BiTree;

void CreateBiTree(BiTree &T)
{

    char ch;
    cin >> ch;
    if (ch == '#')
    {
        T = NULL;
    }
    else
    {
        T = new BiTNode;
        T->data = ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}

void FindParent(BiTree &T, TElemType x, int &flag)  // BITreeΪ�����Ҷ�������xΪ������Ԫ�أ�flag�����ж��Ƿ��ҵ�˫�ף�Ĭ��ֵΪ0����δ�ҵ�˫�׽���ʾ˵��
{
    if (T)
    {
        if (T->lchild && T->lchild->data == x)
        {
            cout << "���" << x << "��˫�׽��Ϊ" << T->data << endl;
            flag = 1;
            return;  // �ҵ�˫�׺��뿪����
        }
        else if (T->rchild && T->rchild->data == x)
        {
            cout << "���" << x << "��˫�׽��Ϊ" << T->data << endl;
            flag = 1;
            return;  // �ҵ�˫�׺��뿪����
        }
        else
        {
            FindParent(T->lchild, x, flag);
            FindParent(T->rchild, x, flag);
        }
    }
}

int main()
{
    BiTree T;
    cout<<"��������չǰ���������������ݱ����빹���������"<<endl;
    CreateBiTree(T);
    TElemType x;
    int flag = 0;
    cout<<"�����������ѯ˫�׵Ľ�㣺"<<endl;
    cin >> x;
    FindParent(T, x, flag);
    if (flag == 0)
        cout << "���" << x << "��˫�׽��" << endl;
    system("pause");
    return 0;
}