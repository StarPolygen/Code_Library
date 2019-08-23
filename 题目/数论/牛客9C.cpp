//高斯二项式系数推广 Gaussian binomial coefficient 
//规律 结论 OEIS/WIKI
//题意：给定集合数组{ai}，统计对于ai的所有排列集合{ri} Σq^t{ri}为多少  其中t{ri}为排列ri的逆序对数
//      也就是求所有排列的q的逆序对次幂之和
//解题：高斯二项式系数 是用于解决统计{0，1}集合的排列的q的逆序对次幂和的一种组合数
//      形式类比二项式系数  C(m,r)=m*m-1*...*m-r+1/1*2*...r   而G（m,r）=(1-q^m)(1-q^m-1)...(1-q^m-r+1)/(1-q)(1-q2)..(1-q^r)
//推广： 本题不仅是{0,1}集合的排列，观察得到高斯系数也可以推广到包含更多元素集合的排列
//      高斯二项式系数可类比求01排列数公式     m!/r!(m-r)!  因为总共m元素，其中r个0，m-r个1   得G（m,r）=(1-q^m)(1-q^m-1)...(1-q)/[(1-q)(1-q2)..(1-q^r)*(1-q)(1-q2)..(1-q^m-r)]
//      推广之后类比                         m!/(r1!r2!...rn!)    r1+...rn=m        总共m元素，其中r1个元素a，r2个元素b...
//      得到         G（m,r）=(1-q^m)(1-q^m-1)...(1-q)/(1-q)(1-q2)..(1-q^r1)/(1-q)(1-q2)..(1-q^r2).../(1-q)(1-q2)..(1-q^rn)  
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll mod = 1E9 + 7;
int arr[100010];
ll powmod(ll a,ll b) {ll res=1;a%=mod; assert(b>=0); for(;b;b>>=1){if(b&1)res=res*a%mod;a=a*a%mod;}return res;}
unordered_map<int, int> mp;
int main() {
    int n, b;
    ll ans = 1;
    scanf("%d %d", &n, &b);
    for (int i = 1; i <= n;i++){
        int x;
        scanf("%d", &x);
        mp[x]++;
        if(b==1){
            ans = ans * i % mod * powmod(mp[x], mod - 2) % mod;
        }else{
            ans = ans * (1 - powmod(b, i)) % mod * powmod(1 - powmod(b, mp[x]), mod - 2) % mod;
        }
    }
    if(ans<0)
        ans += mod;
    printf("%lld\n", ans);
    return 0;
}