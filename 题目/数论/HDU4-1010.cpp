//根据复杂度 妙用分块
//给定n (1e18) 求n分解质因数的最大指数为多少
//观察可知道前期指数增加比较密集 而当底数开始大起来时，指数增加极为缓慢
//因此为了减小复杂度，可以非常巧妙地将n的所有小于等于n^1/5的因数全部暴力处理掉 之后再对剩余的质因数大于n^1/5的聊聊情况讨论
//      预处理前10000中的质数O(10000) 针对每个n进行分解O(90*T)=O(4.5e5)
//      处理完小于等于n^1/5的质因数后 剩余的质因数的次幂之和必然≤4 此时可以根据情况分类讨论 O(T)=O(5e4 )
#pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int INF=1e9;

inline int ctz(ll x) { return __builtin_ctzll(x); }
ll gcd(ll a, ll b) {
    if (!a) return b; if (!b) return a;
    int t = ctz(a | b);
    a >>= ctz(a);
    do {
        b >>= ctz(b);
        if (a > b) swap(a, b);
        b -= a;
    } while (b);
    return a << t;
} 
ll mul(ll u, ll v, ll p) { // 卡常
    ll t = u * v - ll((long double) u * v / p) * p;
    return t < 0 ? t + p : t;
}
ll bin(ll x, ll n, ll mod) {
    ll ret = mod != 1;
    for (x %= mod; n; n >>= 1, x = mul(x,x,mod))
        if (n & 1) ret =mul(ret,x,mod);
    return ret;
}
bool checkQ(ll a, ll n) {
    if (n == 2 || a >= n) return 1;
    if (n == 1 || !(n & 1)) return 0;
    ll d = n - 1;
    while (!(d & 1)) d >>= 1;
    ll t = bin(a, d, n);  // 不一定需要快速乘
    while (d != n - 1 && t != 1 && t != n - 1) {
        t = mul(t, t, n);
        d <<= 1;
    }
    return t == n - 1 || d & 1;
}

bool primeQ(ll n) {
    static vector<ll> t = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    if (n <= 1) return false;
    for (ll k: t) if (!checkQ(k, n)) return false;
    return true;
}

const int MAXSIZE=10001; 
int Mark[MAXSIZE],ind=0;     //prime[0]起 
int prime[MAXSIZE];    //判断是否是一个素数  Mark 标记数组 ind 素数个数  
void Prime(){	
	ind=0;
    for (int i = 2; i < MAXSIZE; i++){
        if(Mark[i]) continue;//如标记则跳过  
        prime[ind++] = i;//否则得到一个素数
        for (int j = i + i; j < MAXSIZE; j += i) Mark[j] = 1;//标记目前得到的素数的i倍为非素数
    }
}

inline int min(int a, int b){
    return a > b? b : a;
}


int main() {
    Prime();
    int T;scanf("%d",&T);
    while(T--){
        ll num; scanf("%lld",&num);
        int ans=INF;
        for(int i=0;i<ind;i++){
            if(num%prime[i]==0){
                int tmp=0;
                while(num%prime[i]==0){
                    num/=prime[i];
                    tmp++;
                }
                ans=min(ans,tmp);
            }
        }
        if(num==1){ printf("%d\n",ans); continue;}
        else{
            int sq3=pow(num,1/3.0);int sq32=sq3+1; int sq31=sq3-1;
            int sq4=sqrt(sqrt(num)); int sq42=sq4+1; int sq41=sq4-1;
            int sq2=sqrt(num); int sq21=sq2+1; int sq20=sq2-1;
            if(primeQ(num)) {ans=1; printf("1\n"); continue;}
            else if(1ll*sq3*sq3*sq3==num||1ll*sq31*sq31*sq31==num||1ll*sq32*sq32*sq32==num) ans=min(ans,3);
            else if(1ll*sq4*sq4*sq4*sq4==num||1ll*sq41*sq41*sq41*sq41==num||1ll*sq42*sq42*sq42*sq42==num) ans=min(ans,4);
            else if(1ll*sq2*sq2==num||1ll*sq20*sq20==num||1ll*sq21*sq21==num) ans=min(ans,2);
            else ans=1;
        }
        
        printf("%lld\n",ans);
        
        
    }
    return 0;
}