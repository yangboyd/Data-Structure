#include "c9-2.h"

void print(ElemType c)
{
    printf("(%d,%d)", c.key, c.order);
}
// 图形化输出当前结构内部实现
static void Print(BSTree T, int row) {
    int k;

    if(T == NULL) {
        return;
    }

    // 访问当前结点
    printf("%02d(%02d) ", T->data.key,T->data.order);

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
void PrintTree(BSTree T) {
    printf("\nBSTree:\n");
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
    BSTree dt, p;
    Status k;
    int i;
    KeyType j;
    ElemType r[N] = { {13,1},{24,2},{37,3},{90,4},{53,5} ,{14,6}}; /* (以教科书图9.12为例) */
    InitDSTable(&dt); /* 初始化空树 */
    for (i = 0; i < N; i++)
        InsertAVL(&dt, r[i], &k); /* 建平衡二叉树 */
    TraverseDSTable(dt, print); /* 按关键字顺序遍历二叉树 */
    PrintTree(dt);
    printf("\n请输入待查找的关键字: ");
    scanf("%d", &j);
    p = SearchBST(dt, j); /* 查找给定关键字的记录 */
    if (p)
        print(p->data);
    else
        printf("表中不存在此值");
    printf("\n");
    DestroyDSTable(&dt);
}
