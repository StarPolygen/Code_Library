//概率DP 记忆化搜索
/*1.起初物品掉落率q=2%;
2.玩家进行一次游戏，有p的概率获胜。
3.如果获胜了，有q的概率掉落一个叫Beta Pack的物品。如果获胜，q+=2%;否则，q+=1.5%。
重复2和3。
求得到一个物品 进行游戏场次的期望。*/
#include <bits/stdc++.h>
#define ll long long
#define maxn 1005
using namespace std;

//dp[q][p]为掉落概率为q，赢概率为p时的round数期望
//p赢的概率 *100保证下标整数
//q掉落概率 *1000保证下标整数 每输一次q+15 赢一次q+20
//q上限1000 p上限100
double dp[maxn][105];
double dfs(int q, int p) //记忆化搜索
{
	if (dp[q][p] != -1)
		return dp[q][p];
	//当前状态期望 = 1（当前轮）+ 赢了但不掉落的Round期望 + 输了的Round期望
	dp[q][p] = 1 + 1.0 * p / 100 * (1 - 1.0 * q / 1000) * dfs(min(q + 20, 1000), p);
	dp[q][p] += (100.0 - p) / 100 * dfs(min(q + 15, 1000), p);
	//记忆化
	return dp[q][p];
}
int main()
{
	int T, p;
	//便于记忆化搜索的初始化
	for (int i = 1; i <= 1000; i++)
		for (int j = 1; j <= 100; j++)
			dp[i][j] = -1;

	//DP基础状态   当100%掉落时,需要进行的Round数期望数为1/赢的概率
	for (int i = 1; i <= 100; i++)
		dp[1000][i] = 100.0 / i;

	scanf("%d", &T);
	for (int i = 1; i <= T; i++)
	{
		scanf("%d", &p);
		//记忆化搜索
		printf("Case %d: %.10f\n", i, dfs(20, p));
	}
	return 0;
}
s