#include <bits/stdc++.h>
#define pair<int,int> pii
using namespace std;
const int MAXN = 105;
const int INF = 2000101010;

struct Node{
    vector<pii> antique;  //
    int val ;
    //这个顺序，先搜大的，minv
    bool operator < ( const Node& a ) const{
        return val > a.val ;
    }
} ;

Node shop[MAXN];
int minv[MAXN][MAXN];
int pre[MAXN];
int tmp[MAXN][MAXN];
int ans;
int n, m, k;

 

void dfs(int cur, int num ){

    int val = 0 ;
    for ( int i = 1 ; i <= n ; ++ i ){

        if (pre[i] == INF)

        {

            val = INF ;

            break ;

        }

        val += pre[i] ;

    }

    if ( val < ans )

        ans = val ;

    //超过k则返回

    if ( num >= k )

        return ;

    int tot = 0 ;

    //很重要的剪枝，如果后面没有更优的，那没有必要再搜索下去

    for ( int i = 1 ; i <= n ; ++ i )

    {

        if ( pre[i] == INF && minv[cur][i] == INF )

            return ;

        tot += min ( pre[i], minv[cur][i] ) ;

        if ( tot >= ans )

            return ;

    }

    for ( int i = cur ; i <= m ; ++ i )

    {

        for ( int j = 1 ; j <= n ; ++ j )

        {

            tmp[num][j] = pre[j] ;

        }

        for ( int j = 0 ; j < a[i].G.size () ; ++ j )

        {

            int x = a[i].G[j].first ;

            pre[x] = min (pre[x], a[i].G[j].second) ;

        }

        dfs ( i + 1, num + 1 ) ;

        for ( int j = 1 ; j <= n ; ++ j )

        {

            pre[j] = tmp[num][j] ;

        }

    }

}

 

void solve ()

{

    

    

    

    sort ( a + 1, a + m + 1 ) ;

    for ( int i = 1 ; i <= n ; ++ i )

    {

        minv[m + 1][i] = INF ;

        pre[i] = INF ;

    }

    for ( int i = m ; i >= 1 ; -- i )

    {

        for ( int j = 1 ; j <= n ; ++ j )

        {

            minv[i][j] = minv[i + 1][j] ;

        }

        for ( int j = 0 ; j < a[i].G.size () ; ++ j )

        {

            int x = a[i].G[j].first, v = a[i].G[j].second ;

            minv[i][x] = min ( minv[i][x], v ) ;

        }

    }

    dfs ( 1, 0 ) ;

    printf ( "%d\n", ans == INF ? -1 : ans ) ;

}

 

int main(){
    scanf("%d%d%d",&n,&m,&k);
    ans = 1000000000;
    for (int i = 1; i <= m; ++ i){
        shop[i].antique.clear () ;
        shop[i].val = 0 ;
    }
    for ( int i = 1 ; i <= n ; ++ i ){
        int a, p, b, q ;
        scanf("%d%d%d%d",&a,&p,&b,&q);
        shop[a].val ++ ;
        shop[b].val ++ ;
        if (p<q)  shop[a].val += 2 ;
        else    shop[b].val += 2 ;

        shop[a].antique.push_back( pii( i,p ) ) ;
        shop[b].antique.push_back( pii( i,q ) ) ;

    }

    return 0 ;

}
