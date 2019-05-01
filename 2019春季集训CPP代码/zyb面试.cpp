#include <bits/stdc++.h>
using namespace std;
using namespace std;

int fkr(int n, int k) {
    int cccc = 1;
    --k;
    while (k > 0) {
        long long step = 0, first = cccc, last = cccc + 1;
        while (first <= n) {
            step += min((long long)n + 1, last) - first;
            first *= 10;
            last *= 10;
        }
        if (step <= k) {
            ++cccc;
            k -= step;
        }
        else {
            cccc *= 10;
            --k;
        }
    }
    return cccc;
}

int main(){
	int T;
	scanf("%d",&T); 
	while(T--){
		int n,k;
		scanf("%d%d",&n,&k);
		printf("%d\n",fkr(n,k));
	}
	return 0;
}
