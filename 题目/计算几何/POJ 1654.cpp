//POJ 1654
//求多边形面积 

/*对叉积性质 :有向面积  的简单应用 
面积可能为负 因此取个fabs再输出
输出要判定是否为小数
*/
#include<stdio.h>
#include<math.h>
#include<algorithm>
#include<iostream>
#define ll long long
const double eps=1e-8;
using namespace std;
const int maxn=1000010;
double ans=0;

struct point{
	ll x,y;
} ;

char op[maxn];

point la;
point getnow(char a){
	point now;
	if(a=='1') now.x=la.x-1,now.y=la.y-1;
	if(a=='2') now.x=la.x,now.y=la.y-1;
	if(a=='3') now.x=la.x+1,now.y=la.y-1;
	if(a=='6') now.x=la.x+1,now.y=la.y;
	if(a=='9') now.x=la.x+1,now.y=la.y+1;
	if(a=='8') now.x=la.x,now.y=la.y+1;
	if(a=='7') now.x=la.x-1,now.y=la.y+1;
	if(a=='4') now.x=la.x-1,now.y=la.y;
	return now;
}

ll cross(point p1,point p2){
	return p1.x*p2.y-p2.x*p1.y;
}

void Area(point a,point b){
	ans+=cross(a,b)/2.0;
	return;
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		for(int i=0;i<maxn;i++) op[i]=0;
		ans=0;
		la.x=la.y=0;
		scanf("%s",op+1);
		int i=1;
		while(op[i]!='5'){
			point now;
			now=getnow(op[i]);
			Area(la,now);
			la=now;
			i++;
		}
		if((fabs(ans)-(ll)(fabs(ans)))>0.2)
		printf("%.1lf\n",fabs(ans));
		else  printf("%.0lf\n",fabs(ans));
	}
	return 0;
	
}
