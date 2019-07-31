//傻逼题
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e6 + 5;
const int MOD = 1e6 + 3;
ll A[N];
int main(){
    A[1] = 1;
    for (int i = 2; i <= MOD;i++)
    {
        A[i] = A[i - 1] * i % MOD;
    }
    int n;
    while (cin>>n){
        cout << (n >= MOD ? 0 : A[n]) << endl;
    }
    return 0;
}