/*具体看lrj学习指导*/
#include<iostream>
#include<cmath>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
#define fod(i,u,d) for (long i=(u); i>=(d); --i)
using namespace std;

const long maxn=20010;
const long maxm=16;

long head[maxn],next[maxn],node[maxn],tt;
long ancestor[maxn][maxm],depth[maxn]; //ancestor[i][j]表示i号节点的第2^j阶祖先,0阶表示自身
long stack[maxn]; //同于计算ancestor,保存的是当前从root到x的路径上的节点
long n,t,root;

void add(long x, long y)
{
	node[++tt]=y; next[tt]=head[x]; head[x]=tt;
}
void init()
{
	memset(head,0,sizeof(head)), tt=0;
}
void pre_k_ancestor(long x, long y, long dep)
{
	depth[x]=dep; stack[dep]=x; ancestor[x][0]=x;
	for (long j=0; dep-(1 << j)>=0; ++j) ancestor[x][j+1]=stack[dep-(1 << j)];
	for (long i=head[x]; i; i=next[i])
		if (node[i]!=y) pre_k_ancestor(node[i], x, dep+1);
}
//求x的第k阶祖先，类似rmq的求法
long cal_k_ancestor(long x, long k)
{
	fod(j,maxm,0) 
		if ((1 << j)<=k) x=ancestor[x][j+1], k-=1 << j;
	return x;
}
void solve()
{
	long x,y;
	scanf("%d%d",&x,&y);
	long low=0, high=depth[x]<depth[y]?depth[x]:depth[y];
	long jie,xx,yy;
	//把x和y上升到同一高度
	x=cal_k_ancestor(x,depth[x]-high);
	y=cal_k_ancestor(y,depth[y]-high);
	if (x==y) {printf("%d\n",x); return;} //x==y表明x和y是祖先后代关系
	/*类似2分的做法，每次找出最大的jie使得high-2^jie<low，通过判断深度为high-2^jie
    的节点是否为公共祖先，同时进行相关处理*/
	while (low+1<high) { //结束条件为x,y到达lca的下方
		jie=long(log(double(high-low-1))/log(2.0));
	    xx=ancestor[x][jie+1];
		yy=ancestor[y][jie+1];
		if (xx==yy) low=high-(1 << jie);
		else high-=1 << jie, x=xx, y=yy;
	}
	printf("%d\n",ancestor[x][1]);
}
int main()
{
	scanf("%d",&t);
	while (t--) {
		init();
		pre_k_ancestor(root,root,0);
		solve();
	}
	return 0;
}
