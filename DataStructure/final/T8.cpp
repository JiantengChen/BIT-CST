#include <bits/stdc++.h>
using namespace std;

#define FALSE 0
#define OK 1
#define ERROR 0
#define MAXSIZE 100
/*
ʵ��˼·Ϊ��ԭ��С����ĩβֱ�Ӳ��������Ԫ��x��֮���x��λ�ý��е�����ֱ������������Ϊ���������ļ�Сֵ��
*/
void HeapInsert(vector<int> &heap, int childIndex)  // heapΪ�Բ���Ԫ��x��С���ѣ�childIndexΪ��ǰx����λ�õ��±�
{
    int parentIndex = (childIndex-1)/ 2;  // x��˫������λ���±�
    int parent = heap[parentIndex];  // x��˫��ֵ
    int child = heap[childIndex];  // xֵ
    if (parent > child)  // �ж��Ƿ�����С����Ҫ�󣬲���������еݹ����
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
    cout<<"???��????"<<endl;
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
    cout<<"??????��????"<<endl;
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
