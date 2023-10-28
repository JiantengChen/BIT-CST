#include <bits/stdc++.h>
using namespace std;

#define FALSE 0
#define OK 1
#define ERROR 0
#define MAXSIZE 100

typedef int TElemType;
typedef int Status;

typedef struct BSTNode
{
    TElemType data;
    struct BSTNode *lchild, *rchild;
} BSTNode, *BSTree;

Status InOrderTraverse(BSTree T)
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

/*
实现思路为初始化一空二叉树，将每一轮输入的数字按照二叉排序树的要求插入二叉树中，以满足排序目的。
*/
Status InitialBST(BSTree &T, TElemType e)  // BSTree为二叉排序树，e为本轮插入排序树的元素
{
    if (T == NULL)
    {
        T = new BSTNode;
        T->data = e;
        T->lchild = T->rchild = NULL;
        return OK;
    }
    else if (e == T->data)
    {
        return FALSE;
    }
    else if (e < T->data)
    {
        return InitialBST(T->lchild, e);
    }
    else
    {
        return InitialBST(T->rchild, e);
    }
}

int main(int argc, char const *argv[])
{
    BSTree T;
    for (int i = 0; i < 10; i++)
    {
        int x;
        cin >> x;
        InitialBST(T, x);
    }
    InOrderTraverse(T);

    system("pause");
    return 0;
}
