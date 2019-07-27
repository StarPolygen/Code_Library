//Autor by zxy
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 1e5 + 5;
int a[N],b[N], pos[N], po[N];
stack<pair<int, int> > st;
int n;
int main(){
    while (~scanf("%d",&n)){
        while (!st.empty())
            st.pop();
        for (int i = 1; i <= n;i++)
        {
            scanf("%d", &a[i]);
        }
        for (int i = n; i > 0;i--)
        {
            while (!st.empty() && st.top().first>a[i]){
                int se = st.top().second;
                pos[se] = i;
                st.pop();
            }
            st.push(make_pair(a[i], i));
        }
        while (!st.empty()){
            int se = st.top().second;
            st.pop();
            pos[se] = 0;
        }
        for (int i = 1; i <= n;i++)
        {
            scanf("%d", &b[i]);
        }
        for (int i = n; i > 0;i--)
        {
            while (!st.empty() && st.top().first>b[i]){
                int se = st.top().second;
                po[se] = i;
                st.pop();
            }
            st.push(make_pair(b[i], i));
        }
        while (!st.empty()){
            int se = st.top().second;
            po[se] = 0;
            st.pop();
        }
        int ans = n;
        for (int i = 1; i <= n;i++)
        {
            if (po[i]!=pos[i]){
                ans = i - 1;
                break;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}