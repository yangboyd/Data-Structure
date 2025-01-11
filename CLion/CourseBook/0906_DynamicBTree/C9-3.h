#ifndef C9_3_H
#define C9_3_H

#include "c1.h"
#include "c9.h"

#define m 3 /* B树的阶，暂设为3 */
#define N 18 /* 数据元素个数 */
#define MAX 5 /* 字符串最大长度+1 */
typedef int KeyType; /* 设关键字域为整型 */
typedef struct
{
  char info[MAX];
}Others;/* 记录的其它部分 */

/* c9-3.h B树的结点类型 */
 typedef struct
 {
   KeyType key; /* 关键字 */
   Others others; /* 其它部分(由主程定义) */
 }Record; /* 记录类型 */

 typedef struct BTNode
 {
   int keynum; /* 结点中关键字个数，即结点的大小 */
   struct BTNode *parent; /* 指向双亲结点 */
   struct Node /* 结点向量类型 */
   {
     KeyType key; /* 关键字向量 */
     struct BTNode *ptr; /* 子树指针向量 */
     Record *recptr; /* 记录指针向量 */
   }node[m+1]; /* key,recptr的0号单元未用 */
 }BTNode,*BTree; /* B树结点和B树的类型 */

 typedef struct
 {
   BTNode *pt; /* 指向找到的结点 */
   int i; /* 1..m，在结点中的关键字序号 */
   int tag; /* 1:查找成功，O:查找失败 */
 }Result; /* B树的查找结果类型 */

Status InitDSTable(BTree *DT);
void DestroyDSTable(BTree *DT);
int Search(BTree p, KeyType K);
Result SearchBTree(BTree T, KeyType K);
void Insert(BTree *q,int i,Record *r,BTree ap);
void split(BTree *q,BTree *ap);
void NewRoot(BTree *T,Record *r,BTree ap);
void InsertBTree(BTree *T,Record *r,BTree q,int i);
void TraverseDSTable(BTree DT,void(*Visit)(BTNode,int));
void DeleteBTree(BTree *T, KeyType K);
 #endif