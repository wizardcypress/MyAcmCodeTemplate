/*每次通过找树的质心来将树尽量划分（使得划分的每棵子树节点数不超过n/2个）
每棵子树递归去做，任意两棵子树之间满足题意的点对则通过排序后线性维护求得*/
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<string.h>
#define fo(	i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=20001;

struct point
{
	long len,id;
} p[maxn];

long head[maxn],next[maxn],node[maxn],tt;
long n,k,m,node_num,root,biggest,tn,ans;//n为节点数，k为点对距离上界
long vis[maxn],dist[maxn];
long sum[maxn];

bool cmp(const point &p1, const point &p2)
{
	return p1.len<p2.len;
}
void add(long x, long y, long d)
{
	node[++tt]=y; next[tt]=head[x]; head[x]=tt;
	dist[tt]=d;
}
void init()
{
	long x,y,d;
	memset(head,0,sizeof(head)), tt=0;
	fo(i,1,n-1) 
		scanf("%d%d%d",&x,&y,&d), add(x,y,d), add(y,x,d);
}
void cal_num(long x, long y)
{
	++node_num;
	for (long i=head[x]; i; i=next[i])
		if (node[i]!=y && !vis[node[i]]) cal_num(node[i],x);
	    //注意排除掉不在子树的点,vis[node[i]]表示node[i]在之前已经被划分掉了
}
long find_root(long x, long y)
{
	long bigger=0, tot=1, now;//biger为以当前x点来划分时最大那棵子树的节点数
	for (long i=head[x]; i; i=next[i])
		if (node[i]!=y && !vis[node[i]]) {
		   if ((now=find_root(node[i],x))>bigger) bigger=now;
		   tot+=now;
	    }
	if (node_num-tot>bigger) bigger=node_num-tot;
	if (bigger<biggest) biggest=bigger, root=x;
	return tot;
}
void count_len(long x, long y, long len)
{
	p[++m].len=len, p[m].id=tn;
	for (long i=head[x]; i; i=next[i]) 
		if (node[i]!=y && !vis[node[i]]) count_len(node[i],x,len+dist[i]);
}
void cal_ans()
{
	memset(sum,0,sizeof(sum)); 
	p[0].len=0, p[0].id=0;
	fo(i,1,m) ++sum[p[i].id];
	for (long i=0, j=m; i<j; --sum[p[++i].id]) {
		while (i<j && p[j].len+p[i].len>k) --sum[p[j--].id];
		ans+=(j-i)-sum[p[i].id];//计算的时候要减去同一棵子树中的满足题意的点对数
	}
}
void cal(long x)
{
	node_num=m=tn=0, biggest=n;
	cal_num(x,x); //统计当前树的节点数
	find_root(x,x); //找质心
	for (long i=head[root]; i; i=next[i]) 
		if (!vis[node[i]]) 
		    ++tn, count_len(node[i],root,dist[i]); //算出每棵子树中节点到质心root的距离，tn记录以root为根的子树的个数
	sort(p+1,p+m+1,cmp);//将所有节点到root的距离排序
	cal_ans();//线性维护求解出满足题意的点对数
	vis[root]=1;
	for (long i=head[root]; i; i=next[i])  //递归求解每一棵子树
		if (!vis[node[i]]) cal(node[i]);
}
void solve()
{
	memset(vis,0,sizeof(vis));
	ans=0;
	cal(1);
	printf("%d\n",ans);
}
int main()
{
	while (scanf("%d%d",&n,&k),n!=0) {
		init();
		solve();
	}
	return 0;
}
