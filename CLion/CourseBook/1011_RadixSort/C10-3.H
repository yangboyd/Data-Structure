#ifndef C10_3_H
#define C10_3_H

#include "c1.h"
#include "c9.h"

#define N 10
typedef int InfoType; /* 定义其它数据项的类型 */
typedef int KeyType; /* 定义RedType类型的关键字为整型 */
typedef struct
{
  KeyType key; /* 关键字项 */
  InfoType otherinfo; /* 其它数据项 */
}RedType; /* 记录类型(同c10-1.h) */
typedef char KeysType; /* 定义关键字类型为字符型 */

/* c10-3.h 基数排序的数据类型 */
 #define MAX_NUM_OF_KEY 8 /* 关键字项数的最大值 */
 #define RADIX 10 /* 关键字基数，此时是十进制整数的基数 */
 #define MAX_SPACE 1000
 typedef struct
 {
   KeysType keys[MAX_NUM_OF_KEY]; /* 关键字 */
   InfoType otheritems; /* 其它数据项 */
   int next;
 }SLCell; /* 静态链表的结点类型 */

 typedef struct
 {
   SLCell r[MAX_SPACE]; /* 静态链表的可利用空间，r[0]为头结点 */
   int keynum; /* 记录的当前关键字个数 */
   int recnum; /*  静态链表的当前长度 */
 }SLList; /* 静态链表类型 */

 typedef int ArrType[RADIX]; /* 指针数组类型 */

 #endif
