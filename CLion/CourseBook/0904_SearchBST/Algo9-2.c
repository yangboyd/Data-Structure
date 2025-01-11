/* algo9-2.c 检验bo9-1.(有序表部分)的程序 */
#include "c9-2.h"

void print(ElemType c)
{
	printf("(%d,%d) ", c.key, c.others);
}

// 图形化输出当前结构内部实现
static void Print(BiTree T, int row) {
	int k;

	if(T == NULL) {
		return;
	}

	// 访问当前结点
	printf("%02d(%02d) ", T->data.key,T->data.others);

	Print(T->lchild, row + 1);

	if(T->rchild != NULL) {
		printf("\n");

		for(k = 0; k < row+1; k++) {
			printf("------ ");
		}

		Print(T->rchild, row+1);
	}
}

// 以图形化形式输出当前结构
void PrintTree(BiTree T) {
	printf("\nBiTree:\n");
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
	BiTree dt, p;
	int i;
	KeyType j;
	ElemType r[N] = { {45,1},{12,2},{53,3},{3,4},{37,5},{24,6},{100,7},{61,8},{90,9},{78,10} }; /* 以教科书图9.7(a)为例 */
	InitDSTable(&dt); /* 构造空表 */
	for (i = 0; i < N; i++)
		InsertBST(&dt, r[i]); /* 依次插入数据元素 */
	TraverseDSTable(dt, print);
	PrintTree(dt);
	printf("\n请输入待查找的值: ");
	scanf("%d", &j);
	p = SearchBST(dt, j);
	if (p)
	{
		printf("表中存在此值。");
		DeleteBST(&dt, j);
		printf("删除此值后:\n");
		TraverseDSTable(dt, print);
		printf("\n");
		PrintTree(dt);
	}
	else
		printf("表中不存在此值\n");
	DestroyDSTable(&dt);
}