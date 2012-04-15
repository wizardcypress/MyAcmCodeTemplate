/*lrj学习指导上的方法*/
#include<iostream>
#include<stdio.h>
#include<string.h>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
#define min(u,d) (u)<(d)?(u):(d)
using namespace std;

const long maxk=11; //k短路的上界
const long maxn=110; //点数上界
const long inf=100000000;

struct kpath //前k短路
{
	long klen[maxk];
	kpath() 
	{
		fo(i,1,maxk-1) klen[i]=inf; //初始化长度为inf
	}
} dist[maxn][maxn]; //i到j的前k短路

long n,k; //点数，k短路数
long heap[maxn],lab[maxn],hlen; //用于加速计算路径和的前k短路的堆

inline void swap(long i)//交换堆中的两个元素
{
	long tmp;

	tmp=heap[i];  heap[i]=heap[i/2];  heap[i/2]=tmp;
    tmp=lab[i]; lab[i]=lab[i/2]; lab[i/2]=tmp;
}
inline void ins(long x, long w)
{
	long tmp;

	if (x>inf) x=inf;
	heap[++hlen]=x; lab[hlen]=w;
	for (long i=hlen; i>1; i/=2) {
		if (heap[i/2]>heap[i]) { swap(i); continue; }
		break;
	}
}
inline void del()
{
	heap[1]=heap[hlen]; lab[1]=lab[hlen--];
	for (long i=2; i<=hlen; i*=2) {
		if (i+1<=hlen && heap[i+1]<heap[i]) ++i;
		if (heap[i/2]>heap[i]) { swap(i); continue; }
		break;
	}
}
inline void init()
{
	long m,x,y,d;
	scanf("%d%d%d",&n,&m,&k);
	//fo(i,1,n) dist[i][i].klen[1]=0;
	fo(i,1,m) { 
		 scanf("%d%d%d",&x,&y,&d);
		 dist[x][y].klen[1]=min(dist[x][y].klen[1],d);
		 dist[y][x].klen[1]=dist[x][y].klen[1];
	}
}
inline kpath min_klen(kpath p1, kpath p2) //从p1,p2中找出前k短路
{
	kpath p;
	long l1=1, l2=1;

	fo(l,1,k) {
		if (l2>k || ( l1<=k && p1.klen[l1]<p2.klen[l2])) { p.klen[l]=p1.klen[l1++]; continue; }
		p.klen[l]=p2.klen[l2++];
	}
	return p;
}
inline kpath add(kpath p1, kpath p2)
/*
计算p1,p2中任意两对路径之和中的前k短路
具体做法先把p1中的每条路径长度加上p2中的最短路加入堆中
每次取出当前最短路后将被取出的p1路径长度加上p2中下一个路径长度加入堆中
要注意路径相加后可能会越界，若越界则缩回inf
*/
{
	kpath p;
	long pt[maxk], wpt; //当前每个p1的路径长度指向的p2中的路径长度
	
	hlen=0;
	fo(i,1,k) {
		pt[i]=1;
		ins(p1.klen[i]+p2.klen[1], i);
	}
	fo(i,1,k) {
		p.klen[i]=heap[1]; //取出当前最短长度作为新的第i短路
		wpt=lab[1]; //被取出的p1中的第wpt短路
		del();
		ins(p1.klen[wpt]+p2.klen[++pt[wpt]],wpt); //更新后加入堆中
	}
	return p;
}
inline kpath extend_kpath(kpath pp)
/*
将pp扩展（即不断走环），取前k短路
*/
{
	kpath p,ext_p=pp;
	fo(i,1,k) {
		p=min_klen(p,pp);
		ext_p=add(ext_p,pp);
	}
	return p;
}
void cal_every_kpath()
{
	kpath pp;
	fo(l,1,n)
		fo(i,1,n) 
		   fo(j,1,n) {
		       pp=extend_kpath(dist[l][l]);
			   //只经过l一次
			   dist[i][j]=min_klen( dist[i][j], add(dist[i][l],dist[l][j]) ); 
			   //经过l两次或以上，因此要扩展
		       dist[i][j]=min_klen( dist[i][j], add( extend_kpath(dist[l][l]) , add(dist[i][l],dist[l][j]) ) );
		   }
	/*
	d[i][j][l]表示的是当前从i到j中间只经过标号为1到l的点的前k短路
	1、只经过1-(l-1)，即d[i][j][l-1]
	2、经过l，由于可能多次经过l，所以要把dist[l][l][l-1]扩展（不断走环，得出多次经过l的前k短路）
	     即dist[i][l][l-1]+extend(dist[l][l][l-1])+dist[j][l][l-1]
	具体做的时候可以将第3维省略掉
	*/
}
void solve()
{
	long x,y,kp;
    while (scanf("%d%d%d",&x,&y,&kp), x!=0) 
		printf("%d\n",dist[x][y].klen[kp]);
}
int main()
{
	init();
	cal_every_kpath();
	solve();
	return 0;
}
