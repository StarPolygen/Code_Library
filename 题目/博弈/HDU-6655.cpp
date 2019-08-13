//双值博弈
//两人玩牌 各自有一手牌 牌有各种颜色 游戏规则： 不能出对方之前出过颜色的牌 可以出自己出过颜色的牌 谁不能出就输 无论是手中无牌或是手中有牌但不能出
//问题可以规约为另一个经典问题：
//一堆物品 有权值Ai，Bi  A获得该物品得分Ai，B获得该物品得分Bi，分高者胜出 A、B轮流选取物品 求最优策略下两人各自收益
//这个问题何解：
//每个人在选取物品时 不仅会带给自己Ai 也潜在地抹杀了对方获得Bi的可能性 因此在竞争的状态下 真正的潜在收益是Ai + Bi 因此按照物品Ai+Bi的权值排序 AB依次选取即为答案
//本题亦是如此：
// 比赛的胜利取决于两人可能出牌的数量    可视为上述问题中的得分
// 每个人在选择出牌时 不仅会让自己手中的相同牌可出       可视为Ai  (相当于使得自己多Ai张牌可出 Ai为自己手中这种颜色牌数)
//                  也会封堵掉对方手牌中同色牌的可能性  可视为Bi  (相当于对方失去出Bi张牌的机会 Bi为对方手中该色牌数)
// 因此选择每种牌潜在的得分都是Ai + Bi，套用经典问题的解法，将所有两人手中都有的颜色按照Ai+Bi 排序，分别让AB轮流选择出牌，贪心比较双方手中剩余牌数即可

#include<bits/stdc++.h>
using namespace std;
#define fi first
#define sc second
#define pb push_back
#define mp make_pair
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pi;
const int N = 1e6 + 5;

unordered_map<int, int> fn1, fn2;
unordered_map<int, char> bel;
pi a[N];
int tot;
ull k1, k2, MOD;
ull rng() {
    ull k3 = k1, k4 = k2;
    k1 = k4;
    k3 ^= k3 << 23;
    k2 = k3 ^ k4 ^ (k3 >> 17) ^ (k4 >> 26);
    return k2 + k4;
}
int main(){
    int _;
    for (scanf("%d", &_); _;_--)
    {   
        fn1.clear();
        fn2.clear();
        bel.clear();
        tot = 0;
        int n, m, p;
        scanf("%d%d%d", &n, &m, &p);
        int ans[2] = {0, 0};
        if (p==1){
            for (int i = 1; i <= n; ++i)
            {
                int x;
                scanf("%d",&x);
                ++fn1[x];
            }
            for (int i = 1; i <= m; ++i)
            {
                int x;
                scanf("%d", &x);
                ++fn2[x];
            }
        }else{
            scanf("%llu%llu%d", &k1, &k2, &MOD);
            for (int i = 1; i <= n; ++i)
            {
                ull x = rng()%MOD;
                ++fn1[x];
            }
            scanf("%llu%llu%d", &k1, &k2, &MOD);
            for (int i = 1; i <= m; ++i)
            {
                ull x = rng() % MOD;
                ++fn2[x];
            }
        }
        for (auto it = fn1.begin(); it != fn1.end();it++){
            auto it2 = fn2.find(it->first);
            if (it2==fn2.end()) continue;
            a[tot++] = mp(it->sc + it2->sc, it->fi);
        }
        sort(a, a + tot, [](pi a, pi b) {
            return a > b;
        });
        for(int i = 0; i < tot;++i)
        {
            bel[a[i].sc] = (i & 1) + '0';
        }
        for (auto it = fn1.begin();it!=fn1.end();it++){
            auto it2 = bel.find(it->first);
            if (it2!=bel.end() && it2->second=='1') continue;
            ans[0] += it->second;
        }
        for (auto it = fn2.begin();it!=fn2.end();it++){
            auto it2 = bel.find(it->first);
            if (it2!=bel.end() && it2->second=='0') continue;
            ans[1] += it->second;
        }
        printf("%s\n", ans[0] > ans[1] ? "Cuber QQ" : "Quber CC");
    }
    return 0;
}