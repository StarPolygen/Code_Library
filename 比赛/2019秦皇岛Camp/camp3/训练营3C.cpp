#include<bits/stdc++.h>
#define ll long long
using namespace std;

const ll INF=1e13;
struct card{
    ll w,h,q;
} arr[19];

ll dp[19][1<<15];


int n,k;

ll cal(ll p){
    ll maxw=0,maxh=0;
    ll all=0;ll num=0;
    for(int i=0;i<n;i++){
        if((1&(p>>i))==1){
            maxw=max(maxw,arr[n-i].w);
            maxh=max(maxh,arr[n-i].h);
            all+=arr[n-i].w*arr[n-i].h*arr[n-i].q;
            num+=arr[n-i].q;
        }
    }
    
    ll res=maxw*maxh*num-all;
    // printf("%lld %lld %lld %lld %lld\n",maxw,maxh,all,num,res);
    return res;
    
}
int main() {
    scanf("%d%d",&n,&k);
    if(k>=n) printf("0\n");
    else{
        ll up= 1<<n;
        for(int i=0;i<19;i++){
            for(int j=0;j<1<<15;j++){
                dp[i][j]=INF;
            }
        }
        for(int i=1;i<=n;i++){
            scanf("%lld %lld %lld",&arr[i].w,&arr[i].h,&arr[i].q);
            // printf("%lld %lld %lld\n",arr[i].w,arr[i].h,arr[i].q);
        }
        for(int i=1;i<up;i++){
            dp[1][i]= cal(i);
            // printf("%lld \n",cal(i));
        }
        // printf("\n");
        dp[1][0]=0;
        for(int i=1;i<=k;i++){
            for(int j=0;j<up;j++){
                for(int s=j;s;s=(s-1)&j){
                   dp[i][j]=min(dp[i][j],dp[i-1][j-s]+dp[1][s]);
                }
            }
        }
        ll ans=INF;
        for(int i=1;i<=k;i++){
            ans=min(ans,dp[k][up-1]);
        }
        printf("%lld\n",ans);

        // for(int i=0;i<=k;i++){
        //     for(int j=0;j<up;j++)
        //     printf("%lld ",dp[i][j]);
        //     printf("\n");
        // }


        
    }
    return 0;
}
/*
5 1 
10 10 5 
9 8 10 
4 12 20
12 4 8 
2 3 16
*/
