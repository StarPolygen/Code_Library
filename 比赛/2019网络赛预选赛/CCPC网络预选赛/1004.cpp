//思维 堆
#include<cstdio>
#include<set>
#include<algorithm>
#include<vector>
#include<iostream>
#include<queue>
using namespace std;

const int maxn=500000;

struct Edge{
    int to;
    long long val;
    Edge () {}
    Edge (int to, long long val) : to(to), val(val){}
    bool operator < (const Edge &x) {
        return val<x.val;
    }
};

int n,m;
int quer[maxn];
long long ans[maxn];

vector<Edge> edge[maxn];


inline void init() {
    for (int i=1;i<=n;i++) {
        edge[i].clear();
    }
}


struct Node{
    int en;
    long long val;
    Node () {}
    Node (int en, long long val) : en(en), val(val){}
    bool operator < (const Node &x) const  {
        if (val==x.val) {
            return en<x.en;
        }
        return val<x.val;
    }
    bool operator == (const Node &x) const {
        return val==x.val&&en==x.en;
    }
    
};



multiset<Node> qq;
multiset<Node>::iterator it;
priority_queue<long long> res;

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%d%d", &n,&m);
        init();
        int Q;
        scanf("%d", &Q);
        qq.clear();
        while (!res.empty()) {
            res.pop();
        }
        
        for (int i=1;i<=m;i++) {
            int x,y;
            long long w;
            scanf("%d%d%lld", &x,&y,&w);
            Edge tmp1(y,w);
            edge[x].push_back(tmp1);
            
            Node tmp2(y,w);
            qq.insert(tmp2);
            res.push(w);
        }
        for (int i=1;i<=n;i++) {
            sort(edge[i].begin(), edge[i].end());
        }
        int siz=0;
        for (int i=1;i<=Q;i++) {
            scanf("%d", &quer[i]);
            siz=max(quer[i], siz);
        }
        while (!qq.empty()) {
            it = qq.begin();
            Node top = *it;
            qq.erase(it);
            
            int u=top.en;
            for (int i=0;i<edge[u].size();i++) {
                int v=edge[u][i].to;
                long long val=edge[u][i].val;
                if (siz<=res.size()) {
                    if (res.top()>top.val+val) {
                        Node tmp(v,top.val+val);
                        qq.insert(tmp);
                        res.push(top.val+val);
                        res.pop();
                    } else {
                        break;
                    }
                } else {
                    Node tmp(v,top.val+val);
                    qq.insert(tmp);
                    res.push(top.val+val);
                }
            }
        }
        for (int i=res.size();i>=1;i--) {
            ans[i]=res.top();
            res.pop();
        }
        for (int i=1;i<=Q;i++) {
            printf("%lld\n",ans[quer[i]]);
        }
    }
    return 0;
}

/*
4
2 2 2
1 2 1
2 1 2
3
4
5 4 5
1 2 3
2 3 1
3 4 2
3 5 4
1
2
4
6
9
2 2 2
1 2 1
2 1 2
4
5
1 1 4
1 1 1
1
2 
3 
4
*/