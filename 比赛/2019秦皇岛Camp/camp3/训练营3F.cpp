#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
using namespace std;
const int mod=1E9+7;
long long f[2][10005];

int main() {
	int n,w,h;
	scanf("%d%d%d", &n,&w,&h);
	memset(f,0,sizeof(f));
	for (int i=0;i<=h;i++) {
		f[1][i]=1;
	}
	int p=1;
	for (int i=2;i<=w;i++) {
		p=p^1;
		for (int j=0;j<=n;j++) {
			f[p][j]=0;
		}
		for (int j=0;j<=n;j++) {
			for (int k=0;k<=h;k++) {
				f[p][j+k]+=f[p^1][j];
				if (f[p][j+k]>=mod) {
					f[p][j+k]-=mod;
				}
			}
		}
	}
	long long ans=0;
	for (int i=0;i<=n;i++) {
		ans+=f[p][i];
		if (f[p][i]>=mod) {
			f[p][i]-=mod;
		}
	}
	ans=(ans-min(h,n/w)-1+mod)%mod;
	printf("%d\n", ans);
	return 0;
}
