#include<cstdio>
#include<cstring>
using namespace std;
bool f[100000];
int cash,n;
int num[11];
int w[11];
int main()
{
	freopen("test.in","r",stdin);
	   while (scanf("%d",&cash)!=EOF)
	{
	    scanf("%d",&n);	   
		for(int i=1;i<=n;++i)
			scanf("%d%d",&num[i],&w[i]);
		memset(f,0,sizeof(f));
		f[0]=1;
		for(int i=1;i<=n;++i)
     	{
			int k=1;
		while(k<=num[i])
		{
     	 for(int j=cash;j>=k*w[i];--j) 
               f[j]|=f[j-k*w[i]];
		 num[i]-=k;
		   k<<=1;
		}
		  k=num[i];
          for(int j=cash;j>=k*w[i];--j) 
               f[j]|=f[j-k*w[i]];
		}
		for(int i=cash;i>=0;--i)
			if(f[i])
		{
		  printf("%d\n",i);
		  break;
		}
	}
	return 0;
}

