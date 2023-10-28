#include <bits/stdc++.h>
using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define MAXSIZE 100
#define MaxInt 32767
#define MVNum 100

typedef char VerTexType;
typedef int ArcType;
typedef char TElemType;
typedef int Status;
typedef int SElemType;

typedef struct
{
    SElemType *base;
    SElemType *top;
    int stacksize;
} SqStack;

Status InitStack(SqStack &S)
{
    S.base = new SElemType[MAXSIZE];
    if (!S.base)
        return OVERFLOW;
    S.top = S.base;
    S.stacksize = MAXSIZE;
    return OK;
}
Status Push(SqStack &S, SElemType e)
{
    if (S.top - S.base == S.stacksize)
        return ERROR;
    *S.top++ = e;
    return OK;
}
Status Pop(SqStack &S, SElemType &e)
{
    if (S.top == S.base)
        return ERROR;
    e = *--S.top;
    return OK;
}
Status GetTop(SqStack S, SElemType &e)
{
    if (S.top == S.base)
        return ERROR;
    e = *(S.top - 1);
    return OK;
}
int StackLength(SqStack S)
{
    return S.top - S.base;
}
bool StackEmpty(SqStack S)
{
    if (S.top == S.base)
        return true;
    else
        return false;
}
typedef struct ArcNode // 边结点
{
    int adjvex;              // 该边所指向的顶点的位置
    struct ArcNode *nextarc; // 指向下一条边的指针
} ArcNode;

typedef struct VNode
{
    VerTexType data;     // 顶点信息
    ArcNode *firstarc;   // 指向第一条依附该顶点的边的指针
} VNode, AdjList[MVNum]; // AdjList表示邻接表类型

typedef struct
{
    AdjList vertices;   // 邻接表
    int vexnum, arcnum; // 图的当前顶点数和边数
} ALGraph;

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

int main(int argc, char const *argv[])
{
    ALGraph G;
    cin >> G.vexnum;
    for (int i = 0; i < G.vexnum; i++)
    {
        cin >> G.vertices[i].data;
        G.vertices[i].firstarc = NULL;
    }
    string r;
    cin >> r;
    int y = stoi(r);
    for (int k = 0; k < G.vexnum; k++)
    {
        string s;
        getline(cin, s);
        SqStack S;
        InitStack(S);
        if (k == 0)
            Push(S, y);
        vector<string> temp = split(s, " ");
        for (auto charnums : temp)
        {
            int a = stoi(charnums);
            if (a == -1)
                break;
            Push(S, a);
        }
        cout << G.vertices[k].data << "  ";
        while (!StackEmpty(S))
        {
            int x, y;
            Pop(S, x);
            Pop(S, y);
            cout << "(" << k << "," << y << ")" << x << "  ";
        }
        cout << endl;
    }

    system("pause");
    return 0;
}
