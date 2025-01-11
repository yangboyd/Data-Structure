#ifndef C9_1_H
#define C9_1_H

#include "c1.h"
#include "c9.h"

#define N 5 /* 数据元素个数 */
typedef int KeyType; /* 设关键字域为整型 */
typedef struct ElemType/* 数据元素类型(以教科书图9.1高考成绩为例) */
{
    long number; /* 准考证号 */
    char name[9]; /* 姓名(4个汉字加1个串结束标志) */
    int politics; /* 政治 */
    int Chinese; /* 语文 */
    int English; /* 英语 */
    int math; /* 数学 */
    int physics; /* 物理 */
    int chemistry; /* 化学 */
    int biology; /* 生物 */
    KeyType key; /* 关键字类型应为KeyType,域名应为key,与bo9-1.c中一致 */
} ElemType;

#define total key /* 定义总分(total)为关键字 */

/* c9-1.h 静态查找表的顺序存储结构 */
 typedef struct SSTable
 {
   ElemType *elem; /* 数据元素存储空间基址，建表时按实际长度分配，0号单元留空 */
   int length; /* 表长度 */
 }SSTable;

extern ElemType r[N];

Status Creat_Ord(SSTable *ST,int n);
Status Destroy(SSTable *ST);
Status Creat_Seq(SSTable *ST,int n);
Status Traverse(SSTable ST,void(*Visit)(ElemType));
int Search_Seq(SSTable ST,KeyType key);
int Search_Bin(SSTable ST,KeyType key);

#endif