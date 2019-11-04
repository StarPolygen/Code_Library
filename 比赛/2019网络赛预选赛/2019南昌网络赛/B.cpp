//扩展欧拉定理  欧拉降幂
//求a^a^a^a....共b个a  mod m的值
//对于每层由上到下使用扩展欧拉定理进行欧拉降幂 
//比赛时 TLE 因为φ（φ（....φ（m）））下降很快到1  因此可以忽略降到1之后的变化 必须加入该剪枝才可过


//扩展欧拉： if(gcd(a,m)==1) a^c = a^c%φ(m)
//          else{
//              if(c>=φ(m)) a^c = a^ c%φ(m)+φ(m)
//              else a^c = a^c
//          }  
#include<bits/stdc++.h>
#define ll long long
using namespace std;

const int p_max = 1E6 + 1;
int phi[p_max];
inline void get_phi() {
    phi[1] = 1;
    static bool vis[p_max];
    static int prime[p_max], p_sz, d;	//使用时注意在函数外初始化 
    for (int i = 2; i < p_max; i++) {
        if (!vis[i]) {
            prime[p_sz++] = i;
            phi[i] = i - 1;
        }
        for (int j = 0; j < p_sz && (d = i * prime[j]) < p_max; ++j) {
            vis[d] = 1;
            if (i % prime[j] == 0) {
                phi[d] = phi[i] * prime[j];
                break;
            }
            else phi[d] = phi[i] * (prime[j] - 1);
        }
    }
}
inline int gcd(int a,int b){    return b?gcd(b,a%b):a;} 
inline int bin(int base, int n, int p) {
    int res = 1;
    while (n) {
        if (n & 1) res = 1ll*res * base % p;
        base =1ll* base * base % p;
        n >>= 1;
    }
    return res;
}




int php[1000010];
int main() {
    get_phi();
    int T; scanf("%d",&T);
    while(T--){
        int a,b,m;
        scanf("%d%d%d",&a,&b,&m);
        if(a==1){
            printf("%d\n",1%m); continue;
        }
        php[0]=m;
        int top=10000000;
        for(register int i=1;i<=b-1;++i){
            php[i]=phi[php[i-1]];
            if(php[i]==1) {
                top=i; break;
            }
        }
        int ans=1; 
        for(register int i=min(top,b-1);i>=0;--i){
            if(i==0||gcd(a,php[i-1])==1){
                ans=bin(a,ans,php[i]);
            }
            else{
                if(log(php[i])/log(a)<=1.0*ans){
                    ans=bin(a,ans,php[i]);
                    ans=ans+php[i];
                }
                else{
                    ans=pow(a,ans);
                } 
            }
        }
        printf("%d\n",ans%m);

    }
    return 0;
}