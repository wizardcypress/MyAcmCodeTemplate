//distance
//中大资料集数据\五\第5章 2004年中山大学集训队内部个人选拔赛\5.9 距离 distance
#include<stdio.h>
#include<mem.h>
#include<vector>
#define MAXN 100010
#define MAXM 200010
using namespace std;
int n,m;
int fa[MAXN];
vector<pair<int,int> > que[MAXN];
vector<pair<int,int> > dis[MAXN];
int d[MAXN];
int ans[MAXM];
bool mark[MAXN];
int ancestor;
void find_dist(int x,int father)
{
    for (int i=0;i<dis[x].size();++i)
      if (dis[x][i].first!=father)
      {
         d[dis[x][i].first]=d[x]+dis[x][i].second;
         find_dist(dis[x][i].first,x);         
	  }
}
int find(int x)
{
    int xx,fx=x;
    while (fa[fx]!=fx)   fx=fa[fx];
     while (x!=fx)
     {
	    xx=fa[x];
	    fa[x]=fx;
	    x=xx;
	 }
   return fx;
}
void dfs(int x,int father)
{
    fa[x]=x;
    mark[x]=true;
    for (int i=0;i<dis[x].size();++i)
       if (dis[x][i].first!=father)
       {
	       dfs(dis[x][i].first,x);	       
	   }
     for (int j=0;j<que[x].size();++j)
       if (mark[que[x][j].first])
       {
	      ancestor=find(que[x][j].first);
	      ans[que[x][j].second]=d[que[x][j].first]+d[x]-2*d[ancestor];
	   }
     fa[x]=father;
}
void tarjan()
{
   memset(d,0,sizeof(d));
   memset(mark,0,sizeof(mark));
   find_dist(1,-1);
   dfs(1,-1);  
   for (int i=1;i<=m;++i)
     printf("%d\n",ans[i]);
     printf("\n");
}
int main()
{
	 freopen("distance.in","r",stdin);
	 freopen("distance.out","w",stdout);
	 int t;
	 int x,y,z;
	   scanf("%d",&t);
	   while (t--)
	   {
	       for (int i=0;i<=MAXN;++i) dis[i].clear(),que[i].clear();
           scanf("%d%d",&n,&m);
           for (int i=1;i<n;++i)
           {
            scanf("%d%d%d",&x,&y,&z);
            dis[x].push_back(make_pair(y,z));
            dis[y].push_back(make_pair(x,z));
           }
           for(int i=1;i<=m;++i)
            {
			   scanf("%d%d",&x,&y);			   
			   que[x].push_back(make_pair(y,i));
			   que[y].push_back(make_pair(x,i));
			}
          tarjan();		   
	   }	   
   return 0;
}
