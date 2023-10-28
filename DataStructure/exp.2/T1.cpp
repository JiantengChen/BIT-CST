#include <bits/stdc++.h>
using namespace std;

#define TRUE 1
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

Status InOrderTraverse(BiTree T)
{
    if (T == NULL)
        return OK;
    else
    {
        InOrderTraverse(T->lchild);
        cout << T->data;
        InOrderTraverse(T->rchild);
    }
    return OK;
}

Status PostOrderTraverse(BiTree T)
{
    if (T == NULL)
        return OK;
    else
    {
        PostOrderTraverse(T->lchild);
        PostOrderTraverse(T->rchild);
        cout << T->data;
    }
    return OK;
}

int main()
{
    BiTree T;
    CreateBiTree(T); // AB#D##C##
    InOrderTraverse(T);
    cout << endl;
    PostOrderTraverse(T);
    cout << endl;
    system("pause");
    return 0;
}