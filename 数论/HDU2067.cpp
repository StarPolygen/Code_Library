#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define MAXN 36
#define TYPE long long
using namespace std;

//两种版本都可以AC
//卡特兰数1 
// ll catalan[MAXN];
// #ifdef MOD
// ll mod_inverse[MAXN];
// #endif
// void init_catalan()
// {
//     catalan[1] = 1;
// #ifdef MOD
//     mod_inverse[0] = 0, mod_inverse[1] = 1;
//     for (ll i = 2; i < MAXN; i++)
//         mod_inverse[i] = (MOD - MOD / i) * mod_inverse[MOD % i] % MOD;
//     for (ll i = 2; i < MAXN; i++)
//         catalan[i] = catalan[i - 1] * (4 * i - 2) % MOD * mod_inverse[i + 1] % MOD;
// #else
//     for (ll i = 2; i < MAXN && i <= 33; i++)
//         catalan[i] = catalan[i - 1] * (4 * i - 2) / (i + 1);
//     if (MAXN > 34) catalan[34] = 812944042149730764;
//     if (MAXN > 35) catalan[35] = 3116285494907301262;
//     // MAXIMUM 35 for long long
// #endif
// }


//卡特兰数2
vector<TYPE> catalan[MAXN]; // catalan[in_stack][out_stack]
void init_catalan2(){
    for (ll i = 0; i < MAXN; i++)
        catalan[i] = vector<TYPE>((unsigned) i + 1, 1);
    for (ll i = 1; i < MAXN; i++)
    {
        for (ll j = 1; j < i; j++)
        {
#ifdef MOD
            catalan[i][j] = (catalan[i - 1][j] + catalan[i][j - 1]) % MOD;
#else
            catalan[i][j] = catalan[i - 1][j] + catalan[i][j - 1];
#endif
        }
        catalan[i][i] = catalan[i][i - 1];
    }
}



int n;
int main() {
    init_catalan2();
    int c=0;
    while(1){
        c++;
        scanf("%d",&n);
        if(n==-1) break;
        else{
            printf("%d %d %lld\n",c,n,catalan[n][n]*2);
        }
    }
    return 0;
}