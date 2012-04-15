/*求第k短路，先求出从t到其他点的最短距离，然后从短到长
迭代计算到各个点的距离，f(x)表示从起点到终点，途中路过顶点x的路径长度，
g(x)表示从起点到顶点x的距离，h(x)表示从x点到终点的最短距离，
用堆维护每次找最优值更新，知道终点第k次迭代即为答案*/

/*用源点到该点标号距离+该点到终点的最短距离作为a*的估价值，按估价值从小到大来进行扩展*/

#include<iostream>
#include<queue>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=1001;
const long maxm=1000001;
const long inf=100000000;

struct point
{
	long id, len;
} node[maxm],heap[maxm],node2[maxm];

bool operator < (const point &p1, const point &p2)
{
	return p1.len>p2.len;
}
long head[maxn],next[maxm],tt,top;
long head2[maxn],next2[maxm];
long dist_h[maxn],n,m,s,t,k,ti[maxn];
priority_queue<point> q;

void add(long x, long y, long d)
{
	node[++tt].id=y; node[tt].len=d;
	next[tt]=head[x]; head[x]=tt;

    node2[tt].id=x; node2[tt].len=d;
	next2[tt]=head2[y]; head2[y]=tt;
}
void init()
{
	scanf("%d%d",&n,&m);
	long x,y,d;
	tt=0;
	memset(head,0,sizeof(head));
	memset(head2,0,sizeof(head2));
	fo(i,1,m) {
		scanf("%d%d%d",&x,&y,&d);
		add(x,y,d);
	}
	scanf("%d%d%d",&s,&t,&k);
	if (s==t) ++k;
}
void cal_len()
{
	point tmp;
	tmp.id=t; tmp.len=0;
	q.push(tmp);
	fo(i,1,n) dist_h[i]=inf; dist_h[t]=0;
	long vis[maxn],x,y,d;
	memset(vis,0,sizeof(vis));
	while (!q.empty()) {
		x=q.top().id;
		q.pop();
		if (vis[x]) continue;
		vis[x]=1; 
		for (long i=head2[x]; i; i=next2[i]) {
			y=node2[i].id; d=node2[i].len;
			if (vis[y]) continue;
			if (dist_h[y]>dist_h[x]+d) {
				dist_h[y]=dist_h[x]+d;
				tmp.id=y; tmp.len=dist_h[y];
				q.push(tmp);
			}
		}
	}
}
void del()
{
	point tmp;
	heap[1]=heap[top--];
	for(long i=2; i<=top; i*=2) {
		if (i+1<=top && heap[i+1].len<heap[i].len) ++i;
		if (heap[i/2].len>heap[i].len) {
			tmp=heap[i/2]; 
			heap[i/2]=heap[i]; 
			heap[i]=tmp;
		} else break;
	}
}
void ins(point x)
{
	point tmp;
	heap[++top]=x;
	for (long i=top; i>1; i/=2) 
		if (heap[i/2].len>heap[i].len) {
			tmp=heap[i/2];
			heap[i/2]=heap[i];
			heap[i]=tmp;
		} else break;
}
void solve()
{
	memset(ti,0,sizeof(ti));
	point tmp;
	tmp.id=s; tmp.len=dist_h[s];
	top=0;
	ins(tmp);
	long x,y,d,len;
	if (dist_h[s]<inf) 
	while (top) {
		tmp=heap[1]; del();
		x=tmp.id; len=tmp.len;
		++ti[x];
		if (ti[t]==k) { printf("%d\n",tmp.len); return; }
		if (ti[x]>k) continue;
		for (long i=head[x]; i; i=next[i]) {
			y=node[i].id; d=node[i].len;
			if (dist_h[y]==inf) continue;
			tmp.id=y; 
			tmp.len=len-dist_h[x]+dist_h[y]+d;
			ins(tmp);
		}
	}
	printf("-1\n");		
}
int main()
{
	init();
	cal_len();
	solve();
	return 0;
}
