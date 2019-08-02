#include<bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod=1E9+7;
const int maxn=1000000;

ll arr[maxn];
struct point{
	ll curr;int number;
	bool operator < ( const point &x) const {return curr<x.curr;	}
} a[maxn];

int main() {
	int n; scanf("%d", &n);
	for (int i=1;i<=n;i++) {
		scanf("%lld", &arr[i]);
	}	sort(arr+1,arr+n+1);
	arr[n+1]=-1;
	ll tot=0;int tmp=0;
	for (int i=1;i<=n;i++) {
		tmp++;
        if(arr[i]==arr[i+1]) continue;
		else {
			tot++;a[tot].number=tmp;
			a[tot].curr=arr[i];tmp=0;
		}
	}
	ll pr=1, curr=0, num=0,ans=1;
	while (pr<=tot) {
		curr=a[pr].curr; num+=a[pr].number;
		while (num>0 && (pr==tot || curr<a[pr+1].curr)) {
			ans=ans*num%mod;num--;	curr++;
		}pr++;
	}
	printf("%lld\n", ans);
	return 0;
}
