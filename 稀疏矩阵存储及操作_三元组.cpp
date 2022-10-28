#include <stdio.h>
#include <stdlib.h>
#define number 20


/*��Ԫ��˳���洢ϡ�����*/
/*
���㷨��ʱ�临�Ӷ�Ϊ O(n2)
Ƕ�׵����� for ѭ����ִ�д��������� mu*nu������ * ����������ʾ��
ϡ������ת���㷨��ҲǶ��ʹ�������� for ѭ����
ִ�д��������� nu*tu������ * �� 0 Ԫ�ظ���������ʾ��
����ϡ������з� 0 Ԫ�صĸ���Ϊ mu*nu��
��ϡ�����ת���㷨�е�Ƕ�� for ѭ��Ҫִ�� mu*nu2 �Σ�
ִ��Ч��û�����¿�ͷ���㷨�ߡ�
Ҳ����˵�������¿�ͷ�ľ���ת���㷨��ȣ�
ϡ������ת���㷨����ʡ�ڴ�ռ䣬
ִ��Ч�ʲ�һ����ǰ�߸ߡ�
*/

//һ.����ṹ��
 
//1.������Ԫ��ṹ��
typedef struct{
	int i, j;
	int e;
}triple;

//2.������Ԫ��洢����ṹ�� 
typedef struct{
	triple data[number];
	int mu, nu, tu;
}TSMatrix;


//��.�������ú���

//ϡ�����ļ�ת��
void transposeMatrix(TSMatrix M, TSMatrix &T);
//ϡ�����Ŀ���ת��
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
    printf("ת�þ�����Ԫ���Ϊ��\n");
    for (int i=0; i<T.tu; i++) {
        printf("(%d,%d,%d)\n",T.data[i].i,T.data[i].j,T.data[i].e);
    }
	return 0;
}


//��.����ʵ�� 

//1.ϡ�����ļ�ת��
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

//2.ϡ�����Ŀ���ת��
/*
��������ת���㷨��ʱ�临�Ӷ�Ϊ O(n)��
��ʹ���������£�������ȫ�����Ƿ�0Ԫ�أ���
���㷨��ʱ�临�Ӷ�Ҳ��Ϊ O(n2)��
*/
void fastTransposeMatrix(TSMatrix M, TSMatrix &T)
{
	T.mu = M.nu;
	T.nu = M.mu;
	T.tu = M.tu;
	
	if(T.tu)
	{
		//����array����
		int array[number];
		for(int col=1; col<=M.nu; col++)
			array[col] = 0;	
		for(int t=0; t<M.tu; t++)
		{
			int j = M.data[t].j;
			array[j]++;
		}
		
		//��������ʼ��pot����
		int pot[T.mu+1];
		pot[1] = 1;
		for(int col=2; col<=M.mu; col++)
			pot[col] = pot[col-1] + array[col-1]; 
			
		//����һ�鼴��ʵ����Ԫ����ת��
		for (int p=0; p<M.tu; p++) 
		{
            //��ȡ��ǰ��Ԫ�������
            int col = M.data[p].j;
            //����������cpot���飬�ҵ���ǰԪ����Ҫ��ŵ�λ��
            int q = pot[col];
            //ת�þ������Ԫ��Ĭ�ϴ������±�0��ʼ�����õ���qֵ�ǵ�����λ�ã�����Ҫ��1
            T.data[q-1].i = M.data[p].j;
            T.data[q-1].j = M.data[p].i;
            T.data[q-1].e = M.data[p].e;
            //�����ɺ�cpot�����Ӧ��λ��Ҫ+1���Ա��´θ��д洢��һ����Ԫ��
            pot[col]++;
        }
	}
} 
