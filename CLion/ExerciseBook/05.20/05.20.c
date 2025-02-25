#include <stdio.h>
#include <stdlib.h>     // 提供 system、rand、srand 原型
#include <time.h>       // 提供 time 原型
#include "Array.h"      //**▲05 数组和广义表**//

// 根据多项式系数表，输出多项式
void Algo_5_20(Array A);

// 数组输出函数的内部实现
static void Print(Array A, int dim, int index[], int minus);


int main(int argc, char* argv[]) {
    Array A;
    int i, j, k;
    ElemType e = 0;
    
    // 初始化一个维度为<2,3,4>的三维数组
    InitArray(&A, 3, 2, 3, 4);
    
    srand((unsigned) time(NULL));   // 用系统时间做随机数种子
    
    // 准备测试数据
    for(i = 0; i < A.bounds[0]; i++) {
        for(j = 0; j < A.bounds[1]; j++) {
            for(k = 0; k < A.bounds[2]; k++) {
                e = rand() % 50 - 25;   // 用随机数填充数组
                Assign(&A, e, i, j, k);
                printf("%d ,", e);
            }
            printf("\n");
        }
        printf("\n\n");
    }
    
    // 输出多项式
    Algo_5_20(A);
    
    return 0;
}

//实现降幂输出
// 根据多项式系数表，输出多项式
void Algo_5_20(Array A) {
    int i;
    int* index;

    //最高幂级
    int total=0;

    // 在遍历数组元素时，记录每个元素的索引（只记录前dim-1维）
    index = (int*) malloc((A.dim - 1) * sizeof(int));
    for(i = 0; i < A.dim; i++) {
        index[i] = -1;
        total += A.bounds[i];
    }

    for(i = 0; i <= total; i++)
    {
        Print(A, 1, index, i);
    }
    
    printf("\n");
}

// 数组输出函数的内部实现
static void Print(Array A, int dim, int index[], int minus) {
    int i, j;
    int start;
    ElemType coef;
    
    if(dim == A.dim) {
        start = 0;

        int dimIndex = A.bounds[dim - 1]-minus-1;
        //无效指数
        if (dimIndex<0)
        {
            return;
        }
        index[dim-1]=dimIndex;
        // 计算本次遍历的起始元素位置
        for(i = 0; i < dim; i++) {
            start += index[i] * A.constants[i];
        }
        
        // 遍历最后一个维度内的元素
        //for(i = 0; i < minus; i++)
        {
            int eleIndex = start;
            // 获取系数
            coef = A.base[eleIndex];
            
            // 系数为0的项不必输出
            if(coef == 0) {
                return;
            }
            
            if(coef < 0) {
                printf(" - ");
            } else {
                printf(" + ");
            }
            
            // 系数的绝对值为1时，无需输出系数
            if(abs(coef) != 1) {
                // 输出系数（不带符号，前面已经输出过符号），第一项也会带着符号
                printf("%d", abs(coef));
            }
            
            /*
             * 输出多项式的每一项，未知数依次用a、b、c...命名
             *
             *【注】
             * 对于指数位0或者指数位1的情形，这里依然将其打印出来了
             * 可以选择不打印这些标记
             */
            for(j = 0; j < dim; j++) {
                printf("%c^%d", 'a' + j, index[j]);
            }
            // printf("%c^%d", 'a' + j, i);
        }
    } else {
        for(i = 0; i <= minus; i++) {
            // 索引轮转
            int left=i;
            int dimIndex = A.bounds[dim - 1]-i-1;
            if (dimIndex>0)
            {
                index[dim - 1] = dimIndex;
                left = minus-i;
                Print(A, dim + 1, index,left);
            }
            else if (dimIndex==0)
            {
                index[dim - 1] = 0;
                left= minus-i;
                Print(A, dim + 1, index,left);
                break;
            }
        }
    }
}
