//给定01序列
//求最长的01数量相等的 子串 和 子序列长
//子串：0变-1 求并保存前缀和 查询是否有相等的
#include<cstdio>
#include<cstring>
 
using namespace std;
const int maxn=2E5;
char ch[maxn];
int a[maxn];
 
int l[2*maxn];
int r[2*maxn];
 
int sum[maxn];
 
int main() {
    int n;
    scanf("%d", &n);
    scanf("%s", ch+1);
    int cnt=0;
    for (int i=1;i<=n;i++) {
        if (ch[i]=='0') {
            a[i]=-1;
        } else {
            a[i]=1;
            cnt++;
        }
    }
    memset(l,-1,sizeof(l));
    memset(r,-1,sizeof(r));
    sum[0]=0;
    for (int i=1;i<=n;i++) {
        sum[i]=sum[i-1]+a[i];
    }
     
    for (int i=0;i<=n;i++) {
        int p=sum[i];
        if (l[p+maxn]==-1) {
            l[p+maxn]=i;
        } else {
            r[p+maxn]=i;
        }
    }
    int ans=0;
    for (int i=-n;i<=n;i++) {
        if (ans<(r[i+maxn]-l[i+maxn])) {
            ans=r[i+maxn]-l[i+maxn];
        }
    }
    int ans1=0;
    if (cnt<=n-cnt) {
        ans1=cnt*2;
    } else {
        ans1=(n-cnt)*2;
    }
    printf("%d %d\n", ans, ans1);
    return 0;
}
 
/*
8
11111110
 
7
1011010
 
8
10101010
 
 
*/