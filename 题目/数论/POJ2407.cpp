//数论 
//欧拉函数的计算 φ(n)
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <math.h>
#define ll long long
using namespace std;

ll eular(ll n)
{
	ll ret=1,i;
	for (i=2;i*i<=n;i++)
		if (n%i==0)
		{
			n/=i,ret*=i-1;
			while (n%i==0)
				n/=i,ret*=i;
		}
	if (n>1)
		ret*=n-1;
	return ret;
}

int main() {
    ll n;
    while(scanf("%lld",&n)&&n){
        printf("%lld\n",eular(n));
    }
    return 0;
}