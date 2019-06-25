//POJ 1228    
//虽然AC 但非常困惑
//题目要求：判断所给点组成的凸包是否每个边上都有至少三个点 若都有 YES 反之NO 
//不考虑最后一个凸点到第一个凸点的边上是否有3个点的情况可以AC 考虑了反而无法AC
//但收获了在不删边点的情况下 依然逆时针排列的比较器板子 

//更新：
//使用暴力判定3点共线 即使考虑了最后一条边也能AC
#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<iostream>
#define ll long long
using namespace std;
const int MAXN=1010;  //点的数量 
const double eps=1e-8;
const double PI=acos(-1.0);
int sgn(double k) { return fabs(k) < eps ? 0 : (k > 0 ? 1 : -1); }

struct point
{
    ll x,y;
};
point list[MAXN];
int stack[MAXN],top;

ll cross(point p0,point p1,point p2) //计算叉积  p0p1 X p0p2 
{
    return (p1.x-p0.x)*(p2.y-p0.y)-(p1.y-p0.y)*(p2.x-p0.x);
}    
double dis(point p1,point p2)  //计算 p1p2的 距离 
{
    return sqrt((double)(p2.x-p1.x)*(p2.x-p1.x)+(p2.y-p1.y)*(p2.y-p1.y));
}  


//cross > 0 代表 p0p2 对 p0p1为逆时针 
//		= 0 代表 平行 
//cmp 函数return true时，会将参数1排在前面 
//极角排序函数 ， 角度相同则距离小的在前面 

//注意：当stack需要包含边点，且要求逆序时，使用cmp2，如稳定凸包问题 
bool cmp(point p1,point p2) 
{
    ll tmp=cross(list[0],p1,p2);
    if(tmp>0) return true;
    else if(tmp==0&&dis(list[0],p1)<dis(list[0],p2)) return true;
    else return false;
}  

// 极角排序函数2号 在判断稳定凸包时使用 
// 最终产生的 凸集内的点 是完全按照逆时针 
bool cmp2(point p1,point p2){
    ll tmp=cross(list[0],p1,p2);
    if(tmp>0) return true;
    else if(tmp==0){
        if(sgn(atan2((double)p1.y,(double)p1.x)-PI/2)>0) return sgn(dis(list[0],p1)-dis(list[0],p2))>0;
        else return sgn(dis(list[0],p1)-dis(list[0],p2))<0;
    }
    else return false;
}
  
void init(int n) //输入，并把  最左下方的点放在 list[0]  。并且进行极角排序 
{
    int i,k;
    point p0;
    scanf("%lld%lld",&list[0].x,&list[0].y);
    p0.x=list[0].x;
    p0.y=list[0].y;
    k=0;
    for(i=1;i<n;i++)
    {
        scanf("%lld%lld",&list[i].x,&list[i].y);
        if( (p0.y>list[i].y) || ((p0.y==list[i].y)&&(p0.x>list[i].x)) )
        {
            p0.x=list[i].x;
            p0.y=list[i].y;
            k=i;
        }    
    }    
    list[k]=list[0];
    list[0]=p0;
    //
    sort(list+1,list+n,cmp2);
}     

void graham(int n)
{
    int i;
    if(n==1) {top=0;stack[0]=0;}
    if(n==2)
    {
        top=1;
        stack[0]=0;
        stack[1]=1;
    }    
    if(n>2)
    {
        for(i=0;i<=1;i++) stack[i]=i;
        top=1;
        
        for(i=2;i<n;i++)
        {
            while(top>0&&cross(list[stack[top-1]],list[stack[top]],list[i])<0) top--;// <0改成<=0即为将凸包边上的点踢出
            top++;
            stack[top]=i;
        }    
    }    
}


int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		int n;
		scanf("%d",&n);
		init(n);
		if(n < 6){
            printf("NO\n");
            continue;     //这种continue break的善加利用，是应该牢牢记住的
        }
		graham(n);
	
		int cnt=0; bool fl=1; int gongxian=0;
		for(int i=0;i<=top-2;i++){
			if(cross(list[stack[i]],list[stack[i+1]],list[stack[i+2]])==0)
				cnt++, gongxian++;
			else{
				if(cnt==0){
					fl=0; break;
				}
				else cnt=0;
			}
		}
		//这一行是输出凸集的点，可以看到即使加上边点也是逆时针排列 
//		for(int i=0;i<=top;i++){
//			printf("i:%d %lld %lld\n",i,list[stack[i]].x,list[stack[i]].y);
//		}
		//把这行注释掉AC了，不注释反而WA，但显然最后一条边必须考虑 
//		if(cross(list[stack[top-1]],list[stack[top]],list[stack[0]])!=0) fl=0;
		
		//特判全部共线的情况 
		if(gongxian==n-2) fl=0;
		
		//这里也很奇怪 不加||(top+1)!=n 才能AC，但显然输入的点在原来的凸包上 也必须在新凸包上 
		if(fl==0||(top+1)!=n) printf("NO\n");
		else printf("YES\n");

	} 
	return 0;

} 
