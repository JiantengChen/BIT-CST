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

void FindParent(BiTree &T, TElemType x, int &flag)  // BITree为待查找二叉树，x为待查找元素，flag用于判断是否找到双亲，默认值为0，如未找到双亲将提示说明
{
    if (T)
    {
        if (T->lchild && T->lchild->data == x)
        {
            cout << "结点" << x << "的双亲结点为" << T->data << endl;
            flag = 1;
            return;  // 找到双亲后离开函数
        }
        else if (T->rchild && T->rchild->data == x)
        {
            cout << "结点" << x << "的双亲结点为" << T->data << endl;
            flag = 1;
            return;  // 找到双亲后离开函数
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
    cout<<"请输入扩展前序遍历结果，将根据本输入构造二叉树："<<endl;
    CreateBiTree(T);
    TElemType x;
    int flag = 0;
    cout<<"请输入你想查询双亲的结点："<<endl;
    cin >> x;
    FindParent(T, x, flag);
    if (flag == 0)
        cout << "结点" << x << "无双亲结点" << endl;
    system("pause");
    return 0;
}