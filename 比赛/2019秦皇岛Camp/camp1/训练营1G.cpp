#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int maxn = 1e3 + 5;
const int N=maxn;
int n;
int pos[N], a[N];
char s[N];
bool maze[N][N];
bool vis[N];
int main(){
    scanf("%d", &n);
    for (int i = 1; i <= n;i++)
    {
        int x;
        scanf("%d", &x);
        a[i] = x;
        pos[x] = i;
    }
    for (int i = 1; i <= n;i++)
    {
        scanf(" %s", s + 1);
        for (int j = 1; j <= n;j++)
        {
            if (s[j]=='1'){
                maze[i][j] = 1;
            }
        }
    }
    for (int k = 1; k <= n;k++)
    {
        for (int i = 1; i <= n;i++)
        {
            if (i==k)
                continue;
            for (int j = 1; j <= n;j++)
            {
                if (i==j ||j==k)
                    continue;
                maze[i][j] = maze[i][j] || maze[i][k] && maze[k][j];
            }
        }
    }
    for (int i = 1; i <= n;i++)//从1开始处理
    {
        int p = -1, x = pos[i];//x为i的原始位置
        for (int j = 1; j <= n;j++)
        {
            if (maze[x][j] && !vis[j]){
                p = j;
                break;
            }
        }
        if (p==-1){
            vis[x] = 1;
        }else if (p>=x){
            vis[x] = 1;
        }else{
            vis[p] = 1;
            pos[a[p]] = x;
            pos[i] = p;
            swap(a[p], a[x]);
        }
    }
    for (int i = 1; i <= n;i++)
    {
        printf("%d ", a[i]);
    }
    return 0;
}
