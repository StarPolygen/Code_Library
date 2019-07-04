//线段相交
//kuangbin专题十三 基础计算几何  POJ2826 An Easy Problem?
//判断线段相交，究极分类讨论题
//1A C++过 G++WA 玄学POJ
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


int main() {
    int n;
    scanf("%d",&n);
    while(n--){
        int x1,y1,x2,y2,x3,y3,x4,y4;
        scanf("%d%d%d%d%d%d%d%d",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4);
        Line v1=Line(Point(x1,y1),Point(x2,y2));
        Line v2=Line(Point(x3,y3),Point(x4,y4));
        double ans;
        //若有水平木板，必定无法储水
        if(y1==y2||y3==y4) {
            ans=0; 
            printf("0.00\n");
            continue;
        }Point ins=(v1&v2).first;
        int state=(v1&v2).second;
        int x11,x22,x33,x44,y11,y22,y33,y44;
        x11=x1;x22=x2;x33=x3;x44=x4;y11=y1;y22=y2;y33=y3;y44=y4;
        if(x11>x22) swap(x11,x22);
        if(y11>y22) swap(y11,y22); Point dd1=Point(y22==y2?x2:x1,y22);
        if(x33>x44) swap(x33,x44);
        if(y33>y44) swap(y33,y44); Point dd2=Point(y44==y4?x4:x3,y44);
        //若木板不相交或重合，必定无法储水
        if(!(state==2&&sgn(ins.x-x11)>=0&&sgn(x22-ins.x)>=0&&sgn(ins.y-y11)>=0&&sgn(y22-ins.y)>=0
        &&sgn(ins.x-x33)>=0&&sgn(x44-ins.x)>=0&&sgn(ins.y-y33)>=0&&sgn(y44-ins.y)>=0)) ans=0;
        else{
            //若木板相交于任意木板的顶端，必定无法储水
            if(sgn(ins.y-y22)==0||sgn(ins.y-y44)==0) ans=0;
            //否则，储水面积必取决于交点到两木板顶端dd1,dd2的三角形
            else{
                Point gao=sgn(dd1.y-dd2.y)>0?dd1:dd2;
                Point di=sgn(dd1.y-dd2.y)>0?dd2:dd1;
                Point dou=sgn(fabs(dd1.y-ins.y)*fabs(dd2.x-ins.x)-fabs(dd2.y-ins.y)*fabs(dd1.x-ins.x))>0?dd1:dd2;
                Point huan=sgn(fabs(dd1.y-ins.y)*fabs(dd2.x-ins.x)-fabs(dd2.y-ins.y)*fabs(dd1.x-ins.x))>0?dd2:dd1;
                //若两顶端水平，则必然可以储水,，且储水面积为三角形面积
                if(sgn(dd1.y-dd2.y)==0){
                    ans=fabs(dd1.x-dd2.x)*(dd1.y-ins.y)/2.0;
                }
                //否则若有一木板为竖直，则必然可以储水
                else if(ins.x==dd1.x||ins.x==dd2.x){
                    Line tmp1=Line(di,Point(10001,di.y));
                    Line tmp2=Line(ins,gao);
                    Point jiao=(tmp1&tmp2).first;
                    ans=fabs(jiao.x-di.x)*(di.y-ins.y)/2.0;
                }
                //否则若两顶端在交点右侧
                else if(sgn(dd1.x-ins.x)>=0&&sgn(dd2.x-ins.x)>=0){
                    //较陡峭的顶端在x轴投影距离交点在x投影远，则无法储水
                    if(sgn(dou.x-huan.x)>=0) ans=0;
                    else{
                        Line tmp1=Line(di,Point(10001,di.y));
                        Line tmp2=Line(ins,gao);
                        Point jiao=(tmp1&tmp2).first;
                        ans=fabs(jiao.x-di.x)*fabs(di.y-ins.y)/2.0;
                    }
                }else if(sgn(dd1.x-ins.x)<=0&&sgn(dd2.x-ins.x)<=0){
                    //左侧同理
                    if(sgn(dou.x-huan.x)<=0) ans=0;
                    else{
                        Line tmp1=Line(di,Point(10001,di.y));
                        Line tmp2=Line(ins,gao);
                        Point jiao=(tmp1&tmp2).first;
                        ans=fabs(jiao.x-di.x)*fabs(di.y-ins.y)/2.0;
                    }
                }else{
                    Line tmp1=Line(di,Point(10001,di.y));
                    Line tmp2=Line(ins,gao);
                    Point jiao=(tmp1&tmp2).first;
                    ans=fabs(jiao.x-di.x)*fabs(di.y-ins.y)/2.0;
                }
            }
        }
        printf("%.2f\n",ans);
    }
    return 0;
}