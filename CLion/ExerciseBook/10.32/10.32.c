#include <stdio.h>
#include "SequenceListType.h"//**▲10 内部排序**//

/* 函数原型 */
void Algo_10_32(SqList_sort *L, int low, int high);
void PrintKey(KeyType e);

int main(int argc, char *argv[])
{	
	FILE *fp;
	SqList_sort L;
	
	printf("创建并输出一个任意序列...\n");
	fp = fopen("TestData.txt", "r");
	CreateSortList(fp, &L);
	Traverse(L, PrintKey);
	printf("\n");	

	printf("重排不同色条按1.2.3的顺序输出...\n");
	Algo_10_32(&L, 1, L.length); 
	Traverse(L, PrintKey);
	printf("\n");	

	return 0;
}

/*━━━━━━━━━━━┓
┃题10.32：荷兰国旗问题 ┃
┗━━━━━━━━━━━*/
void Algo_10_32(SqList_sort *L, int low, int high)
{
	int cur;	
	RcdType tmp;						//辅助空间 
	
	cur = low;
	
	while(cur<=high)					
	{
        while((*L).r[low].key==1)
        {
            low++;
        }
        while((*L).r[high].key==3)
        {
            high--;
        }

		if((*L).r[cur].key==1)			//1代表红色在最前面 
		{
            if(cur>low) {
                tmp = (*L).r[low];
                (*L).r[low] = (*L).r[cur];
                (*L).r[cur] = tmp;
                low++;
            }
			cur++;
		}
		else if((*L).r[cur].key==3)		//3代表蓝色在最后面
		{
            if(cur!=high)
            {
                tmp = (*L).r[high];
                (*L).r[high] = (*L).r[cur];
                (*L).r[cur] = tmp;
            }
			high--;
		}
		else
			cur++;		
	}
}

void PrintKey(KeyType e)
{
	printf("%d ", e);
}
