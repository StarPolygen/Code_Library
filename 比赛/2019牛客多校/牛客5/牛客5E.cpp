//图论 构造
//自补图：和自己补图相同构的图定义为自补图
//给定n 求是否有n阶自补图 若有输出yes 该图的邻接矩阵 和其补图与其同构的点映射  若无输出no即可
//由于自补图和其补图同构 必须满足边的数量为偶数 因此n=4k+2 和 4k+3的情况必定无法构造出自补图
//而一个点和4个点的自补图题目中已给出，我们把他们作为基础状态
//通过用一条4个点的链，中间两点向n个点的自补图中每个点连边，可以构造出n+4个点的自补图 原有n个点内映射无需改变 新加入的4个点的映射仿照n=4的基础情况即可
//因此从n=1和n=4两种基础状态，可以完全生成4k+1和4k的自补图 

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
typedef vector<int> vi;
typedef double db;
int ma[2010][2010];
int f[2010];
int re[2010];
int main() {
    int T;
    scanf("%d", &T);
    for (int cas = 1; cas <= T; cas++) {
        int n;
        scanf("%d", &n);
        printf("Case #%d: ", cas);
        memset(ma, 0, sizeof(ma));
        if (n == 1) {
            printf("Yes\n");
            printf("0\n1\n");
        }
        else if (n % 4 == 0) {
            ma[1][2] = 1;
            ma[2][3] = 1;
            ma[3][4] = 1;
            ma[2][1] = 1;
            ma[3][2] = 1;
            ma[4][3] = 1;
            for (int i = 5; i <= n; i += 4) {
                ma[i][i + 1] = ma[i + 1][i] = 1;
                ma[i + 1][i + 2] = ma[i + 2][i + 1] = 1;
                ma[i + 2][i + 3] = ma[i + 3][i + 2] = 1;
                for (int j = 1; j < i; j++) {
                    ma[j][i + 1] = ma[i + 1][j] = 1;
                    ma[j][i + 2] = ma[i + 2][j] = 1;
                }
            }
            printf("Yes\n");
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    printf("%d", ma[i][j]);
                }
                printf("\n");
            }
            printf("2 4 1 3");
            f[1] = 2;
            f[2] = 4;
            f[3] = 1;
            f[4] = 3;
            for (int i = 5; i <= n; i+=4) {
                printf(" %d %d %d %d", i + 2, i, i + 3, i + 1);
                /*f[i] = i + 1;
                f[i + 1] = i;
                f[i + 2] = i + 3;
                f[i + 3] = i + 2;*/
                f[i] = i + 2;
                f[i + 1] = i;
                f[i + 2] = i + 3;
                f[i + 3] = i + 1;
            }
            printf("\n");
            for (int i = 1; i <= n; i++)re[f[i]] = i;
            /*for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    if (i == j)printf("0");
                    else printf("%d", !ma[re[i]][re[j]]);
                }
                printf("\n");
            }*/
        }
        else if (n % 4 == 1) {
            ma[1][2] = 1;
            ma[2][3] = 1;
            ma[3][4] = 1;
            ma[2][1] = 1;
            ma[3][2] = 1;
            ma[4][3] = 1;
            for (int i = 5; i <= n-1; i += 4) {
                ma[i][i + 1] = ma[i + 1][i] = 1;
                ma[i + 1][i + 2] = ma[i + 2][i + 1] = 1;
                ma[i + 2][i + 3] = ma[i + 3][i + 2] = 1;
                for (int j = 1; j < i; j++) {
                    ma[j][i + 1] = ma[i + 1][j] = 1;
                    ma[j][i + 2] = ma[i + 2][j] = 1;
                }
            }
            for (int i = 1; i <= n - 1; i += 4) {
                ma[i + 1][n] = ma[n][i + 1] = 1;
                ma[i + 2][n] = ma[n][i + 2] = 1;
            }
            printf("Yes\n");
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) {
                    printf("%d", ma[i][j]);
                }
                printf("\n");
            }
            printf("2 4 1 3");
            for (int i = 5; i <= n-1; i += 4) {
                printf(" %d %d %d %d", i + 2, i, i + 3, i + 1);
            }
            printf(" %d", n);
            printf("\n");
        }
        else printf("No\n");
    }
}