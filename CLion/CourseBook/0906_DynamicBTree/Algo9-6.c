/* algo9-6.c 检验bo9-4.c的程序 */

#include "c9-3.h"


void print(BTNode c, int i) /* TraverseDSTable()调用的函数 */
{
	printf("(%d,%s)", c.node[i].key, c.node[i].recptr->others.info);
}

static void Print(BTree T, int row) {
	int k;

	if(T == NULL) {
		return;
	}
	// if(T->node[0].ptr) /* 有第i棵子树 */
	// {
	// 	printf("\n");
	//
	// 	for(k = 0; k < row+1; k++) {
	// 		printf("------ ");
	// 	}
	// 	Print(T->node[0].ptr,row+1);
	// }

	for(int i=0;i<=T->keynum;i++)
	{
		// 访问当前结点
		if (i>0 && T->node[i].recptr)
		{
			printf("\n");
			for(k = 0; k < row; k++) {
				printf("------ ");
			}
			printf("%02d(%02s) ", T->node[i].key,T->node[i].recptr->others.info);
		}

		if(T->node[i].ptr) /* 有第i棵子树 */
		{
			Print(T->node[i].ptr,row+1);
		}
	}
}

// 以图形化形式输出当前结构
void PrintTree(BTree T) {
	printf("\nBTree:\n");
	// 遇到空树则无需继续计算
	if(T == NULL) {
		printf("\n");
		return;
	}

	Print(T, 0);

	printf("\n");
}

void main()
{
	Record r[N] = { {24,"1"},{45,"2"},{53,"3"},{12,"4"},{37,"5"},
				 {50,"6"},{61,"7"},{90,"8"},{100,"9"},{70,"10"},
				 {3,"11"},{30,"12"},{26,"13"},{85,"14"},{3,"15"},
		 {7,"16"},{6,"5"} ,{5,"4"}}; /* (以教科书中图9.16为例) */
	BTree t;
	Result s;
	int i;
	InitDSTable(&t);
	for (i = 0; i < N; i++)
	{
		s = SearchBTree(t, r[i].key);
		if (!s.tag)
			InsertBTree(&t, &r[i], s.pt, s.i);
	}
	printf("按关键字的顺序遍历B_树:\n");
	TraverseDSTable(t, print);
	PrintTree(t);
	while (TRUE)
	{
		printf("\n请输入待查找记录的关键字: ");
		scanf("%d", &i);
		if (0==i)
		{
			break;
		}
		s = SearchBTree(t, i);
		if (s.tag)
			print(*(s.pt), s.i);
		else
			printf("没找到");
		printf("\n");

		printf("\n删除待查找记录的关键字\n");
		DeleteBTree(&t,  i);
		PrintTree(t);
	}
	DestroyDSTable(&t);
	return;
}
