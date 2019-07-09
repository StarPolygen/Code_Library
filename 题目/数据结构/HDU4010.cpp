//HDU 4010 
//LCT区间修改模板题

#include <bits/stdc++.h>
using namespace std;
//相适配的·宏
#define N 300008               
#define lson l,m,rt<<1
#define rson m+1,r,rt<<1|1 
#define clr(x,v) memset(x,v,sizeof(x));
#define rep(x,y,z) for (int x=y;x<=z;x++)
#define repd(x,y,z) for (int x=y;x>=z;x--)
/**************************************************************************/

//spaly部分 
//val：点值  mx：维护最大值  tag：额外lz标记  
int val[N],c[N][2],fa[N],mx[N],tag[N],rev[N],lt[N],st[N];
int n,q,sum; 
struct line{
    int u,v,nt;
}eg[N*2];
void addedge(int u,int v){ //加边
    eg[++sum]=(line){u,v,lt[u]};
    lt[u]=sum;
}
void init(){ //初始化
    rep(i,1,n) val[i]=c[i][0]=c[i][1]=mx[i]=tag[i]=rev[i]=lt[i]=fa[i]=0;
    sum=1;
}
void dfs(int u){   //建树
    for (int i=lt[u];i;i=eg[i].nt){
        int v=eg[i].v;
        if (fa[v] || v==1) continue;
        fa[v]=u;
        dfs(v);
    }
}
bool isroot(int k){  //判断节点是否为一个Splay的根（与普通Splay的区别1）
    return c[fa[k]][0]!=k && c[fa[k]][1]!=k;
}
void pushup(int x){  //上传信息
    int l=c[x][0],r=c[x][1];
    mx[x]=max(max(mx[l],mx[r]),val[x]);
}
void pushdown(int x){  //判断并释放懒标记
    int l=c[x][0],r=c[x][1];
    if (rev[x]){ //自带的区间反转lazy标记
        if (l) rev[l]^=1;
        if (r) rev[r]^=1;
        rev[x]^=1;
        swap(c[x][0],c[x][1]);
    }
    if (tag[x]){ //额外添加的线段树区间修改lazy标记
        if (l) {tag[l]+=tag[x]; mx[l]+=tag[x], val[l]+=tag[x]; }
        if (r) {tag[r]+=tag[x]; mx[r]+=tag[x], val[r]+=tag[x]; }
        tag[x]=0;
    }
}
void rotate(int x){ //一次旋转
    int y=fa[x],z=fa[y],l,r;
    if (c[y][0]==x) l=0; else l=1; r=l^1;
    if (!isroot(y)){
        if (c[z][0]==y) c[z][0]=x; else c[z][1]=x;
    }
    fa[x]=z; fa[y]=x; fa[c[x][r]]=y;
    c[y][l]=c[x][r]; c[x][r]=y;
    pushup(y); pushup(x);
}
void splay(int x){  //splay转到根上
    int top=0; st[++top]=x;
    for (int i=x;!isroot(i);i=fa[i]) st[++top]=fa[i];
    while (top) pushdown(st[top--]);
    while (!isroot(x)){
        int y=fa[x],z=fa[y];
        if (!isroot(y)){
            if (c[y][0]==x^c[z][0]==y) rotate(x);
            else rotate(y);
        }
        rotate(x);
    }
}

//LCT部分
void access(int x){//访问
    int t=0;
    while (x){
        splay(x);
        c[x][1]=t;
        pushup(x);            
        t=x; x=fa[x];
    }
}
int find(int u){//找根（在真实的树中的）
    access(u); splay(u);
    while (c[u][0]) u=c[u][0];
    return u;
}
bool judge(int u,int v){//判断uv是否在同一颗树内（原树）
    return find(u)==find(v);
}
void rever(int u){//区间翻转
    access(u); splay(u); rev[u]^=1;
}
void link(int u,int v){//连边
    rever(u); fa[u]=v; 
}
void cut(int u,int v){//断边
    rever(u); access(v); splay(v); fa[c[v][0]]=0; c[v][0]=0; pushup(v);
}
void add(int u,int v,int w){//区间加
    rever(u); access(v); splay(v); tag[v]+=w; mx[v]+=w; val[v]+=w;
}
void query(int u,int v){//区间查询
    rever(u); access(v); splay(v); printf("%d\n",mx[v]);
}
int main(){
    while (~scanf("%d",&n))
    {
        init();
        rep(i,1,n-1){
            int u,v;
            scanf("%d%d",&u,&v);//双向加边
            addedge(u,v); addedge(v,u);
        }
        rep(i,1,n){
            int x;
            scanf("%d",&x);//初始化节点的权值和需要维护的最大值
            val[i]=mx[i]=x;
        }
        dfs(1);
        scanf("%d",&q);
        while (q--){
            int x,u,v,w;
            scanf("%d",&x);
            if (x==1){
                scanf("%d %d",&u,&v);        
                if (!judge(u,v)) link(u,v); else puts("-1");
            }
            if (x==2){
                scanf("%d %d",&u,&v);        
                if (judge(u,v) && u!=v) cut(u,v); else puts("-1");
            }
            if (x==3){
                scanf("%d %d %d",&w,&u,&v);
                if (judge(u,v)) add(u,v,w);    else puts("-1");
            }
            if (x==4){
                scanf("%d %d",&u,&v);        
                if (judge(u,v)) query(u,v); else puts("-1");
            }
        }
        printf("\n");
    }
}