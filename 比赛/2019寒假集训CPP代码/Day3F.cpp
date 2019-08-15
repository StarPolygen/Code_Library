 #include<stdio.h>
 #include<string.h>
 #include<stack>
 using namespace std;
 const int mx=5e5+10;
 char str[mx];
 int num=0;
 int sum[mx];
  int sum2[mx];
 int n;
 int ans=0;
 stack<char>st;
 int main()
 {
     int t;
     scanf("%d",&t);
     for (int i=1;i<=t;++i)
     {
         scanf("%s",str);
         while (!st.empty()) st.pop();
         st.push(str[0]);
         for (int j=1;str[j]!='\0';++j)
         {
             if (!st.empty())
             {
                if (st.top()=='('&&str[j]==')')
                 {
                     st.pop();
                 }
                 else st.push(str[j]);
             }
             else st.push(str[j]);
         }
         int ls=0,rs=0;
         while (!st.empty())
         {
             char xx=st.top();
             st.pop();
             if (xx=='(') ls++;
            else rs++;
         }
         if (ls!=0&&rs!=0)
         {
             continue;
         }
         else if (ls==0&&rs==0)
         {
             num++;
         }
         else if (rs!=0)
         {
             sum2[rs]++;
         }
         else sum[ls]++;
     }
     for (int i=1;i<=mx-10;++i)
     {
         if (sum[i]>sum2[i])
         {
             ans+=sum2[i];
         }
         else ans+=sum[i];
     }
     ans+=num/2;
     printf("%d\n",ans);
}
