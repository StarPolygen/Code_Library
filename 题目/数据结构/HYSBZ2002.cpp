//Bounce 弹飞绵羊
//LCT 单点修改模板题
#include<bits/stdc++.h>
using namespace std;

//LCT 模板
#define R register int
#define I inline void
#define lc c[x][0]
#define rc c[x][1]

const int N=200010;//点数
int f[N],c[N][2],v[N],s[N],st[N];
//f:父节点  c[][0]:左子  v:节点的值  s:子树下的储存的权值数（包括重复权值） r:区间翻转的lazy
bool r[N];

//splay 部分
inline bool nroot(R x){//判断节点是否为一个Splay的根（与普通Splay的区别1）
    return c[f[x]][0]==x||c[f[x]][1]==x;
}//原理很简单，如果连的是轻边，他的父亲的儿子里没有它
I pushup(R x){//上传信息
    s[x]=s[lc]+s[rc]+v[x];
}
I pushr(R x){R t=lc;lc=rc;rc=t;r[x]^=1;}//翻转操作
I pushdown(R x){//判断并释放懒标记
    if(r[x]){
        if(lc)pushr(lc);
        if(rc)pushr(rc);
        r[x]=0;
    }
}
I rotate(R x){//一次旋转
    R y=f[x],z=f[y],k=c[y][1]==x,w=c[x][!k];
    if(nroot(y))c[z][c[z][1]==y]=x;c[x][!k]=y;c[y][k]=w;//额外注意if(nroot(y))语句，此处不判断会引起致命错误（与普通Splay的区别2）
    if(w)f[w]=y;f[y]=x;f[x]=z;
    pushup(y);
}
I splay(R x){//只传了一个参数，因为所有操作的目标都是该Splay的根（与普通Splay的区别3）
    R y=x,z=0;
    st[++z]=y;//st为栈，暂存当前点到根的整条路径，pushdown时一定要从上往下放标记（与普通Splay的区别4）
    while(nroot(y))st[++z]=y=f[y];
    while(z)pushdown(st[z--]);
    while(nroot(x)){
        y=f[x];z=f[y];
        if(nroot(y))
            rotate((c[y][0]==x)^(c[z][0]==y)?x:y);
        rotate(x);
    }
    pushup(x);
}

//LCT 部分
I access(R x){//访问
    for(R y=0;x;x=f[y=x])
        splay(x),rc=y,pushup(x);
}
I makeroot(R x){//换根
    access(x);splay(x);
    pushr(x);
}
int findroot(R x){//找根（在真实的树中的）
    access(x);splay(x);
    while(lc)pushdown(x),x=lc;
    splay(x);
    return x;
}
I split(R x,R y){//提取路径
    makeroot(x);
    access(y);splay(y);
}
I link(R x,R y){//连边
    makeroot(x);
    if(findroot(y)!=x)f[x]=y;
}
I cut(R x,R y){//断边
    makeroot(x);
    if(findroot(y)==x&&f[y]==x&&!c[y][0]){
        f[y]=c[x][1]=0;
        pushup(x);
    }
}

int arr[N];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        v[i]=1;
    }
    v[n+1]=0;
    for(int i=1;i<=n;i++){
        scanf("%d",&arr[i]);
        if(i+arr[i]<=n) f[i]=i+arr[i];
        else f[i]=n+1;
    }
    int m;
    scanf("%d",&m);
    for(int i=1;i<=m;i++){
        int op,a,b;
        scanf("%d%d",&op,&a);
        a++;
        if(op==1) {
            split(n+1,a);
            printf("%d\n",s[a]);
        }else{
            scanf("%d",&b);
            if(a+arr[a]<=n)    cut(a,a+arr[a]);
            else cut(a,n+1);
            // cut(a,f[a]);//这样写是对LCT的错误应用，在调用时要以数值为准，决不能使用splay的内部关系数组，如f，因为他们随时会随着splay或LCT的操作被修改
            if(a+b<=n) link(a,a+b); 
            else link(a,n+1);
            arr[a]=b;
        }
    }
}
/*
6
1 1 2 1 1 2
5
1 1
4
2 1 5
1 1
1
2 1 2
1 1
4
*/