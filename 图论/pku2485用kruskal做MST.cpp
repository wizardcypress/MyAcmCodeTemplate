#include <stdio.h>
#include<string.h>
#include<algorithm>
#define MAX 1000000000
using namespace std;
struct edge
{
   int u,v,w;
};
edge e[250010];
int fa[510];
int m,n;
bool cmp(const edge &p1,const edge &p2)
{
    return p1.w<p2.w;
}
int find(int x)
{
  int fx,xx;
  fx=x;
  while(fa[fx]!=fx) fx=fa[fx];
  while (x!=fx)
  {
      xx=fa[x];
	  fa[x]=fx;
	  x=xx;
  }
  return fx;
}
void kru()
{
	int x,y;
	int ans=-1;
    for(int i=1;i<=n;++i)
		fa[i]=i;
	sort(e+1,e+m+1,cmp);
	for(int i=1;i<=m;++i)
	{
	    x=find(e[i].u);
		y=find(e[i].v);
		if (x!=y)
		{
		   if (e[i].w>ans) ans=e[i].w;
		   fa[x]=y;
		}
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("test.in","r",stdin);
	int cs,tm;
	scanf("%d",&cs);
	while(cs--)
	{
	    scanf("%d",&n);
		m=0;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=n;++j)
		{ 
			   scanf("%d",&tm);
			   e[++m].u=i;e[m].v=j;e[m].w=tm;
			   e[++m].u=j;e[m].v=i;e[m].w=tm;
		}
		kru();	   
	}
	return 0;
}
