#include <bits/stdc++.h>
using namespace std;

#define MaxInt 32767
#define MVNum 100
#define ERROR 0
#define OK 1

typedef char VerTexType;
typedef int ArcType;
typedef char TElemType;
typedef int Status;
typedef int SElemType;
typedef struct ArcNode
{                            // 边结点
    int adjvex;              // 该边所指向的顶点的位置
    struct ArcNode *nextarc; // 指向下一条边的指针
    int ID;                  // 和边相关的信息
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

// void TopologicalSort(ALGraph &G)
// {
//     for (int k = 0; k < G.vexnum; k++)
//     {
//         if (G.vertices[k].firstarc->ID == 0)
//         {
//             cout << G.vertices[k].data << " ";
//             G.vertices->firstarc = NULL;
//         }
//     }
// }

// Status TopologicalSort(ALGraph &G)
// {
//     FindInDegree(G, indegree);
//     InitStack(S);
//     ArcNode *p;
//     int count, i, k;
//     for (i = 0; i < G.vexnum; ++i)
//         if (!indegree[i])
//             Push(S, i);
//     count = 0;
//     while (!StackEmpty(S))
//     {
//         Pop(S, i);
//         cout << i << "," << G.vertices[i].data;
//         count++;
//         for (ArcNode p = G.vertics[i].firstarc; p; p = p->nextarc)
//         {
//             k = p->adjvex;
//             if (!(--indegree[k]))
//                 Push(S, k);
//         }
//     }
//     if (count < G.vexnum)
//         return ERROR;
//     else
//         return OK;
// }

/*
AlGraph中，vertices为邻接表，vexnum为元素个数，在每一个G.vertices[]中，data存放顶点信息，firstarc指向ArcNode类型的指针，每一个ArcNode结点中包含adjvex(指向顶点的位置)，nextarc(指向下一边的指针)，ID(当前顶点的入度)。
*/
Status TopologicalSort(ALGraph &G, vector<int> result) // result用于存储拓扑排序的结果
{
    queue<int> q;
    // 将入度为0的顶点入队，即没有直接前驱
    for (int i = 0; i < G.vexnum; ++i)
    {
        if (G.vertices[i].firstarc->ID == 0)
            q.push(i);
    }

    while (!q.empty()) // 直到全部顶点处理完或剩余顶点都有直接前驱
    {
        int v = q.front();
        result.push_back(v);                                         // 选择一个入度为0的顶点并加入结果中
        q.pop();                                                     // 在队列中删除该顶点信息
        for (ArcNode *p = G.vertices[v].firstarc; p; p = p->nextarc) // 删除该顶点发出的所有有向边
        {
            int k = p->adjvex;
            if (--p->ID == 0)
                q.push(k);
        }
    }

    if (result.size() != G.vexnum)
        return ERROR; // 说明有环，返回假
    return OK;
}

int main(int argc, char const *argv[])
{
    vector<int> result;
    ALGraph G;
    cin >> G.vexnum;
    for (int i = 0; i < G.vexnum; i++)
    {
        cin >> G.vertices[i].data;
        G.vertices[i].firstarc = NULL;
    }

    for (int k = 0; k < G.vexnum; k++)
    {
        int flag;
        while (1)
        {
            int id;
            ArcNode *p;
            cout << "当前顶点的入度: ";
            cin >> id;
            p->ID = id;
            p->nextarc = G.vertices[k].firstarc;

            cout << "顶点" << G.vertices[k].data << "是否指向其他顶点，如无请输入-1: ";
            cin >> flag;
            if (flag == -1)
                break;

            cout << "当前顶点指向的顶点的序号: ";
            int a;
            cin >> a;

            p->adjvex = a;
            p->nextarc = G.vertices[k].firstarc;
            G.vertices[k].firstarc = p;
        }
    }
    TopologicalSort(G, result);
    system("pause");
    return 0;
}
