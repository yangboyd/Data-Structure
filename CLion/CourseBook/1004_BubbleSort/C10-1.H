#ifndef C10_1_H
#define C10_1_H

#include "c1.h"
#include "c9.h"

#define N 8

typedef int InfoType; /* 定义其它数据项的类型 */

 /* c10-1.h 待排记录的数据类型 */
 #define MAXSIZE 20 /* 一个用作示例的小顺序表的最大长度 */
 typedef int KeyType; /* 定义关键字类型为整型 */
 typedef struct
 {
   KeyType key; /* 关键字项 */
   InfoType otherinfo; /* 其它数据项，具体类型在主程中定义 */
 }RedType; /* 记录类型 */

 typedef struct
 {
   RedType r[MAXSIZE+1]; /* r[0]闲置或用作哨兵单元 */
   int length; /* 顺序表长度 */
 }SqList; /* 顺序表类型 */

void InsertSort(SqList *L);
void BInsertSort(SqList *L);
void P2_InsertSort(SqList *L);

 #endif