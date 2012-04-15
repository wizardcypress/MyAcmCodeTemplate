//用Tarjan的SCC算法
#include<cstdio>
#include<cstring>
using namespace std;
int n,m;
struct node
{
	int u,v,next;
}e[50010];
int num,x,y;
int low[10010],dfn[10010],len,beg[10010],stk[10010];
int od[10010],top,id[10010],scc,w;
void insert(int u,int v)
{
    e[++num]=(node){u,v,beg[u]};
	beg[u]=num;               
}
void dfs(int x)
{
   low[x]=dfn[x]=++len; 
   stk[++top]=x;
   for(int q=beg[x];q;q=e[q].next)
   {
	   int v=e[q].v;
	   if(dfn[v]==0) dfs(v);
	   if(low[v]<low[x]) low[x]=low[v];//取子孙中能连接到的最先访问的点
   }  
   if(low[x]<dfn[x]) return ; 
   //若子孙能连接到祖先，那么不能从当前的点把强连通分支分出去
   ++scc;//否则就可以以当前的点为界线，把它下面的没有连接到比它更早的
   //点和它本身都加入到新的分支中，并标号
    do{ 
		id[w=stk[top--]]=scc;
		low[w]=inf;//这里要注意的是，在有向图中是存在横边的，所以
		//就需要把加入SCC的点的low都赋为oo，解决了横向边的问题。
	}while(w!=x);
}
void find_block()
{
	memset(dfn,0,sizeof(dfn));
	memset(low,0,sizeof(low));
	top=0;
	scc=0;
    for(int i=1;i<=n;++i)		
		if(dfn[i]==0)  dfs(i);	 
}
void judge()
{
	memset(od,0xff,sizeof(od));
     for(int i=1;i<=num;++i)
		 if(id[e[i].u]!=id[e[i].v])
	 {
		 if (od[id[e[i].u]]==-1) od[id[e[i].u]]=1;
		 else od[id[e[i].u]]++;
	 }
	 int ans=0;
    for(int i=1;i<=scc;++i)
		if(od[i]==-1)
	{
		if(ans!=0) 
		{
			printf("0\n");
			return ;
		}
		for(int j=1;j<=n;++j)
			if(id[j]==i) ++ans;		
	}
	if(ans==0) ans=n;
	printf("%d\n",ans);	
}
int main()
{
	freopen("test.in","r",stdin);
	   while(scanf("%d%d",&n,&m)!=EOF)
	{
		   num=0;
		   memset(beg,0,sizeof(beg));
	      for(int i=1;i<=m;++i)
		  {
		      scanf("%d%d",&x,&y);              
			  insert(x,y);
		  }
		  find_block();
		  judge();
	   }
	return 0;
}
