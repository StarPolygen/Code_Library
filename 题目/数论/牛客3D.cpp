//同余 因数分解

//反思：需要注意mod数大于1e9时快速幂可能爆ll，需要加快速乘弥补

//问有多少数对(i,j)使得 1≤i≤n, 1≤j≤m, A(i^j)≡0(mod p).其中A(k)代表k个1.
//首先观察什么情况下 A(k)≡0(mod p):   等价于 (10^k-1)/9 ≡ 0(mod p)
//思路1：  1）上式 => (10^k-1) ≡ 0(mod p) 但注意只有在gcd(9,p)=1时才可以反推回去 因此对p=3的情况特判，其他情况下两式等价
//              上式又等价于 10^k ≡ 1(mod p) 
//              我们需要找到10^k ≡ 1(mod p) 的最小循环节d、 显然这个循环节是p-1的因数 枚举因数找到d
//        2）考虑对于1≤i≤n, 1≤j≤m, A(i^j)≡0(mod p).如何枚举贡献：
//              对于每个j 什么i能满足要求？ 
//                  由于0满足条件 由于循环节点 i^j如果是d的倍数就可以.
//                  将d分解质因数 对于每个质因数的指数pk 取ceil(pk/j)这样就找到了当前j下最小满足情况的i值 设为g
//              对于每个j 如何统计多少个i满足要求？
//                  对于j<=30 i是g的倍数即可 贡献为n/g
//                  对于j>30  由于pk≤30 贡献等同于j为30时
//思路2：   (10^k-1)/9 ≡ 0(mod p) 在任何时候等价于 (10^k-1) ≡ 0(mod 9p)   10^k ≡ 1(mod 9p)  
//          寻找最小循环节d时 用φ(9p)的因数枚举即可 其他操作相同
//          理论上讲正确 但不知为何WA  
//          UPD:  因为快速幂的时候 mod数最高可达为9e9 快速幂时爆ll了 加了快速乘AC        
 
#include <bits/stdc++.h>
#include <vector>
using namespace std;
typedef long long ll;

ll eular(ll n)
{
    ll ret = 1, i;
    for (i = 2; i * i <= n; i++)
        if (n % i == 0)
        {
            n /= i, ret *= i - 1;
            while (n % i == 0)
                n /= i, ret *= i;
        }
    if (n > 1)
        ret *= n - 1;
    return ret;
}

ll mul(ll u, ll v, ll p) { 
    return (u * v - ll((long double) u * v / p) * p + p) % p;
}
ll bin(ll x, ll n, ll mod)
{
    ll ret = mod != 1;         //坑2：快速幂取模时，由于本题方法2模数在9e9，因此爆ll了，需要用快速乘处理一下
    for (x %= mod; n; n >>= 1, x = mul(x,x,mod))
        if (n & 1)
            ret = mul(ret,x,mod);
    return ret;
}

ll factor[30], f_sz, factor_exp[30];
void get_factor(ll x)
{
    f_sz = 0;
    memset(factor, 0, sizeof(factor));
    memset(factor_exp, 0, sizeof(factor_exp));
 
    for (ll i = 2; i * i <= x; i++)
        if (x % i == 0)
        {
            factor[f_sz] = i;
            factor_exp[f_sz] = 0;
            while (x % i == 0)
            {
                x /= i;
                factor_exp[f_sz]++;
            }
            f_sz++;
        }
    if (x > 1)
    {
        factor[f_sz] = x;
        factor_exp[f_sz] = 1;
        f_sz++;
    }
}
//坑1： 不能用素数筛的方法加速分解，因为本题待分解的数数据范围到1e9,而素数筛加速只适用于1e8以下
//素数筛                               
// const int MAXSIZE = 1000000;
// int Mark[MAXSIZE], ind = 0; //prime[0]起
// int prime[MAXSIZE];         //判断是否是一个素数  Mark 标记数组 ind 素数个数
// void Prime()
// {
//     ind = 0;
//     for (int i = 2; i < MAXSIZE; i++)
//     {
//         if (Mark[i])
//             continue;     //如标记则跳过
//         prime[ind++] = i; //否则得到一个素数
//         for (int j = i + i; j < MAXSIZE; j += i)
//             Mark[j] = 1; //标记目前得到的素数的i倍为非素数
//     }
// }
// 分解质因数
// 前置模板：素数筛
// 带指数
// void get_factor(ll x) {                                      
//     f_sz = 0;
//     for (ll i = 0; i < ind && prime[i] * prime[i] <= x; ++i){
//         if (x % prime[i] == 0) {
//             factor_exp[f_sz] = 0;
//             while (x % prime[i] == 0) {
//                 x /= prime[i];
//                 ++factor_exp[f_sz];
//             }
//             factor[f_sz++] = prime[i];
//         }
//  }
//     if (x > 1) {
//         factor_exp[f_sz] = 1;
//         factor[f_sz++] = x;
//     }
// }
signed main()
{
    int T;
    scanf("%d", &T);
    // Prime();
    while (T--)
    {
        ll p, m, n;
        scanf("%lld%lld%lld", &p, &n, &m);
        if (p == 2 || p == 5)
        {
            printf("0\n");
            continue;
        }
        else if(p==3){
            printf("%lld\n",n/3*m);
            continue;
        }
        else
        {
            ll num = 1ll *9* p;
            ll x = 1ll*6*(p-1);     //求φ(9p)
 
            // 方法2: 枚举φ(9p)的因数求d    
            ll d=x;
            for (ll j = 2; j <=sqrt(x); j++)  //错误1：板子错误，不应是j<=sqrt(x)，必须是j*j<=x
            {
                if (x % j == 0) {   
                    if (bin(10, j, num) == 1)  d=min(d,j); 
                    if (bin(10, x/j, num) == 1)   d=min(d,x/j);        
                }  
            }
            // 方法1：特判3之后枚举p-1的因数求d   AC
            // ll tmp=p-1,d=tmp;
            // for (ll i=1;i*i<=tmp;i++)
            // if (tmp%i==0){
            //     if (bin(10,i,p)==1) d=min(d,i);
            //     if (tmp!=i*i)
            //     if (bin(10,tmp/i,p)==1) d=min(d,tmp/i);
            // }
 
            // 对d分解质因数
            get_factor(d);
            ll ans30 = 0;
            ll ans = 0;
            for (int j = 1; j <= min(m, (ll)30); j++)
            {
                ll g = 1;
                for (int i = 0; i < f_sz; i++)
                {
                    g = g * pow(factor[i], ceil((double)factor_exp[i] / (double)j));//这里可以用快速幂，但不知为何pow反而跑的更快
                }
                ans += n / g;
                if (j == 30)
                    ans30 = n / g;
            }
            if (m > 30)
                ans += 1ll * ans30 * (m - 30);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
/*
100
19 444 444
32806
3 20 20000
120000
11 22333333 22333333
249388870277778

100
3 100 100
3300
3 200 3210
211860
*/