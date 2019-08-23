#include<cstdio>
using namespace std;

const int maxn=1E5;


int n;
int w[maxn];
int q[maxn];
bool vis[maxn];
int po;

bool check(int p1,int p2,int p3,int p4) {
    for (int i=0;i<=20;i++) {
        vis[i]=false;
    }
    vis[0]=true;
    for (int i=1;i<=p1;i++) {
        for (int j=20;j>=10;j--) {
            if (vis[j-10]) {
                vis[j]=true;
            }
        }
    }
    for (int i=1;i<=p2;i++) {
        for (int j=20;j>=5;j--) {
            if (vis[j-5]) {
                vis[j]=true;
            }
        }
    }
    for (int i=1;i<=p3;i++) {
        for (int j=20;j>=2;j--) {
            if (vis[j-2]) {
                vis[j]=true;
            }
        }
    }
    for (int i=1;i<=p4;i++) {
        for (int j=20;j>=1;j--) {
            if (vis[j-1]) {
                vis[j]=true;
            }
        }
    }
    for (int i=1;i<=n;i++) {
        if (q[i]<po) {
            bool pd=true;
            if (w[i]>=10 && vis[w[i]-10]) {
                pd=false;
            }
            if (vis[w[i]]) {
                pd=false;
            }
            if (pd) {
                return false;
            }
        } else {
            if (!vis[w[i]]) {
                return false;
            }
        }
    }
    return true;
}

int main() {
    int T;
    scanf("%d",&T);
    while (T--) {
        scanf("%d", &n);
        bool pd=true;
        for (int i=1;i<=n;++i) {
            scanf("%d", &w[i]);
            if (w[i]%10!=0) {
                pd=false;
            }
            w[i]=w[i]/10;
        }
        if (!pd) {
            printf("-1\n");
            continue;
        }
        po = 0;
        for (int i=1;i<=n;i++) {
            if (w[i]/10-1>po) {
                po=w[i]/10-1;
            }
            if (w[i]/10>0) {
                q[i]=w[i]/10-1;
                w[i]=w[i]%10+10;
            } else {
                q[i]=0;
                w[i]=w[i]%10;
            }
        }
        int ans=10000000;
        for (int p1=0;p1<=1;p1++) {
            for (int p2=0;p2<=3;p2++) {
                for (int p3=0;p3<=9;p3++) {
                    for (int p4=0;p4<=19;p4++) {
                        if (ans<=p1+p2+p3+p4) {
                            continue;
                        }
                        if (check(p1,p2,p3,p4)) {
                            ans=p1+p2+p3+p4;
                        }
                    }
                }
            }
        }
        printf("%d\n", ans+po);
    }
    return 0;
}

/*
5
3
60 40 20
5
110 60 50 40 20
5
10 20 30 40 50
5
100 200 300 400 500
1
1

*/