//扩倍 直线相交
//kuangbin专题十三 基础计算几何 Kadj Squares 
//计算几何新技巧扩倍 + 直线线段相交判断
//1A 
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
const double tw=sqrt(2);

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

const int maxn=55;
struct Node{
    int len,l,r;
}node[maxn];

int arr[maxn];

void init(){
    memset(node,0,sizeof(node));
    memset(arr,0,sizeof(arr));
}
int main() {
    int n;
    while(scanf("%d",&n)==1&&n){
        init();
        for(int i=1;i<=n;i++){
            scanf("%d",&node[i].len); //边长，也是半对角线的根号2倍,由于扩倍操作，当做半对角线处理
        }
        node[1].l=0;node[1].r=2*node[1].len;
        for(int i=2;i<=n;i++){
            for(int j=1;j<i;j++){
                node[i].l=max(node[i].l,node[j].r-abs(node[j].len-node[i].len));//放置正方形
            }
            node[i].r=node[i].l+2*node[i].len;
        }
        //从上方扫描，每隔x=0.5的竖直线扫描一次，寻找最上方的图形
        for(int i=1;i<=3300;i++){
            Line ver=Line(Point(i/2.0,0),Point(i/2.0,1));
            double maxy=0; int top=0;
            for(int j=1;j<=n;j++){
                Point left=Point(node[j].l,node[j].len);
                Point mid=Point(node[j].l+node[j].len,2*node[j].len);
                Point right=Point(node[j].r,node[j].len);
                Line lj=Line(left,mid);
                Line rj=Line(mid,right);
                Point o1=(lj&ver).first;
                Point o2=(rj&ver).first;
                if((lj&ver).second==2&&sgn(o1.x-left.x)>=0&&sgn(mid.x-o1.x)>=0&&sgn(o1.y-left.y)>=0&&sgn(mid.y-o1.y)>=0){
                    if(o1.y>maxy){
                        maxy=o1.y;
                        top=j;
                    }
                }if((rj&ver).second==2&&sgn(o2.x-mid.x)>=0&&sgn(right.x-o2.x)>=0&&sgn(o2.y-right.y)>=0&&sgn(mid.y-o2.y)>=0){
                    if(o2.y>maxy){
                        maxy=o2.y;
                        top=j;
                    }
                }
            }
            arr[top]++;
        }
        //输出被扫描到的图形编号
        for(int i=1;i<=n;i++){
            if(arr[i]>0) printf("%d ",i);
        }
        printf("\n");
    }
    return 0;
}