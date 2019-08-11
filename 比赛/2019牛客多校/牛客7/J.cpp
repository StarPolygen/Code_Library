//签到题
//栈 模拟即可
// #pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define sc second
#define pb push_back
#define mp make_pair
#define LEN(X) strlen(X)
#define SZ(X) ((int)(X).size())
#define ALL(X) (X).begin(), (X).end()
#define FOR(I, N) for (int I = 0; I < (N); ++I)
#define FORD(I, N) for (int I = N; I; ++I)
#define REP(I, A, B) for (int I = A; I <= (B); ++I)
#define REPD(I, A, B) for (int I = B; I >= A; --I)
#define FORS(I, S) for (int I = 0; S[I]; ++I)
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pi;
const int N = 1e6 + 5;
list<char> ls;
char s[N];
int main(){
    scanf(" %s",s);
    int ans = 0;
    FORS(i,s){
        ls.pb(s[i]);
        auto it = ls.end();
        it--;
        while (SZ(ls)>=3){
            it = ls.end();
            it--;
            auto it2 = it;
            it2--;
            auto it3 = it2;
            it3--;
            if (*it3 == *it2 && *it2==*it){
                ans++;
                ls.erase(it);
                ls.erase(it2);
                ls.erase(it3);
            }else{
                break;
            }
        }
    }
    printf("%d\n", ans);
 
    return 0;
}