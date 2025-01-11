#ifndef C9_4_H
#define C9_4_H

#include "c1.h"
#include "c9.h"

#define N 16 /* 数据元素个数 */
typedef struct
{
  int ord;
}Others; /* 记录的其它部分 */
#define Nil ' ' /* 定义结束符为空格(与教科书不同) */

/* c9-4.h 双链树的存储结构 */
 #define MAXKEYLEN 16 /* 关键字的最大长度 */
 typedef struct
 {
   char ch[MAXKEYLEN]; /* 关键字 */
   int num; /* 关键字长度 */
 }KeysType; /* 关键字类型 */

 typedef struct
 {
   KeysType key; /* 关键字 */
   Others others; /* 其它部分(由主程定义) */
 }Record; /* 记录类型 */

 typedef enum{LEAF,BRANCH}NodeKind; /* 结点种类:{叶子,分支} */
 typedef struct DLTNode /* 双链树类型 */
 {
   char symbol;
   struct DLTNode *next; /* 指向兄弟结点的指针 */
   NodeKind kind;
   union
   {
     Record *infoptr; /* 叶子结点的记录指针 */
     struct DLTNode *first; /* 分支结点的孩子链指针 */
   }a;
 }DLTNode,*DLTree;

/* c3-1.h 栈的顺序存储表示 */
#define STACK_INIT_SIZE 10 /* 存储空间初始分配量 */
#define STACKINCREMENT 2 /* 存储空间分配增量 */

typedef struct
{
  char ch;
  DLTree p;
}SElemType; /* 定义栈元素类型 */

typedef struct SqStack
{
  SElemType *base; /* 在栈构造之前和销毁之后，base的值为NULL */
  SElemType *top; /* 栈顶指针 */
  int stacksize; /* 当前已分配的存储空间，以元素为单位 */
}SqStack; /* 顺序栈 */

Status InitDSTable(DLTree *DT);
Status InitStack(SqStack *S);
Status DestroyStack(SqStack *S);
Status ClearStack(SqStack *S);
Status StackEmpty(SqStack S);
Status GetTop(SqStack S,SElemType *e);
Status Push(SqStack *S,SElemType e);
Status Pop(SqStack *S,SElemType *e);
Status StackTraverse(SqStack S,Status(*visit)(SElemType));
void DestroyDSTable(DLTree *DT);
void InsertDSTable(DLTree *DT, Record *r);
void TraverseDSTable(DLTree DT, void(*Vi)(Record));
Record *SearchDLTree(DLTree T, KeysType K);

 #endif