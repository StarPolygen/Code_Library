#include<bits/stdc++.h>
#define maxn 100010
#define p 1000000007
#define ll long long
using namespace std;

//dp[i][j][0] 表示第i个座位成绩为j，且Ai-1 >= Ai 且之前全部满足的方案数
//dp[i][j][1] 表示第i个座位成绩为j，且Ai-1 < Ai  且之前全部满足的方案数
ll dp[maxn][110][2];
    
ll arr[maxn];

ll add(ll a,ll b,ll c){
    return (a + b + c) % p;
}


int n;
int main(){
    memset(dp, 0, sizeof(dp));
    ll sum = 0;
    scanf("%d",&n);
    
    for(int i=1;i<=n;i++)   scanf("%lld",&arr[i]);

    //基础情况
    if(arr[1]==-1)  for(int i=1;i<=100;i++)  dp[1][i][1]=1; 
    else  dp[1][arr[1]][1]=1; 


    for(int i=2;i<=n;i++){

        //每轮清空当前i对应滚动数组中的行
        for(int j=0;j<=100;j++){
            dp[i%2][j][1]=dp[i%2][j][0]=0;
        }

        //当前位置为 j 满足 Ai-1 < Ai 的方案    1: 最后一个升高
        for (int j=1;j<=100;j++) {
            dp[i%2][j][1]=add(dp[(i-1)%2][j-1][1], dp[(i-1)%2][j-1][0], dp[i%2][j-1][1]);
        }
 
        //当前位置为 j 满足 Ai-1 >= Ai 的方案   0：最后一个降落或平
        //最后两个降落 降落    或者降落 平
        for(int j=100;j>=1;j--){
            dp[i%2][j][0]=(dp[(i-1)%2][j][0] + dp[i%2][j+1][0]) % p;
        }
        //最后两个为升高 平
        for(int j=100;j>=1;j--){
            dp[i%2][j][0]=(dp[i%2][j][0] + dp[(i-1)%2][j][1])%p;
        }

        //若当前位置有人，则当前位置成绩只能是此人成绩，不存在是其他可能
        if(arr[i]!=-1){
            for(int j=1;j<=100;j++) {
                if(j!=arr[i])
                   dp[i%2][j][1]=dp[i%2][j][0]=0;
            }
        }
    }


    //统计得到答案    
    ll ans=0;
    for(int j=1;j<=100;j++){
        ans=(ans+dp[n%2][j][0])%p;
    }
    printf("%lld\n",ans);
}


