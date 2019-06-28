//kuangbin专题七 线段树 
//单点修改 区间查询 最值
//线段树的题目 最重要的是确定要存储什么值 可以完成题目所需要求
#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int maxn=200010;
int n,m;
int st[maxn];

//节点,其中1为根节点
struct node{
    int l,r;
    int ms;
}a[maxn<<2];


//线段树三部曲：建树,修改,查询
//建树
void init(int l,int r,int i){//初始化线段树节点,将未被修改之前的状态计算好保存在各个节点内   
    a[i].l=l;
    a[i].r=r;
    if(l==r) {
        a[i].ms=st[l];//叶子
        return;
    }
    //设置子节点
    int mid=(l+r)>>1;
	init(l,mid,2*i);
	init(mid+1,r,2*i+1);
    //由子节点计算当前节点
    a[i].ms=max(a[2*i].ms,a[2*i+1].ms);
}


//单点修改
void change(int i,int t,int x){//i:节点编号  t:被单点修改的数据下标  x：更新值
    if(a[i].l==a[i].r){//叶子
        a[i].ms=x;
        return;
    }//查询子节点直至访问到所需区间并更新
    int mid=(a[i].l+a[i].r)>>1;
	if(t<=mid) change(2*i,t,x);
	else change(2*i+1,t,x);

    //更新当前节点
    a[i].ms=max(a[2*i].ms,a[2*i+1].ms);
}


//单点查询
int query(int i,int t){//i:节点编号 t:被查询的数据下标
    if(a[i].r==a[i].l) 
		return a[i].ms;
	int mid=(a[i].l+a[i].r)>>1;
	if(t<=mid) return query(2*i,t);
	else return query(2*i+1,t);
}

//区间查询1：针对单点修改
int Max=0;
void query(int i,int l,int r){
    //若[L,R]和当前节点代表区间不相交,停止继续搜素
    if(r<a[i].l||l>a[i].r) return;
    //若[L,R]完全包含当前节点代表区间,用当前节点信息更新查询结果
    if(a[i].l>=l&&a[i].r<=r) {
        Max=max(Max,a[i].ms);
        return;
    }
    //否则,递归处理当前节点左右两个子节点
    query(2*i,l,r);
    query(2*i+1,l,r);
}


int main() {
    while(~scanf("%d %d",&n,&m)){
        getchar();
        memset(st,0,sizeof(st));
        memset(a,0,sizeof(a));
        for(int i=1;i<=n;i++){
            scanf("%d",&st[i]);
        }
        getchar();
        init(1,n,1);
        char c;
        int a,b,l,r;
        for(int i=1;i<=m;i++){
            scanf("%c",&c);
            if(c=='Q') {
                scanf("%d%d",&l,&r);
                getchar();
                //每次查询前,查询结果清空
                Max=0;
                query(1,l,r);
                printf("%d\n",Max);
            }else if(c=='U'){
                scanf("%d%d",&a,&b);
                getchar();
                change(1,a,b);
            }
        }
    }
    return 0;
}
