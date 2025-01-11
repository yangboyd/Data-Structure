#ifndef C10_1_H
#define C10_1_H

#include "c1.h"
#include "c9.h"

// #define k 5 /* k路归并 */
#define k 3 /* k路归并 */
 #define N 3 /* 设每小个文件有N个数据(可将整个文件一次读入内存的称为小文件) */
 #define M 10 /* 设输出M个数据换行 */

#define MINKEY INT_MIN
#define MAXKEY INT_MAX



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


extern FILE *fp[k+1]; /* k+1个文件指针(fp[k]为大文件指针)，全局变量 */
typedef int LoserTree[k]; /* 败者树是完全二叉树且不含叶子，可采用顺序存储结构 */
typedef RedType ExNode,External[k+1]; /* 外结点,有改变 */
External b; /* 全局变量 */
#define MINKEY INT_MIN
#define MAXKEY INT_MAX

void InsertSort(SqList *L);
void BInsertSort(SqList *L);
void P2_InsertSort(SqList *L);


void K_Merge(LoserTree ls,External b);

 #endif