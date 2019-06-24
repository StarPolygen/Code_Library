//kuangbin专题十三 基础计算几何 
//POJ 3449
//判断几何图形相交 1A
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

//线段相交判定，包括重合
bool SegIct(Line l1,Line l2){
    int state=(l1&l2).second;
    Point pt=(l1&l2).first;
    double x1,x2,x3,x4,y1,y2,y3,y4;
    x1=l1.e.x; y1=l1.e.y;
    x2=l1.s.x; y2=l1.s.y;
    x3=l2.e.x; y3=l2.e.y;
    x4=l2.s.x; y4=l2.s.y;
    if(x1>x2) swap(x1,x2);
    if(y1>y2) swap(y1,y2);
    if(x3>x4) swap(x3,x4);
    if(y3>y4) swap(y3,y4);
    double x=pt.x;
    double y=pt.y;
    if(state==0||(state==2&&sgn(x-x1)>=0&&sgn(x2-x)>=0&&sgn(y-y1)>=0&&sgn(y2-y)>=0&&
    sgn(x-x3)>=0&&sgn(x4-x)>=0&&sgn(y-y3)>=0&&sgn(y4-y)>=0)) return 1;
    else return 0;

}
char c;
int tot;
pair<int,Line> all[550];
char ins[30][30];
char type[20];
void init(){
    memset(all,0,sizeof(all));
    memset(ins,0,sizeof(ins));
    memset(type,0,sizeof(type));
}
void solve(){
    for(int i=0;i<tot;i++){
        // printf("%c :(%.0f,%.0f) (%.0f,%.0f)\n",'A'+all[i].first,all[i].second.s.x,all[i].second.s.y,all[i].second.e.x,all[i].second.e.y);
    }
    for(int i=0;i<tot;i++){
        for(int j=0;j<tot;j++){
            Line l1=all[i].second;
            Line l2=all[j].second;
            if(SegIct(l1,l2)) ins[all[i].first][all[j].first]++;
            // if(SegIct(l1,l2)&&all[i].first==0&&all[j].first==1) {
                // printf("%c :(%.0f,%.0f) (%.0f,%.0f)\n",'A'+all[i].first,all[i].second.s.x,all[i].second.s.y,all[i].second.e.x,all[i].second.e.y);
                // printf("%c :(%.0f,%.0f) (%.0f,%.0f)\n",'A'+all[j].first,all[j].second.s.x,all[j].second.s.y,all[j].second.e.x,all[j].second.e.y);
            // }
        }
    }
    for(int i=0;i<=25;i++){
        if(ins[i][29]!=1) continue;
        else{
            int num=0;int tmp=0;
            // printf("%c :",('A'+i));
            for(int j=0;j<=25;j++){
                if(ins[i][j]!=0&&j!=i) num++;
            }
            if(num==0) printf("%c has no intersections",'A'+i);
            else{
                for(int j=0;j<=25;j++){
                    if(ins[i][j]!=0&&j!=i){
                        if(tmp==0) printf("%c intersects with %c",'A'+i,'A'+j);
                        else if(tmp==num-1&&num!=2) printf(", and %c",'A'+j);
                        else if(tmp==num-1&&num==2) printf(" and %c",'A'+j);
                        else printf(", %c",'A'+j);
                        tmp++;
                    }
                }
            }
        }
        printf("\n");
    }
    tot=0;
    init();
    printf("\n");
    return;
}

int main() {
    init();
    while(true){
        scanf("%c",&c);
        // printf("%c\n",c);
        if(c=='-')  {
           getchar(); solve();
        }
        else if(c=='.')  break;
        else{
            ins[c-'A'][29]=1;
            scanf(" %s",type);
            if(type[0]=='s'){
                int x1,y1,x2,y2,x3,y3,x4,y4;
                scanf(" (%d,%d) (%d,%d)",&x1,&y1,&x3,&y3);
                getchar();
                // printf("%d %d %d %d\n",x1,y1,x3,y3);
                double midx=(x1+x3)/2.0;
                double midy=(y1+y3)/2.0;
                double xcha=midx-x1;
                double ycha=midy-y1;
                Point P1=Point(midx+ycha,midy-xcha);
                Point P2=Point(midx-ycha,midy+xcha);
                all[tot++]=make_pair(c-'A',Line(Point(x1,y1),P1));
                all[tot++]=make_pair(c-'A',Line(Point(x1,y1),P2));
                all[tot++]=make_pair(c-'A',Line(Point(x3,y3),P1));
                all[tot++]=make_pair(c-'A',Line(Point(x3,y3),P2));
                // printf("s get\n");
            }else if(type[0]=='r'){
                int x1,y1,x2,y2,x3,y3,x4,y4;
                scanf(" (%d,%d) (%d,%d) (%d,%d)",&x1,&y1,&x2,&y2,&x3,&y3);
                getchar();
                int xcha=x3-x2;
                int ycha=y3-y2;
                Point P4=Point(x1+xcha,y1+ycha);
                all[tot++]=make_pair(c-'A',Line(Point(x1,y1),P4));
                all[tot++]=make_pair(c-'A',Line(Point(x3,y3),P4));
                all[tot++]=make_pair(c-'A',Line(Point(x1,y1),Point(x2,y2)));
                all[tot++]=make_pair(c-'A',Line(Point(x2,y2),Point(x3,y3)));
                // printf("r get\n");
            }else if(type[0]=='l'){
                int x1,x2,y1,y2;
                scanf(" (%d,%d) (%d,%d)",&x1,&y1,&x2,&y2);
                getchar();
                all[tot++]=make_pair(c-'A',Line(Point(x1,y1),Point(x2,y2)));
                // printf("l get\n");
            }else if(type[0]=='t'){
                int x1,y1,x2,y2,x3,y3;
                scanf(" (%d,%d) (%d,%d) (%d,%d)",&x1,&y1,&x2,&y2,&x3,&y3);
                getchar();
                all[tot++]=make_pair(c-'A',Line(Point(x1,y1),Point(x2,y2)));
                all[tot++]=make_pair(c-'A',Line(Point(x2,y2),Point(x3,y3)));
                all[tot++]=make_pair(c-'A',Line(Point(x3,y3),Point(x1,y1)));
                // printf("t get\n");
            }else if(type[0]=='p'){ 
                int n;
                scanf(" %d",&n);
                Point pt[n+10];
                for(int i=1;i<=n;i++){
                    int a,b;
                    scanf(" (%d,%d)",&a,&b);
                    pt[i]=Point(a,b);
                }
                getchar();
                // for(int i=1;i<=n;i++) printf("%.0f %.0f\n",pt[i].x,pt[i].y);
                for(int i=1;i<n;i++){
                    all[tot++]=make_pair(c-'A',Line(pt[i],pt[i+1]));
                }
                all[tot++]=make_pair(c-'A',Line(pt[n],pt[1]));
                // printf("p get\n");
            }else{}

        }
    }
    return 0;
}
    
    
    
