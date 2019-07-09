//区间修改成三次方，查询mod 99971的和
//由模数小猜测具有循环节 打表得到所有数三次对99971取模循环节均为48的因数
//因此线段树 区间修改 可做
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll mod=99971;
const ll maxn=1e5+7;
const ll maxl=48;
ll tree[maxn<<2][maxl];
ll lazy[maxn<<2];
int N,Q;
ll p3(ll x)
{return x*x%mod*x%mod;}
void init(int l, int r,int pos){
    lazy[pos]=0;
    if(l==r) {
        scanf("%lld",tree[pos]);
        tree[pos][0]%=mod;
        for(int i=1;i<maxl;i++)
            tree[pos][i]=p3(tree[pos][i-1]);
        return;
    }
    int mid=(l+r)>>1;
    init(l,mid,pos<<1);
    init(mid+1,r,pos<<1|1);
    for(int i=0;i<maxl;i++) 
        tree[pos][i]=(tree[pos<<1][i]+tree[pos<<1|1][i])%mod;
}
int from,to;
void down(int pos){
    if(lazy[pos]){
        lazy[pos<<1]=(lazy[pos<<1]+lazy[pos])%maxl;
        lazy[pos<<1|1]=(lazy[pos<<1|1]+lazy[pos])%maxl;
        lazy[pos]=0;
    }
}

void up(int pos){
    for(int i=0;i<maxl;i++){
        ll a=(i+lazy[pos<<1])%maxl;
        ll b=(i+lazy[pos<<1|1])%maxl;
        tree[pos][i]=(tree[pos<<1][a]+tree[pos<<1|1][b])%mod;
    }
}

void update(int l,int r,int from,int to,int pos)
{
    if(from<=l&&r<=to){
        lazy[pos]=(lazy[pos]+1)%maxl;
        return;
    }
    down(pos);
    int mid=(l+r)>>1;
    if(from<=mid) update(l,mid,from,to,pos<<1);
    if(mid<to) update(mid+1,r,from,to,pos<<1|1);
    up(pos);
}

ll query(int l,int r,int from,int to,int pos)
{
    if(from<=l&&r<=to) return tree[pos][lazy[pos]];
    down(pos);
    int mid=(l+r)>>1;
    ll res=0;
    if(from<=mid) res+=query(l,mid,from,to,pos<<1);
    if(mid<to) res+=query(mid+1,r,from,to,pos<<1|1);
    up(pos);
    return res%mod;
}

int main() {
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf("%d%d",&N,&Q);
        init(1,N,1);
        while(Q--){
            int op;
            scanf("%d%d%d",&op,&from,&to);
            if(op==1) 
                update(1,N,from,to,1);
            else 
                printf("%lld\n",query(1,N,from,to,1));
        }
    }
    return 0;
}