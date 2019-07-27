//作者：小明
//n个点的树上有k个人，可以选择一个树上一个点会合，问全部会合最短时间，已知走一条边要花费1单位时间，会合时间是所有人中最后到达该点的人花费时间
//删除外层多余的树枝，剩余的树最外端都是这k个人，求(树的直径+1)/2即可
#include<cstdio>
using namespace std;
const int maxn=1E6;
 
struct Edge{
    int from;
    int to;
    int next;
} edge[maxn];
int head[maxn];
int valid[maxn];
int degree[maxn];
int tot;
int ans;
int ansp;
 
inline void init(int n) {
    for (int i=1;i<=n;i++) {
        head[i]=0;
        valid[i]=1;
        degree[i]=0;
    }
    tot=0;
    ans=0;
}
 
inline void addedge(int x,int y) {
    tot++;
    edge[tot].next=head[x];
    edge[tot].from=x;
    edge[tot].to=y;
    head[x]=tot;
}
 
bool del(int u, int fa) {
    bool pd=false;
    for (int p=head[u];p;p=edge[p].next) {
        int v=edge[p].to;
        if (v==fa) {continue;}
        if (del(v, u)) {
            pd=true;
        } else {
            degree[u]--;
            degree[v]--;
        }
    }
     
    if (valid[u]==2 || pd) {
        return true;
    } else {
        valid[u]=0;
        return false;
    }
}
 
void getres(int u,int fa,int dis){
    if (dis>ans) {
        ans=dis;
        ansp=u;
    }
    for (int p=head[u];p;p=edge[p].next) {
        int v=edge[p].to;
        if (v==fa) {continue;}
        if (valid[v]==0) {continue;}
        getres(v,u,dis+1);
    }
    return ;
}
 
int main() {
    int n,k;
    scanf("%d%d", &n,&k);
    init(n);
     
    for (int i=1;i<n;i++) {
        int x,y;
        scanf("%d%d", &x,&y);
        degree[x]++;
        degree[y]++;
        addedge(x,y);
        addedge(y,x);
    }
    for (int i=1;i<=k;i++) {
        int x;
        scanf("%d", &x);
        valid[x]=2;
    }
    for (int i=1;i<=n;i++) {
        if (valid[i]==2) {
            del(i,0);
            break;
        }
    }
     
//  for (int i=1;i<=n;i++) {
//      printf("?? %d %d\n", valid[i], degree[i]);
//  }
     
    for (int i=1;i<=n;i++) {
        if (degree[i]==1 && valid[i]==2) {
            getres(i,0,0);
            getres(ansp,0,0);
            break;
        }
    }
    printf("%d\n", (ans+1)/2);
    return 0;
     
}
 
/*
9 3
1 3
3 5
3 4
1 2
1 6
6 8
6 7
8 9
5 2 9
 
*/