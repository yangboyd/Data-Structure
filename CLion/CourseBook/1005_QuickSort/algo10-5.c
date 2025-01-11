/* algo10-5.c 调用算法10.6(a)的程序 */
#include "c10-1.h"


void main()
{
	RedType d[N] = { {49,1},{38,2},{65,3},{97,4},{76,5},{13,6},{27,7},{49,8} };
	SqList l;
	int i;
	for (i = 0; i < N; i++)
		l.r[i + 1] = d[i];
	l.length = N;
	printf("排序前:\n");
	print(l);
	QuickSort(&l);
	printf("排序后:\n");
	print(l);
}
