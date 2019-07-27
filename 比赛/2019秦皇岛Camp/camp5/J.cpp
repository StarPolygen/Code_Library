//简单DP
//倒着DP
#include<bits/stdc++.h>
#pragma GCC optimize(2) 
#define ll long long
using namespace std;

double arr[200][200];
int diren[10010];
double dp[200][10100];
const double eps=1e-8;
inline double max(double a,double b){ return (a-b)>eps?a:b;}
int main() {
    int n1;
    while(~scanf("%d",&n1)){
        int n=n1*(n1-1)*(n1-2)/6;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                double tmp; scanf("%lf",&tmp);
                arr[i][j]=1.0-tmp;  //i被j打败的概率
            }
        }
        // for(int i=0;i<n;i++){
        //     for(int j=0;j<n;j++){
        //         printf("%.2lf",arr[i][j]);
        //     }
        // }
        int m; scanf("%d",&m);
        for(int i=0;i<m;i++){
            scanf("%d",&diren[i]);
        }
        memset(dp,0,sizeof(dp));
        for(int i=0;i<n;i++){
            dp[i][m-1]=arr[diren[m-1]][i];
        }
        for(int j=m-2;j>=0;j--){
            for(int i=0;i<n;i++){
                dp[i][j]=max(dp[i][j+1]*arr[diren[j]][i],dp[diren[j]][j+1]*arr[diren[j]][i]);
            }
        }
        double ans=0;
        for(int i=0;i<n;i++){
            ans=max(ans,dp[i][0]);
        }
        printf("%.6f\n",ans);
    }
    return 0;
}