#include<iostream>
#include<cstdio>
#include<cstring>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
#define min(u,d) (u)<(d)?(u):(d)
using namespace std;

const long maxn=5100;
const long maxm=100010;
const long inf=1000000000;

long head[maxn],next[maxm],node[maxm],tt;
long c[maxm],cost[maxm]; //残留网，边费用
long dist[maxn]; //距离标号 
long pre_d[maxn],pre_e[maxn]; //记录增广路上每点的前驱、到达它的边
long que[maxm];
bool vis[maxn];
long n,m,st,ed;
long maxflow,mincost;

void add(long x, long y, long ff, long cc)
{
    node[++tt]=y, next[tt]=head[x], head[x]=tt;
    c[tt]=ff, cost[tt]=cc;
}
void init()
{

}
bool cal_dist()
//spfa求出最短增广路
{
	memset(vis,0,sizeof(vis));
	fo(i,st,ed) dist[i]=inf;  dist[st]=0;
	que[0]=st; vis[st]=1;
	for (long x=que[0],s=0,t=1; s!=t; vis[x]=0, ++s, x=que[s])
		for (long dd, i=head[x]; i>-1; i=next[i])
			if (c[i] && dist[node[i]]>(dd=dist[x]+cost[i])) {
			   pre_d[node[i]]=x, pre_e[node[i]]=i, dist[node[i]]=dd;
			   if (!vis[node[i]]) {
				   vis[node[i]]=1;
				   que[t++]=node[i];
			   }
	        } 
	return dist[ed]!=inf;
}
long aug()
//沿最短路增广
{
    long x, aug_flow=inf;

    for (x=ed; x!=st; x=pre_d[x])
        aug_flow=min(aug_flow,c[pre_e[x]]);

	mincost+=aug_flow*dist[ed];

    for (x=ed; x!=st; x=pre_d[x])
        c[pre_e[x]]-=aug_flow, c[pre_e[x]^1]+=aug_flow;

	return aug_flow;
}
void solve()
{
	maxflow=0; mincost=0;
	while (cal_dist()) 
		maxflow+=aug();

}
int main()
{
    init();
    solve();
    return 0;
}
