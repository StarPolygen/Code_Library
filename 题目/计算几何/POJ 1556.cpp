//kuangbin专题十三 基础计算几何 
//The Doors POJ 1556
//Dijkstra + 判断垂直的直线线段相交
//由于初始化的原因未能1A！！
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

struct doorway{
    double x,y1,y2,y3,y4;
    //缝隙为y1y2,y3y4 障碍为0-y1,y2-y3,y4-10
}st [80];

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


const double INF=100000.0;
const int MAXN=1000;
struct qnode{
    int v;
    double c;
    qnode(int _v=0,double _c=0):v(_v),c(_c){}
    bool operator <(const qnode &r)const {
        return sgn(c-r.c)>=0;
    }
};
struct Edge{
    int v;
    double cost;
    Edge(int _v=0,double _cost=0):v(_v),cost(_cost){}
};
vector<Edge>E[MAXN];
bool vis[MAXN];
double dist[MAXN];
void Dijkstra(int n,int start)//点的编号从1开始
{
    memset(vis,false,sizeof(vis));
    for(int i=1;i<=n;i++) dist[i]=INF;
    priority_queue<qnode>que;
    while(!que.empty())que.pop();
    dist[start]=0;
    que.push(qnode(start,0));
    qnode tmp;
    while(!que.empty())
    {
        tmp=que.top();
        que.pop();
        int u=tmp.v;
        if(vis[u])continue;
        vis[u]=true;
        for(int i=0;i<E[u].size();i++)  {
            int v=E[tmp.v][i].v;
            double cost=E[u][i].cost;
            if(!vis[v]&&dist[v]>dist[u]+cost)  {
                dist[v]=dist[u]+cost;
                que.push(qnode(v,dist[v]));
            }
        }
    }
}
void addedge(int u,int v,double w){
    E[u].push_back(Edge(v,w));
}
void ini(){
    memset(st,0,sizeof(st));
    memset(E,0,sizeof(E));
    memset(vis,0,sizeof(vis));
    memset(dist,0,sizeof(dist));
}



Point arr[200];
Line vet[80];
int main() {
    int n; 
    while(true){
        ini();
        scanf("%d",&n);
        if(n==-1) break;
        Point s=Point(0,5); arr[1]=s;
        Point t=Point(10,5); arr[4*n+2]=t;
        for(int i=1;i<=n;i++){
            scanf("%lf%lf%lf%lf%lf",&st[i].x,&st[i].y1,&st[i].y2,&st[i].y3,&st[i].y4);
            int tmp=4*(i-1)+1;
            arr[tmp+1]=Point(st[i].x,st[i].y1);
            arr[tmp+2]=Point(st[i].x,st[i].y2);
            arr[tmp+3]=Point(st[i].x,st[i].y3);
            arr[tmp+4]=Point(st[i].x,st[i].y4);
            vet[i]=Line(Point(st[i].x,0),Point(st[i].x,10));
        }
        for(int i=1;i<4*n+2;i++){
            for(int j=i+1;j<=4*n+2;j++){
                Line cur=Line(arr[i],arr[j]);
                int flag=1; int k,f;
                if(i==1) k=1;
                else k=(i-2)/4+2;
                if(j==4*n+2) f=n;
                else f=(j-2)/4;
                for(k;k<=f;k++){
                    if((vet[k]&cur).second==2){
                        double y0=(vet[k]&cur).first.y;
                        if((sgn(st[k].y1-y0)>=0||(sgn(y0-st[k].y2)>=0&&sgn(st[k].y3-y0)>=0)||sgn(y0-st[k].y4)>=0)){
                            flag=0; break;
                        }
                    }
                }
                if(flag==1){
                    // printf("%d %d %lf\n",i,j,dis(arr[i],arr[j]));
                    addedge(i,j,dis(arr[i],arr[j]));
                    addedge(j,i,dis(arr[i],arr[j]));
                } 
            }
        }
        Dijkstra(4*n+2,1);
        printf("%.2f\n",dist[4*n+2]);

    }
    
    return 0;
}