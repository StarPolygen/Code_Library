#include<bits/stdc++.h>
const int INF = 0x3f3f3f3f;
struct node
{
    int cost,flow,v,u,next;
};

int N;
node edges[N*1000];
int head[N],e,s,t;
int pre[N];


void add(int u,int v,int flow,int cost)
{
    edges[e].u=u;
    edges[e].v=v;
    edges[e].cost=cost;
    edges[e].flow=flow;
    edges[e].next=head[u];
    head[u]=e++;
}


void Add(int u,int v,int flow,int cost)
{
    add(u,v,flow,cost);
    add(v,u,0,-cost);
}


int SPFA(int s,int t)
{
    clr(pre,-1);
    int F[N],h[N],C[N],i,u,v,f,c;
    queue<int> Q;
    for(int i=0,i<=t+1;i++) C[i]=INF,h[i]=0,F[i]=0;
    Q.push(s); C[s]=0; F[s]=INF;
    while(!Q.empty())
    {
        u=Q.front();
        Q.pop();


        h[u]=0;
        for(i=head[u];i!=-1;i=edges[i].next)
        {
            v=edges[i].v;
            f=edges[i].flow;
            c=edges[i].cost;
            if(f>0&&C[v]>C[u]+c)
            {
                C[v]=C[u]+c;
                F[v]=min(F[u],f);
                pre[v]=i;
                if(!h[v]) h[v]=1,Q.push(v);
            }
        }
    }
    return F[t];
}


int MCMF(int s,int t)
{
    int ans=0,i,temp;
    while(temp=SPFA(s,t))
    {
        for(i=pre[t];i!=-1;i=pre[edges[i].u])
        {
            ans+=temp*edges[i].cost;
            edges[i].flow-=temp;
            edges[i^1].flow+=temp;
        }
    }
    return ans;
}


int n,m,d[N];


int main()
{
    RD(n,m); clr(head,-1); e=0; s=0; t=n+2;
    int i,u,v,c,temp;
    FOR1(i,n) RD(d[i]);
    FOR1(i,m)
    {
        RD(u,v,c);
        Add(u,v+1,INF,c);
    }
    FOR1(i,n+1)
    {
        temp=d[i]-d[i-1];
        if(temp>=0) Add(s,i,temp,0);
        else Add(i,t,-temp,0);
        if(i>1) Add(i,i-1,INF,0);
    }
    PR(MCMF(s,t));
}
