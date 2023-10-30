# dict.c代码解析
> **首先 什么是redis？**  
> Redis是一个使用ANSI C编写的开源、支持网络、基于内存、分布式、可选持久性的键值对存储数据库。  
> 从2015年6月开始，Redis的开发由Redis Labs赞助，而2013年5月至2015年6月期间，其开发由Pivotal赞助。  
> 根据月度排行网站DB-Engines.com的数据，Redis是最流行的键值对存储数据库。
## 源代码
- dict.c
- dict.h
****
## 初步评价
> redis经过了这么多年的历练，也经历过质疑，也存在本身的缺陷，但是不能不否认，redis仍然是一个极其优秀的工业代码，非常的工整与明了，这也对我们阅读带来了方便。  
> redis现在仍是最流行的key-value类型数据库，为内置型的数据库。  
> redis的的很大优点之一在于实现了很多操作在服务端就可以完成了，这个对客户端而言非常方便。

## redis中基于hash table的字典是如何实现的
> **首先我们应当对字典的层次有一个认知**  
> dictEntry->dict  
> 我们能在dict.h中找到相关代码
### dict相关代码
```c
struct dict {
    dictType *type;

    dictEntry **ht_table[2];
    unsigned long ht_used[2];

    long rehashidx; /* rehashing not in progress if rehashidx == -1 */

    /* Keep small vars at end for optimal (minimal) struct padding */
    int16_t pauserehash; /* If >0 rehashing is paused (<0 indicates coding error) */
    signed char ht_size_exp[2]; /* exponent of size. (size = 1<<exp) */
};
```
ht属性，用于实现渐进式rehash  
rehashidx属性用来记录rehash进度，当rehash没有在进行的时候，rehashidx=-1  
pauserehash属性用于判断是否暂停rehash进程  
type属性是一个指向dictType结构的指针，每个dictType结构保存了一组用于操纵特定类型键值对的函数，而redis会为不同用途的字典设置不同的类型特定函数  
#### dictType相关代码
```c
typedef struct dictType {
    uint64_t (*hashFunction)(const void *key);
    void *(*keyDup)(dict *d, const void *key);
    void *(*valDup)(dict *d, const void *obj);
    int (*keyCompare)(dict *d, const void *key1, const void *key2);
    void (*keyDestructor)(dict *d, void *key);
    void (*valDestructor)(dict *d, void *obj);
    int (*expandAllowed)(size_t moreMem, double usedRatio);
    /* Allow a dictEntry to carry extra caller-defined metadata.  The
     * extra memory is initialized to 0 when a dictEntry is allocated. */
    size_t (*dictEntryMetadataBytes)(dict *d);
} dictType;
```

### dictEntry相关代码
```c
typedef struct dictEntry {
    void *key;
    union {
        void *val;
        uint64_t u64;
        int64_t s64;
        double d;
    } v;
    struct dictEntry *next;     /* Next entry in the same hash bucket. */
    void *metadata[];           /* An arbitrary number of bytes (starting at a
                                 * pointer-aligned address) of size as returned
                                 * by dictType's dictEntryMetadataBytes(). */
} dictEntry;
```
在dict.h中能找到关于dictEntry这一类型的声明，dictEntry是哈希表节点，也就是我们存储数据的地方，其保护的成员有：key,v,next指针。key保存着键值对中的键，v保存着键值对中的值。next是指向另一个哈希表节点的指针。
### 现在我们可以来看redis是如何实现基于hash table的字典的相关操作了
从源码看哈希表包括的成员有table、size、used等。table是一个数组，数组中的每个元素都是一个指向dictEntry结构的指针， 每个dictEntry结构保存着一个键值对；size 属性记录了哈希表table的大小，而used属性则记录了哈希表目前已有节点的数量。  
****

## dict的API
**不难发现，dict的函数实现分为两种，一种是通过宏定义的函数，一种是在dict.c内实现的函数。**  
- dict.h中通过宏定义实现了部分函数
- dict.c中定义了大部分函数
- 由于本人时间和经历有限且课程要求未明确，无法对函数的具体实现与分析一一进行解析，但redis的渐进式rehash是区分于普通rehash的一个过程，将进行分析。

## 渐进式rehash的实现
```c
int dictRehash(dict *d, int n) {
    int empty_visits = n*10; /* Max number of empty buckets to visit. */
    if (!dictIsRehashing(d)) return 0;

    while(n-- && d->ht_used[0] != 0) {
        dictEntry *de, *nextde;

        /* Note that rehashidx can't overflow as we are sure there are more
         * elements because ht[0].used != 0 */
        assert(DICTHT_SIZE(d->ht_size_exp[0]) > (unsigned long)d->rehashidx);
        while(d->ht_table[0][d->rehashidx] == NULL) {
            d->rehashidx++;
            if (--empty_visits == 0) return 1;
        }
        de = d->ht_table[0][d->rehashidx];
        /* Move all the keys in this bucket from the old to the new hash HT */
        while(de) {
            uint64_t h;

            nextde = de->next;
            /* Get the index in the new hash table */
            h = dictHashKey(d, de->key) & DICTHT_SIZE_MASK(d->ht_size_exp[1]);
            de->next = d->ht_table[1][h];
            d->ht_table[1][h] = de;
            d->ht_used[0]--;
            d->ht_used[1]++;
            de = nextde;
        }
        d->ht_table[0][d->rehashidx] = NULL;
        d->rehashidx++;
    }

    /* Check if we already rehashed the whole table... */
    if (d->ht_used[0] == 0) {
        zfree(d->ht_table[0]);
        /* Copy the new ht onto the old one */
        d->ht_table[0] = d->ht_table[1];
        d->ht_used[0] = d->ht_used[1];
        d->ht_size_exp[0] = d->ht_size_exp[1];
        _dictReset(d, 1);
        d->rehashidx = -1;
        return 0;
    }

    /* More to rehash... */
    return 1;
}
```
**以上代码实现了哈希表的重散列，这是一种渐进式的rehash，以下将具体进行分析。**
- 为ht[1]分配了空间。
- 将rehashidx设置为0，代表开始rehash，同时这个rehashidx是递增的。
- 在rehash进行期间，每次操作程序除了执行指定的操作以外，还会将ht[0]哈希表在rehashidx索引上的键值对rehash到ht[1]，当rehash工作完成之后，将rehashidx属性的值+1，表示下一次要迁移的链表所在位置。
- 渐进式rehash将rehash键值对工作分散到了对字典的增删改查，避免了集中式rehash而带来的阻塞问题。

> 以上为关于redis中dict.c,dict.h文件的个人解析。