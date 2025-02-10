#include <stdio.h>

/* 结点数量 */
#define N 15

/*
 * 求符合题意的整数值
 */
int Algo_6_35(char* BiTree, int i, int ret, int base);


int main(int argc, char* argv[]) {
    // 顺序存储的二叉树(结点从0号单元开始存储)
    char BiTree[N] = {'A', 'B', 'C', 'D', 'E', 'F', '\0', 'G', '\0', 'H', 'I', '\0', 'J', '\0', '\0'};
    int i, j;
    
    printf("作为示例，建立二叉树的顺序存储结构（^代表空字符，即此处没有结点信息）：ABCDEF^G^HI^J^^");
    printf("\n");
    
    printf("请输入结点索引(0~%d)：", N);
    scanf("%d", &i);
    printf("\n");
    
    j = Algo_6_35(BiTree, i,0,1);
    
    if(j != -1) {
        printf("结点 %d 对应的十进制整数为 %d 。\n", i, j);
    } else {
        printf("此处结点不存在！\n");
    }
    
    return 0;
}


/*
 * 求符合题意的整数值
 */
int Algo_6_35(char* BiTree, int i, int ret, int base) {
    if(BiTree[i] == '\0') {
        return -1;  // 此处不存在结点
    }

    int nret=ret;
    if(0==(i%2))
    {
        nret=base+ret;
    }
    else
    {
        nret=ret;
    }

    if(0==i)
    {
        return nret;
    }
    else
    {
        int j=(i-1)/2;
        int nbase=base*2;
        return Algo_6_35(BiTree, j, nret, nbase);
    }
}
