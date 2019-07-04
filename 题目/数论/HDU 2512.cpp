//贝尔数
//HDU 2512
//集合划分 ——贝尔数
#include<bits/stdc++.h>
#define ll long long
#define MAXN 2010
#define MOD 1000
#define TYPE long long
using namespace std;


//贝尔数 
TYPE bell[MAXN];
TYPE temp[MAXN];
void init_bell()
{
    bell[0] = bell[1] = temp[0] = 1;
    for (ll i = 2; i < MAXN; i++)
    {
        temp[i - 1] = bell[i - 1];
        for (ll j = i - 2; j >= 0; j--)
        {
#ifdef MOD
            temp[j] = (temp[j] + temp[j + 1]) % MOD;
#else
            temp[j] = temp[j] + temp[j + 1];
#endif
        }
        bell[i] = temp[0];
    }
}

int main() {
    init_bell();
    int n,x;
    scanf("%d",&n);
    while(n--){
        scanf("%d",&x);
        printf("%lld\n",bell[x]);
    }

    return 0;
}