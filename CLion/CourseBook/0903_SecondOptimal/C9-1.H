#ifndef C9_1_H
#define C9_1_H

#include "c1.h"
#include "c9.h"

#define N 9 /* 数据元素个数 */
typedef char KeyType; /* 设关键字域为字符型 */
typedef struct /* 数据元素类型 */
{
    KeyType key;
    int weight;
}ElemType;

typedef ElemType TElemType;

/* c9-2.h 平衡二叉树的类型 */
typedef struct BSTNode
{
    ElemType data;
    int bf; /* 结点的平衡因子 */
    struct BSTNode *lchild,*rchild; /* 左、右孩子指针 */
}BSTNode,*BSTree;

/* c6-2.h 二叉树的二叉链表存储表示 */
typedef struct BiTNode
{
    TElemType data;
    struct BiTNode *lchild,*rchild; /* 左右孩子指针 */
}BiTNode,*BiTree;

#define total key /* 定义总分(total)为关键字 */

/* c9-1.h 静态查找表的顺序存储结构 */
 typedef struct SSTable
 {
   ElemType *elem; /* 数据元素存储空间基址，建表时按实际长度分配，0号单元留空 */
   int length; /* 表长度 */
 }SSTable;


extern ElemType r[N];

Status Creat_Ord(SSTable *ST,int n);
Status Destroy(SSTable *ST);
Status Creat_Seq(SSTable *ST,int n);
Status Traverse(SSTable ST,void(*Visit)(ElemType));
int Search_Seq(SSTable ST,KeyType key);
int Search_Bin(SSTable ST,KeyType key);

#endif