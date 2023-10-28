# 预定义常量与类型

- #define TRUE 1
- #define FALSE 0
- #define OK 1
- #define ERROR 0
- #define OVERFLOW -2

# typedef描述

```cpp
typedef struct{
    ElemType *elem; //指向数据元素的基地址
    int length; //线性表的当前长度
}SqList;
```

```****
Status InitList_Sq(SqList &L){
    L.elem = new ElemType[MAXSIZE];
    if(! L.elem) exit(OVERFLOW);
    L.length = 0;
    return OK;
}
```

- 旧的传递参数方法

>值传递  
>地址传递

- 新的传递参数方法

>引用传递

## 引用传递

> 类型 & 引用变量名 = 已定义的变量名  
> 定义引用并初始化，给变量起一个别名，修改引用值就是修改所引用的变量值  
> 定义同时赋值，只可以操作指向的值，访问指向的值无需向指针一样访问

## 用new分配内存

```cpp
int *anAge;
anAge=new int;
*anAge=71;
```

```cpp
int *anAge = new int (71);
```

## 用delete释放内存

```cpp
char *cityName = new char[9]
delete []cityName
```

# 线性表

## 抽象数据类型定义

```cpp
ADT List { 
    数据对象：
        D＝{ ai | ai ∈ElemSet, i=1,2,...,n, n≥0 }
                            {称 n 为线性表的表长; 
                                称 n=0 时的线性表为空表。} 
        数据关系： 
            R1＝{ <ai-1 ,ai >|ai-1 ,ai∈D, i=2,...,n } 
    {设线性表为 (a1，a2, . . . ，ai，. . . ，an),称 i 为 ai在线性表中的位序。}
    基本操作： 
        初始化操作InitList(&L)
        取值操作GetElem(L,i,&e)
        查找操作(L,e)
        插入操作(&L,i,e)
        删除操作(&L,i,&e)
        清空操作(Sqlist &L)
        销毁操作(Sqlist &L)
}ADT List
```

## 定义

> 用数据元素的有限序列表示
> 直接前趋，直接后继
> 下标指元素的标号，n为元素总个数
> 线性&相同特性

```cpp
#define MAXSIZE 100
typedef struct{
    ElemType *elem;
    int length;
}SqList;

Status InitList_Sq(SqList &L){
    L.elem = new ElemType[MAXSIZE];
    if(!L.elem) exit(OVERFLOW);
    L.length = 0;
    return OK;
}

int GetElem(SqList, int i, ElemType &e){
    if(i<1||i>L.length)return ERROR;
    e=L.elem[i-1];
    return OK;
}

int LocateElem(SqList L,ElemType e){

}

```

## 链表

- 头指针
- 头节点 可以表示空链表 数据域可以为空 也可以存放线性表长度等附加信息
- 首元节点

```cpp
typedef struct Lnode{
    ElemType data;
    struct LNode *next;
}LNode, *LinkList;
```

# 栈和队列

## 栈

# 树

**树是n个结点的有限集合**

## 定义

- 根：根节点，没有前驱
- 叶子：终端节点，没有后继
- 森林：m棵不相交的树的集合
- 有序树：结点各子树从左至右有序，不能互换，左为第一
- 无序树：结点各子树可互换位置
- 双亲：直接前驱
- 孩子：下层结点的子树的根，直接后继
- 兄弟：同一双亲下的同层结点
- 堂兄弟：双亲位于同一层的结点，但并非同一双亲
- 祖先：从根到该结点所经分支的所有结点
- 子孙：结点下层子树中的任意节点
- 结点：树的数据元素
- 结点的度：结点挂接的子树数
- 结点的层次：从根到该结点的层数，根节点酸第一层
- 终端结点：度为0，叶子
- 分支节点：度不为0，也称你为内部节点
- 树的度：结点度中的最大值
- 树的深度：所有结点中最大的层数

## 二叉树

**二叉树（Binary Tree）是n（n≥0）个结点所构成的集合，它或为空树（n = 0）；或为非空树，对于非空树T：有且仅有一个根节点；除了根节点以为的其余节点分为两个互不相交的子集T1和T2，分别称为T的左子树和右子树，且T1和T2本身又都是二叉树**

- 二叉树或为空树，或是有一个根节点以及两颗不相交的左子树和右子树构成，左右也为二叉树
- 有序树
- 结点的度<=2
- 所有树都能转为唯一对应的二叉树

### 性质

- 二叉树的第i层上至多有$2^{(i-1)}$个结点
- 深度为k的二叉树至多有$2^k-1$个结点
- 对于任何一棵二叉树，若2度的结点树有$n_2$个，则必有叶子数$n_0=n_2+1$
- 满二叉树：深度为k，有$2^k-1$个结点的二叉树
- 完全二叉树：深度为k，只有最后一层节点不满且全部集中在左边，允许底层在右边缺少连续若干节点
- 满二叉树是完全二叉树的一个特例，两种形式可以实现顺序存储
- 具有n个结点的完全二叉树深度必为$\lfloor \log_2 x \rfloor+1$
- 对完全二叉树，若从上至下从左至右进行1至n的编号，编号为i的结点，左孩子编号必为2i，右孩子编号必为2i+1，双亲编号为i/2

### 顺序存储

    节点间关系蕴含在存储位置中  
    浪费空间，适合满二叉树与完全二叉树

### 链式存储

- lchild,data,rchild

```cpp
typedef struct BiNode{
    TElemType data;
    struct BiNode *lchild,*rchild;
}BiNode,*BiTree;
```

- parent,lchild,data,rchild

```cpp
typedef struct TriTNode
{
    TElemType data;
    struct TriTNode *lchild,*parent,*rchild;
}TriTNode,*TriTree;
```

### 遍历

- 先序遍历DLR，先根再左再右

```cpp
Status PreOrderTraverse(BiTree T){
    if(T==NULL)return OK;
    else{
        cout<<T->data;
        PreOrderTraverse(T->lchild);
        PreOrderTraverse(T->rchild);
    }
}
```

- 中序遍历LDR，先左再根再右

```cpp
Status InOrderTraverse(BiTree T){
    if(T==NULL) return OK; //空二叉树
    else{
        InOrderTraverse(T->lchild); //递归遍历左子树
        cout<<T->data; //访问根结点
        InOrderTraverse(T->rchild); //递归遍历右子树
    }
}
```

- 后序遍历LRD，先左再右再根

```cpp
Status PostOrderTraverse(BiTree T){
    if(T==NULL) return OK; //空二叉树
    else{
        PostOrderTraverse(T->lchild); //递归遍历左子树
        PostOrderTraverse(T->rchild); //递归遍历右子树
        cout<<T->data; //访问根结点
    }
}
```

- **上述的左，右，根为遍历左子树，右子树，根**
- 三种算法的访问路径相同，只是访问结点的时机不同，每个结点访问三次

#### 应用场景

- 建立二叉树的存储结构

```cpp
void CreateBiTree(BiTree &T){
    cin>>ch;
    if(ch =='#') T=NULL;
    else{
        T = new BiTNode; T->data=ch;
        CreateBiTree(T->lchild);
        CreateBiTree(T->rchild);
    }
}
```

同时知道先序序列与中序序列时

```cpp
void CrtBT(BiTree& T, char pre[], char ino[],int ps, int is, int n ) {
// 已知pre[ps..ps+n-1]为二叉树的先序序列，
// ino[is..is+n-1]为二叉树的中序序列，
// 本算法由此两个序列构造二叉链表
    if (n==0) T=NULL;
    else {
        k=Search(ino[], pre[ps]); // 在中序序列中查询
        if (k== -1) T=NULL;
        else { }
    } 
} 

T = (BiTNode*)malloc(sizeof(BiTNode));
T->data = pre[ps];
if (k==is) T->lchild = NULL;
else CreBT(T->lchild, pre[], ino[], ps+1, is, k-is);
if(k == is+n-1) T->rchild = NULL;
else CreBT(T->rchild, pre[], ino[], ps+1+(k-is), k+1, n-(k-is)-1);
```

- 统计二叉树中总结点的个数

```cpp
int NodeCount(BiTree T){
    if (T==NULL) return 0;
    else return NodeCount(T->lchild)+NodeCount(T->rchild)+1;
}
```

- 计算二叉树中叶子结点总数  

```cpp
int LeafCount(BiTree T){
    if(T==NULL)
        return 0;
    if(T->lchild == NULL && T->rchild == NULL)
        return 1;
    else return LeafCount(T->lchild)+LeafCount(T->rchild)
}
```

- 求二叉树的深度

```cpp
int Depth(BiTree T){
    if(T == NULL)
        return 0;
    else return 1+MAX(Depth(T->lchild),Depth(T->rchild))
}
```

- 复制二叉树

```cpp
void Copy(BiTree T, BiTree &NewT ) {
    if (T= NULL) {
        NewT=NULL; return;
    }
    else {
        NewT=new BiTNode;
        NewT->data=T->data;
        Copy (T->lchild, NewT->lchild );
        Copy (T->rchild, NewT->rchild );
    }
}
```

### 线索化二叉树

```cpp
typedef struct BiThrNode{
    TElemType data;
    struct BiThrNode *lchild, *rchild;
    int LTag,RTag;
}BiThrNode,*BiThrTree;
```

    ltag=0时，lchild指向左孩子
    ltag=1时，lchild指向其前驱域
    rtag=0时，rchild指向右孩子
    rtag=1时，rchild指向后继
    建立线索链表时，附设指针pre，始终保持指针pre指向当前访问的指针p所指结点的前驱

线索化中序搜索二叉树

```cpp
void InThreading(BiThrNode *p, BiThrNode *&pre) {
    if (p!=NULL) { // 对以p为根的非空二叉树进行线索化
        InThreading(p->lchild, pre); // 左子树线索化
        if (p->lchild==NULL) // 建前驱线索
        { p->LTag = 1; p->lchild = pre; }
        if (pre->rchild==NULL) // 建后继线索
        { pre->RTag = 1; pre->rchild = p; }
        pre = p; // 保持 pre 指向 p 的前驱
        InThreading(p->rchild, pre); // 右子树线索化
    } // if
} // InThreading
```

线索二叉树的遍历

```cpp
void InOrderTraverse_Thr(BiThrTree T) {
    BiThrNode *p;
    p = T->lchild; // p指向根结点
    while (p != T) { // 空树或遍历结束时，p==T
        while (p->LTag==0) p = p->lchild; // 第一个结点
        cout<<p->data;
        while (p->RTag==1 && p->rchild!=T) {
            p = p->rchild; cout<<p->data; // 访问后继结点
        }
        p = p->rchild; // p进至其右子树根
    }
}
```

## 树的表示方法

### 双亲表示法

    以一组连续的存储单元来存放树中的结点，每个结点有data域和parent域，data存放结点信息，parent存放双亲位置。  
    找双亲方便，找孩子难。

```cpp
typedef struct{
    TElemType data;
    int Parent;
}PTNode;
typedef struct{
    PTNode nodes[MAXSIZE];  //结点数组
    int r,n;  //根的位置和结点数
}PTree;
```

### 孩子表示法

    将一个结点所有孩子链接成一个单链表形，而树中有若干个结点，故有若干个单链表，每个单链表有一个表头结点，所有表头结点用一个数组来描述。  
    找孩子方便，找双亲难。

```cpp
typedef struct CTNode{
    int child;
    struct CTNode *next;
}*ChildPtr;
typedef struct {
    TElemType data;
    ChildPtr firstchild ;
}CTBox;
typedef struct {
    CTBox nodes[maxsize];
    int r,n;
}CTree;
```

### 孩子-双亲表示法

    表头结点中有三个域，分别为data，双亲位置，孩子。

### 孩子-兄弟表示法

    链表中结点的两个指针域分别指向该结点的第一个孩子结点和下一个兄弟结点。

```cpp
typedef struct CSNode{
    ElemType data;
    struct CSNode *firstchild, *nextsibling;
}CSNode,*CSTree;
```

    树的孩子兄弟链表结构与二叉树的二叉链表结构，都以二叉链表作为存储结构，它们的物理结构完全相同；

## 树转换为二叉树

**树和二叉树之间必然存在一一对应关系**

1. 将树中同一结点的兄弟相连
2. 保留结点的最左孩子连线，删除其他孩子连线
3. 将同一孩子的连线绕左孩子旋转45度
**目的时利用二叉树的算法解决树的相关问题**

## 深度优先遍历

### 先根次序遍历

- 对应先序遍历
- 访问树的根结点
- 先跟次序遍历根的第一棵子树
- 先跟次序遍历根的第二棵子树、第三棵...直到遍历完整棵树

### 后根次序遍历

- 对应中序遍历
- 后跟次序遍历根的第一棵子树
- 后跟次序遍历跟的第二棵子树、第三棵子树...直到遍历完所有子树
- 访问根结点

## 层次遍历

- 访问层次为1的根结点
- 自左向右顺序访问层次为2的各个结点
- 自左向右顺序访问层次为3的各个结点
- 直到所有的结点都访问完

## 哈夫曼树与哈夫曼编码

    采用二叉树涉及前缀编码  
    分解接受字符串：遇到0向左，遇到1向右，到达叶子结点则翻译出一个字符，反复由根出发，直到译码完成

- 路径：从树中的一个结点到另一个结点之间的分支构成这两个结点间的路 径
- 路径长度：路径上的分支数目称为路径长度
- 结点的权：给树中结点所赋的具有物理意义的值
- 结点的带权路径长度：从根到该结点的路径长度与该结点权的乘积
- 树的带权路径长度：树中所有叶子结点的带权路径长度之和，记作$WPL = \Sigma(w_i*L_i)$
- 最优二叉树(哈夫曼树)：假设有n个权值，构造有n个叶子结点的二叉树，每个叶子结点有一个$w_i$作为它的权值，则带权路径长度最小的二叉树成为哈夫曼树

### 哈夫曼树的构造过程

    使权大的结点靠近根  
    对权值的合并、删除与替换总是合并当前值最小的两个

- 根据给定的n个权值{w1,w2,……,wn}，构造n棵只有根结点的二叉树。
- 在森林中选取两棵根结点权值最小的树作左右子树，构造一棵新的二叉树，置新二叉树根结点权值为其左右子树根结点权值之和。
- 在森林中删除这两棵树，同时将新得到的二叉树加入森林中。
- 重复上述两步，直到只含一棵树为止，这棵树即哈夫曼树。
