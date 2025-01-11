
#ifndef C9_2_H
#define C9_2_H

#include "c1.h"
#include "c9.h"

#define N 6 /* 数据元素个数 */
typedef char KeyType; /* 设关键字域为字符型 */
typedef struct
{
    KeyType key;
    int order;
}ElemType; /* 数据元素类型 */

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

Status InitDSTable(BSTree *DT); /* 同bo6-2.c */
void DestroyDSTable(BSTree *DT); /* 同bo6-2.c */
BSTree SearchBST(BSTree T,KeyType key);
void R_Rotate(BSTree *p);
void L_Rotate(BSTree *p);
void LeftBalance(BSTree *T);
void RightBalance(BSTree *T);
Status InsertAVL(BSTree *T,ElemType e,Status *taller);
void TraverseDSTable(BSTree DT,void(*Visit)(ElemType));

#endif