//博弈好题  SG函数

//组合博弈 所以划分成子问题的NIM和
//子问题的NIM和需要求得子问题的SG,
//本题由于可行操作f过多且不断变化 SG打表不可行 但手动推得NP后 可以由DAG的某些性质获得某些结论快速得到SG

//思考 N,P 寻找必败态：
/*设t，t*t +t < s 而且使 t 尽量的大，则(t+1)*(t+1) +(t+1) >= s，由此性质
    1. c > t 则当前状态是N必胜态，因为c*c+c >= s成立
    2. c == t 则当前状态为P必败态，因为最多放c*c个石头，瓶子未满，对手必胜，至少放1个石头，则对手也是必胜。
    3. c < t 当前状态无法确定，而在瓶子中已经有c个石头的前提下，容量为 s 和容量为 t 的状态是等价的，如果(t, c)是必败态，则(s, c)也是必败态。
*/
//由以上性质，则对于每对给定的s,c  子游戏SG函数可以推得为：
    //由有向无环图的性质   当c > t时     SG=s-c
    //                   否则          SG(s,c)=SG(t,c)递归 （在瓶子中已经有c个石头的前提下，容量为 s 和容量为 t 的状态是等价的，如果(t, c)是必败态，则(s, c)也是必败态。）

#include <cstdio>
#include <cmath>
int SG(int s, int c) {
    int t = sqrt(s);
    while (t*t + t >= s) t--;
    if (c > t) return s-c;
    else return SG(t, c);
}

int main() {
    int cas = 1, ans, c, s, n;
    while(scanf("%d", &n)==1 && n) {
        ans = 0;
        while(n--) { scanf("%d%d", &s, &c); ans ^= SG(s, c); }
        printf("Case %d:\n", cas++); puts(ans?"Yes":"No");
    }
    return 0;
}
