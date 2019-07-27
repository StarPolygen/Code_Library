//Author by zxy
//牛客3F Planting Tree 单调队列
#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int N = 5e2 + 5;
int a[N][N];
int n, m;
int q1[N], q2[N];
int mx[N], mn[N];
void work(){
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= n;i++)
    {
        for (int j = 1; j <= n;j++)
        {
            scanf("%d", &a[i][j]);
        }
    }
    int ans = 0;
    for (int i = 1; i <= n;i++)
    {
        for (int k = 1; k <= n;k++)
            mx[k] = mn[k] = a[i][k];
        for (int j = i; j <= n; j++)
        {
            for (int k = 1; k <= n; k++){
                mx[k] = max(mx[k], a[j][k]);
                mn[k] = min(mn[k], a[j][k]);
            }
            int l = 1;
            int h1 = 1, h2 = 1, t1 = 0, t2 = 0;
            for (int r = 1; r <= n;r++)
            {
                while (h1<=t1 && mn[q1[t1]]>mn[r])
                    t1--;
                q1[++t1] = r;
                while (h2<=t2 && mx[q2[t2]]<mx[r])
                    t2--;
                q2[++t2] = r;
                while (mx[q2[h2]]-mn[q1[h1]]>m){
                    l++;
                    if (h1<=t1 && q1[h1]<l)
                        h1++;
                    if (h2<=t2 && q2[h2]<l)
                        h2++;
                    if (l>r)
                        break;
                }
                ans = max(ans, (j - i + 1) * (r - l + 1));
            }
        }
    }
    printf("%d\n", ans);
}
int main(){
    int t;
    scanf("%d", &t);
    while (t--){
        work();
    }
    return 0;
}