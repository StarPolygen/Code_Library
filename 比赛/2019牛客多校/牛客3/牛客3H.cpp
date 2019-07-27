//平面几何
//平面上n个点，求一条线将它们分在两侧,线不能过点
//按照x轴排序，由于点坐标都在-1000至1000内，可以找（x1,-10000）,(x2,10000)形成一条接近竖直的线.
//x1=x2的情况时，过俩中点类似地构造一条接近竖直的线即可
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
pair<int,int> a[N];
int main(){
    int t;
    scanf("%d", &t);
    while (t--){
        int n;
        scanf("%d", &n);
        for (int i = 1; i <= n;i++)
        {
            int x, y;
            scanf("%d%d", &x, &y);
            a[i] = make_pair(x, y);
        }
        sort(a + 1, a + 1 + n);
        int mid = n / 2;
        if (a[mid].first==a[mid+1].first){
            printf("%d %d %d %d\n", a[mid].first - 1, a[mid].second + 10000000, a[mid].first + 1, a[mid + 1].second - 10000000);
        }else{
            printf("%d %d %d %d\n", a[mid].first, 999000000, a[mid + 1].first, -999000000);
        }
    }
    return 0;
}