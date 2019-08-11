//单调栈 前缀和
//给定01矩阵 询问极大全1子矩阵的个数
//将所有1堆叠到一起 ：求前缀和
//对于行i 维护两个unordered_map分别代表 i-1th的最大可行区间f1 和 当前行i的最大可行区间f2
//单调栈处理i行j元素的小于等于它的区间[l,r]
//对于每个j元素所对应的区间 若该元素为0 再见 否则查询f2 和 f1中是否已经有该区间
//              f2查询到代表当前行已经出现过该区间 不统计 否则将区间插入f2
//              f1查询到代表该区间可以与上一行合并 不统计 
//否则代表该区间有效 答案+1
#pragma GCC optimize(3)
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
#define REPD(I, B, A) for (int I = B; I >= A; --I)
#define FORS(I, S) for (int I = 0; S[I]; ++I)
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pi;
typedef pair<ll, ll> pl;
const int N = 3e3 + 5;
int n, m;
int maze[N][N];
char s[N];
unordered_map<int, char> f1, f2;
stack<pi> st;
int l[N], r[N];
int main(){
    // clock_t sst = clock();
    scanf("%d%d", &n, &m);

    //将所有1堆叠到一起 ：求前缀和
    for (register int i = 1; i <= n;++i)
    {
        scanf(" %s", s);
        int len = strlen(s);
        for (register int j = 0; j < len;++j)
        {
            maze[i][j + 1] = s[j] - '0';
            if (!maze[i][j+1]) continue;
            maze[i][j + 1] += maze[i - 1][j + 1];
        }
    }
    int ans = 0;

    //对于行i
    for (register int i = 1; i <= n;++i)
    {
        //维护两个unordered_map分别代表 i-1th的最大可行区间f1 和 当前行i的最大可行区间f2
        f1 = f2;
        f2.clear();
        //单调栈处理i行j元素的小于等于它的区间
        //获得区间右边界
        for (register int j = 1; j <= m; ++j)
        {
            while (!st.empty() && maze[i][j]<st.top().fi) {
                r[st.top().sc] = j;
                st.pop();
            }
            st.push(mp(maze[i][j], j));
        }
        while (!st.empty()){
            r[st.top().sc] = m + 1;
            st.pop();
        }

        //获得区间左边界
        for (register int j = m; j >= 1;--j)
        {
            while (!st.empty() && maze[i][j]<st.top().fi){
                l[st.top().sc] = j;
                st.pop();
            }
            st.push(mp(maze[i][j], j));
        }
        while (!st.empty()){
            l[st.top().sc] = 0;
            st.pop();
        }

        //对于每个j元素所对应的区间
        for (register int j = 1; j <= m;++j)
        {
            //若该元素为0 再见
            if (!maze[i][j]) continue;
            //否则查询f2 和 f1中是否已经有该区间
            int now = (l[j] + 1) * 10000 + (r[j] - 1);  //将区间映射成一个数，加快unordered_map运行
            auto it1 = f1.find(now);
            auto it2 = f2.find(now);
            if (it2!=f2.end()) continue;//如果当前行已经出现过
            //否则将该区间插入当前行
            f2[now] = '1';
            if (it1!=f1.end()) continue;//上一行出现过意味着可以合并
            ++ans;
        }
    }
    printf("%d\n", ans);
    // clock_t et = clock();
    // cout << (double)(et - sst) / CLOCKS_PER_SEC << endl;
    return 0;
}