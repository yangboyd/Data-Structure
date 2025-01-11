#ifndef C10_1_H
#define C10_1_H

#include "c1.h"
#include "c9.h"


typedef int InfoType; /* 定义其它数据项的类型 */

#define MAXKEY INT_MAX
#define RUNEND_SYMBOL INT_MAX
#define w 6 /* 内存工作区可容纳的记录个数 */
#define M 10 /* 设输出M个数据换行 */
#define N 24 /* 设大文件有N个数据 */

typedef int LoserTree[w]; /* 败者树是完全二叉树且不含叶子，可采用顺序存储结构 */


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
    RedType rec; /* 记录 */
    KeyType key; /* 从记录中抽取的关键字 */
    int rnum; /* 所属归并段的段号 */
}RedNode, WorkArea[w]; /* 内存工作区，容量为w */

 typedef struct
 {
   RedType r[MAXSIZE+1]; /* r[0]闲置或用作哨兵单元 */
   int length; /* 顺序表长度 */
 }SqList; /* 顺序表类型 */



 #endif