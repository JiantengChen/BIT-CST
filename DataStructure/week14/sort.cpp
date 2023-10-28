#include <iostream>
using namespace std;
template <typename T>
void bubble_sort(T arr[], int len)
{
    int i, j;
    for (i = 0; i < len - 1; i++)
    {
        for (j = 0; j < len - 1 - i; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                cout << "±¾ÂÖÅÅÐò£º";
                for (int i = 0; i < len; i++)
                    cout << arr[i] << ' ';
                cout << endl;
            }
        }
    }
}

int main()
{
    int arr[] = {2, 5, 3, 4, 1, 6, 7};
    int len = (int)sizeof(arr) / sizeof(*arr);
    cout<<"³õÊ¼Ë³Ðò£º";
    for (int i = 0; i < len; i++)
        cout << arr[i] << ' ';
    cout<<endl;
    bubble_sort(arr, len);
    cout<<"×îÖÕË³Ðò£º";
    for (int i = 0; i < len; i++)
        cout << arr[i] << ' ';
    cout << endl;
    system("pause");
    return 0;
}