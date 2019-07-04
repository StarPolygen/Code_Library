//线段相交
//kuangbin专题十三 基础计算几何 
//TOY Storage POJ 2398
//将2318分割线排序，稍微改改即可
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
#define maxn 5010
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

bool cmp(Line a,Line b){
    return a.s.x<b.s.x;
}

Line l[maxn];
int ans1[maxn];
int ans2[maxn];
void ini(){
    memset(l,0,sizeof(l));
    memset(ans1,0,sizeof(ans1));
    memset(ans2,0,sizeof(ans2));
}
int main() {
    while(true){
        ini();
        int n,m; 
        double x1,y1,x2,y2;
        scanf("%d",&n);
        if(n==0) break;
        scanf("%d%lf%lf%lf%lf",&m,&x1,&y1,&x2,&y2);
        for(int i=1;i<=n;i++){
            double ui,li;
            scanf("%lf %lf",&ui,&li);
            Point a(ui,y1);
            Point b(li,y2);
            Line ab(a,b);
            l[i]=ab;
        }
        l[n+1]=Line(Point(x2,y2),Point(x2,y1));
        sort(l+1,l+n+1,cmp);
        for(int i=1;i<=m;i++){
            double xj,yj;
            scanf("%lf %lf",&xj,&yj);
            Line cur=Line(Point(xj,yj),Point(x2,y1));
            for(int j=1;j<=n+1;j++){
                if((l[j]&cur).first.x>xj&&(l[j]&cur).first.y<=y1&&(l[j]&cur).first.y>=y2){
                    ans1[j-1]++; break;
                }
            }
        }
        for(int i=0;i<=n;i++){
            ans2[ans1[i]]++;
        }
        printf("Box\n");
        for(int i=0;i<=n;i++){
            if(ans2[i]&&i) printf("%d: %d\n",i,ans2[i]);
        }
    }
    return 0;
}
    
    
    
