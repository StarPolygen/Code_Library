//找规律
//询问不超过n的 约束和为even的数有多少
//根据题面中的公式： 约束和函数 = p1^(e1+1)-1/p1-1 * p2^(e2+1)-1/p2-1 *......pk^(ek+1)-1/pk-1
//直接分析出：当且仅当n存在质因数pk不为2，且ek为奇数，约束和函数为偶数
//反面得出：n的所有不为2的质因数指数必须为偶数，才会让约束和函数为奇数，之后陷入僵局，不知如何统计这种数字的个数
//化简后：其实就是2*x^2 和 x^2的数的个数，因此用n减去2倍的完全平方数和完全平方数的个数即可
#include<bits/stdc++.h>
#define ll long long
using namespace std;


int main() {
    int T;scanf("%d",&T); int Cas=0;
    while(T--){
        Cas++;
        ll n; scanf("%lld",&n);
        ll num1 = (ll)sqrt(n);        
        ll num2 = (ll)sqrt(n/2.0);
        if((num1+1) * (num1+1) <= n) num1++;
        if(num1 * num1 > n) num1--;
        if(2ll * num2 *num2 > n) num2--;
        if(2ll * (num2+1) * (num2+1) <= n) num2++;
        printf("Case %d: %lld\n",Cas,n-num1-num2);
    }
    return 0;
}