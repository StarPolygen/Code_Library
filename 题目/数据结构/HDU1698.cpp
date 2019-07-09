//kuangbin 专题线段树 Just a Hook
//区间修改
#include<bits/stdc++.h>
#define ll long long
#define maxn 100010
using namespace std;

struct node{
    int l,r;
    ll val;
}tree[maxn<<2];
ll lazy[maxn<<2];
void init(int l,int r,int pos){
    tree[pos].l=l; 
    tree[pos].r=r;
    lazy[pos]=0;
    //初始化叶子节点
    if(l==r){
        tree[pos].val=1;  //根据题目不同，赋予不同的初始值
        return;
    }
    int mid=(l+r)>>1;
    init(l,mid,pos<<1);
    init(mid+1,r,pos<<1|1);
    //由子节点推得当前节点
    tree[pos].val=tree[pos<<1].val+tree[pos<<1|1].val;
}
void pushdown(int pos){ //下放lazy标记,并将当前节点子节点的所有相关信息更新
    if(lazy[pos]){
        lazy[pos<<1]=lazy[pos];
        lazy[pos<<1|1]=lazy[pos];
        //将当前节点子节点的所有信息变为可信
        tree[pos<<1].val=lazy[pos]*(tree[pos<<1].r-tree[pos<<1].l+1);
        tree[pos<<1|1].val=lazy[pos]*(tree[pos<<1|1].r-tree[pos<<1|1].l+1);
        lazy[pos]=0;
    }
}
void pushup(int pos){ //向上更新节点
    tree[pos].val=tree[pos<<1].val+tree[pos<<1|1].val;
}
void update(int l,int r,int from,int to,int pos,int k) //区间更新
{
    if(from<=l&&r<=to){
        tree[pos].val=k*(r-l+1);
        lazy[pos]=k;
        return;
    }
    pushdown(pos);
    int mid=(l+r)>>1;
    if(from<=mid) update(l,mid,from,to,pos<<1,k);
    if(mid<to) update(mid+1,r,from,to,pos<<1|1,k);
    pushup(pos);
}

ll query(int l,int r,int from,int to,int pos)
{
    if(from<=l&&r<=to) return tree[pos].val;
    pushdown(pos);
    int mid=(l+r)>>1;
    ll res=0;
    if(from<=mid) res+=query(l,mid,from,to,pos<<1);
    if(mid<to) res+=query(mid+1,r,from,to,pos<<1|1);
    pushup(pos);
    return res;
}

int main() {
    int T,kcase=0; scanf("%d",&T);
    while(T--){
        int n;
        scanf("%d",&n);
        int q;
        scanf("%d",&q);
        init(1,n,1);
        while(q--){
            int from,to,k;
            scanf("%d%d%d",&from,&to,&k);
            update(1,n,from,to,1,k);
        }
        printf("Case %d: The total value of the hook is %lld.\n",++kcase,query(1,n,1,n,1));

    }
    return 0;
}