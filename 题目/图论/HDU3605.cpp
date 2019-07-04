//最大流
//首先需要预处理，将人按照10个星球的不同分类。从源点分别连线这些类，容量为该类的人数。每类向各自可适应的星球连边，容量无限。每个星球向汇点连线，容量为星球容量。最大流即为答案。
#include<bits/stdc++.h> 
#define maxn 
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
const int N = 2000;//要注意根据题目的不同调整参数 N为图中点数 本题中为源点+汇点+maxn个基站+maxm个用户 
const int M = 30000;// M为图中边数，本题中为（3*maxm+1*maxn）*2 注意本模板中所有的加边都是加两条边，正向的容量边和逆向的容量为0的回边，所以边数要乘以2 
int cnt;
int Head[N];
int Next[M];
int W[M];
int V[M];
int Depth[N];
int cur[N];//cur就是记录当前点u循环到了哪一条边
int s, t,n,m;//s,t:源点，汇点
const int inf = 0x3f3f3f3f;

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
int arr[1050];
int all[15];
void init()
{
	cnt = -1;
	memset(Head, -1, sizeof(Head));
	memset(Next, -1, sizeof(Next));
	memset(arr,0,sizeof(arr));
	memset(all,0,sizeof(all));
}
int main() {
	while(~scanf("%d%d",&n,&m)){
		init();
        for(int i=1;i<=n;i++){
			int ind=0;
			for(int j=1;j<=m;j++){
				int tmp;
				scanf("%d",&tmp);
				ind+=(tmp<<(m-j));
			}
			arr[ind]++;
        }
		s=0;
		for(int i=0;i<(1<<m);i++){
			Add_Edge(s,i+1,arr[i]);
			for(int j=m-1;j>=0;j--){
				if((i>>j)&1==1) Add_Edge(i+1,(1<<m)+(m-j),inf);
			}
		}
		t=(1<<m)+m+1;
		for(int i=1;i<=m;i++){
			int rl;//容量
			scanf("%d",&rl);
			Add_Edge((1<<m)+i,t,rl);
		}

		int ans=Dinic();
		if(ans==n) printf("YES\n");
		else printf("NO\n");
    }
	
}