#include <bits/stdc++.h>
#define MAXN 100011
using namespace std;
int dp[MAXN][12],pile[MAXN][12];
int max_is(int a,int b,int c);
int main(){    
 	int n,x,t,j,maxt;
	while(scanf("%d",&n)!=EOF&&n){
	    memset(dp,0,sizeof(dp));        
		memset(pile,0,sizeof(pile));        
		maxt=0;        
		for(int i=0;i<n;i++){            
			scanf("%d%d",&x,&t);            
			pile[t][x]++;            
			if(maxt<t) maxt=t;        
		}        
		for(int i=0;i<=10;i++)            
		dp[maxt][i]=pile[maxt][i];        
		for(int i=maxt-1;i>=0;i--){            
			for(j=0;j<11;j++){                
				if(j==0) dp[i][j]=max(dp[i+1][j],dp[i+1][j+1])+pile[i][j];                
				else dp[i][j]=max_is(dp[i+1][j-1],dp[i+1][j],dp[i+1][j+1])+pile[i][j];            
			}        
		}        
		printf("%d\n",dp[0][5]);    
	}    
	return 0;
}
int max_is(int a,int b,int c){    
	return max(a,max(b,c));
}
