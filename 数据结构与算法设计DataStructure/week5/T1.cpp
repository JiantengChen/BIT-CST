#include <iostream>
#include <cstdio>

using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

typedef int Status;

typedef struct
{
    char *ch;   //�����ǿ�,�򰴴�������洢��,
                //����chΪNULL
    int length; //������
} HString;

int main()
{
    char input1[MAXSIZE], input2[MAXSIZE];
    string A, B;
    cin >> A >> B;
    int m = A.compare(B);
    if (m == 0)
        cout << "equal" << endl;
    else
        cout << "not equal" << endl;
    system("pause");
    return 0;
}