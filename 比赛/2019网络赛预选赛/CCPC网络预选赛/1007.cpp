//分治 模拟
#include<cstdio>
#include<cstring>
using namespace std;


char ch[2000][2000];

void dfs(int p) {
    if (p==1) {
        ch[p][p]='C';
        return ;
    }
    dfs(p/2);
    for (int i=1;i<=p/2;i++) {
        for (int j=1;j<=p/2;j++) {
            if (ch[i][j]=='C') {
                ch[i+p/2][j]='P';
            } else {
                ch[i+p/2][j]='C';
            }
            ch[i][j+p/2]=ch[i][j];
            ch[i+p/2][j+p/2]=ch[i][j];
        }
    }
    return ;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        int k;
        scanf("%d", &k);
        int p=1;
        for (int i=1;i<=k;i++) {
            p=p*2;
        }
        dfs(p);
        for (int i=1;i<=p;i++) {
            for (int j=1;j<=p;j++) {
                printf("%c", ch[i][j]);
            } printf("\n");
        }
    }
    return 0;
}