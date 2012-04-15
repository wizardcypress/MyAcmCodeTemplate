#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#define maxn 5010
#define inf 2000000000
using namespace std;

struct edge{
	int v,c,w,next;
};
vector<edge> e;
int beg[maxn];
//
int n,m,st,ed,k,n2,minCost,maxFlow;
int matrix[60][60];
//spfa
int pre_d[maxn],pre_e[maxn];
int dis[maxn];
bool inq[maxn];
//
void add(int x,int y,int c,int w)
{
	int nE=e.size();
	e.push_back(edge());
	e[nE].v=y;
	e[nE].c=c;
	e[nE].w=w;
	e[nE].next=beg[x];
	beg[x]=nE;
}
void add_edge(int x,int y,int c,int w)
{
	add(x,y,c,w);
	add(y,x,0,-w);
}
int lb(int x,int y)
{
	return (x-1)*n+y;
}
void input()
{
	memset(beg,255,sizeof(beg));
	e.resize(0);
	n2=n*n;
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)		
		{
			scanf("%d",&matrix[i][j]);
			add_edge(lb(i,j),lb(i,j)+n2,1,-matrix[i][j]);
			add_edge(lb(i,j),lb(i,j)+n2,inf,0);
		}
	st=2*n2+1; ed=2*n2+2;
	
	add_edge(st,1,k,0);
	add_edge(lb(n,n)+n2,ed,k,0);
	
	for(int i=1;i<=n;++i)
		for(int j=1;j<=n;++j)
		{
			if(j<n) add_edge(lb(i,j)+n2,lb(i,j+1),inf,0);
			if(i<n) add_edge(lb(i,j)+n2,lb(i+1,j),inf,0);
		}
	n=2*n2+2;
}
bool spfa()
{
	queue<int> que;
	memset(pre_d,0,sizeof(pre_d));
	memset(pre_e,0,sizeof(pre_e));
	memset(inq,0,sizeof(inq));
	
	for(int i=1;i<=n;++i) dis[i]=inf;
	inq[st]=true;  dis[st]=0;
	que.push(st);
	while(!que.empty())
	{
		int x=que.front();
		que.pop();
		for(int i=beg[x];i!=-1;i=e[i].next)
		if(e[i].c){
			int v=e[i].v;
			if(dis[x]+e[i].w<dis[v]){
				dis[v]=dis[x]+e[i].w;
				pre_d[v]=x;	 pre_e[v]=i;
				if(!inq[v])  que.push(v),inq[v]=true;
			}
		}
		inq[x]=false;
	}
	return dis[ed]!=inf;
}
int aug()
{
	int ext=inf;
	for(int x=ed;x!=st;x=pre_d[x])
		if(e[pre_e[x]].c<ext) ext=e[pre_e[x]].c;
	minCost+=ext*dis[ed];
	
	for(int x=ed;x!=st;x=pre_d[x])
		e[pre_e[x]].c-=ext,e[pre_e[x]^1].c+=ext;
	return ext;
}
void maxFlow_minCost()
{
	minCost=maxFlow=0;
	while(spfa()) maxFlow+=aug();
	printf("%d\n",-minCost);
}
int main()
{
	freopen("pku3422.in","r",stdin);
	while(scanf("%d%d",&n,&k)!=EOF)
	{
		input();
		maxFlow_minCost();
	}
	return 0;
}
