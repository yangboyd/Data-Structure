#ifndef C9_6_H
#define C9_6_H

#include "c1.h"
#include "c9.h"


#define NULLKEY 0 /* 0为无记录标志 */
#define N 10 /* 数据元素个数 */
typedef int KeyType; /* 设关键字域为整型 */
typedef struct
{
    KeyType key;
    int ord;
}ElemType; /* 数据元素类型 */

 /* c9-6.h 开放定址哈希表的存储结构 */

 typedef struct
 {
   ElemType *elem; /* 数据元素存储基址，动态分配数组 */
   int count; /* 当前数据元素个数 */
   int sizeindex; /* hashsize[sizeindex]为当前容量 */
 }HashTable;

 #define SUCCESS 1
 #define UNSUCCESS 0
 #define DUPLICATE -1

void DestroyHashTable(HashTable *H);
void collision(int *p,int d); /* 线性探测再散列 */
void RecreateHashTable(HashTable *H); /* 重建哈希表 */
void TraverseHash(HashTable H,void(*Vi)(int,ElemType));
Status InitHashTable(HashTable *H);
Status SearchHash(HashTable H,KeyType K,int *p,int *c);
Status InsertHash(HashTable *H,ElemType e);
Status Find(HashTable H,KeyType K,int *p);

 #endif