#include "c10-1.h"

int Partition(SqList *L, int low, int high)
{ /* 交换顺序表L中子表L.r[low..high]的记录，使枢轴记录到位， */
  /* 并返回其所在位置，此时在它之前(后)的记录均不大(小)于它。算法10.6(a) */
  RedType t;
  KeyType pivotkey;
  pivotkey = (*L).r[low].key; /* 用子表的第一个记录作枢轴记录 */
  while (low < high)
  { /* 从表的两端交替地向中间扫描 */
    while (low < high && (*L).r[high].key >= pivotkey)
      --high;
    t = (*L).r[low]; /* 将比枢轴记录小的记录交换到低端 */
    (*L).r[low] = (*L).r[high];
    (*L).r[high] = t;
    while (low < high && (*L).r[low].key <= pivotkey)
      ++low;
    t = (*L).r[low]; /* 将比枢轴记录大的记录交换到高端 */
    (*L).r[low] = (*L).r[high];
    (*L).r[high] = t;
  }
  return low; /* 返回枢轴所在位置 */
}

/* bo10-2.c 快速排序的函数 */
 void QSort(SqList *L,int low,int high)
 { /* 对顺序表L中的子序列L.r[low..high]作快速排序。算法10.7 */
   int pivotloc;
   if(low<high)
   { /* 长度大于1 */
     pivotloc=Partition(L,low,high); /* 将L.r[low..high]一分为二 */
     QSort(L,low,pivotloc-1); /* 对低子表递归排序，pivotloc是枢轴位置 */
     QSort(L,pivotloc+1,high); /* 对高子表递归排序 */
   }
 }

 void QuickSort(SqList *L)
 { /* 对顺序表L作快速排序。算法10.8 */
   QSort(L,1,(*L).length);
 }

 void print(SqList L)
 {
   int i;
   for(i=1;i<=L.length;i++)
     printf("(%d,%d)",L.r[i].key,L.r[i].otherinfo);
   printf("\n");
 }