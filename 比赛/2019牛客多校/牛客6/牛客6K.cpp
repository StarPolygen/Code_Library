//min_25筛
//作用：积性函数求前缀和  适用条件：F(p)是简单多项式 F(p^c)可以快速计算
//注意：F(p)可以是分段函数 但只要保证每段都是简单多项式即可
//核心：先求质数前缀和 通过质数前缀和求得全部前缀和
//特殊性： 本题F(p)不是统一的多项式 而是分段函数 
//        1)当 p mod 4 余1时 F(P)=4
//        2)当 p mod 4 余3时 F(P)=1  
//        3)   F(2)=1单独考虑
#include<bits/stdc++.h>
#define ll long long
using namespace std;

//步骤1：线性筛预处理   下标1——ind
const int N = 1E5 + 7;
const int MAXSIZE = N;
bool Mark[MAXSIZE]; int ind = 0;
int pre[2][N]; //预处理 mod4为1和为3 的函数个数   以便之后统计质数贡献
int pr[N/10];   
void Prime() { 
    memset(Mark, 0, sizeof(Mark));
    ind = 0; Mark[0] = Mark[1] = 1;  
    for (int i = 2; i < MAXSIZE; i++){
        if (Mark[i]) continue;    
        pr[++ind] = i; 
        //预处理所有组件： mod4为1和为3 的函数个数
        pre[0][ind] = pre[0][ind-1] + (i % 4 == 1);
        pre[1][ind] = pre[1][ind-1] + (i % 4 == 3);
        for (int j = i + i; j < MAXSIZE; j += i)  Mark[j] = 1; 
    }
} 


// min_25筛模板
namespace min25 {
    const int D = 3e5;  //D ：根号n级别
    int id[D], w[D];
    ll B, _n, dp[2][D];  //构成质数前缀和的若干组成部分，本题中只有两部分构成：mod 4余1的质数  和 mod 4余3的质数  （2在之后单独考虑）
    int idx(ll x) {  //离散化数论分块
        if (x <= B) return id[x];
        return _n / x;
    }
    ll calc(int prime, int e) { //根据题意更改F(p,e)               //注意一： 此处要随着题目所给函数F(P) P∈Prime 发生变化
        if (prime % 4 == 1) return 3 * e + 1; return 1;
    }
    ll F(ll x, int y) { // 在1 ～ x中，最小素因子 >= 2的函数和
        if (x <= 1 || pr[y] > x) return 0;
        int k = idx(x);
        
        //将之前处理的各个组成部分乘以系数加权合并为真正的素数前缀和    如本题组件1：pmod4=1的系数为4 组件2：pmod4=3 的系数为1
        ll ans = 4ll * (dp[0][k] - pre[0][y - 1]) + (dp[1][k] - pre[1][y - 1]);   
        if (y == 1) ans ++; // 素数2                               //注意二： 此处应当是Ans+=F(2)
 
        for (int i = y; i <= ind && 1ll * pr[i] * pr[i] <= x; ++ i) {
            ll aa = pr[i];
            // e 是 pr[i] 的指数
            for (int e = 1; 1ll * aa * pr[i] <= x; ++ e, aa *= pr[i]) {
                ans += F(x / aa, i + 1) * calc(pr[i], e) + calc(pr[i], e + 1);
            }
        }
        return ans;
    }   
    ll solve(ll n) { //处理出构成素数前缀和的各个部分
        B = sqrt(n + .5); _n = n; int m = 0;
        for (ll l = 1, r; l <= n; l = r + 1) {//数论分块
            r = n / (n / l);
            w[++ m] = n / l; // 第m个块包含了 1～ w[m]范围内的函数和
            //按照各组成部分含义 计算其在当前块内的函数和
            dp[0][m] = w[m] / 4 + (w[m] % 4 >= 1) - 1;          //注意三 ：统计各组成部分函数和时务必将1和2剔除
            dp[1][m] = w[m] / 4 + (w[m] % 4 >= 3);
            if (n / l <= B) id[n / l] = m;
        }
        int t;
        for (int j = 1; j <= ind; ++ j) {
            for(int i = 1; i <= m && 1LL * pr[j] * pr[j] <= w[i]; ++i) {
                t = idx(w[i] / pr[j]);
                if (pr[j] % 4 == 1) { //−F(Pj)⋅(g(i/Pj,j−1)−sumf(j−1))
                    dp[0][i] -= dp[0][t] - pre[0][j - 1];
                    dp[1][i] -= dp[1][t] - pre[1][j - 1];
                }
                else if (pr[j] % 4 == 3) {
                    dp[0][i] -= dp[1][t] - pre[1][j - 1];
                    dp[1][i] -= dp[0][t] - pre[0][j - 1];
                }
            }
        }
        
        return F(n, 1) + 1ll;                                   //注意四：最后将F(1)也加入其中
    }
}
int main() {
    Prime();
    int _;
    cin >> _;
    while (_ --) {
        ll n;
        cin >> n;
        cout << min25::solve(n) << endl;
    }
    return 0;
}