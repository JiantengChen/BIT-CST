#include <iostream>
#include <cstdio>
using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

typedef int ElemType;
typedef int Status;

typedef struct // ˳�������Ͷ���
{
    ElemType *elem;
    int length;
} SqList;

Status InitList_Sq(SqList &L) // ��ʼ�����Ա�L ����������
{
    L.elem = new ElemType[MAXSIZE];
    if (!L.elem)
        exit(OVERFLOW);
    L.length = 0;
    return OK;
}

void DestroyList(SqList &L) // �������Ա�L
{
    if (L.elem)
        delete[] L.elem;
}

void ClearList(SqList &L) // ������Ա�L
{
    L.length = 0;
}

int GetLength(SqList L) // �����Ա�L����
{
    return (L.length);
}

int IsEmpty(SqList L) // �ж��Ƿ�Ϊ��
{
    if (L.length == 0)
        return 1;
    else
        return 0;
}

int GetElem(SqList L, int i, ElemType &e) // ��ȡ���Ա�L�е�ĳ������Ԫ�ص�����

{
    if (i < 1 || i > L.length)
        return ERROR;
    e = L.elem[i - 1];
    return OK;
}

int LocateElem(SqList L, ElemType e) // �����Ա�L�в���ֵΪe������Ԫ��
{
    for (int i = 0; i < L.length; i++)
        if (L.elem[i] == e)
            return i + 1;
    return 0;
}

Status ListDelete_Sq(SqList &L, int i) // ɾ����i�����
{
    if ((i < 1) || (i > L.length))
        return ERROR;
    for (int j = i; j <= L.length - 1; j++)
        L.elem[j - 1] = L.elem[j];
    --L.length;
    return OK;
}

Status InputList_Sq(SqList &L, char arr[])
{
    int count = 0;
    int arr_num[MAXSIZE] = {0};
    for (int i = 0; i < MAXSIZE; i++)
    {
        if (arr[i] != ',' && (arr[i] > '9' || arr[i] < '0'))
            break;
        if (arr[i] == ',' && arr[i] != '\n')
        {
            count++;
            continue;
        }
        arr_num[count] += arr[i] - 48;
    }
    L.length = count + 1;
    if (L.length == MAXSIZE)
    {
        return ERROR;
    }
    for (int i = 0; i < L.length; i++)
    {
        L.elem[i] = arr_num[i];
    }
    return OK;
}

void print(SqList &L)
{
    for (int i = 0; i < L.length - 1; i++)
    {
        printf("%d,", L.elem[i]);
    }
    printf("%d", L.elem[L.length - 1]);
    printf("\n");
}

Status InsertOrderList(SqList &L, ElemType x)
{
    L.length++;
    int i = L.length - 2;
    while (i >= 0 && x < L.elem[i])
        i--;
    for (int j = L.length - 2; j > i; j--)
        L.elem[j + 1] = L.elem[j];
    L.elem[i + 1] = x;
    return OK;
}

int main()
{
    SqList L;
    InitList_Sq(L);
    char arr[MAXSIZE];
    scanf("%s", &arr);
    InputList_Sq(L, arr);
    int Insert_Num;
    cin >> Insert_Num;
    InsertOrderList(L, Insert_Num);
    print(L);
    system("pause");
    return 0;
}