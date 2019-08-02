//网络流2选1模型
//变式重构版本 在本题中 选择两个集合之间也有相应的贡献 
//但本质相同 关键是抓住： 依然将s作为集合A t作为集合B 割完之后留下的边权和 应当是这种割对应状态的题目所求贡献
//因此 对组合i ：在将他们都割到S一侧即集合A时 未被切割的边权值之和应当是ai
//            : 都割到T一侧即集合B时 未被切割的边权值之和应当是bi
//            : 一个在S侧一个在T侧，即分属AB集合时，未被切割的边权值之和应当是ci = ai/4 + bi/3
//根据以上三个关系，可以列出三个方程，结合方程约束构造网络流二选一模型即可
#include<bits/stdc++.h>
#define int long long 
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
const int N = 240600;//要注意根据题目的不同调整参数 N为图中点数 本题中为源点+汇点+maxn个基站+maxm个用户 
const int M = 201000;// M为图中边数，本题中为（3*maxm+1*maxn）*2 注意本模板中所有的加边都是加两条边，正向的容量边和逆向的容量为0的回边，所以边数要乘以2 
int cnt;
int Head[N];
int Next[M];
int W[M];
int V[M];
int Depth[N];
int cur[N];//cur就是记录当前点u循环到了哪一条边
int s, t,n,m;//s,t:源点，汇点
const int inf = 0x3f3f3f3f;
void init()
{
	cnt = -1;
	memset(Head, -1, sizeof(Head));
	memset(Next, -1, sizeof(Next));
}
void _Add(int u, int v, int w)
{
	cnt++;
	Next[cnt] = Head[u];
	Head[u] = cnt;
	V[cnt] = v;
	W[cnt] = w;
}
void Add_Edge(int u, int v, int w)
{
	_Add(u, v, w);
	_Add(v, u, 0);
}
int dfs(int u, int flow)
{
	if (u == t)
		return flow;
	for (int& i = cur[u]; i != -1; i = Next[i])//注意这里的&符号，这样i增加的同时也能改变cur[u]的值，达到记录当前弧的目的
	{
		if ((Depth[V[i]] == Depth[u] + 1) && (W[i] != 0))
		{
			int di = dfs(V[i], min(flow, W[i]));
			if (di>0)
			{
				W[i] -= di;
				W[i ^ 1] += di;
				return di;
			}
		}
	}
	return 0;
}
int bfs()
{
	queue<int> Q;
	while (!Q.empty())
		Q.pop();
	memset(Depth, 0, sizeof(Depth));
	Depth[s] = 1;
	Q.push(s);
	do
	{
		int u = Q.front();
		Q.pop();
		for (int i = Head[u]; i != -1; i = Next[i])
			if ((Depth[V[i]] == 0) && (W[i]>0))
			{
				Depth[V[i]] = Depth[u] + 1;
				Q.push(V[i]);
			}
	} while (!Q.empty());
	if (Depth[t]>0)
		return 1;
	return 0;
}
int Dinic()
{
	int Ans = 0;
	while (bfs())
	{
		for (int i = s; i <= t; i++)//每一次建立完分层图后都要把cur置为每一个点的第一条边 感谢@青衫白叙指出这里之前的一个疏漏
			cur[i] = Head[i];
		while (int d = dfs(s, inf))
		{
			Ans += d;
		}
	}
	return Ans;
}
signed main() {
    while(~scanf("%d%d", &n, &m)){
        init();
	    int ans=0;
	    s=0;t=n+2*m+1;
	    for (int i = 1; i <= m; i++) {
		    int u,v,ai,bi,ci;
		    scanf("%d%d%d%d%d",&u,&v,&ai,&bi,&ci);
		    ans+=ci; ans+=ai;
			int le = n + 2* (i-1) +1;
			int ri = n + 2* (i-1) +2;
		    Add_Edge(s,u,ai/4);
            Add_Edge(s,v,ai/4);
            Add_Edge(s,le,ai/2);
            Add_Edge(le,u,inf);
            Add_Edge(le,v,inf);
            Add_Edge(u,ri,inf);
            Add_Edge(v,ri,inf);
            Add_Edge(ri,t,ci/3);
            Add_Edge(u,t,ci/3);
            Add_Edge(v,t,ci/3);
	    }
//	scanf("%d%d", &s, &t);
	    int ans1=Dinic();
	    printf("%lld\n",ans-ans1);	//当初这道题求得是最大权闭合子图，所以等于(正权和-最小割/最大流) 
    }
	
}