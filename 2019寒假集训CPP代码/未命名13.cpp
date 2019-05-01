#include <iostream>
#include<stdio.h>
#include<map>
using namespace std;

int main(){    
	int t;
	scanf("%d",&t);
	while(t--)    {  
	    int n;     
		scanf("%d",&n);
		int ans=0;
		if(n==1) ans=-1;
		else if(n==7) ans=3;
		else{
			int mo=n%11;
			int to=n/11;
			if(mo<=5&&mo!=0)  ans=to*2+1;
			else if(mo==0){
				ans=to*2;
			}
			else ans=to*2+2;
			
		}
		
		printf("%d\n",ans);    
	}    
	return 0;
}

