/*
树的级序遍历BFS + 优先队列乱搞 


H君喜欢在阳台晒太阳，闲暇之余他会玩一些塔防小游戏。H君玩的小游戏可以抽象成一棵 
n 个节点的有根树，树以1 为根，每个点的深度定义为其到根的简单路径上的点数（根的深度为1）。
H君有 n 个干员，H君会按照某种顺序把她们部署到树的每一个节点上，使得每个节点上恰好有一个干员。
由于游戏的机制，他们对每个节点 i都给出了个限制参数 ai。 
要求H君在第 i个节点部署干员之前，所有深度 >ai的节点上不能有干员。
同时游戏为了让玩家过关，保证了 ai大于等于点 i 的深度。
H君将每一次部署干员的节点按顺序写在纸上，形成了一个 1…n 的排列
H君为了获得更多的奖励，想要最小化这个列的字典序。
*/
 
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 5e5 + 5;
priority_queue<int, vector<int>, greater<int>> q;
priority_queue<int, vector<int>, greater<int>> qn;
struct NODE{
	int p, d;
	bool operator < (const NODE & b) const{
		if (d==b.d)
			return p < b.p;
		else
			return d < b.d;
	}
} a[N];
int cnt, he[N], ne[N * 2], v[N * 2];
int res[N];
int vis[N];
int n;
void add(int x,int y){
	cnt++;
	ne[cnt] = he[x];
	he[x] = cnt;
	v[cnt] = y;
}
void dfs(int x,int fa,int dep){
	a[x].d = dep;
	for (int i = he[x]; i;i=ne[i])
	{
		int p = v[i];
		if (p==fa)
			continue;
		dfs(p, x, dep + 1);
	}
}
int main(){
	scanf("%d", &n);
	for (int i = 1; i < n;i++)
	{
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
		add(y, x);
	}
	for (int i = 1; i <= n;i++)
	{
		scanf("%d", &res[i]);
		a[i].p = i;
	}
	dfs(1, 0, 1);
	sort(a + 1, a + 1 + n);
	for (int i = 1; i <= n;i++)
	{
		int p = a[i].p;
		int d = a[i].d;
		int r = res[p];
		while (!qn.empty() && qn.top()<d){
			int now = q.top();
			q.pop();
			printf("%d ", now);
			vis[res[now]]--;
			while (!qn.empty() && vis[qn.top()]==0)
				qn.pop();
		}
		if (!vis[r])
			qn.push(r);
		vis[r]++;
		q.push(p);
	}
	while (!q.empty()){
		printf("%d ",q.top());
		q.pop();
	}
	return 0;
}
