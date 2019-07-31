//补题：构造
//给定n个石子，权重分别为1到n，要求将之分成k堆，每堆权值和相同，保证k为n的因子
//首先若总权值和 %k 不为0，则必不可能
//其次考虑1）n/k为偶数情况  易构造
//       2）n/k为奇数      则考虑先取出前1-3K的石子 进行构造 可以证明此时k必为奇数（偶数可推出矛盾）  剩余石子按照1）中进行分配即可
#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int n, k;
        scanf("%d %d", &n, &k);
        vector<int> a[k];
        if ((1ll * (1 + n) * n / 2) % k) {  printf("no\n");  continue; }
        printf("yes\n");
        if (n == k && n == 1) {  printf("1\n");  continue; };
        if ((n / k) & 1){
            for (int i = 0; i < k; i++)  a[i].push_back(3 * k - i);
            for (int i = 2 * k; i >= k + 1; i--)  a[(k / 2 + (2 * k - i)) % k].push_back(i);
            for (int i = 0; i < k; i++)  a[i].push_back(1ll * (1 + 3 * k) * 3 / 2 - a[i][0] - a[i][1]);
            for (int i = 3 * k; i < n; i++)  a[i % k].push_back(i + 1);
            for (int i = 3; i < n / k; i += 2) for (int j = 0; j * 2 < k; j++)  swap(a[j][i], a[k - 1 - j][i]);
        }
        else {
            for (int i = 0; i < n; i++) a[i % k].push_back(i + 1);
            for (int i = 0; i < n / k; i += 2) for (int j = 0; j * 2 < k; j++)  swap(a[j][i], a[k - 1 - j][i]);
        }
        for (int i = 0; i < k; i++)
            for (int j = 0; j < a[i].size(); j++){
                printf("%d", a[i][j]);
                if (j < a[i].size() - 1)  printf(" ");
                else printf("\n");
            }
    }
    return 0;
}