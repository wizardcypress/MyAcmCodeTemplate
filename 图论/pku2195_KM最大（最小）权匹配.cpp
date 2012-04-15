//KM算法
#include<cstdio>
#include<cstring>
#include<algorithm>
#define INF 1000000000
using namespace std;
bool x[110],y[110];
int link[110],lx[110],ly[110];
int w[110][110];
struct point
{
   int x,y;
}man[110],house[110];
int n,m,lm,lh,ans;
char ch;
void build()
{
	memset(w,0,sizeof(w));
   for(int i=1;i<=lm;++i)
	   for(int j=1;j<=lh;++j)
	   //最大还是最小权匹配主要在这里区分，
   //如果是最大权，那么就是正的，否则就是负权。
	      w[i][j]=-(abs(man[i].x-house[j].x)+abs(man[i].y-house[j].y));
}
bool dfs(int src)
{
   x[src]=true;
   for(int j=1;j<=lh;++j)
   {
	    if(!y[j]&&lx[src]+ly[j]==w[src][j])
	   {
            y[j]=true;
		    if(link[j]==0||dfs(link[j]))
		   {
			   link[j]=src;
			   return true;
			}
		}
   }
   return false;
}
void KM()
{
   fill(lx,lx+lm+1,-INF);
   memset(ly,0,sizeof(ly));   
   memset(link,0,sizeof(link));
   for(int i=1;i<=lm;++i)
	   for(int j=1;j<=lh;++j)
	      lx[i]=max(lx[i],w[i][j]);
    for(int i=1;i<=lm;++i)
	   while(1)
	  {
		memset(x,0,sizeof(x));
		memset(y,0,sizeof(y));
		if(dfs(i)) break;
		int d=INF;
		for(int j=1;j<=lm;++j)
			if(x[j])
			for(int k=1;k<=lh;++k)
			  if(!y[k])
			       d=min(d,lx[j]+ly[k]-w[j][k]);
	     for(int j=1;j<=lh;++j)
		  {
               if(x[j]) lx[j]-=d;
			   if(y[j]) ly[j]+=d;
		  }
	  }
	ans=0;
	for(int i=1;i<=lh;++i) if(link[i]>0)
		ans+=w[link[i]][i];
	printf("%d\n",-ans);
}
int main()
{
	freopen("test.in","r",stdin);
	 scanf("%d%d\n",&n,&m);
	 while(n+m!=0)
	{
		 lm=lh=0;
       for(int i=1;i<=n;++i)
		{
		   for(int j=1;j<=m;++j)
		   {
		       ch=getchar();
			   if(ch=='m')  man[++lm]=(point){i,j};
			   else if(ch=='H') house[++lh]=(point){i,j};
		   }
		   getchar();
		}
		build();
		KM();
	   scanf("%d%d\n",&n,&m);
	}
	return 0;
}
