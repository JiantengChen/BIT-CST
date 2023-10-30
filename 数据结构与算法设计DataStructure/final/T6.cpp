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
{                            // �߽��
    int adjvex;              // �ñ���ָ��Ķ����λ��
    struct ArcNode *nextarc; // ָ����һ���ߵ�ָ��
    int ID;                  // �ͱ���ص���Ϣ
} ArcNode;

typedef struct VNode
{
    VerTexType data;     // ������Ϣ
    ArcNode *firstarc;   // ָ���һ�������ö���ıߵ�ָ��
} VNode, AdjList[MVNum]; // AdjList��ʾ�ڽӱ�����

typedef struct
{
    AdjList vertices;   // �ڽӱ�
    int vexnum, arcnum; // ͼ�ĵ�ǰ�������ͱ���
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
AlGraph�У�verticesΪ�ڽӱ�vexnumΪԪ�ظ�������ÿһ��G.vertices[]�У�data��Ŷ�����Ϣ��firstarcָ��ArcNode���͵�ָ�룬ÿһ��ArcNode����а���adjvex(ָ�򶥵��λ��)��nextarc(ָ����һ�ߵ�ָ��)��ID(��ǰ��������)��
*/
Status TopologicalSort(ALGraph &G, vector<int> result) // result���ڴ洢��������Ľ��
{
    queue<int> q;
    // �����Ϊ0�Ķ�����ӣ���û��ֱ��ǰ��
    for (int i = 0; i < G.vexnum; ++i)
    {
        if (G.vertices[i].firstarc->ID == 0)
            q.push(i);
    }

    while (!q.empty()) // ֱ��ȫ�����㴦�����ʣ�ඥ�㶼��ֱ��ǰ��
    {
        int v = q.front();
        result.push_back(v);                                         // ѡ��һ�����Ϊ0�Ķ��㲢��������
        q.pop();                                                     // �ڶ�����ɾ���ö�����Ϣ
        for (ArcNode *p = G.vertices[v].firstarc; p; p = p->nextarc) // ɾ���ö��㷢�������������
        {
            int k = p->adjvex;
            if (--p->ID == 0)
                q.push(k);
        }
    }

    if (result.size() != G.vexnum)
        return ERROR; // ˵���л������ؼ�
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
            cout << "��ǰ��������: ";
            cin >> id;
            p->ID = id;
            p->nextarc = G.vertices[k].firstarc;

            cout << "����" << G.vertices[k].data << "�Ƿ�ָ���������㣬����������-1: ";
            cin >> flag;
            if (flag == -1)
                break;

            cout << "��ǰ����ָ��Ķ�������: ";
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
