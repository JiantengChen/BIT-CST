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

TSMatrix res;

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
int lgh = 1;
void stringManage(string x)
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

int main()
{

    string x, y;
    stringManage(x);
    stringManage(y);
    int matrix[MAXSIZE][MAXSIZE] = {0};
    for (int i = 1; i < MAXSIZE + 1; i++)
    {
        int line = res.data[i].i;
        int column = res.data[i].j;
        matrix[line][column] += res.data[i].e;
    }
    string result = "";
    for (int i = 0; i < 100; i++)
        for (int j = 0; j < 100; j++)
            if (matrix[i][j] != 0)
                result += to_string(i) + "," + to_string(j) + "," + to_string(matrix[i][j]) + ";";

    for (int i = 0; i < result.size() - 1; i++)
        cout << result[i];
    cout << endl;
    system("pause");
    return 0;
}