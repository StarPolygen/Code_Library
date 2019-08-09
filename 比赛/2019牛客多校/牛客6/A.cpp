//暴力：Author BigBang_019
// #pragma GCC optimize(2)
#include<bits/stdc++.h>
using namespace std;
#define mp make_pair
#define fi first
#define sc second
#define pb push_back
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pi;
const int N = 2e3 + 5;
const int MOD = 1e9 + 7;
char s[N];
list<string> ls;
int main(){
    int _;
    for (scanf("%d", &_); _; _--)
    {
        ls.clear();
        scanf(" %s",s);
        stringstream ss;
        int len = strlen(s);
        for (int i = 0; i < len;i++)
        {
            char sss[2] = {s[i], '\0'};
            ls.pb(sss);
        }
        for (int i = 1; i <= len; i++)
        {
            bool fl = 0;
            auto it = ls.end();
            it--;
            for (; ;)
            {
                if (it==ls.begin())
                    break;
                auto it2 = it;
                it2--;
                if ((*it).compare(*it2)>=0){
                    auto it3 = it;
                    it = it2;
                    ss.str("");
                    ss << *it2 << *it3;
                    ls.insert(it2, ss.str());
                    it--;
                    ls.erase(it3);
                    ls.erase(it2);
                }else
                    it--;
            }
        }
        for (auto it = ls.begin(); it != ls.end();it++)
        {
            printf("%s ", (*it).c_str());
        }
        puts("");
    }
    return 0;
}