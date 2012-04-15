/*
	1.先求原图的最小生成树T，并记录树边和最小值small1
	2.然后求dis[i][j],表示在T中x到y的唯一路径上的最大边
	3.枚举所有非树边(u,v),设其值为w,那么small2=min{small1-dis[u][v]+w},最后看small1和
	small2是否一样就可以了。
*/
#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
#define maxn 110
#define maxm 10000
using namespace std;
struct edge{
	int u,v,w,next,inv;
	bool inTree;
};
vector<edge> e;
int id[maxm];
int beg[maxn];
int fa[maxn];
int dis[maxn][maxn];
int n,m;
int small1,small2;
int nE;
void add(int x,int y ,int z,int invFlag)
{
	e.push_back(edge());
	int last=e.size()-1;
	e[last].u=x;
	e[last].v=y;
	e[last].next=beg[x];
	e[last].w=z;
	e[last].inTree=false;
	beg[x]=last;
	
	if(!invFlag) e[last].inv=last+1;
	else e[last].inv=last-1;
}
bool cmp(int x,int y)
{
	return e[x].w<e[y].w;
}
void input()
{
	int x,y,z;
	e.resize(1);
	memset(beg,0,sizeof(beg));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%d",&x,&y,&z);
		add(x,y,z,0);
		add(y,x,z,1);
	}
	//label
	nE=e.size()-1;
	for(int i=1;i<=nE;++i)	id[i]=i;	
	sort(id+1,id+nE+1,cmp);
}
int find(int x)
{
	int fx,tm;
	fx=x;
	while(fa[fx]!=fx) fx=fa[fx];
	while(fa[x]!=fx)
	{
		tm=fa[x];
		fa[x]=fx;
		x=tm;
	}
	return fx;
}
void kruskal()
{
	small1=0;
	for(int i=1;i<=n;++i)	fa[i]=i;
	for(int i=1;i<=nE;++i)
	{
		int x=e[id[i]].u;
		int y=e[id[i]].v;
		x=find(x);
		y=find(y);
		if(x!=y) {
			e[id[i]].inTree=true;
			e[e[id[i]].inv].inTree=true;
			small1+=e[id[i]].w;
			fa[x]=y;
		}
	}
}
void dfs(int x,int father,int now,int best[])
{
	best[x]=now;
	for(int i=beg[x];i;i=e[i].next)
		if(e[i].inTree && e[i].v!=father)
		{
			if(e[i].w>now) dfs(e[i].v,x,e[i].w,best);
			else dfs(e[i].v,x,now,best);
		}
}
void find_dis()
{
	memset(dis,0,sizeof(dis));
	for(int i=1;i<=n;++i)	
		dfs(i,0,0,dis[i]);	
}
void cal_second()
{
	small2=2000000000;
	for(int i=1;i<=nE;++i)
		if(!e[i].inTree){
			int sub=dis[e[i].u][e[i].v];
			if(small1-sub+e[i].w<small2)
				small2=small1-sub+e[i].w;
		}	
}
void output()
{
	if(small1==small2) printf("Not Unique!\n");
	else printf("%d\n",small1);
}
int main()
{
	freopen("pku1679.in","r",stdin);
	int cs;
	scanf("%d",&cs);
	while(cs--)
	{
		input();
		kruskal();
		find_dis();
		cal_second();
		output();
	}
	return 0;
}
