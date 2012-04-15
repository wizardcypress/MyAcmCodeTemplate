//BOI 2001 exc
#include<cstdio>
#include<cstring>
#include<vector>
#define MAXN 2*8010
#define INF 2000000000
using namespace std;
int n,m;
vector<int> a[MAXN],b[MAXN],c[MAXN];
int id[MAXN],fa[MAXN],low[MAXN],dfn[MAXN],stk[MAXN],num,top;
int list[MAXN],len,scc,w,g[MAXN];
int chose[MAXN],ans[MAXN];
int neg(int x)
{
  return x<=n?x+n:x-n;
}
void insert(int x,int y)
{
   a[x].push_back(y);  
}
void dfs(int x)//寻找scc
{
   low[x]=dfn[x]=++num;
   stk[++top]=x;
   for(int i=0;i<a[x].size();++i)
   {
	    if(!dfn[a[x][i]]) dfs(a[x][i]);
		if(low[a[x][i]]<low[x]) low[x]=low[a[x][i]];
   }
   if(low[x]<dfn[x]) return ;
   ++scc;
   do{
      fa[w=stk[top--]]=scc;
	  low[w]=INF;
   }while(w!=x);
}
void init()
{
	int x,y;
   scanf("%d%d",&m,&n);  
    for(int i=1;i<=m;++i)
	{
	   scanf("%d%d",&x,&y);
	   if(-x!=y) 
		{
       if(x<0) x=-x;
	     else x+=n;
	   if(y<0) y=-y;
	    else y+=n;
	  insert(neg(x),y);//-x==>y
	  insert(neg(y),x);//-y==>x
		}
	}
	num=top=scc=0;
	memset(dfn,0,sizeof(dfn));
	for(int i=1;i<=2*n;++i)	if(dfn[i]==0)
		  dfs(i);
}
bool check()//通过SCC缩点，重新构图
{
   memset(g,0,sizeof(g));	   
   for(int i=1;i<=n;++i)
	   if(fa[i]==fa[i+n]) return false;
      else {
          g[fa[i]]=fa[i+n]; //g 记录反点所在的scc编号
		 g[fa[i+n]]=fa[i];
	  }
    memset(id,0,sizeof(id));
    for(int i=1;i<=2*n;++i)
		for(int j=0;j<a[i].size();++j)
		  if(fa[i]!=fa[a[i][j]]){
			int v=a[i][j];
	      b[fa[i]].push_back(fa[a[i][j]]);
		  c[fa[a[i][j]]].push_back(fa[i]); //c为逆向边
		  id[fa[a[i][j]]]++;
	   }
   return true;
}
void tuopu()//拓扑排序
{
   len=0;
   for(int i=1;i<=scc;++i) 
	   if (id[i]==0) list[++len]=i;
   for(int i=1;i<=len;++i)
      for(int j=0;j<b[list[i]].size();++j)
	   {
	     if(--id[b[list[i]][j]]==0)
			 list[++len]=b[list[i]][j];
	   }
}
void work()
{
	memset(chose,0,sizeof(chose));
   for(int i=scc;i>=1;--i)
  //按照拓扑排序的相反方向来进行选择，或删除
   {
      if(chose[list[i]]==0)//可选的话就尽量选
	   {
           chose[list[i]]=1;
		   chose[g[list[i]]]=-1;//当前的选了，那么对应的那个就不能选		  
	   }else {
        for(int j=0;j<c[list[i]].size();++j)//加入当前的不能选，那么指向它的也就不能选，而且由于按照拓扑的顺序，只需要删除和它相隔一条边的就可以了。
		   chose[c[list[i]][j]]=-1;
	   }
   }
}
void print()
{
   len=0;
   for(int i=n+1;i<=2*n;++i)
	   if(chose[fa[i]]==1) ans[++len]=i-n;
   printf("%d\n",len);
   for(int i=1;i<len;++i) printf("%d ",ans[i]);
   printf("%d\n",ans[len]);
}
int main()
{
	freopen("exc.in","r",stdin);
	freopen("exc.out","w",stdout);
	  init();
	  if(!check()) printf("NO\n");
	  else {
	    tuopu();
		work();
		print();
	  }
	return 0;
}
