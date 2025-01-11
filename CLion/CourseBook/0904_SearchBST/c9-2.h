
#ifndef C9_2_H
#define C9_2_H

#include "c1.h"
#include "c9.h"

#define N 10 /* 数据元素个数 */
typedef int KeyType; /* 设关键字域为整型 */
typedef struct
{
    KeyType key;
    int others;
} ElemType; /* 数据元素类型 */

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

Status InitDSTable(BiTree *DT);
void DestroyDSTable(BiTree *DT); /* 同bo6-2.c */
BiTree SearchBST(BiTree T,KeyType key);
void SearchBST1(BiTree *T,KeyType key,BiTree f,BiTree *p,Status *flag) ;/* 算法9.5(b)改 */
Status InsertBST(BiTree *T, ElemType e);
void Delete(BiTree *p);
Status DeleteBST(BiTree *T,KeyType key);
void TraverseDSTable(BiTree DT,void(*Visit)(ElemType));

#endif