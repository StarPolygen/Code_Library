//贪心
#include<cstdio>
#include<algorithm>

using namespace std;
const int maxn=1000000;

long long ti[maxn];
long long re[maxn];

bool cmp(long long x,long long y) {
    return x>y;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n;
        long long k;
        scanf("%d%lld", &n, &k);
        long long m=n-1;
        long long ans=k;
        for (int i=1;i<=n;i++) {
            scanf("%lld", &ti[i]);
            m=m-ti[i]/k;
            re[i]=ti[i]%k;
            ans=ans+ti[i];
        }
        sort(re+1,re+n+1, cmp);
        if (m>0) {
            for (int i=1;i<=m;i++) {
                ans=ans+k-re[i];
            }
        }
        
//        printf("??\n");
//        for (int i=1;i<=n;i++) {
//            printf("%lld ", re[i]);
//        } printf("\n");
//        printf("?? %lld\n", m);
        printf("%lld\n", ans);
    }
    return 0;
}

/*
7
3 5
5 5 8
2 4
3 3
8 3
7 8 1 1 2 1 1 1
3 8
10 11 2
5 1
1 2 3 4 5
5 3
1 2 3 4 5
3 1
1000000000 1000000000 1000000000
*/