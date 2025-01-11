#include "c9-4.h"

/* bo9-5.c 动态查找表(双链键树)的基本操作 */
Status InitDSTable(DLTree *DT)
{ /* 操作结果: 构造一个空的双链键树DT */
	*DT = NULL;
	return OK;
}

void DestroyDSTable(DLTree *DT)
{ /* 初始条件: 双链键树DT存在。操作结果: 销毁双链键树DT */
	if (*DT) /* 非空树 */
	{
		if ((*DT)->kind == BRANCH && (*DT)->a.first) /* *DT是分支结点且有孩子 */
			DestroyDSTable(&(*DT)->a.first); /* 销毁孩子子树 */
		if ((*DT)->next) /* 有兄弟 */
			DestroyDSTable(&(*DT)->next); /* 销毁兄弟子树 */
		free(*DT); /* 释放根结点 */
		*DT = NULL; /* 空指针赋0 */
	}
}

Record *SearchDLTree(DLTree T, KeysType K)
{ /* 在非空双链键树T中查找关键字等于K的记录，若存在， */
  /* 则返回指向该记录的指针，否则返回空指针。算法9.15，有改动 */
	DLTree p;
	int i;
	if (T)
	{
		p = T; /* 初始化 */
		i = 0;
		while (p&&i < K.num)
		{
			while (p&&p->symbol != K.ch[i]) /* 查找关键字的第i位 */
				p = p->next;
			if (p&&i < K.num) /* 准备查找下一位 */
				p = p->a.first;
			++i;
		} /* 查找结束 */
		if (!p) /* 查找不成功 */
			return NULL;
		else /* 查找成功 */
			return p->a.infoptr;
	}
	else
		return NULL; /* 树空 */
}

void InsertDSTable(DLTree *DT, Record *r)
{ /* 初始条件: 双链键树DT存在，r为待插入的数据元素的指针 */
  /* 操作结果: 若DT中不存在其关键字等于(*r).key.ch的数据元素， */
  /*           则按关键字顺序插r到DT中 */
	DLTree p = NULL, q = NULL, ap;
	int i = 0;
	KeysType K = r->key;
	if (!*DT&&K.num) /* 空树且关键字符串非空 */
	{
		*DT = ap = (DLTree)malloc(sizeof(DLTNode));
		for (; i < K.num; i++) /* 插入分支结点 */
		{
			if (p)
				p->a.first = ap;
			ap->next = NULL;
			ap->symbol = K.ch[i];
			ap->kind = BRANCH;
			p = ap;
			ap = (DLTree)malloc(sizeof(DLTNode));
		}
		p->a.first = ap; /* 插入叶子结点 */
		ap->next = NULL;
		ap->symbol = Nil;
		ap->kind = LEAF;
		ap->a.infoptr = r;
	}
	else /* 非空树 */
	{
		p = *DT; /* 指向根结点 */
		while (p&&i < K.num)
		{
			while (p&&p->symbol < K.ch[i]) /* 沿兄弟结点查找 */
			{
				q = p;
				p = p->next;
			}
			if (p&&p->symbol == K.ch[i]) /* 找到与K.ch[i]相符的结点 */
			{
				q = p;
				p = p->a.first; /* p指向将与K.ch[i+1]比较的结点 */
				++i;
			}
			else /* 没找到,插入关键字 */
			{
				ap = (DLTree)malloc(sizeof(DLTNode));
				if (q->a.first == p)
					q->a.first = ap; /* 在长子的位置插入 */
				else /* q->next==p */
					q->next = ap; /* 在兄弟的位置插入 */
				ap->next = p;
				ap->symbol = K.ch[i];
				ap->kind = BRANCH;
				p = ap;
				ap = (DLTree)malloc(sizeof(DLTNode));
				i++;
				for (; i < K.num; i++) /* 插入分支结点 */
				{
					p->a.first = ap;
					ap->next = NULL;
					ap->symbol = K.ch[i];
					ap->kind = BRANCH;
					p = ap;
					ap = (DLTree)malloc(sizeof(DLTNode));
				}
				p->a.first = ap; /* 插入叶子结点 */
				ap->next = NULL;
				ap->symbol = Nil;
				ap->kind = LEAF;
				ap->a.infoptr = r;
			}
		}
	}
}


/* bo3-1.c 顺序栈（存储结构由c3-1.h定义）的基本操作（9个） */
Status InitStack(SqStack *S)
{ /* 构造一个空栈S */
	(*S).base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!(*S).base)
		exit(OVERFLOW); /* 存储分配失败 */
	(*S).top=(*S).base;
	(*S).stacksize=STACK_INIT_SIZE;
	return OK;
}

Status DestroyStack(SqStack *S)
{ /* 销毁栈S，S不再存在 */
	free((*S).base);
	(*S).base=NULL;
	(*S).top=NULL;
	(*S).stacksize=0;
	return OK;
}

Status ClearStack(SqStack *S)
{ /* 把S置为空栈 */
	(*S).top=(*S).base;
	return OK;
}

Status StackEmpty(SqStack S)
{ /* 若栈S为空栈，则返回TRUE，否则返回FALSE */
	if(S.top==S.base)
		return TRUE;
	else
		return FALSE;
}

int StackLength(SqStack S)
{ /* 返回S的元素个数，即栈的长度 */
	return S.top-S.base;
}

Status GetTop(SqStack S,SElemType *e)
{ /* 若栈不空，则用e返回S的栈顶元素，并返回OK；否则返回ERROR */
	if(S.top>S.base)
	{
		*e=*(S.top-1);
		return OK;
	}
	else
		return ERROR;
}

Status Push(SqStack *S,SElemType e)
{ /* 插入元素e为新的栈顶元素 */
	if((*S).top-(*S).base>=(*S).stacksize) /* 栈满，追加存储空间 */
	{
		(*S).base=(SElemType *)realloc((*S).base,((*S).stacksize+STACKINCREMENT)*sizeof(SElemType));
		if(!(*S).base)
			exit(OVERFLOW); /* 存储分配失败 */
		(*S).top=(*S).base+(*S).stacksize;
		(*S).stacksize+=STACKINCREMENT;
	}
	*((*S).top)++=e;
	return OK;
}

Status Pop(SqStack *S,SElemType *e)
{ /* 若栈不空，则删除S的栈顶元素，用e返回其值，并返回OK；否则返回ERROR */
	if((*S).top==(*S).base)
		return ERROR;
	*e=*--(*S).top;
	return OK;
}

Status StackTraverse(SqStack S,Status(*visit)(SElemType))
{ /* 从栈底到栈顶依次对栈中每个元素调用函数visit()。 */
	/* 一旦visit()失败，则操作失败 */
	while(S.top>S.base)
		visit(*S.base++);
	printf("\n");
	return OK;
}

void TraverseDSTable(DLTree DT, void(*Vi)(Record))
{ /* 初始条件: 双链键树DT存在，Vi是对结点操作的应用函数， */
  /*           ViR是对记录操作的应用函数 */
  /* 操作结果: 按关键字的顺序输出关键字及其对应的记录 */
	SqStack s;
	SElemType e;
	DLTree p;
	int i = 0, n = 8;
	if (DT)
	{
		InitStack(&s);
		e.p = DT;
		e.ch = DT->symbol;
		Push(&s, e);
		p = DT->a.first;
		while (p->kind == BRANCH) /* 分支结点 */
		{
			e.p = p;
			e.ch = p->symbol;
			Push(&s, e);
			p = p->a.first;
		}
		e.p = p;
		e.ch = p->symbol;
		Push(&s, e);
		Vi(*(p->a.infoptr));
		i++;
		while (!StackEmpty(s))
		{
			Pop(&s, &e);
			p = e.p;
			if (p->next) /* 有兄弟结点 */
			{
				p = p->next;
				while (p->kind == BRANCH) /* 分支结点 */
				{
					e.p = p;
					e.ch = p->symbol;
					Push(&s, e);
					p = p->a.first;
				}
				e.p = p;
				e.ch = p->symbol;
				Push(&s, e);
				Vi(*(p->a.infoptr));
				i++;
				if (i%n == 0)
					printf("\n"); /* 输出n个元素后换行 */
			}
		}
	}
}
