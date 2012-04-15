/*
	主要算法，先把V0点排除，然后对于每个连通块求mst，
	然后V0对于每个连通块都连接最优的那条边
	接着每次都寻找最大差价的那条边来进行优化
*/
#include<cstdio>
#include<cstring>
#include<string>
#include<algorithm>
#include<map>
#include<vector>
#define maxm 800
#define maxn 30
#define inf 1000000000
using namespace std;
struct edge{
	int v,d,next;
	bool intree; //是否在生成树中
};
vector<edge> e;
struct bedge{ //kruskal用到的边
	int x,y,d,id;
	bedge(int _x=0,int _y=0,int _d=0,int _id=0):x(_x),y(_y),d(_d),id(_id){}
	bool operator<(const bedge & that)const{
		return d<that.d;
	}
};
vector<bedge> be;
int n,m,park,mst,k;
int beg[maxn];
int fa[maxn];
map<string,int> hash;

int min_e[maxn],which_e[maxn],max_e[maxn];
void add(int u,int v,int d)
{
	int ne=e.size();
	e.push_back(edge());	
	e[ne].v=v;
	e[ne].d=d;
	e[ne].next=beg[u];
	e[ne].intree=false;
	beg[u]=ne;
}
void input()
{
	hash.clear();	
	memset(beg,255,sizeof(beg));
	e.resize(0); be.resize(0);
	n=0;
	
	char s1[20],s2[20];
	int dis,n1,n2;
	for(int i=0;i<m;i++)
	{
		scanf("%s%s%d",s1,s2,&dis);
		if(!hash.count(s1))  n1=hash[s1]=++n;
		else n1=hash[s1];
		if(!hash.count(s2))  n2=hash[s2]=++n;
		else n2=hash[s2];
		if(strcmp(s1,"Park")==0) park=n1;
		if(strcmp(s2,"Park")==0) park=n2;
		add(n1,n2,dis); add(n2,n1,dis);
		be.push_back(bedge(n1,n2,dis,e.size()-1));
	}
	scanf("%d",&k);
}
int find_fa(int x)
{
	if(fa[x]==x) return x; else return fa[x]=find_fa(fa[x]);
}
void kruskal()
{
	sort(be.begin(),be.end());
	for(int i=1;i<=n;i++) fa[i]=i;
	mst=0;
			
	for(int i=0;i<be.size();i++)
	if(be[i].x!=park && be[i].y!=park){
		int fx=find_fa(be[i].x);
		int fy=find_fa(be[i].y);
		if(fx!=fy)	{
			fa[fx]=fy;
			mst+=be[i].d;
			e[be[i].id].intree=e[be[i].id^1].intree=true;
		}
	}
}
void link_component()
{	
	//link all components
	for(int i=0;i<be.size();i++)
		if(be[i].x==park || be[i].y==park){
			int fx=find_fa(be[i].x);
			int fy=find_fa(be[i].y);
			if(fx!=fy)	{
				fa[fx]=fy;
				mst+=be[i].d;
				e[be[i].id].intree=e[be[i].id^1].intree=true;
			}
		}	
}
void update_maxe(int x,int fat)
{
	for(int i=beg[x];i!=-1;i=e[i].next)
	if(e[i].v!=fat && e[i].intree){
		if(max_e[x]>e[i].d)	
		max_e[e[i].v]=max_e[x],which_e[e[i].v]=which_e[x];
		else max_e[e[i].v]=e[i].d,which_e[e[i].v]=i;
		update_maxe(e[i].v,x);
	}
}
void extend_degree()
{
	int ncomp=0;
	for(int i=beg[park];i!=-1;i=e[i].next)
		if(e[i].intree) ncomp++;

	for(ncomp++;ncomp<=k;ncomp++)
	{
		//每次都更新每个点到该连通块代表点的最大边，通过dfs完成
		for(int i=1;i<=n;i++) max_e[i]=-inf;
		for(int i=beg[park];i!=-1;i=e[i].next)
			if(e[i].intree)	update_maxe(e[i].v,park); 
			
		//寻找最大差价，更新
		int Max_diff=-inf,add_e,del_e;
		for(int i=beg[park];i!=-1;i=e[i].next)
			if(!e[i].intree && e[which_e[e[i].v]].d-e[i].d>Max_diff)
			{
				Max_diff=e[which_e[e[i].v]].d-e[i].d;
				add_e=i;
				del_e=which_e[e[i].v];
			}
		if(Max_diff<=0) break;
		mst=mst-e[del_e].d+e[add_e].d;
		e[del_e].intree=e[del_e^1].intree=false;
		e[add_e].intree=e[add_e^1].intree=true;
	}
	printf("Total miles driven: %d\n",mst);	
}
int main()
{
	freopen("pku1639.in","r",stdin);
	while(scanf("%d",&m)!=EOF)
	{
		input();
		kruskal();//除了V0以外的各个连通块的生成树
		link_component();//把V0连接到各个连通块上
		extend_degree();//不断寻找最大差价来更新
	}
	return 0;
}
