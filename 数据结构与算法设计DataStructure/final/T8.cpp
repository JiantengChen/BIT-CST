#include <bits/stdc++.h>
using namespace std;

#define FALSE 0
#define OK 1
#define ERROR 0
#define MAXSIZE 100
/*
实现思路为在原本小顶堆末尾直接插入待插入元素x，之后对x的位置进行调整，直到满足任意结点为左右子树的极小值。
*/
void HeapInsert(vector<int> &heap, int childIndex)  // heap为以插入元素x的小顶堆，childIndex为当前x所在位置的下标
{
    int parentIndex = (childIndex-1)/ 2;  // x的双亲所在位置下标
    int parent = heap[parentIndex];  // x的双亲值
    int child = heap[childIndex];  // x值
    if (parent > child)  // 判断是否满足小顶堆要求，不满足则进行递归调整
    {
        heap[parentIndex] = child;
        heap[childIndex] = parent;
        HeapInsert(heap, parentIndex);
    }
}

int main(int argc, char const *argv[])
{
    vector<int> heap {1, 2, 6, 11, 10, 9, 8, 12, 16, 14};
    int n = heap.size();
    cout<<"???С????"<<endl;
    for (int i = 0; i < n; i++)
    {
        if (i != n - 1)
            cout << heap[i] << " ";
        else
            cout << heap[i] << endl;
    }
    int x;
    cout<<"????????????????"<<endl;
    cin >> x;
    heap.push_back(x);
    n = heap.size();
    int childIndex = n;
    HeapInsert(heap, childIndex-1);
    cout<<"??????С????"<<endl;
    for (int i = 0; i < n; i++)
    {
        if (i != n - 1)
            cout << heap[i] << " ";
        else
            cout << heap[i] << endl;
    }
    system("pause");
    return 0;
}
