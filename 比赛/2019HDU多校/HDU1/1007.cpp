//分数二分 莫比乌斯反演 类欧几里得 Stern-Brocot树

//题意：求分子分母均小于n且互素的第K小的真分数

//解法：根据k做分数二分 二分答案所在实数区间
//判断函数: 根据莫比乌斯化简得 小于等于分数x的满足条件的数有： Σd μ(d) Σi∈[1,n/d] ⌊xi⌋
//又由于x是a/b的形式 和式的后半部分可以O(maxlog(a,c))得到，因此二分judge的复杂度为√nlogC  (整除分块 类欧几里得) 二分部分总复杂度O(2logn*√nlogC) 
//二分到的区间内有且只有一个满足条件的数即为答案，在SB树上搜索区间左端点的后继即可，复杂度最劣O(n)

#include <bits/stdc++.h>
#define ll long long
using namespace std;

typedef pair<ll,ll> Frac;  //pair表示分数

//分数加法 自动化简
Frac operator + (Frac a,Frac b) {
    ll y=a.second/__gcd(a.second,b.second)*b.second,
               x=a.first*(y/a.second)+b.first*(y/b.second);
    return {x,y};
} 
//分数除以整数 自动化简
Frac operator /(Frac a,int b) {
    ll x=a.first,y=a.second*b,
               d=__gcd(x,y);
    return {x/d,y/d};
}
//为之后的分数二分做准备


//处理μ 及其前缀和
const int p_max = 1E6 + 100;
int mu[p_max];
void get_mu() {
    mu[1] = 1;
    static bool vis[p_max];
    static int prime[p_max], p_sz, d;
    mu[1] = 1;
    for (int i = 2; i < p_max; i++) {
        if (!vis[i]) {
            prime[p_sz++] = i;
            mu[i] = -1;
        }
        for (int j = 0; j < p_sz && (d = i * prime[j]) < p_max; ++j) {
            vis[d] = 1;
            if (i % prime[j] == 0) {
                mu[d] = 0;
                break;
            }
            else mu[d] = -mu[i];
        }
    }mu[0]=0;
    for(int i=1;i<p_max;++i) mu[i]=mu[i-1]+mu[i];
} 


//类欧几里得求和 Σi∈[1,n/l] ai/b
ll f(ll a,ll b,ll c,ll n){
    if(a==0)return (n+1)*(b/c);
    if(a>=c||b>=c)return (f(a%c,b%c,c,n)+(__int128)n*(n+1)/2*(a/c)+(n+1)*(b/c));
    ll M=(a*n+b)/c;
    return (__int128)n*M-f(c,c-b-1,a,M-1);
}
//求有多少满足条件的分数 ≤ 当前二分的数x
ll Count(Frac x,int n) {   
    ll res=0;
    for(int l=1,r;l<=n;l=r+1) {
        r=n/(n/l);
        res+=f(x.first,0,x.second,n/l)*(mu[r]-mu[l-1]);
    }
    return res;
}


//SB树上搜索L后继  SB树是二叉排序树
//从区间左端点L=a/b出发 在Stern-Brocot树上搜索答案 复杂度：O(n) 当答案为1/n时取到最劣
Frac Gen(ll a,ll b,int n,ll k) {
    Frac l{0,1},mid{1,1},r{1,0},res{-1,-1};
    ll x=a,y=b;    //在SB树上查找第一个≥L的数 （SB树中L的后继）
    //停止条件:1.x=y代表找到L  2.分子或分母即将超过n 找到的L后继为大于L的最小分数 
    while(x!=y && max(mid.first,mid.second)<=n) { 
        if(a*mid.second<b*mid.first)   //更新后继
            res=mid;
        if(x<y) {     //若x<y L在当前区间左子树 向左搜索 分数变小
            tie(l,mid,r)=make_tuple(l,make_pair(l.first+mid.first,l.second+mid.second),mid);
            y-=x;
        }
        else {  //若x>y L在当前区间右子树 向右搜索 分数变大
            tie(l,mid,r)=make_tuple(mid,make_pair(mid.first+r.first,mid.second+r.second),r);
            x-=y;
        }
    }
    return res;
}



int main() {
    //两者搭配使用可以有效加速IO
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    
    get_mu();
    int T;scanf("%d",&T);
    while(T--) {
        int n;ll k;
        cin>>n>>k;
        //实数域上进行分数二分，二分到的是答案所在区间
        Frac l{0,1},r{1,1};

        //二分：O(2logn*√nlogC) 根据K二分得到答案所在区间 
        for(int t=40;t--;) {
            Frac mid=(l+r)/2;
            if(Count(mid,n)<k) { //小于等于mid的满足条件分数个数 < k ,说明左端还能继续紧缩
                l=mid;
            } else  //反之右端可以紧缩
                r=mid;
        }

        //从所获区间左端出发  在Stern-Brocot树上搜索该区间内满足条件的数 即为答案
        auto Ans=Gen(l.first,l.second,n,k);
        printf("%lld/%lld\n",Ans.first,Ans.second);
    }
    return 0;
}