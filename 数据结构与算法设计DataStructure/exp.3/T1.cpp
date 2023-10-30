#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    void InsertSort(int a[])
    {
        for (int i = 1; i < 10; i++)
        {
            int key = a[i];
            int j = i - 1;
            while ((j >= 0 && key < a[j]))
            {
                a[j + 1] = a[j];
                j--;
            }
            a[j + 1] = key;
        }
    }
    void QuicklySort(int a[], int left, int right)
    {
        if (left >= right)
        {
            return;
        }
        int val = a[left];
        int l, r;
        l = left, r = right;
        while (l != r)
        {
            while (a[r] >= val and l < r)
            {
                r--;
            }
            while (a[l] <= val and l < r)
            {
                l++;
            }
            if (l < r)
            {
                int temp = a[l];
                a[l] = a[r];
                a[r] = temp;
            }
        }
        a[left] = a[l];
        a[l] = val;
        QuicklySort(a, left, l - 1);
        QuicklySort(a, l + 1, right);
    }
    void SelectSort(int a[])
    {
        for (int i = 0; i < 10; i++)
        {
            int min = 2147483647, pos;
            for (int j = i + 1; j < 10; j++)
            {
                if (a[j] < min)
                {
                    min = a[j];
                    pos = j;
                }
            }
            if (a[pos] < a[i])
            {
                int temp = a[i];
                a[i] = a[pos];
                a[pos] = temp;
            }
        }
    }
};

int main()
{
    int a[10];
    cout << "请依次输入十个数字，用空格分隔，输入完成后敲击回车：" << endl;
    for (int i = 0; i < 10; i++)
        cin >> a[i];
    cout << "请选择需要的排序方式，选择方式为输入对应数字并敲击回车：\n1.插入排序\n2.快速排序\n3.选择排序" << endl;
    int s;
    cin >> s;

    Solution solution;
    switch (s)
    {
    case 1:
        solution.InsertSort(a);
        break;
    case 2:
        solution.QuicklySort(a, 0, 9);
        break;
    case 3:
        solution.SelectSort(a);
        break;
    }

    for (int i = 0; i < 10; i++)
        cout << a[i] << "\t";
    cout << endl;

    system("pause");
    return 0;
}
