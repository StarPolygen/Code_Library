#include<bits/stdc++.h>
using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=1005;
int dp[maxn][maxn],vis[maxn][maxn];
int a[maxn];
int sum[maxn];
int dfs(int l,int r){    
	if(vis[l][r]) 
		return dp[l][r];    
	else if(l==r) 
		return dp[l][l];    
	vis[l][r]=1;    
	int le=dfs(l+1,r),ri=dfs(l,r-1);    
	int all=sum[r]-sum[l-1];    
	dp[l][r]=max(all-le,all-ri);    
	return dp[l][r];
}
void init(){
	for(int i=0;i<maxn;i++){
		for(int j=0;j<maxn;j++){
			dp[i][j]=0;
			vis[i][j]=0;
		}
	}
}
int main(){    
	int T,n;    
	scanf("%d",&T);   
	while(T--){  
		init();          
		scanf("%d",&n);        
		for(int i=1;i<=n;i++){	            
		scanf("%d",&a[i]);            
		sum[i]=sum[i-1]+a[i];            
		vis[i][i]=1;            
		dp[i][i]=a[i];        
		}        
		int ans=dfs(1,n);        
		printf("%d\n",ans*2-sum[n]);    
	}    
	return 0;
}

