//素数打表
//给定n 1e7 求有多少种可能将n分解为n = a + b，a ≤ b且a b均为质数
//T ≤ 300 ,1e7 以内素数6e5 对于每个T，枚举<n的素数p直接判断n-p是否为素数即可
#include<bits/stdc++.h>
#define ll long long
using namespace std;

//素数筛 埃氏筛 O(nloglogn)
const int MAXSIZE = 1E7+10;
bool Mark[MAXSIZE];int ind = 0; //prime[0]起
int prime[1000000];    //判断是否是一个素数  Mark 标记数组 ind 素数个数
void Prime() {
    ind = 0;
    for (int i = 2; i < MAXSIZE; i++){
        if (Mark[i])  continue;     //如标记则跳过
        prime[ind++] = i; //否则得到一个素数
        for (int j = i + i; j < MAXSIZE; j += i)
            Mark[j] = 1; //标记目前得到的素数的i倍为非素数
    }
}
int ans[200010];
int main() {
    int T; scanf("%d",&T); int Cas=0;
    memset(Mark,0,sizeof(Mark));
    memset(ans,0,sizeof(ans));
    Prime(); Mark[0] = Mark[1] = 1;
    //// printf("%d\n",ind);                   //尝试加一些预处理 卡数据减少复杂度 但基于本题数据 时间没有明显提升
    // for(int i = 0; i< 4204; i++){
    //     for(int j = i; j < 4204; j++){
    //         ans[prime[i]+prime[j]]++;
    //     }
    // }
    //// printf("%lld\n",prime[4203]);
    while(T--){
        Cas++;
        int n; scanf("%d",&n);
        ll as = 0; 
        // if(n<=4E4) as=ans[n];
        // else{
            for(int i = 0; prime[i] < n && i < ind; i++ ){
                if(Mark[n-prime[i]]==0 && n-prime[i] <= prime[i]) as++; 
            }
        // }
        printf("Case %d: %lld\n",Cas, as);
    }

    return 0;
}