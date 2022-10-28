#include <stdio.h>
#include <stdlib.h>
#define number 20


/*三元组顺序表存储稀疏矩阵*/
/*
该算法的时间复杂度为 O(n2)
嵌套的两个 for 循环的执行次数可以用 mu*nu（行数 * 列数）来表示；
稀疏矩阵的转置算法中也嵌套使用了两个 for 循环，
执行次数可以用 nu*tu（列数 * 非 0 元素个数）来表示。
假设稀疏矩阵中非 0 元素的个数为 mu*nu，
则稀疏矩阵转置算法中的嵌套 for 循环要执行 mu*nu2 次，
执行效率没有文章开头的算法高。
也就是说，和文章开头的矩阵转置算法相比，
稀疏矩阵的转置算法更节省内存空间，
执行效率不一定比前者高。
*/

//一.定义结构体
 
//1.定义三元组结构体
typedef struct{
	int i, j;
	int e;
}triple;

//2.定义三元组存储矩阵结构体 
typedef struct{
	triple data[number];
	int mu, nu, tu;
}TSMatrix;


//二.声明所用函数

//稀疏矩阵的简单转置
void transposeMatrix(TSMatrix M, TSMatrix &T);
//稀疏矩阵的快速转置
void fastTransposeMatrix(TSMatrix M, TSMatrix &T); 

int main()
{
	TSMatrix M;
    M.mu=2, M.nu=3, M.tu=3;
  
    M.data[0].i=1, M.data[0].j=2, M.data[0].e=1;
  
    M.data[1].i=2, M.data[1].j=2, M.data[1].e=3;
  
    M.data[2].i=3, M.data[2].j=1, M.data[2].e=6;
  
    TSMatrix T;
    fastTransposeMatrix(M, T);
    printf("转置矩阵三元组表为：\n");
    for (int i=0; i<T.tu; i++) {
        printf("(%d,%d,%d)\n",T.data[i].i,T.data[i].j,T.data[i].e);
    }
	return 0;
}


//三.函数实现 

//1.稀疏矩阵的简单转置
void transposeMatrix(TSMatrix M, TSMatrix &T)
{
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	
	if(T.tu)
	{
		int col, p;
		int q = 0;
		for(col=1; col <= M.nu; col++)
		{
			for(p=0; p<M.tu; p++)
			{
				if(M.data[p].j == col)
				{
					T.data[q].i = M.data[p].j;
					T.data[q].j = M.data[p].i;
					T.data[q].e = M.data[p].e;
					q++;
				}
			}
		}
	}
}

//2.稀疏矩阵的快速转置
/*
疏矩阵快速转置算法的时间复杂度为 O(n)。
即使在最坏的情况下（矩阵中全部都是非0元素），
该算法的时间复杂度也才为 O(n2)。
*/
void fastTransposeMatrix(TSMatrix M, TSMatrix &T)
{
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	
	if(T.tu)
	{
		//计算array数组
		int array[number];
		for(int col=1; col<=M.nu; col++)
			array[col] = 0;	
		for(int t=0; t<M.tu; t++)
		{
			int j = M.data[t].j;
			array[j]++;
		}
		
		//创建并初始化pot数组
		int pot[T.mu+1];
		pot[1] = 1;
		for(int col=2; col<=M.mu; col++)
			pot[col] = pot[col-1] + array[col-1]; 
			
		//遍历一遍即可实现三元组表的转置
		for (int p=0; p<M.tu; p++) 
		{
            //提取当前三元组的列数
            int col = M.data[p].j;
            //根据列数和cpot数组，找到当前元素需要存放的位置
            int q = pot[col];
            //转置矩阵的三元组默认从数组下标0开始，而得到的q值是单纯的位置，所以要减1
            T.data[q-1].i = M.data[p].j;
            T.data[q-1].j = M.data[p].i;
            T.data[q-1].e = M.data[p].e;
            //存放完成后，cpot数组对应的位置要+1，以便下次该列存储下一个三元组
            pot[col]++;
        }
	}
} 
