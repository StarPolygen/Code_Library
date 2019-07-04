//最大流
/*网络流最大流。从源点分别连线N项任务，容量为该任务的Pi，共N条边。从每个任务，向其可以被执 行的天数（Si，Si+1...Ei）连边，容量为1。从每天向汇点连边，容量为M。验证最大流是否等于所有任务的总
执行天数即可。*/
#include<bits/stdc++.h> 
using namespace std;
typedef long long ll;
typedef pair<int, int> P;
const int N = 550030;//要注意根据题目的不同调整参数 N为图中点数 本题中为源点+汇点+maxn个基站+maxm个用户 
const int M = 3200010;// M为图中边数，本题中为（3*maxm+1*maxn）*2 注意本模板中所有的加边都是加两条边，正向的容量边和逆向的容量为0的回边，所以边数要乘以2 
int cnt;
int Head[N];
int Next[M];
int W[M];
int V[M];
int Depth[N];
int cur[N];//cur就是记录当前点u循环到了哪一条边
int s,t,n,m;//s,t:源点，汇点
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
int main() {
    int a;
    cin>>a;
    for(int k=1;k<=a;k++){
        init();
        int MaxE=0,SumP=0;
        cin>>n>>m;
        for(int i=1;i<=n;i++){
            int P,S,E;
            cin>>P>>S>>E;
            SumP+=P;
            if(E>MaxE) MaxE=E;
            Add_Edge(1,i+1,P);
            for(int j=S;j<=E;j++){
                Add_Edge(i+1,n+j+1,1);
            }
        }
        s=1; t=MaxE+n+2;
        for(int j=n+2;j<=n+MaxE+1;j++){
            Add_Edge(j,t,m);
        }
        int ans=Dinic();
        if(ans==SumP) cout<<"Case "<<k<<": Yes"<<endl;
        else cout<<"Case "<<k<<": No"<<endl;
        cout<<endl;
    }
    return 0;

}

