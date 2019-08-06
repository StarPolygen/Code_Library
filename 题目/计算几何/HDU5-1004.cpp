#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define N 200010


ll gcd(ll a,ll b){ return (b ? gcd(b, a % b) : a); }
struct LINE
{
    ll a, b;
    ll s, m;
    LINE() {}
    LINE(ll a, ll b) : a(a), b(b)
    {
        s = -b;
        m = a;
        ll d = gcd(abs(s), abs(m));
        s /= d;
        m /= d;
        if (m < 0)
        {
            m *= -1;
            s *= -1;
        }
    }
    bool operator <(const LINE &b) const
    {
        return s * b.m < b.s * m;
    }
    bool operator == (const LINE & b) const {
        return s * b.m == b.s * m;
    }
};

LINE line[N];
ll A[N],B[N];
ll tran[N];
ll ans1[N],ans2[N];
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        ll n, c;
        memset(line,0,sizeof(line));
        memset(ans1,0,sizeof(ans1));
        memset(ans2,0,sizeof(ans2));
        memset(tran,0,sizeof(tran));
        memset(A,0,sizeof(A));
        memset(B,0,sizeof(B));
        scanf("%lld %lld", &n, &c);
        for (int i = 1; i <= n; i++)
        {
            ll ai, bi;
            scanf("%lld%lld", &ai, &bi);
            line[i] = LINE(ai, bi);
        }sort(line+1,line+1+n);

        // debug2
        // for(int i=1;i<=n;i++){
        //     printf(" %lldx + %lld \n",line[i].a,line[i].b);
        // }


        ll A0=0, B0=0;
        for(int i=1;i<=n;i++){
            A0+=-line[i].a;
            B0+=-line[i].b;
        }A[0]=A0; B[0]=B0;
        
        ll ans = 0; int tot = 1;
        ll trans = 0;
        for(int i=1;i<=n;i++){
            if(i!=1 && !(line[i]==line[i-1]) ){ //若当前的更换下表不同，之间的Ax+b生效
                A[tot]=A0;
                B[tot]=B0;
                tran[tot++] = trans;
                // printf("%lldx + %lld = %lld   trans: %.2f %d\n ",A0,B0,c,tran[tot-1],tot);
            }
            A0 += 2*line[i].a;
            B0 += 2*line[i].b;
            trans = i;
        }
        A[tot] = A0; B[tot]=B0; tran[tot++]=trans; //特殊处理最后一个

        // debug1
        // for(int i=0;i<tot;i++){
        //    printf("%lldx + %lld = %lld   trans: %d %d\n",A[i],B[i],c,tran[i],i);
        // }
        
        for(int i=0;i<tot;i++){
            ll ta = A[i];
            ll tb = B[i];
            ll z = c - tb;
            ll m = ta;
            if (z==0 && m==0){ans = -1; break;}
            if(z == 0) {
                if(( i==0 || z*line[tran[i]].m >= line[tran[i]].s * m ) && ( i==tot-1 || z*line[tran[i+1]].m <= line[tran[i+1]].s *m)){
                if(ans==0 || (z!=ans1[ans-1] || m!=ans2[ans-1])){
                ans1[ans]=0; ans2[ans++]=1;
                }}
                continue;
            }
            if(m == 0) {continue;}
            ll d = gcd(abs(z), abs(m));
            z /= d;  m /= d;
            if(m < 0) {
                z *= -1;
                m *= -1;
            } 
            //debug3
            // printf("%lld %lld %.2f %lld\n",z,m,tmp,ans);
            if(( i==0 || z*line[tran[i]].m >= line[tran[i]].s * m ) && ( i==tot-1 || z*line[tran[i+1]].m <= line[tran[i+1]].s *m)){
                if(ans==0 || (z!=ans1[ans-1] || m!=ans2[ans-1])){
                    ans1[ans]=z;
                    ans2[ans++]=m;
                    // printf("%lld %lld %lld %lld %lld\n",ta,tb,c-tb,d,z,m);
                }
                
            }
        }


        //输出 
        printf("%lld",ans);
        for(int i=0;i<ans;i++){
            printf(" %lld/%lld",ans1[i],ans2[i]);
        }printf("\n");
    }
    return 0;
}

