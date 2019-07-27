// 作者：朱
// 模拟
#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define sc second
#define fi first
using namespace std;
typedef long long ll;
typedef pair<int, int > pi;
const int N = 1e6 + 5;
char s[N];
ll tot, c[4], r[N];
int main(){
    scanf(" %s", s);
    int len = strlen(s);
    ll ans = 0;
    for (int i = 0; i < len;i++)
    {
        if (s[i]=='0'){
            tot++;
        }else{
            ans += tot * (tot + 1) / 2;
            tot = 0;
        }
    }
    int now = 0;
    for (int i = len - 1; i >= 0;i--)
    {
        r[i] = now;
        if (s[i]=='0')
            now++;
        else
            now = 0;
    }
    ans += tot * (tot + 1) / 2;
    ll sum = 0;
    for (int i = len - 1; i >= 0; i--)
    {
        if (s[i] != '0')
        {
            c[sum % 3] += max(r[i] - 1, 0ll);
        }
        sum += s[i] - '0';
        ans += c[sum % 3];
    }
    printf("%lld\n", ans);
    return 0;
}