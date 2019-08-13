//思维 构造
//期末考试共n道题总分为m 某道题分数可以为0或m 想要通过一道题目 需要时间为该题分数+1 小时
//小明不知道题目的分数分布，求小明想要能做出k道题至少需要的总复习时间
//可以换位思考现在有一个老师可以根据小明的复习策略卡小明，这样会排除所有运气因素：
//老师会怎么卡小明呢？其复习最少的n-k+1道题目的分数正好设置为他的复习时间 这样这n-k+1道题目他永远无法通过 剩下的k-1道就算通过也没有用 她永远无法打到k题
//也就是说，小明想要保证赢 只要让复习最少的n-k+1道的总和超过m 这样无论如何分数分布也不能卡掉小明
//因此答案就是 最少的n-k+1道复习m+1小时 剩余的k-1道题目复习时间要大于等于第n-k+1小就行，我们让第n-k+1最小，为m/(n-k+1)+1
//因此共： m+1+(m/(n-k+1)+1)*(k-1)
#include <iostream>
#include <cstdio>
#define ll long long
using namespace std;

int main(){
    int t;
	scanf("%d",&t);
	while(t--){
		ll n,m,k;
		scanf("%lld%lld%lld",&n,&m,&k);
		printf("%lld\n",m+1+(m/(n-k+1)+1)*(k-1));
	}
	return 0;
} 
