/* algo9-1.c 检验bo9-1.c(顺序表部分)的程序 */
#include "c9-1.h"

ElemType r[N] = { {'A',1},{'B',1},{'C',2},{'D',5},{'E',3},
			   {'F',4},{'G',4},{'H',3},{'I',5} }; /* 数据元素(以教科书例9-1为例),全局变量 */
int sw[N + 1]; /* 累计权值，全局变量 */

Status SecondOptimal(BiTree *T, ElemType R[], int sw[], int low, int high)
{ /* 由有序表R[low..high]及其累计权值表sw(其中sw[0]==0)递归构造 */
	/* 次优查找树T。算法9.3 */
	int i, j;
	double min, dw;
	i = low;
	min = fabs(sw[high] - sw[low]);
	dw = sw[high] + sw[low - 1];
	for (j = low + 1; j <= high; ++j) /* 选择最小的△Pi值 */
		if (fabs(dw - sw[j] - sw[j - 1]) < min)
		{
			i = j;
			min = fabs(dw - sw[j] - sw[j - 1]);
		}
	*T = (BiTree)malloc(sizeof(BiTNode));
	if (!*T)
		return ERROR;
	(*T)->data = R[i]; /* 生成结点 */
	if (i == low)
		(*T)->lchild = NULL; /* 左子树空 */
	else
		SecondOptimal(&(*T)->lchild, R, sw, low, i - 1); /* 构造左子树 */
	if (i == high)
		(*T)->rchild = NULL; /* 右子树空 */
	else
		SecondOptimal(&(*T)->rchild, R, sw, i + 1, high); /* 构造右子树 */
	return OK;
}

void FindSW(int sw[], SSTable ST)
{ /* 按照有序表ST中各数据元素的Weight域求累计权值表sw */
	int i;
	sw[0] = 0;
	for (i = 1; i <= ST.length; i++)
		sw[i] = sw[i - 1] + ST.elem[i].weight;
}

typedef BiTree SOSTree; /* 次优查找树采用二叉链表的存储结构 */
Status CreateSOSTree(SOSTree *T, SSTable ST)
{ /* 由有序表ST构造一棵次优查找树T。ST的数据元素含有权域weight。算法9.4 */
	if (ST.length == 0)
		*T = NULL;
	else
	{
		FindSW(sw, ST); /* 按照有序表ST中各数据元素的Weight域求累计权值表sw */
		SecondOptimal(T, ST.elem, sw, 1, ST.length);
	}
	return OK;
}

Status Search_SOSTree(SOSTree *T, KeyType key)
{ /* 在次优查找树T中查找关键字等于key的元素。找到则返回OK，否则返回FALSE */
	while (*T) /* T非空 */
		if ((*T)->data.key == key)
			return OK;
		else if ((*T)->data.key > key)
			*T = (*T)->lchild;
		else
			*T = (*T)->rchild;
	return FALSE; /* 顺序表中不存在待查元素 */
}

void print(ElemType c) /* Traverse()调用的函数 */
{
	printf("(%c %d) ", c.key, c.weight);
}



// 图形化输出当前结构内部实现
static void Print(SOSTree T, int row) {
	int k;

	if(T == NULL) {
		return;
	}

	// 访问当前结点
	printf("%02c(%02d) ", T->data.key,T->data.weight);

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
void PrintTree(SOSTree T) {
	printf("\nSOSTree:\n");
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
	SSTable st;
	SOSTree t;
	Status i;
	KeyType s;
	Creat_Ord(&st, N); /* 由全局数组产生非降序静态查找表st */
	Traverse(st, print);
	CreateSOSTree(&t, st); /* 由有序表构造一棵次优查找树 */
	PrintTree(t);
	printf("\n请输入待查找的字符: ");
	scanf("%c", &s);
	i = Search_SOSTree(&t, s);
	if (i)
		printf("%c的权值是%d\n", s, t->data.weight);
	else
		printf("表中不存在此字符\n");
}
