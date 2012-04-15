/*最小树形图，每次每个点选一条最小的入边，若不存在环则
完成。否则将环缩点，从环上的点出来的边权值不变，从外部点
进环的边权值减去换内点所选边的边权，注意更新边权的时候要
取最小值*/

#include<iostream>
#include<cmath>
#include<memory>
#include<stdio.h>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=501;
const double inf=1e20;

double g[maxn][maxn],ans;
long du[maxn],fa[maxn],n,m,b[maxn];
//g为边权，fa为每个点的入边的点，b表示每个点是否存在
void init()
{

}
long cal_tree()//每个点选最小的入边
{
	double len[maxn];
	fo(i,1,n) len[i]=inf;
	memset(fa,0,sizeof(fa));
	memset(du,0,sizeof(du));
	fo(i,1,n) if (!b[i]) 
		fo(j,2,n) if (!b[j] && g[i][j]>0 && g[i][j]<len[j])  
		    len[j]=g[i][j], --du[fa[j]], fa[j]=i, ++du[i];
		    
	fo(i,2,n) 
	   if (!b[i] && fa[i]==0) return 1;
	return 0;
}
long top_find()//用拓扑排序找环
{
	long st=0,ed=0,q[maxn],x;
	fo(i,2,n) if (!b[i] && du[i]==0) q[ed++]=i;
	for (x=q[st] ; st<ed ; ++st, x=q[st])  
		if ( (--du[fa[x]]) == 0 ) q[ed++]=fa[x];
		
	fo(i,2,n) if (!b[i] && du[i]) return i;
	return 0;
}
void up_b(long x)
{
	long i=x;
	b[x]=1;
	while (fa[i]!=x) b[fa[i]]=1, i=fa[i];
}
void zip_point(long x)//更新边权，注意取最小值
{
	long i=x;
	++n;
	do {
		ans+=g[fa[i]][i];
		fo(j,1,n-1) if (!b[j]) {
			if (g[i][j]>0 && (g[n][j]<0 || g[n][j]>g[i][j]) ) g[n][j]=g[i][j];
			if (g[j][i]>0 && (g[j][n]<0 || g[j][n]>g[j][i]-g[fa[i]][i]) ) g[j][n]=g[j][i]-g[fa[i]][i];
		}
		i=fa[i];
	} while (i!=x);
}
void solve()
{
	memset(b,0,sizeof(b));
	long point;
	ans=0;
	for(;;) {
	   if (cal_tree()) { printf("NO\n"); return; }
	   if (point=top_find()) 
	       up_b(point), zip_point(point);
	   else break;
	}
	fo(i,2,n) if (!b[i]) ans+=g[fa[i]][i];
}
int main()
{
	while (scanf("%d%d",&n,&m)!=EOF) {
		init();
		solve();
	}
	return 0;
}
