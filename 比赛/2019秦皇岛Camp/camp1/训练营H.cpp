#include<bits/stdc++.h>
#define ll long long
using namespace std;
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <cassert>
#include <queue>
#define ll long long
using namespace std;
const ll INF=1000000000000000000;
const int MAXN=200100;
struct qnode{
    int v;
    ll c;
    qnode(int _v=0,ll _c=0):v(_v),c(_c){}
    bool operator <(const qnode &r)const {
        return c-r.c>=0;
    }
};

struct Edge{
    int v;
    ll cost;
    Edge(int _v=0,ll _cost=0):v(_v),cost(_cost){}

};

vector<Edge>E[MAXN];
void addedge(int u,int v,ll w){
    E[v].push_back(Edge(u,w));
    E[u].push_back(Edge(v,w));
}

void ini(){
    memset(E,0,sizeof(E));
}
int main(){
    return 0;
}