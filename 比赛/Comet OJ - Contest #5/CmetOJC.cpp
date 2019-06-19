/*
���ļ������BFS + ���ȶ����Ҹ� 


H��ϲ������̨ɹ̫������Ͼ֮��������һЩ����С��Ϸ��H�����С��Ϸ���Գ����һ�� 
n ���ڵ���и���������1 Ϊ����ÿ�������ȶ���Ϊ�䵽���ļ�·���ϵĵ������������Ϊ1����
H���� n ����Ա��H���ᰴ��ĳ��˳������ǲ�������ÿһ���ڵ��ϣ�ʹ��ÿ���ڵ���ǡ����һ����Ա��
������Ϸ�Ļ��ƣ����Ƕ�ÿ���ڵ� i�������˸����Ʋ��� ai�� 
Ҫ��H���ڵ� i���ڵ㲿���Ա֮ǰ��������� >ai�Ľڵ��ϲ����и�Ա��
ͬʱ��ϷΪ������ҹ��أ���֤�� ai���ڵ��ڵ� i ����ȡ�
H����ÿһ�β����Ա�Ľڵ㰴˳��д��ֽ�ϣ��γ���һ�� 1��n ������
H��Ϊ�˻�ø���Ľ�������Ҫ��С������е��ֵ���
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
