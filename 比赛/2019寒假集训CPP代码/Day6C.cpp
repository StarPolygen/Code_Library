#include<bits/stdc++.h>
#define ll  unsigned long long
int main(){
	int n;ll ans;
	while(true){
		scanf("%d",&n);
		if(n==0) break;
		else {
			ans=(1ll*n*n*n*n*n*n + 1ll*3*n*n*n*n + 1ll*12*n*n*n + 1ll*8*n*n)/24;
			printf("%llu\n",ans);
		}
	}
	
	return 0;
}
