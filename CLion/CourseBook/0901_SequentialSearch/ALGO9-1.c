/* algo9-1.c 检验bo9-1.c(顺序表部分)的程序 */
#include "c9-1.h"

void print(ElemType c) /* Traverse()调用的函数 */
{
	printf("%-8ld%-8s%4d%5d%5d%5d%5d%5d%5d%5d\n", c.number, c.name, c.politics, c.Chinese, c.English, c.math, c.physics, c.chemistry, c.biology, c.total);
}

ElemType r[N] = { {179324,"何芳芳",85,89,98,100,93,80,47},
			   {179325,"陈红",85,86,88,100,92,90,45},
			   {179326,"陆华",78,75,90,80,95,88,37},
			   {179327,"张平",82,80,78,98,84,96,40},
			   {179328,"赵小怡",76,85,94,57,77,69,44} }; /* 全局变量 */

void main()
{
	SSTable st;
	int i, s;
	for (i = 0; i < N; i++) /* 计算总分 */
		r[i].total = r[i].politics + r[i].Chinese + r[i].English + r[i].math + r[i].physics + r[i].chemistry + r[i].biology;

	printf("顺序查找\n");
	Creat_Seq(&st, N); /* 由全局数组产生静态查找表st */
	printf("准考证号  姓名  政治 语文 外语 数学 物理 化学 生物 总分\n");
	Traverse(st, print); /* 按顺序输出静态查找表st */
	printf("请输入待查找人的总分: ");
	scanf("%d", &s);
	i = Search_Seq(st, s); /* 顺序查找 */
	if (i)
		print(*(st.elem + i));
	else
		printf("没找到\n");
	Destroy(&st);

	printf("二分查找\n");

	SSTable ot;
	Creat_Ord(&ot,N);
	Traverse(ot, print); /* 按顺序输出静态查找表st */
	printf("请输入待查找人的总分: ");
	scanf("%d", &s);
	i = Search_Bin(ot, s);
	if (i)
		print(*(ot.elem + i));
	else
		printf("没找到\n");
	Destroy(&ot);
}
