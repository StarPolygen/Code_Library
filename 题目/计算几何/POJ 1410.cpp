//kuangbin专题十三 基础计算几何 1410 Insection
//判断线段和矩形相交
//bug: 1 题目说了坐标输入没有任何顺序，所谓l，r，bottom，top只是误导
//      2 db大小比较要用sgn
//      3 该点需要满足不仅与对角线有交点，且交点在矩形内，且交点在线段上
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

double dis(Point a, Point b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

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


int n;
int main(){
    scanf("%d",&n);
    while(n--){
        int x1,y1,x2,y2;
        int xl,yt,xr,yb;
        scanf("%d%d%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&xl,&yt,&xr,&yb);
        if(xl>xr) swap(xl,xr);
        if(yb>yt) swap(yb,yt);
        Point s=Point(x1,y1);
        Point t=Point(x2,y2);
        Point P1=Point(xl,yt);
        Point P2=Point(xr,yt);
        Point P3=Point(xr,yb);
        Point P4=Point(xl,yb);
        Line seg=Line(s,t);
        bool flag=0;
        if(x1<=xr&&x1>=xl&&y1<=yt&&y1>=yb) flag=1;
        // printf("%d\n",flag);
        if(x2<=xr&&x2>=xl&&y2<=yt&&y2>=yb) flag=1;
        // printf("%d\n",flag);
        Line diag1=Line(P1,P3);
        Line diag2=Line(P2,P4);
        double xcur1=(diag1&seg).first.x;
        double ycur1=(diag1&seg).first.y;
        double xcur2=(diag2&seg).first.x;
        double ycur2=(diag2&seg).first.y;
        if(x1>x2) swap(x1,x2);
        if(y1>y2) swap(y1,y2);
        if(flag==0&&(diag1&seg).second==2&&sgn(xr-xcur1)>=0&&sgn(xcur1-xl)>=0&&sgn(yt-ycur1)>=0&&sgn(ycur1-yb)>=0&&
        sgn(x2-xcur1)>=0&&sgn(xcur1-x1)>=0&&sgn(y2-ycur1)>=0&&sgn(ycur1-y1)>=0) flag=1;
        // printf("%d\n",flag);
        if(flag==0&&(diag2&seg).second==2&&sgn(xr-xcur2)>=0&&sgn(xcur2-xl)>=0&&sgn(yt-ycur2)>=0&&sgn(ycur2-yb)>=0&&
        sgn(x2-xcur2)>=0&&sgn(xcur2-x1)>=0&&sgn(y2-ycur2)>=0&&sgn(ycur2-y1)>=0) flag=1;
        // printf("%d\n",flag);
        if(flag==1) printf("T\n");
        else printf("F\n");

    }
    return 0;
}
/*
11
2 2 10 2 1 5 7 1
4 9 11 2 1 5 7 1
2 2 2 3 1 5 7 1
1 5 7 1 1 5 7 1
1 5 2 3 1 5 7 1
1 1 1 1 1 5 7 1
3 8 10 1 1 5 7 1
0 0 10 0 1 5 7 1
4 4 0 0 1 5 7 1
0 0 100 100 1 5 7 1
0 0 0 0 1 5 7 1

T F T T T T T F T T F
*/