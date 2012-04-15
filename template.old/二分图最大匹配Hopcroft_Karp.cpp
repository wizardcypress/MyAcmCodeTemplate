/*Hopcroft-Karp算法*/
#include<iostream>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=10000;
const long maxm=1000000;

long head[maxn],next[maxm],node[maxm],tt;
long vis[maxn],w[maxn],n,m;


void init()
{

}
long bfs()//求极大最短路径增广路集
{
	long pd=0,q[maxn],st=1,ed=1;
	memset(hx,0,sizeof(hx));
	memset(hy,0,sizeof(hy));
	fo(i,1,n) 
		if (!wx[i]) q[ed++]=i;

	for (; st<ed; ++st) 
		for (long i=head[q[st]]; i; i=next[i]) 
		   if (!hy[node[i]]) {
		      hy[node[i]]=hx[q[st]]+1;
		      if (!wy[node[i]]) pd=1;
		      else hx[wy[node[i]]]=hy[node[i]]+1, q[ed++]=wy[node[i]];
	       }
	return pd;
}
long dfs(long x)//沿最短路增广
{
	for (long i=head[x]; i; i=next[i])
		if (hy[node[i]]==hx[x]+1) {
		   hy[node[i]]=0;
		   if (!wy[node[i]] || dfs(wy[node[i]])) {
		        wx[x]=node[i];
				wy[node[i]]=x;
				return 1;
	       }
	   }
	return 0;
}
void solve()
{
	memset(wx,0,sizeof(wx));
	memset(wy,0,sizeof(wy));
	long tot=0;
	while (bfs()) {
		fo(i,1,n)
			if (!wx[i] && dfs(i)) ++tot;
	}
	printf("%d\n",tot);
}
int main()
{
	init();
	solve();
	return 0;
}
