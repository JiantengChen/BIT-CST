#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>

using namespace std;
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 100

typedef int Status;
typedef int ElemType;

typedef struct
{
    int i, j;
    ElemType e;
} Triple;

typedef struct
{
    Triple data[MAXSIZE + 1];
    int mu, nu, tu;
} TSMatrix;

vector<string> split(const string &s, const string &seperator)
{
    vector<string> result;
    typedef string::size_type string_size;
    string_size i = 0;

    while (i != s.size())
    {
        // �ҵ��ַ������׸������ڷָ�������ĸ��
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

        // �ҵ���һ���ָ������������ָ���֮����ַ���ȡ����
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

void stringManage(string x, TSMatrix &res, int &lgh)
{
    cin >> x;
    vector<string> q = split(x, ";");
    for (auto a : q)
    {
        vector<string> temp = split(a, ",");
        int count = 0;
        for (auto b : temp)
        {
            int num = stoi(b);
            switch (count)
            {
            case 0:
                res.data[lgh].i = num;
                break;
            case 1:
                res.data[lgh].j = num;
                break;
            case 2:
                res.data[lgh].e = num;
                break;
            default:
                break;
            }
            count++;
        }
        lgh++;
    }
}

/*
ע���������������ο��·����������зֱ��������˵���������ϡ�����ĵ�0����Ԫ��ֱ��ʾ��������������ǰ����Ԫ�ظ��������·���һ��3��4��4����һ���������У����ĸ�Ԫ�صľ���
3,4,4;1,1,3;1,4,5;2,2,-1;3,1,2
4,2,4;1,2,2;2,1,1;3,1,-2;3,2,4
ͨ������������������д���󣬷ֱ�ֵ��ϡ�����rx��ry�����о����������
*/
void MatrixMultiply(TSMatrix &rx, TSMatrix &ry, vector<vector<int>> &matrix)
{
    for (int q = 1; q < rx.data[0].i + 1; q++)  // �������������
    {
        for (int k = 1; k < ry.data[0].j + 1; k++)  // �������������
        {
            for (int w = 1; w <= rx.data[0].e; w++)  // ��������ĵ�һ��ϡ�����
            {
                for (int r = 1; r <= rx.data[0].e; r++)  // ��������ĵڶ���ϡ�����
                {
                    int lx = rx.data[w].i;  // ��һ��ϡ�����Ԫ�ص�����
                    int cx = rx.data[w].j;  // ��һ��ϡ�����Ԫ�ص�����
                    int ly = ry.data[r].i;  // �ڶ���ϡ�����Ԫ�ص�����
                    int cy = ry.data[r].j;  // �ڶ���ϡ�����Ԫ�ص�����
                    if (lx == q && cy == k && cx == ly)  // �����������
                    {
                        matrix[q][k] += rx.data[w].e * ry.data[r].e;
                    }
                }
            }
        }
    }
}


int main()
{
    string x, y;
    TSMatrix rx, ry;
    int lenx = 0, leny = 0;
    stringManage(x, rx, lenx);
    stringManage(y, ry, leny);
    vector<vector<int>> matrix(rx.data[0].i + 1, vector<int>(ry.data[0].j + 1, 0));
    if (rx.data[0].j == ry.data[0].i)
        MatrixMultiply(rx, ry, matrix);
    else
    {
        cout << "ERROR" << endl;
        system("pause");
        return 0;
    }
    string result = "";
    for (int i = 1; i < rx.data[0].i + 1; i++)
    {
        for (int j = 1; j < ry.data[0].j + 1; j++)
        {
            if (matrix[i][j] != 0)
                result += to_string(i) + "," + to_string(j) + "," + to_string(matrix[i][j]) + ";";
        }
    }
    cout << "��ϡ������ʽ������ʽΪ��" << endl;
    for (int i = 0; i < result.size() - 1; i++)
        cout << result[i];
    cout << endl;

    system("pause");
    return 0;
}