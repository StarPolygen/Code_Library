//分类讨论 + 暴力
//小明
#include<cstdio>
#include<cstring>
#include<algorithm>

using namespace std;

int per[100000][10];
int fn[100000];

int path[10];
int vis[10];
int cnt;
int W;
int pref;

int ans[100];

void dfs(int x) {
    if (x==W+1) {
        cnt++;
        for (int i=1;i<=W;i++) {
            per[cnt][i]=path[i];
        }
        return ;
    }
    for (int i=1;i<=W;i++) {
        if (vis[i]) {continue;}
        vis[i]=1;
        path[x]=i;
        dfs(x+1);
        vis[i]=0;
    }
    return ;
}

bool cmp(int x,int y){
    if (pref>=0) {
        int u=per[x][1]-pref;
        int v=per[y][1]-pref;
        if (u<v) {
            return true;
        }
        if (u>v) {
            return false;
        }
    }
//    printf("%d %d\n", fn[x], fn[y]);
    for (int i=2;i<=W;i++) {
        int u=per[x][i]-per[x][i-1];
        int v=per[y][i]-per[y][i-1];
        if (u<v) {
//            printf("<\n");
            return true;
        }
        if (u>v) {
//            printf(">\n");
            return false;
        }
    }
    return false;
}

inline void debug() {
    printf("elo!\n");
    for (int i=1;i<=cnt;i++) {
        for (int j=1;j<=W;j++) {
            printf("%d%s", per[i][j], j==W?"\n":" ");
        }
    }
    printf("all\n");
    for (int i=1;i<=cnt;i++) {
        printf("%d%s", fn[i], i==cnt?"\n":" ");
    }
}
int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int n,k;
        scanf("%d%d", &n,&k);
        
        if (n<=8) {
            W=n;
            cnt=0;
            pref=-1;
            for (int i=1;i<=W;i++) {
                vis[i]=0;
            }
            dfs(1);
            for (int i=1;i<=cnt;i++) {
                fn[i]=i;
            }
            sort(fn+1,fn+cnt+1, cmp);
            for (int i=1;i<=n;i++) {
                ans[i]=per[fn[k]][i];
            }
            for (int i=1;i<=n;i++) {
                printf("%d%s", ans[i], i==n?"\n":" ");
            }
        } else {
            W=8;
            cnt=0;
            if (n==9) {
                pref=9;
            } else {
                pref=0;
            }
            dfs(1);
            for (int i=1;i<=cnt;i++) {
                fn[i]=i;
            }
            sort(fn+1,fn+cnt+1, cmp);
            
            
            ans[1]=n;
            for (int i=2;i<=n-W;i++) {
                ans[i]=i-1;
            }
            for (int i=n-W+1;i<=n;i++) {
                ans[i]=per[fn[k]][i-n+W]+n-9;
            }
            for (int i=1;i<=n;i++) {
                printf("%d%s", ans[i], i==n?"\n":" ");
            }
        }
//        debug();
    }
}

/*
7
3 1
3 2
3 3
3 4
3 5
3 6
20 10000
*/