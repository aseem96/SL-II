#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int num;
void strassens(int A[][num],int B[][num],int C[][num],int size)
{
	int sz=size/2;
	int p1[sz][sz], p2[sz][sz], p3[sz][sz], p4[sz][sz],p5[sz][sz],p6[sz][sz],p7[sz][sz];
	int temp1[sz][sz], temp2[sz][sz];
	int i,j;

	if(size>=2)
	{
		//p1
		for(i=0;i< sz;i++)
		{
			for(j=0;j< sz;j++)
			{
				temp1[i][j] = A[i][j]+A[i+ sz][j+ sz];
			}
		}

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp2[i][j] = B[i][j]+B[i+ sz][j+ sz];
			}
		}
		num = sz;
		strassens(temp1,temp2,p1,sz);

		// p2
		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp1[i][j] = A[i+ sz][j]+A[i+ sz][j+ sz];
			}
		}

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp2[i][j] = B[i][j];
			}
		}
		num = sz;
		strassens(temp1,temp2,p2,sz);

		// p3
		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp1[i][j] = A[i][j];
			}
		}

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp2[i][j] = B[i][ j+ sz] - B[i+ sz][j+ sz];
			}
		}
		num = sz;
		strassens(temp1,temp2,p3,sz);

		// p4
		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp1[i][j] = A[i+ sz][j+ sz];
			}
		}

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp2[i][j] = B[i+ sz][j] - B[i][j];
			}
		}
		num = sz;
		strassens(temp1,temp2,p4,sz);

		// p5
		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp1[i][j] = A[i][j] + A[i][j+ sz];
			}
		}

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp2[i][j] = B[i+ sz][j+ sz];
			}
		}
		num = sz;
		strassens(temp1,temp2,p5,sz);

		//p6
		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp1[i][j] = A[i+ sz][j] - A[i][j];
			}
		}

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp2[i][j] = B[i][j]+B[i][j+ sz];
			}
		}
		num = sz;
		strassens(temp1,temp2,p6,sz);

		//p7
		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp1[i][j] = A[i][j+ sz] - A[i+ sz][j+ sz];
			}
		}

		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				temp2[i][j] = B[i+ sz][j]+B[i+ sz][j+ sz];
			}
		}
		num = sz;
		strassens(temp1,temp2,p7,sz);

		// c00
		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				C[i][j] = p1[i][j] + p4[i][j] - p5[i][j] + p7[i][j];
			}
		}

		// c01
		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				C[i][j+sz] = p3[i][j] + p5[i][j];
			}
		}

		// c10
		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				C[i+sz][j] = p2[i][j] + p4[i][j];
			}
		}

		//c11
		for(i=0;i<sz;i++)
		{
			for(j=0;j<sz;j++)
			{
				C[i+sz][j+sz] = p1[i][j] + p3[i][j] - p2[i][j] + p6[i][j];
			}
		}

	}
	else if(size==1)
	{
		C[0][0]= A[0][0] * B[0][0];
	}
}

int padding(int num)
{
	int original_num = num, temp= 0, i, actual_num=1;
	if(num == 1)
		return 1;
	while(num > 1)
	{
		temp++;
		num /=2;
	}
	for(i=0;i<temp;i++)
	{
		actual_num *=2;
	}
	if(actual_num == original_num)
		return original_num;
	else
		return actual_num * 2;
}



int main()
{

	int temp, i, j;
	printf("Enter the size of N*N matrix : ");
	scanf("%d",&num);
	temp=num;
	if(num<=0)
	{
		return 0;
	}

	num=padding(num);
	int a[num][num],b[num][num],c[num][num];
	printf("Enter matrix a:\n");
	for(i=0;i<temp;i++)
	{
		for(j=0;j<temp;j++)
		{
			scanf("%d",&a[i][j]);
		}
		for(j=temp;j<num;j++)
		{
			a[i][j]=0;
		}
	}
	for(i=temp;i<num;i++)
	{
		for(j=0;j<num;i++)
		{
			a[i][j]=0;
		}
	}

	printf("\nEnter matrix b:\n");
	for(i=0;i<temp;i++)
	{
		for(j=0;j<temp;j++)
		{
			scanf("%d",&b[i][j]);
		}
		for(j=temp;j<num;j++)
		{
			b[i][j]=0;
		}
	}

	for(i=temp;i<num;i++)
	{
		for(j=0;j<num;j++)
		{
			b[i][j]=0;
		}
	}
	printf("\nMatrix a:\n");
	for(i=0;i<num;i++)
	{
		for(j=0;j<num;j++)
		{
			printf("%d\t",a[i][j]);
		}
		printf("\n");
	}
	printf("\nMatrix b:\n");
	for(i=0;i<num;i++)
	{
		for(j=0;j<num;j++)
		{
			printf("%d\t",b[i][j]);
		}
		printf("\n");
	}
	strassens(a,b,c,num);
	printf("\nResultant matrix c is:\n");
	for(i=0;i<temp;i++)
	{
		for(j=0;j<temp;j++)
		{
			printf("%d\t",c[i][j]);
		}
		printf("\n");
	}
	return 0;
}
