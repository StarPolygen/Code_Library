//签到
#include<cstdio>
using namespace std;

const int maxn=2005;

int g[maxn][maxn];
int n,m,q;

int dele(int x,int y) {
    if (x<1 || x>n || y<1 || y>m) {
        return 0;
    }
    if (g[x][y]==0) {
        return 0;
    }
    int res=0;
    if (g[x][y+1]==0 || g[x][y-1]==0) {
        if (g[x+1][y]==0 || g[x-1][y]==0) {
            res++;
            g[x][y]=0;
            res=res+dele(x+1,y);
            res=res+dele(x-1,y);
            res=res+dele(x,y+1);
            res=res+dele(x,y-1);
        }
    }
    
    return res;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d%d", &n,&m, &q);
        for (int i=0;i<=n+1;i++) {
            for (int j=0;j<=m+1;j++) {
                g[i][j]=1;
            }
        }
        for (int i=1;i<=q;i++) {
            int x,y;
            scanf("%d%d", &x,&y);
            int res=0;
            if (g[x][y]==0) {
                res=0;
            } else {
                res++;
                g[x][y]=0;
                res=res+dele(x+1,y);
                res=res+dele(x-1,y);
                res=res+dele(x,y+1);
                res=res+dele(x,y-1);
            }
            printf("%d\n", res);
        }
    }
}
/*
2
2 2 3
1 1
1 2
2 2
4 4 6
1 1
1 2
2 1
2 2
4 4
3 3
*/