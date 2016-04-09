/*
 * s.cpp
 *
 *  Created on: 27-Jan-2016
 *      Author: Aseem Raina
 */
#include<iostream>
#include<iomanip>
using namespace std;
#define N 100
class m
{	public:
    	int rs;
    	int re;
    	int cs;
    	int ce;
    	int a[N][N]={{0}};

};
class strassen
{
	public:
		void input(m &matrix,int n,int c)
		{	matrix.rs=matrix.cs=0;
			matrix.re=matrix.ce=n-1;
			for(int i=0;i<=n-1-c;i++)
				for(int j=0;j<=n-1-c;j++)
				{
					cout<<"\nenter element of row index "<<i<<" column index "<<j<<":";
					cin>>matrix.a[i][j];
				}
		}
		void display(m matrix,int d)
		{
			for(int i=matrix.rs;i<=matrix.re-d;i++)
			{	for (int j=matrix.cs;j<=matrix.ce-d;j++)
					cout<<setw(3)<<matrix.a[i][j];
	        	cout<<endl;
			}
			cout<<endl;
		}
		m plus(m m1,m m2)
		{	m result;
	    	int m1_i,m1_j;
	    	int m2_i,m2_j;
	    	int i, j;
	    	int n=m1.re-m1.rs;
	    	result.rs=result.cs=0;
	    	result.re=result.ce=n;
	    	for (m1_i=m1.rs,m2_i=m2.rs,i=0;m1_i<=m1.re;m1_i++,m2_i++,i++)
	    		for (m1_j=m1.cs,m2_j=m2.cs,j=0;m1_j<=m1.ce;m1_j++,m2_j++,j++)
	    			result.a[i][j]=m1.a[m1_i][m1_j]+m2.a[m2_i][m2_j];
	    	return result;
		}
		m minus(m m1,m m2)
		{	m result;
	    	int m1_i,m1_j;
	    	int m2_i,m2_j;
	    	int i, j;
	    	int n=m1.re-m1.rs;
	    	result.rs=result.cs=0;
	    	result.re=result.ce=n;
	    	for (m1_i=m1.rs,m2_i=m2.rs,i=0;m1_i<=m1.re;m1_i++,m2_i++,i++)
	    		for (m1_j=m1.cs,m2_j=m2.cs,j=0;m1_j<=m1.ce;m1_j++,m2_j++,j++)
	    			result.a[i][j]=m1.a[m1_i][m1_j]-m2.a[m2_i][m2_j];
	    	return result;
		}
		m multiply(m mat1,m mat2)
		{	int i,j,m1_i,m1_j,n=mat1.re-mat1.rs+1;
			m m1,m2,m3,m4,m5,m6,m7,q1,q2,q3,q4,result,a11,a12,a21,a22,b21,b22,b11,b12;
	    	if(n<=2)
	    	{
	    		int a,b,c,d,e,f,g;
	    		m m3=mat1;

	    		a=(mat1.a[mat1.rs][mat1.cs]+mat1.a[mat1.rs+1][mat1.cs+1])*(mat2.a[mat2.rs][mat2.cs]+mat2.a[mat2.rs+1][mat2.cs+1]);
	    		b=(mat1.a[mat1.rs+1][mat1.cs]+mat1.a[mat1.rs+1][mat1.cs+1])*mat2.a[mat2.rs][mat2.cs];
	    		c=mat1.a[mat1.rs][mat1.cs]*(mat2.a[mat2.rs][mat2.cs+1]-mat2.a[mat2.rs+1][mat2.cs+1]);
	    		d=mat1.a[mat1.rs+1][mat1.cs+1]*(mat2.a[mat2.rs+1][mat2.cs]-mat2.a[mat2.rs][mat2.cs]);
	    		e=(mat1.a[mat1.rs][mat1.cs]+mat1.a[mat1.rs][mat1.cs+1])*mat2.a[mat2.rs+1][mat2.cs+1];
	    		f=(mat1.a[mat1.rs+1][mat1.cs]-mat1.a[mat1.rs][mat1.cs])*(mat2.a[mat2.rs][mat2.cs]+mat2.a[mat2.rs][mat2.cs+1]);
	    		g=(mat1.a[mat1.rs][mat1.cs+1]-mat1.a[mat1.rs+1][mat1.cs+1])*(mat2.a[mat2.rs+1][mat2.cs]+mat2.a[mat2.rs+1][mat2.cs+1]);
	    		m3.a[m3.rs][m3.cs]=a+d-e+g;
	    		m3.a[m3.rs][m3.cs+1]=c+e;
	    		m3.a[m3.rs+1][m3.cs]=b+d;
	    		m3.a[m3.rs+1][m3.cs+1]=a-b+c+f;
	    		return m3;
	    	}
			a11=a12=a21=a22=mat1;
			b11=b12=b21=b22=mat2;
			result.rs=result.cs=0;
			result.ce=result.re=n-1;
			a11.rs=mat1.rs;
			a11.re=mat1.re/2;
			a11.cs=mat1.cs;
			a11.ce=mat1.ce/2;
			a12.rs=mat1.rs;
			a12.re=mat1.re/2;
			a12.cs=mat1.ce/2+1;
			a12.ce=mat1.ce;
			a21.rs=mat1.re/2+1;
			a21.re=mat1.re;
			a21.cs=mat1.cs;
			a21.ce=mat1.ce/2;
			a22.rs=mat1.re/2+1;
			a22.re=mat1.re;
			a22.cs=mat1.ce/2+1;
			a22.ce=mat1.ce;
			b11.rs=mat2.rs;
			b11.re=mat2.re/2;
			b11.cs=mat2.cs;
			b11.ce=mat2.ce/2;
			b12.rs=mat2.rs;
			b12.re=mat2.re/2;
			b12.cs=mat2.ce/2+1;
			b12.ce=mat2.ce;
			b21.rs=mat2.re/2+1;
			b21.re=mat2.re;
			b21.cs=mat2.cs;
			b21.ce=mat2.ce/2;
			b22.rs=mat2.re/2+1;
			b22.re=mat2.re;
			b22.cs=mat2.ce/2+1;
			b22.ce=mat2.ce;
			m1=multiply(plus(a11,a22),plus(b11,b22));
			m2=multiply(plus(a21,a22),b11);
			m3=multiply(a11,minus(b12,b22));
			m4=multiply(a22,minus(b21,b11));
			m5=multiply(plus(a11,a12),b22);
			m6=multiply(minus(a21,a11),plus(b11,b12));
			m7=multiply(minus(a12,a22),plus(b21,b22));
			q1=plus(plus(m1,m4),minus(m7,m5));
			q2=plus(m3,m5);
			q3=plus(m2,m4);
			q4=plus(minus(m1,m2),plus(m3,m6));
	    	for(m1_i=q1.rs,i=0;m1_i<=q1.re;m1_i++,i++)
	    		for(m1_j=q1.cs,j=0;m1_j<=q1.ce;m1_j++,j++)
	    			result.a[i][j]=q1.a[m1_i][m1_j];
	    	for(m1_i=q2.rs,i=0;m1_i<=q2.re;m1_i++,i++)
	    		for (m1_j=q2.cs,j=n/2;m1_j<=q2.ce;m1_j++,j++)
	    			result.a[i][j]=q2.a[m1_i][m1_j];
	    	for(m1_i=q3.rs,i=n/2;m1_i<=q3.re;m1_i++,i++)
	    		for(m1_j=q3.cs,j=0;m1_j<=q3.ce;m1_j++,j++)
	    			result.a[i][j]=q3.a[m1_i][m1_j];
	    	for(m1_i=q4.rs,i=n/2;m1_i<=q4.re;m1_i++,i++)
	    		for (m1_j=q4.cs,j=n/2;m1_j<=q4.ce;m1_j++,j++)
	    			result.a[i][j]=q4.a[m1_i][m1_j];
	    	return result;

		}

};

int main(void)
{	m m1,m2;
	int d,c=0;
	strassen s;
	cout<<"Enter dimensions of matrix : ";
	cin>>d;
	if(((d&(d-1))==0))
		c=0;
	else
	{
		while((d&(d-1))!=0)
		{	c++;
			d++;
			cout<<"\nAdjusted dimension : "<<d<<" Offset : "<<c;
		}
	}
	cout<<"\nEnter matrix 1:\n";
	s.input(m1,d,c);
	cout<<"\nFor matrix 2:\n";
	s.input(m2,d,c);
	s.display(m1,c);
    s.display(m2,c);

    cout<<"Result:\n";
   	s.display(s.multiply(m1,m2),c);

    return 0;
}
