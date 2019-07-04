//极角排序
//kuangbin专题十三 基础计算几何 
//POJ 1606
//极角排序 1A

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <math.h>
#define ll long long
#define MAXN 55
using namespace std;
const double eps = 1e-8;
const double PI=acos(-1.0);
int sgn(double k) { return fabs(k) < eps ? 0 : (k > 0 ? 1 : -1); }


int t,n,l;
struct point
{
    int index;
    int x,y;
};
point list[MAXN];

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

// 极角排序函数2 在判断稳定凸包时使用 
// 最终产生的 凸集内的点 完全按照逆时针排列 
bool cmp2(point p1,point p2){
    ll tmp=cross(list[l],p1,p2);
    if(tmp>0) return true;
    else if(tmp==0){
        if(sgn(atan2((double)p1.y,(double)p1.x)-PI/2)>0) return sgn(dis(list[l],p1)-dis(list[l],p2))>0;
        else return sgn(dis(list[l],p1)-dis(list[l],p2))<0;
    }
    else return false;
}

void init(){
    memset(list,0,sizeof(list));
}

int main() {
    
    scanf("%d",&t);
    while(t--){
        init();
        scanf("%d",&n);
        getchar();
        int i,k;
        point p0;
        scanf("%d%d%d",&list[0].index,&list[0].x,&list[0].y);
        getchar();
        p0.x=list[0].x;
        p0.y=list[0].y;
        p0.index=list[0].index;
        k=0;
        for(i=1;i<n;i++)
        {
            scanf("%d%d%d",&list[i].index,&list[i].x,&list[i].y);
            getchar();
            if( (sgn(p0.y-list[i].y)>0) || ((sgn(p0.y-list[i].y)==0&&sgn(p0.x-list[i].x)>=0)))
            {
                p0.index=list[i].index;
                p0.x=list[i].x;
                p0.y=list[i].y;
                k=i;
            }    
        }    
        list[k]=list[0];
        list[0]=p0;
        // printf("%d %d\n",list[0].x,list[0].y);
        for(l=0;l<n;l++){
            sort(list+l+1,list+n,cmp2);
        }
        printf("%d ",n);
        for(int i=0;i<n;i++){
            printf("%d ",list[i].index);
            // if(list[i].index==27) printf("?%d,%d",list[i].x,list[i].y);
        }
        printf("\n");

    }
    return 0;
}