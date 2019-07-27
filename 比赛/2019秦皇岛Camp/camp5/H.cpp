//题意题 模拟
//题意题。题意有些难懂，但看完就能秒。做完A题就来看它了，第二个AC的题目，模拟即可。
#include<bits/stdc++.h>
using namespace std;
const double pi=acos(-1);



int main(){
    double R,r,H,F,S;
    while(~scanf("%lf%lf%lf%lf%lf",&R,&r,&H,&F,&S)) {
        double h=H/F;
        double ans=0;
        int maxx=100000;
        for(int i=F;i>=1;i--){
            double tmpr=1.0*(R-r)/F*(i-1)+r;  //当前层的半径
            int ll=3,rr=maxx,mid,num;
            double s;
            while(ll<=rr) { //二分
                mid=(ll+rr)>>1;
                double tmp=2.0*tmpr*tan(pi/(double)mid)*h;
                if(tmp-S>1e-8)
                {
                    s=tmp;
                    num=mid;
                    ll=mid+1;
                }
                else  rr=mid-1;

            }
            ans+=num*s;
            maxx=num;
        }
        printf("%.3lf\n",ans);
    }
    return 0;

}
