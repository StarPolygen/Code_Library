//模拟
//非常简单的模拟，根据打印数量的不同单价阶梯式下降，问最优花费。
//Wa了2发，因为没有考虑到一种极端情况，就是在当前这个区间并不最优，而最优的情况可能在更远的区间
//比如前两区间都是单价2000，但第100个区间单价0，显然补满到第100个区间更优，今后需要更加注意特别讨论细节，尤其是水题，不要鲁莽提交。
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
const ll inf =2e18;
int n, m, s[maxn], p[maxn];
ll ans[maxn];

int main () {
    int T;  scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for (int i = 0; i < n; i++) {
            scanf("%d%d", &s[i], &p[i]);
            ans[i] = 1ll * s[i] * p[i];
        }
        ans[n] = inf;
        for (int i = n-1; i >= 0; i--)
            ans[i] = min(ans[i], ans[i+1]);
        int x, k;
        for(int i=1;i<=m;i++) {
            scanf("%d", &x);
            k = upper_bound(s, s + n, x) - s - 1;
            printf("%lld\n", min(1ll * p[k] * x, ans[k+1]));
        }
    }
    return 0;
}
