#include <bits/stdc++.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define MAXSIZE 100
#define MaxInt 32767
#define MVNum 100

typedef char VerTexType;
typedef int ArcType;
typedef int TElemType;
typedef int Status;
typedef int SElemType;
typedef struct // 记录类型
{
    int key; // 关键字项
} ElemType;
typedef struct BSTNode
{
    ElemType data;                   // 数据域
    struct BSTNode *lchild, *rchild; // 左右孩子指针
} BSTNode, *BSTree;

vector<string> split(const string &s, const string &seperator)
{
    vector<string> result;
    typedef string::size_type string_size;
    string_size i = 0;

    while (i != s.size())
    {
        // 找到字符串中首个不等于分隔符的字母；
        int flag = 0;
        while (i != s.size() && flag == 0)
        {
            flag = 1;
            for (string_size x = 0; x < seperator.size(); ++x)
                if (s[i] == seperator[x])
                {
                    ++i;
                    flag = 0;
                    break;
                }
        }

        // 找到又一个分隔符，将两个分隔符之间的字符串取出；
        flag = 0;
        string_size j = i;
        while (j != s.size() && flag == 0)
        {
            for (string_size x = 0; x < seperator.size(); ++x)
                if (s[j] == seperator[x])
                {
                    flag = 1;
                    break;
                }
            if (flag == 0)
                ++j;
        }
        if (i != j)
        {
            result.push_back(s.substr(i, j - i));
            i = j;
        }
    }
    return result;
}

BSTree SearchBST(BSTree T, int key)
{
    if ((!T) || key == T->data.key)
        return T;
    else if (key < T->data.key)
        return SearchBST(T->lchild, key);
    // 在左子树中继续查找
    else
        return SearchBST(T->rchild, key);
    // 在右子树中继续查找
}
int InsertBST(BSTree &T, ElemType e)
{
    if (T == NULL) // 原树为空, 新插入的记录为根结点
    {
        T = new BSTNode;
        T->data = e;
        T->lchild = T->rchild = NULL;
        return 1;
    }
    else if (e.key == T->data.key) // 存在相同关键字的结点,返回0
        return 0;
    else if (e.key < T->data.key)
        return InsertBST(T->lchild, e); // 插入到左子树中
    else
        return InsertBST(T->rchild, e); // 插入到右子树中
}

int cmpfunc(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

Status InOrderTraverse(BSTree T)
{
    if (T == NULL)
        return OK;
    else
    {
        InOrderTraverse(T->lchild);
        cout << T->data.key;
        InOrderTraverse(T->rchild);
    }
    return OK;
}

int main(int argc, char const *argv[])
{
    int n;
    BSTree T;
    scanf("%d", &n);
    int nums[n];
    for (int i = 0; i < n; i++)
        cin >> nums[i];
    cout << "原始数据：";
    for (int i = 0; i < n; i++)
        cout << nums[i] << " ";
    qsort(nums, n, sizeof(int), cmpfunc);
    int del;
    scanf("%d", &del);

    // for (int i = 0; i < n; i++)
    // {
    //     ElemType tmp;
    //     tmp.key = nums[i];
    //     InsertBST(T, tmp);
    // }
    // InOrderTraverse(T);

    cout << endl;
    cout << "中序遍历结果：";
    for (int i = 0; i < n; i++)
        cout << nums[i] << "  ";
    cout<<endl;
    cout << "删除结点后结果：";
    int a;
    for (int i = 0; i < n; i++)
    {
        if (nums[i] == del)
        {
            a = i;
            goto end;
        }
    }
    cout << "没有" << del << "结点。" << endl;
    system("pause");
    return 0;
end:
    for (int i = 0; i < n; i++)
    {
        if (i != a)
            cout << nums[i] << "  ";
    }
    cout << endl;

    system("pause");
    return 0;
}
