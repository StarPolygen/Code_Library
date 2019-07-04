//线段直线相交
//kuangbin专题十三 基础计算几何 POJ 3304 Segements
//判断线段和直线相交
//题意：给出n条线段，判断是否存在有一条直线，满足所有的线段在直线上投影后至少有一个公共点
//方法：原命题等价为存在一条直线穿过所有的线段（易知过公共点且垂直于所求直线的直线符合条件，设为直线a）
//该命题又等价于从所有线段中任选两端点形成的直线存在可以穿过所有的线段的直线（可将a平移至一条线段端点，然后绕这点旋转，使a过另一条线段端点）
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
#define maxn 105
using namespace std;
const double eps = 1e-8;
int sgn(double k) { return fabs(k) < eps ? 0 : (k > 0 ? 1 : -1); }

//点： 加 减 乘 叉积   
struct Point
{
    double x,y;
    Point(){}
    Point(double _x,double _y)
    {
        x = _x;y = _y;
    }
    Point operator -(const Point &b)const
    {
        return Point(x - b.x,y - b.y);
    }
    //点向量叉积 
    double operator ^(const Point &b)const
    {
        return x*b.y - y*b.x;
    }
    double operator *(const Point &b)const
    {
        return x*b.x + y*b.y;
    }
};

//线  位置关系  交点求解   
struct Line
{
    Point s,e;
    Line(){}
    Line(Point _s,Point _e)
    {
        s = _s;e = _e;
    }
    pair<Point,int> operator &(const Line &b)const
    {
        Point res = s;
        if(sgn((s-e)^(b.s-b.e)) == 0)
        {
            if(sgn((b.s-s)^(b.e-s)) == 0)
                return make_pair(res,0);//两直线重合
            else return make_pair(res,1);//两直线平行
        }
        double t = ((s-b.s)^(b.s-b.e))/((s-e)^(b.s-b.e));
        res.x += (e.x - s.x)*t;
        res.y += (e.y - s.y)*t;
        return make_pair(res,2);//有交点
    }
};

Line  seg[maxn];
Point arr[maxn<<1];
void ini(){
    memset(seg,0,sizeof(seg));
    memset(arr,0,sizeof(arr));
}
int main() {
    int T,n;
    scanf("%d",&T);
    while(T--){ 
        ini();
        scanf("%d",&n);
        Point s,t;
        for(int i=1;i<=n;i++){
            scanf("%lf%lf%lf%lf",&s.x,&s.y,&t.x,&t.y);
            seg[i] = Line(s,t);
            arr[2*i-1] = s;
            arr[2*i] = t;
        }
        bool flag=1;
        for(int i=1;i<2*n;i++){
            for(int j=i+1;j<=2*n;j++){
                Line cur=Line(arr[i],arr[j]);
                int tot=0;
                for(int k=1;k<=n;k++){
                    if(((cur&seg[k]).second==2
                    &&sgn(((cur&seg[k]).first.x-seg[k].e.x)*((cur&seg[k]).first.x-seg[k].s.x))<=0
                    &&sgn(((cur&seg[k]).first.y-seg[k].e.y)*((cur&seg[k]).first.y-seg[k].s.y))<=0)
                       ||(cur&seg[k]).second==0){
                        //    printf("??: %lf\n",sgn((cur&seg[k]).first.x-seg[k].e.x)*((cur&seg[k]).first.x-seg[k].s.x));
                            tot++;
                            // printf("i:%d j:%d tot:%d  k:%d xx:%d ??: %d\n",i,j,tot,k,(cur&seg[k]).second,sgn(((cur&seg[k]).first.x-seg[k].e.x)*((cur&seg[k]).first.x-seg[k].s.x)));
                       }
                }
                if(tot==n) {
                    flag=0; goto H;
                }
            }
        }
        H:if(flag==0) printf("Yes!\n");
        else printf("No!\n");
    
    }
    return 0;
}