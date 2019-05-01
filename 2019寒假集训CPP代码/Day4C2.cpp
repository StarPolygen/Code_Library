#include<bits/stdc++.h>
using namespace std;
const int MAXN=210000;
int n,m,k;
vector<int> head[MAXN];
vector<pair<int, int> > rnk[MAXN];
int solid[MAXN];
int low[MAXN],ans[MAXN];
int high[MAXN];
int in[MAXN];
int flag=1;
struct Edge
{
    int x,y;
    Edge() {}
}edge[MAXN];
void Input()
{
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&solid[i]);
    }
    int u,v;
    for(int i=1;i<=m;++i)
    {
        scanf("%d%d",&edge[i].x,&edge[i].y);
    }
}
void init()
{
    for(int i=1;i<=n;++i)
    {
        head[i].clear();
        in[i]=0;
    }
}
void toposort(int now[],int type)
{
    queue<int > q;
    int cnt=0;
    for(int i=1;i<=n;++i)
    {
        if(!in[i])
        {
            q.push(i);
            ++cnt;
        }
    }
    while(!q.empty())
    {
        int u=q.front();q.pop();
        for(int i=0;i<head[u].size();++i)
        {
            int v=head[u][i];
            if(type<0)
            {
                now[v]=min(now[v],now[u]-1);
            }
            else
            {
                now[v]=max(now[v],now[u]+1);
            }
            if(--in[v]<=0)
            {
                ++cnt;
                q.push(v);
            }
        }
    }
    if(cnt!=n)
    {
        flag=0;
    }
}
void work()
{
    int u,v;
    flag=1;
    init();
    for(int i=1;i<=n;++i)
    {
        if(solid[i]) high[i]=solid[i];
        else high[i]=k;
    }
    for(int i=1;i<=m;++i)
    {
        u=edge[i].x,v=edge[i].y;
        head[u].push_back(v);
        in[v]++;
    }
    toposort(high,-1);
    if(flag==0)
    {
        printf("-1\n");
        return;
    }
    init();
    for(int i=1;i<=n;++i)
    {
        if(solid[i]) low[i]=solid[i];
        else low[i]=1;
    }
    for(int i=1;i<=m;++i)
    {
        u=edge[i].y;v=edge[i].x;
        head[u].push_back(v);
        in[v]++;
    }
    toposort(low,1);
    if(flag==0)
    {
        printf("-1\n");
        return;
    }

    for(int i=1;i<=n;++i)
    {
        if(low[i]>high[i])
        {
            printf("-1\n");return;
        }
    }
    int top=k;
    for(int i=1;i<=k;++i) rnk[i].clear();
    for(int i=1;i<=n;++i)
    {
        rnk[high[i]].push_back(make_pair(-low[i],i));
    }
    set< pair<int,int> > S;
    set< pair<int,int> >::iterator it;
    for(int i=0;i<rnk[k].size();++i)
    {
        S.insert(rnk[k][i]);
    }
    pair<int ,int > tmp;
    while(top)
    {
        if(S.empty())
        {
            printf("-1\n");
            return;
        }
        it=S.begin();
        tmp=*it;
        ans[tmp.second]=top;
        S.erase(it);
        while(1)
        {
            it=S.begin();
            tmp=*it;
            if(-tmp.first<top) break;
            ans[tmp.second]=top;
            S.erase(it);
        }
        --top;
        for(int i=0;i<rnk[top].size();++i)
        {
            S.insert(rnk[top][i]);
        }
    }
    while(!S.empty())
    {
        tmp=*it;
        ans[tmp.second]=1;
        S.erase(it);
    }
    for(int i=1;i<=n;++i)
        printf("%d ",ans[i]);
    printf("\n");
}
int main()
{
  //  freopen("in.txt","r",stdin);
    Input();
    work();
    return 0;
}
