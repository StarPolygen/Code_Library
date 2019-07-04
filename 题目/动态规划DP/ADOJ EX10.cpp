//分组背包
#include<bits/stdc++.h>
#define ll long long
using namespace std;
#define INF 1e9

int N,M,K,ans;

//读入数据
int arr[55][55];

//每条珠链的前i位置1的个数
int sum[55][55];

//第i条珠链粉刷j次到k位置的最大贡献
int f[55][55][55];

//分组背包
int dp[55][2515]; 

void init(){
    memset(arr,0,sizeof(arr));
    memset(sum,0,sizeof(sum));
    memset(f,0,sizeof(f));
    memset(dp,0,sizeof(dp));
    ans = 0;
}

int main()
{
    init();
    scanf("%d%d%d",&N,&M,&K);

    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++){
            scanf("%d",&arr[i][j]);
        }
    }

    //预处理每条珠链的前i位置1的个数
    for(int i=1;i<=N;i++){
        for(int j=1;j<=M;j++){
            if(arr[i][j]==1) sum[i][j]=sum[i][j-1]+1;
            else   sum[i][j]=sum[i][j-1]; 
        }
    }

    //DP1：获得每条珠链被涂色j次到k位置的最大贡献
    for(int i=1;i<=N;i++){
        for(int j=1;j<=min(M,K);j++){
            for(int k=1;k<=M;k++){
                f[i][j][k]=f[i][j-1][k];
				f[i][j][k]=max(f[i][j][k],f[i][j][k-1]);
                for(int l=0;l<k;l++){
                    f[i][j][k] = max(f[i][j][k], f[i][j-1][l]+max(sum[i][k]-sum[i][l],(k-l-sum[i][k]+sum[i][l])));
                }
            }
        }
    }



    //DP2：分组背包  i:组数 j：容积
    for(int i=1;i<=N;i++){
        for(int j=1;j<=K;j++){
            for(int p=1;p<=min(M,K);p++){
                dp[i][j]=max(dp[i-1][j],dp[i-1][j-p]+f[i][p][M]);
            }
        }
    }


	// for (int i=1;i<=K;i++) ans=max(ans,dp[N][i]);
    printf("%d\n",N*M-dp[N][K]);

    return 0;
}
