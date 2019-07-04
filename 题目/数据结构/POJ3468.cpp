
//kuangbin专题七 线段树 
//区间修改 区间查询 区间和
//树状数组以add方法装填
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <queue>
#include <map>
#include <vector>
#include <set>
#include <string>
#include <math.h>
#define LL long long
const int maxn=100010;
using namespace std;

//树状数组
LL lowbit(LL x){return x&(-x);}
void add(LL* arr,int x,LL k,int n){
	while(x<=n){
		arr[x]+=k;
		x+=lowbit(x); 
	}
}
LL query(LL* arr,int x){
	LL sum=0;
	while(x>0){
		sum+=arr[x];
		x-=lowbit(x);
	}
	return sum;
}
LL C[maxn],jmC[maxn];
void addRange(int L,int R,LL k,int n){
	add(C,L,k,n);
	add(C,R+1,-k,n);
	add(jmC,L,1LL*k*L,n);
	add(jmC,R+1,1LL*(-k)*(R+1),n);
}
LL queryRange(int L,int R){
	L--;
	LL sumL=(L+1)*query(C,L)-query(jmC,L);
	LL sumR=(R+1)*query(C,R)-query(jmC,R);
	return sumR-sumL;
}


int n,q;
LL st[maxn];
int main() {
    memset(st,0,sizeof(st));
    memset(C,0,sizeof(C));
    memset(jmC,0,sizeof(jmC));
    scanf("%d %d",&n,&q);
    getchar();
    for(int i=1;i<=n;i++){
        scanf("%lld",&st[i]);
    }
    for(int i=1;i<=n;i++){
        //由于树状数组结构,此处不能直接赋值,必须以add方法装填
        add(C,i,st[i]-st[i-1],n);
        add(jmC,i,1ll*i*(st[i]-st[i-1]),n);
        // printf("%lld %lld\n",C[i],jmC[i]);
    }
    getchar();
    char c;
    int l,r;LL k;
    for(int i=1;i<=q;i++){
        scanf("%c ",&c);
        if(c=='C'){
            scanf("%d %d %lld",&l,&r,&k);
            getchar();
            addRange(l,r,k,n);
        }
        else if(c=='Q'){
            scanf("%d %d",&l,&r);
            getchar();
            printf("%lld\n",queryRange(l,r));
        }
    }
    
    return 0;
}
