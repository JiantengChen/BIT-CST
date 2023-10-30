#include <bits/stdc++.h>

using namespace std;
int cmpfunc(const void *a, const void *b)
{
    return *(int *)b - *(int *)a;
}
int main(int argc, char const *argv[])
{
    int count = 0;
    while (count < 2)
    {
        int n, m;
        cin >> n >> m;
        if (m > n)
        {
            cout << "ERROR" << endl;
            continue;
        }
        int nums[n];
        for (int i = 0; i < n; i++)
            cin >> nums[i];
        qsort(nums, n, sizeof(int), cmpfunc);
        for (int i = 0; i < m; i++)
        {
            cout << nums[i];
            if (i == m - 1)
                cout << endl;
            else
                cout << " ";
        }
        count++;
    }

    system("pause");
    return 0;
}