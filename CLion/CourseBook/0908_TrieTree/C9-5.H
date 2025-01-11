#ifndef C9_5_H
#define C9_5_H

#include "c1.h"

#define Nil ' ' /* 定义结束符为空格(与教科书不同) */

#define N 16 /* 数据元素个数 */
#define LENGTH 27 /* 结点的最大度+1(大写英文字母) */
typedef struct
{
  int ord;
}Others; /* 记录的其它部分 */

/* c9-5.h Trie键树类型 */
 #define MAXKEYLEN 16 /* 关键字的最大长度，同c9-4.h */
 typedef struct
 {
   char ch[MAXKEYLEN]; /* 关键字 */
   int num; /* 关键字长度 */
 }KeysType; /* 关键字类型，同c9-4.h */

 typedef struct
 {
   KeysType key; /* 关键字 */
   Others others; /* 其它部分(由主程定义) */
 }Record; /* 记录类型，同c9-4.h */

 typedef enum{LEAF,BRANCH}NodeKind; /* 结点种类:{叶子,分支}，同c9-4.h */

 typedef struct TrieNode /* Trie键树类型 */
 {
   NodeKind kind;
   union
   {
     struct /* 叶子结点 */
     {
       KeysType K;
       Record *infoptr;
     }lf;
     struct /* 分支结点 */
     {
       struct TrieNode *ptr[LENGTH]; /* LENGTH为结点的最大度+1,在主程定义 */
     /*  int num; 改 */
     }bh;
   }a;
 }TrieNode,*TrieTree;

 /* 对两个字符串型关键字的比较约定为如下的宏定义 */
 #define EQ(a,b) (!strcmp((a),(b)))
 #define LT(a,b) (strcmp((a),(b))<0)
 #define LQ(a,b) (strcmp((a),(b))<=0)

Status InitDSTable(TrieTree *T);
void TraverseDSTable(TrieTree T,Status(*Vi)(Record*));
void DestroyDSTable(TrieTree *T);
void InsertTrie(TrieTree *T,Record *r);
void TraverseDSTable(TrieTree T,Status(*Vi)(Record*));
Record *SearchTrie(TrieTree T,KeysType K);

 #endif