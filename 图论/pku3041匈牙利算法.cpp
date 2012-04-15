#include <stdio.h>
#include<string.h>
using namespace std;
bool g[510][510];
int mark[510];
int p[510];
int n,k,turn;
int ans;
bool dfs(int src)
{
   for(int i=1;i<=n;++i)
    if (g[src][i]&&mark[i]!=turn)
	{
	   mark[i]=turn;   	  
	   if (p[i]==-1||dfs(p[i]))
	   {
		   p[i]=src;
		   return true;
	   }
   }
   return false;
}
int main()
{
	freopen("test.in","r",stdin);
	int x,y;
	while (scanf("%d%d",&n,&k)!=EOF)	  
	{
		memset(g,0,sizeof(g));
		memset(p,0xff,sizeof(p));
	    for(int i=1;i<=k;++i)      
		{
			scanf("%d%d",&x,&y);
			g[x][y]=1;
		}
		turn=0;
		 ans=0;
		for(int i=1;i<=n;++i)
	    {  
			++turn;		
			if(dfs(i)) ++ans;
		}
	  printf("%d\n",ans);
	}
	return 0;
}
