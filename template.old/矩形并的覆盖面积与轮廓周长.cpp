#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<memory>
#define fo(i,u,d) for(long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=20001;

struct node
{
	long len,l,r,d,m,c;//区间长度、左右是否覆盖标记、测度、连续区间数、区间被覆盖次数
} tree[maxn*4];

struct line
{
	long y1,y2,x,w;
} p[maxn];

long n,ll,rr,w;

bool cmp(const line &p1, const line &p2)
{
	return (p1.x<p2.x) || (p1.x==p2.x && p1.w>p2.w);
}
void init()
{
	scanf("%d",&n);
	long d[4];
	fo(i,1,n) {
		fo(j,0,3) scanf("%d",&d[j]), d[j]+=10000;
		p[i*2-1].y1=d[1], p[i*2-1].y2=d[3], p[i*2-1].x=d[0], p[i*2-1].w=1;
	    p[i*2].y1=d[1], p[i*2].y2=d[3], p[i*2].x=d[2], p[i*2].w=-1;
	}
	n*=2;
}
long ab(long x)
{
	return x<0?-x:x;
}
void updata(long h)
{
	if (tree[h].c) {
		tree[h].d=tree[h].len;
		tree[h].m=1;
		tree[h].l=1, tree[h].r=1;
	} else {
		tree[h].d=tree[h*2].d+tree[h*2+1].d;
		tree[h].m=tree[h*2].m+tree[h*2+1].m-tree[h*2].r*tree[h*2+1].l;
		tree[h].l=tree[h*2].l ,tree[h].r=tree[h*2+1].r;
	}
}
void ins(long x, long y, long h)
{
	if (y<ll || x>rr) return;
	if (ll<=x && y<=rr) {
		tree[h].c+=w;
		tree[h].len=y-x+1;
		if (x!=y) updata(h);
		else {
			if (tree[h].c)
				tree[h].l=1, tree[h].r=1, tree[h].d=1, tree[h].m=1;
			else
				tree[h].l=0, tree[h].r=0, tree[h].d=0, tree[h].m=0;
		}
	} else {
		ins(x,(x+y)/2,h*2);
		ins((x+y)/2+1,y,h*2+1);
		updata(h);
	}
}
void solve()
{
	memset(tree,0,sizeof(tree));
	long lastd=0,lastm=0,len=0,area=0;
	fo(i,1,n) {
       ll=p[i].y1+1, rr=p[i].y2, w=p[i].w;
	   ins(1,maxn-1,1);
	   len+=lastm*2*(p[i].x-p[i-1].x);
	   len+=ab(lastd-tree[1].d);
	   area+=lastd*(p[i].x-p[i-1].x);
	   lastd=tree[1].d;
	   lastm=tree[1].m;
	}
	printf("%d\n%d\n",len,area);//周长，面积
}
int main()
{
	init();
	sort(p+1,p+n+1,cmp);
	solve();
	return 0;
}
