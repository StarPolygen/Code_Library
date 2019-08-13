//二分 DP
//f[0, x] = min(max(f[0, i i 1] + b, f[0, x x i] + a)) 表示区间长度为 x, 左端点为 0．
//f[1, x] = min(max(f[1, i i 1] + b, f[0, x x i] + a)) 表示区间长度为 x, 左端点不为 0．
//初始值 f[0, 0] = 0, f[1, 0] = a．
//转移：二分确定对于成功和失败最接近的位置
#include <bits/stdc++.h>
#define ll long long 
using namespace std;
const ll inf = 1E18;
unordered_map <int, ll> f1, f2;

ll cal1(int x, int a, int b);
ll cal2(int x, int a, int b);

int main()
{
    int T;
    cin >> T;
    while(T--){
        int l, r, a, b;
        scanf("%d%d%d%d", &l, &r, &a, &b);
        f1.clear(), f2.clear();
        if (l == 0) cout << cal1(r, a, b) << endl;
        else cout << cal2(r - l, a, b) << endl;
    }
    return 0;
}

ll cal1(int x, int a, int b){
    if (x == 0)
         return 0;
    if (f1.find(x) != f1.end()) 
        return f1[x];
    int l = 0, r = x;
    while(l < r){
        int m = (l + r + 1) / 2;
        if (cal1(m - 1, a, b) + b > cal1(x - m, a, b) + a) {
            r = m - 1;
        }
        else{
            l = m;
        }
    }
    int m = l;
    ll tmp = inf;
    for (int i = max(m - 1, 1); i <= min(x, m + 1); i++)
    {
        tmp = min(tmp, max(cal1(i - 1, a, b) + b, cal1(x - i, a, b) + a));
    }
    f1[x] = tmp;
    
    return tmp;
}
ll cal2(int x, int a, int b){
    if (x == 0) 
        return a;
    if (f2.find(x) != f2.end()) 
        return f2[x];
    int l = 0, r = x;
     while(l < r){
        int m = (l + r + 1) / 2;
        if (cal1(m - 1, a, b) + b > cal1(x - m, a, b) + a) {
            r = m - 1;
        }
        else{
            l = m;
        }
    }
    int m = l;
    ll tmp = inf;
    for (int i = max(m - 1, 1); i <= min(x, m + 1); i++){
        tmp = min(tmp, max(cal2(i - 1, a, b) + b, cal1(x - i, a, b) + a));
    }
    f2[x] = tmp;
    
    return tmp;
}