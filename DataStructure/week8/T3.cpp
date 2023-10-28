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
Status PreOrderTraverse(BiTree T)
{
    if (T == NULL)
        return OK;
    else
    {
        PreOrderTraverse(T->lchild);
        cout << T->data << " ";
        PreOrderTraverse(T->rchild);
    }
    return OK;
}

Status InOrderTraverse(BiTree T)
{
    if (T == NULL)
        return OK;
    else
    {
        InOrderTraverse(T->lchild);
        cout << T->data << " ";
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
        cout << T->data << " ";
    }
    return OK;
}

void CountLeaf(BiTree T, int &leafs)
{
    if (T)
    {
        if ((!T->lchild) && (!T->rchild))
            leafs++;
        CountLeaf(T->lchild, leafs);
        CountLeaf(T->rchild, leafs);
    }
}

int CountDepth(BiTree T)
{
    int depth = 0;
    if (T)
    {
        int leftdepth = CountDepth(T->lchild);
        int rightdepth = CountDepth(T->rchild);
        depth = leftdepth >= rightdepth ? leftdepth + 1 : rightdepth + 1;
    }
    return depth;
}

int main()
{
    int leafs = 0, Depth = 0;
    BiTree T;
    CreateBiTree(T);
    CountLeaf(T, leafs);
    Depth = CountDepth(T);
    cout << "leafs=" << leafs << endl;
    cout << "Depth=" << Depth << endl;

    system("pause");
    return 0;
}