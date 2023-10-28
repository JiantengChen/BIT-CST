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
注：本题测试输入请参考下方，即在两行分别输入待相乘的两个矩阵，稀疏矩阵的第0个三元组分别表示行数，列数，当前矩阵元素个数，即下方第一行3，4，4代表一个三行四列，有四个元素的矩阵。
3,4,4;1,1,3;1,4,5;2,2,-1;3,1,2
4,2,4;1,2,2;2,1,1;3,1,-2;3,2,4
通过其他函数对输入进行处理后，分别赋值给稀疏矩阵rx和ry，进行矩阵相乘运算
*/
void MatrixMultiply(TSMatrix &rx, TSMatrix &ry, vector<vector<int>> &matrix)
{
    for (int q = 1; q < rx.data[0].i + 1; q++)  // 遍历结果矩阵行
    {
        for (int k = 1; k < ry.data[0].j + 1; k++)  // 遍历结果矩阵列
        {
            for (int w = 1; w <= rx.data[0].e; w++)  // 遍历输入的第一个稀疏矩阵
            {
                for (int r = 1; r <= rx.data[0].e; r++)  // 遍历输入的第二个稀疏矩阵
                {
                    int lx = rx.data[w].i;  // 第一个稀疏矩阵元素的行数
                    int cx = rx.data[w].j;  // 第一个稀疏矩阵元素的列数
                    int ly = ry.data[r].i;  // 第二个稀疏矩阵元素的行数
                    int cy = ry.data[r].j;  // 第二个稀疏矩阵元素的列数
                    if (lx == q && cy == k && cx == ly)  // 满足相乘条件
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
    cout << "以稀疏矩阵格式输出表达式为：" << endl;
    for (int i = 0; i < result.size() - 1; i++)
        cout << result[i];
    cout << endl;

    system("pause");
    return 0;
}