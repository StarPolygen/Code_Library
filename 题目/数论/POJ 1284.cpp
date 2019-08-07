//数论  原根个数
//n的原根个数 ：几个重要结论 
//1.对于任意正整数m  若原根存在，个数为φ(φ(m))
//2.对于素数p        p,p^2均存在原根，个数分别为φ(p-1)  (p-1)φ(p-1)
//3.对于奇素数p      p^n的原根存在，个数为 p^(n-2)*(p-1)*φ(p-1)   n>=2

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
        printf("%lld\n",eular(n-1)); //由于本题保证n为奇素数 因此φ(n-1)和φ(φ(n))均可
    }
    return 0;
}
