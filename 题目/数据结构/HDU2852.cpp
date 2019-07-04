//pb_ds 红黑树
//另外存在解法：树状数组 + 二分
//             权值线段树
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/hash_policy.hpp>
#include <ext/pb_ds/priority_queue.hpp>
#pragma GCC optimize(1) 
#define ll long long
using namespace std;
using namespace __gnu_pbds;
const int inf=0x3f3f3f3f;


typedef pair<int,int> pii;
typedef tree<pii,null_type,less<pii>,rb_tree_tag,tree_order_statistics_node_update> rbtree;
rbtree q;
int n; 
int main() {
    while(~scanf("%d",&n)){
        q.clear();
        int tot=0;
        for(int i=1;i<=n;i++){
            int op,e,k; scanf("%d",&op);
            if(op == 0){
                scanf("%d",&e);
                q.insert(make_pair(e,tot++));
            }
            else if(op == 1){
                scanf("%d",&e);
                auto it=q.lower_bound(make_pair(e,0));
                if((*it).first!=e) printf("No Elment!\n");
                else{
                    q.erase(it);
                }
            }
            else{
                //求kth（find_by_order）返回的是迭代器，求rank(order_of_key)返回的是rank，两者都是从0开始计算的
                // for (auto x:q) cout<<x<<' ';cout<<endl; 
                scanf("%d%d",&e,&k);
                int cur=q.order_of_key(make_pair(e+1,0));
                int len=q.order_of_key(make_pair(inf,0));
                // printf("%d %d\n",len,cur);
                auto it=q.find_by_order(cur+k-1);
                if((cur+k-1)>=len||cur==len) printf("Not Find!\n");
                else printf("%d\n",(*it).first);
            }

        }
    }
    return 0;
}