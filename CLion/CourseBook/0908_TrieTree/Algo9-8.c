/* algo9-8.c 检验bo9-6.c的程序 */
#include "c9-5.h"

Status pr(Record *r)
{
	printf("(%s,%d)", r->key.ch, r->others.ord);
	return OK;
}

// 图形化输出当前结构内部实现
static void Print(TrieTree T, int row) {
	int k;
	int i;
	TrieTree p;

	if(T == NULL) {
		return;
	}

	// 访问当前结点
	if (T->kind==BRANCH)
	{
		for(i=0;i<LENGTH;i++)
		{
			p=T->a.bh.ptr[i];
			if (p)
			{
				printf("\n");
				for(k = 0; k < row; k++) {
					printf("- ");
				}
			}
			if(p&&p->kind==LEAF)
			{
				pr(p->a.lf.infoptr);
			}
			else if(p&&p->kind==BRANCH)
			{
				printf("%c ",'A'+i-1);
				Print(p, row+1);
			}
		}
	}
	else
	{
		pr(p->a.lf.infoptr);
	}


}

// 以图形化形式输出当前结构
void PrintTree(TrieTree T) {
	printf("\nTrieTree:\n");
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
	TrieTree t;
	int i;
	char s[MAXKEYLEN + 1];
	KeysType k;
	Record *p;
	Record r[N] = { {{"CAI"},1},{{"CAO"},2},{{"LI"},3},{{"LAN"},4},
				 {{"CHA"},5},{{"CHANG"},6},{{"WEN"},7},{{"CHAO"},8},
				 {{"YUN"},9},{{"YANG"},10},{{"LONG"},11},{{"WANG"},12},
				 {{"ZHAO"},13},{{"LIU"},14},{{"WU"},15},{{"CHEN"},16} };
	/* 数据元素(以教科书式9-24为例) */
	InitDSTable(&t);
	for (i = 0; i < N; i++)
	{
		r[i].key.num = strlen(r[i].key.ch) + 1;
		r[i].key.ch[r[i].key.num] = Nil; /* 在关键字符串最后加结束符 */
		p = SearchTrie(t, r[i].key);
		if (!p)
			InsertTrie(&t, &r[i]);
	}
	printf("按关键字符串的顺序遍历Trie树(键树):\n");
	TraverseDSTable(t, pr);
	PrintTree(t);
	printf("\n请输入待查找记录的关键字符串: ");
	scanf("%s", s);
	k.num = strlen(s) + 1;
	strcpy(k.ch, s);
	k.ch[k.num] = Nil; /* 在关键字符串最后加结束符 */
	p = SearchTrie(t, k);
	if (p)
		pr(p);
	else
		printf("没找到");
	printf("\n");
	DestroyDSTable(&t);
}
