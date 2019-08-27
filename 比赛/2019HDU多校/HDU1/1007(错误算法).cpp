//错误想法： 差值规律 莫比乌斯反演 二分分子分母差值 遍历查询
//求分子分母均小于等于n 的第k大真分数
//大胆尝试  但想法出错 不过锻炼了推式子的能力 值得鼓励
#include<bits/stdc++.h>
#define LL long long
using namespace std;

//线性筛+欧拉函数 O(n)+莫比乌斯函数
const LL p_max = 1E6 + 100;
LL phi[p_max]; 
LL mu[p_max];  
void get_muphi() {
    phi[0]=mu[0]=0;
    phi[1] = 1; mu[1] = 1;
    static bool vis[p_max];
    static LL prime[p_max], p_sz, d;	//使用时注意在函数外初始化 
    for (int i = 2; i < p_max; i++) {
        if (!vis[i]) {
            prime[p_sz++] = i;
            phi[i] = i - 1;
            mu[i] = -1;
        }
        for (LL j = 0; j < p_sz && (d = i * prime[j]) < p_max; ++j) {
            vis[d] = 1;
            if (i % prime[j] == 0) {
                phi[d] = phi[i] * prime[j];
                mu[d] = 0;
                break;
            }
            else {
                phi[d] = phi[i] * (prime[j] - 1);
                mu[d] = -mu[i];
            }
        }
    }
}


//预处理欧拉函数和莫比乌斯前缀和
void Prepare(){
    for(int i=1;i<p_max;i++){
        phi[i]=phi[i-1]+phi[i];
        mu[i]=mu[i-1]+mu[i];
    }
}

int n; LL k;
LL count(int m){
    LL ans=1;
    for(int l=1,r;l<=n-1;l=r+1)
    {
        r=n/(n/l);
        ans+=(mu[r]-mu[l-1])* ((n-m/l*l)/l + (n-l)/l) * (m/l) /2;
    }
    return ans;
}

int main() {
    get_muphi();
    Prepare();
    int T; scanf("%d",&T);
    while(T--){
        scanf("%d %lld",&n,&k);
        k = phi[n]-k+1;
        printf("%lld\n",phi[n]);
        //debug1：
        // for(int i=1;i<=100;i++) printf("%lld ",phi[i]); puts("");
        // for(int i=1;i<=100;i++) printf("%lld ",mu[i]);

        //二分：O(√nlogn)
        // int left =0; int right = n-1;
        // int mid;
        // while(left<right){
        //     mid = left + (right-left)>>1;
        //     int num = count(mid);
        //     if(num < k){
        //         left = mid+1;
        //     }else if(num == k){
        //         break;
        //     }else{
        //         right = mid-1;
        //     }
        // }
        // printf("%d\n",mid);

        //暴力O(n√n)
        int cha;
        for(int i=0;i<=n-1;i++){
            if(count(i)==k){
               cha=i; break;
            }else if(count(i-1)<k && count(i)>k){
                cha=i; break;
            }
        }

        printf("%d\n",cha);
    }
    return 0;
}