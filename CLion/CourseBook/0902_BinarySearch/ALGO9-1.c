/* algo9-1.c 检验bo9-1.c(顺序表部分)的程序 */
#include "c9-1.h"

ElemType r[N] = { {5,1},{13,2},{19,3},{21,4},{37,5},{56,6},{64,7},{75,8},
	   {80,9},{88,10},{92,11} }; /* 数据元素(以教科书P.219的数据为例),全局变量 */

void print(ElemType c) /* Traverse()调用的函数 */
{
	printf("(%d %d) ", c.key, c.others);
}

void main()
{
	SSTable st;
	int i;
	KeyType s;
	Creat_Ord(&st, N); /* 由全局数组产生非降序静态查找表st */
	Traverse(st, print); /* 顺序输出非降序静态查找表st */
	printf("\n");
	printf("请输入待查找值的关键字: ");
	scanf("%d", &s);
	i = Search_Bin(st, s); /* 折半查找有序表 */
	if (i)
		printf("(%d %d) %d是第%d个记录的关键字\n", st.elem[i].key, st.elem[i].others, s, i);
	else
		printf("没找到\n");
	Destroy(&st);
}
