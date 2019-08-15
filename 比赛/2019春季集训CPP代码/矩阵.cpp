#include <bits/stdc++.h>
#include<stdio.h>
#include<windows.h>
#include <bitset>
#include<string>
#include<iostream>
#define N 2
using namespace std;
double src[2][2],des [2][2];


using namespace std;

double getA(double arcs[N][N],int n)
{
    if(n==1)
    {
        return arcs[0][0];
    }
    double ans = 0;
    double temp[N][N]={0.0};
    int i,j,k;
    for(i=0;i<n;i++)
    {
        for(j=0;j<n-1;j++)
        {
            for(k=0;k<n-1;k++)
            {
                temp[j][k] = arcs[j+1][(k>=i)?k+1:k];

            }
        }
        double t = getA(temp,n-1);
        if(i%2==0)
        {
            ans += arcs[0][i]*t;
        }
        else
        {
            ans -=  arcs[0][i]*t;
        }
    }
    return ans;
}
//计算每一行每一列的每个元素所对应的余子式，组成A*
void  getAStart(double arcs[N][N],int n,double ans[N][N])
{
    if(n==1)
    {
        ans[0][0] = 1;
        return;
    }
    int i,j,k,t;
    double temp[N][N];
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            for(k=0;k<n-1;k++)
            {
                for(t=0;t<n-1;t++)
                {
                    temp[k][t] = arcs[k>=i?k+1:k][t>=j?t+1:t];
                }
            }


            ans[j][i]  =  getA(temp,n-1);
            if((i+j)%2 == 1)
            {
                ans[j][i] = - ans[j][i];
            }
        }
    }
}
//得到给定矩阵src的逆矩阵保存到des中。
bool GetMatrixInverse(double src[N][N],int n,double des[N][N])
{
    double flag=getA(src,n);
    double t[N][N];
    if(flag==0)
    {
        return false;
    }
    else
    {
        getAStart(src,n,t);
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                des[i][j]=t[i][j]/flag;
            }

        }
    }


    return true;

}
//按第一行展开计算|A|

int main(){
	int T;
	scanf("%d",&T);
	double x1,x2,x3,y1,y2,y3,x4,y4,x5,y5,x6,y6 ;
	while(T--){
		scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf", &x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4,&x5,&y5,&x6,&y6);
		double a=x2-x1,b=y2-y1,c=x3-x1,d=y3-y1,A=x5-x4,B=y5-y4,C=x6-x4,D=y6-y4;
		src[0][0]=a,src[0][1]=b,src[1][0]=c,src[1][1]=d;
		int n=2;
		GetMatrixInverse(src,n,des);
		double k[2][2];
//		for(int i=0;i<2;i++){
//			for(int j=0;j<2;j++){
//				printf("%f ",src[i][j]);
//			}
//		}
//		for(int i=0;i<2;i++){
//			for(int j=0;j<2;j++){
//				printf("%f ",des[i][j]);
//			}
//		}
		
		k[0][0]=des[0][0]*A+des[0][1]*C;
		k[0][1]=des[0][0]*B+des[0][1]*D;
		k[1][0]=des[1][0]*A+des[1][1]*C;
		k[1][1]=des[1][0]*B+des[1][1]*D;
		int Q;
		scanf("%d",&Q);
		for(int i=1;i<=Q;i++){
			double n1,n2,ans1,ans2;
			scanf("%lf%lf",&n1,&n2);
			n1=n1-x1,n2=n2-y1;
			ans1=n1*k[0][0]+n2*k[1][0];
			ans2=n1*k[0][1]+n2*k[1][1];
			ans1=x4+ans1;
			ans2=y4+ans2;
			printf("%.2f %.2f",ans1,ans2);
		}
	} 
	
}
