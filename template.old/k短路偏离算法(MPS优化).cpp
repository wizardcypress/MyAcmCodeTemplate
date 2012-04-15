/*k短路(点和边可重复走)的偏离算法(MPS优化)*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=6100;
const long maxm=300010;
const long inf=2000000000;

struct point //用于求最短路临时标号和求k短路时表示偏离路
{
/*
在求最短路时h没有用到，在表示偏离路时dist表示当前st到ed的距离。
u表示偏离节点，h表示偏离边在邻接表中的编号。
*/
	long dist,u,h;
	point() {}
	point(long dist, long u, long h) 
	{
		this->dist=dist;
		this->u=u;
		this->h=h;
    }
};

struct heap //用于求最短路和k短路的堆struct
{
	point p[maxm];
	long len;

	void clear() { len=0; }

	void swap(point &p1, point &p2)
	{
		point tmp;
		tmp=p1;  p1=p2; p2=tmp;
	}

	void ins(point x) 
	{
		p[++len]=x;
		for (long i=len; i>1; i/=2)
			if (p[i].dist<p[i/2].dist) swap(p[i],p[i/2]);
		    else break;
	}

	point pop() //返回堆顶元素同时删除堆顶元素
	{
		point now=p[1];
		p[1]=p[len--];
		for (long i=2; i<=len; i*=2) {
			if (i+1<=len && p[i].dist>p[i+1].dist) ++i;
			if (p[i].dist<p[i/2].dist) swap(p[i],p[i/2]);
			else break;
		}
		return now;
	}

} min_heap;

//如果图中的边是有向的，在求从ed出发的最短路时要将边的方向翻转之后才来求
long head[maxn],next[maxm],node[maxm],tt; 
long len[maxm],plen[maxm]; //len边权，plen偏离路长度
long shortest[maxn],pre[maxn]; //shortest从ed出发的最短路，pre最短路树中的前驱
long n,m,st,ed,k;//点数，边数，起点，终点，k短路

void add(long x, long y, long d)
{
	node[++tt]=y, next[tt]=head[x], head[x]=tt;
	len[tt]=d;
}
void init()
{
	long x,y,d;
	memset(head,0,sizeof(head)), tt=0;
	scanf("%d%d%d",&n,&m,&k);
	st=1; ed=n;
	fo(i,1,m) {
		scanf("%d%d%d",&x,&y,&d);
		add(x,y,d), add(y,x,d);
	}
}
void cal_shortest() //heap优化的dijkstra
{
	bool vis[maxn];
	memset(vis,0,sizeof(vis));
	fo(i,1,n) shortest[i]=inf; shortest[ed]=0; pre[ed]=0;
	min_heap.clear();
	min_heap.ins(point(0,ed,0));

    for (point p; min_heap.len>0; ) {
		p=min_heap.pop();
		if (vis[p.u]) continue;
		vis[p.u]=1;
		for (long i=head[p.u]; i; i=next[i]) {
			if (vis[node[i]]) continue;
			if (shortest[p.u]+len[i]<shortest[node[i]]) {
				shortest[node[i]]=shortest[p.u]+len[i];
				pre[node[i]]=p.u;
				min_heap.ins(point(shortest[node[i]],node[i],0));
			}
		}
	}
}

struct edge //用于保存邻接表中的边，dz表示边在邻接表中的地址，dist表示偏离路长度
{
	long dz,dist;
};

bool cmp(const edge &p1, const edge &p2)
{
	return p1.dist<p2.dist;
}

void sort_edge()
{
	edge e[maxn];
	long tot;
	fo(l,1,n) {
		tot=1; 
		e[tot].dz=0, e[tot].dist=inf; //用于方便对边进行排序
		//把从l出发的每一条边在邻接表中的位置和以其为偏离边的偏离路径的长度
		for (long i=head[l]; i; i=next[i]) 
			e[++tot].dz=i, e[tot].dist=len[i]+shortest[node[i]];
		sort(e+1,e+tot+1,cmp); //按偏离路径的长度升序排序

        //按偏离路径长度从小到大重新排列从l出发的边
        head[l]=e[1].dz;
		for (long i=1; i<=tot-1; ++i)
			next[e[i].dz]=e[i+1].dz, plen[e[i].dz]=e[i].dist; //连接链表，同时赋值对应的偏离路径长度
	}
}
void cal_k_shortest() //求第k短路
{
	min_heap.clear();
	min_heap.ins(point(shortest[st],st,head[st])); //初始化
	long now_len;
	point p=min_heap.pop();

    for (long l=1; l<k; ++l, p=min_heap.pop() ) {
		//p.u表示当前路径的偏离点，p.h表示偏离边

		if (next[p.h]!=0) { //当前偏离路径的第一个点p.u选择新的偏离路，要选以前没选过的最短偏离路径
		    now_len=p.dist-plen[p.h]+plen[next[p.h]]; 
			min_heap.ins(point(now_len,p.u, next[p.h]));
		}

		for (long x=node[p.h]; x>0 && x!=p.u; x=pre[x]) { 
		//从偏离边的node[p.h]开始到ed的最短路径上经过的点都扩展出行的偏离路径
			if (x!=ed && next[head[x]]!=0)  { //非ed的点从以第2短的路径开始走偏离路
				now_len=p.dist-plen[head[x]]+plen[next[head[x]]];
			    min_heap.ins(point(now_len,x,next[head[x]]));
		    }
			if (x==ed) {//ed从最短的路径作为偏离路
			   now_len=p.dist+plen[head[x]];
			   min_heap.ins(point(now_len,x,head[x]));
		     }
		}

	}

    //第k次出堆得就是k短路
	printf("%d\n",p.dist);
}
int main()
{
	init();
	cal_shortest();
	sort_edge();
	cal_k_shortest();
	return 0;
}
