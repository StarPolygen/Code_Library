#include<bits/stdc++.h>
using namespace std;

int main(){
    int T;
    scanf("%d",&T);
    for (int i = 1; i <= T; i++) {
        double h, r, x, y, z, vx, vy, vz;
        scanf("%lf%lf", &r, &h);
        scanf("%lf%lf%lf", &x, &y, &z);
        scanf("%lf%lf%lf", &vx, &vy, &vz);
        z -= h;
        //一元二次方程
        double K = r/h;
        double A = vx*vx+vy*vy-K*K*vz*vz;
        double B = 2*(vx*x+vy*y-K*K*vz*z);
        double C = x*x+y*y-K*K*z*z;
        double ans = (-B - sqrt(B*B-4*A*C)) / 2 / A;
        printf("Case %d: %.10lf\n", i, ans);
    }
}

