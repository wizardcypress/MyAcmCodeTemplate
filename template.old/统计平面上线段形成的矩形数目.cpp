/*统计平面上的线段能划分出多少个矩形
先按竖直线从左到右排序，然后将水平线按左端点的x坐标排序
枚举左竖直线，然后将左端点x坐标比竖直线x坐标小的插入线段树
（按y坐标），然后再枚举右竖直线，同时维护线段树
（把水平线的右端点x坐标比右竖直线x坐标小的从线段树中删除）。
一边维护一边统计两条竖直线形成的矩形数（两条竖直线的交集
在线段树中查询到的跨越两条竖直线的线段树num，
ans+=num*(num-1)/2）*/
#include<iostream>
#include<algorithm>
#include<stdio.h>
#include<memory>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
#define fod(i,u,d) for (long i=(u); i>=(d); --i)
using namespace std;

const long maxn=101;
const long maxm=1001;

struct line
{
	long d[3];
} p[2][maxn],pp[maxn];

long n,t,tree[maxm*4],tl[2],tp,ll,rr,pos,w;

void swap(long &x, long &y)
{
	if (x>y) 
		x+=y, y=x-y, x-=y;
}
void init()
{
	scanf("%d",&n);
	tl[1]=0, tl[0]=0;
	long x[2],y[2];
	fo(i,1,n) {
		fo(j,0,1)
		   scanf("%d%d",&x[j],&y[j]);
		if (x[0]==x[1]) {
			swap(y[0],y[1]);
			p[0][++tl[0]].d[0]=x[0], p[0][tl[0]].d[1]=y[0], p[0][tl[0]].d[2]=y[1];
		} else {
			swap(x[0],x[1]);
			p[1][++tl[1]].d[0]=y[0], p[1][tl[1]].d[1]=x[0], p[1][tl[1]].d[2]=x[1];
		}
	}
}
bool cmp1(const line &p1, const line &p2)
{
	return p1.d[0]<p2.d[0];
}
bool cmp2(const line &p1, const line &p2)
{
	return p1.d[1]<p2.d[1];
}
void ins(long x, long y, long h)
{
	if (pos<x || pos>y) return;
	tree[h]+=w;
	if (x<y) {
		ins(x,(x+y)/2,h*2);
		ins((x+y)/2+1,y,h*2+1);
	}
}
long cal(long x, long y ,long h)
{
	if (y<ll || rr<x) return 0;
	if (ll<=x && y<=rr) return tree[h];
	long w1,w2;
	w1=cal(x,(x+y)/2,h*2);
	w2=cal((x+y)/2+1,y,h*2+1);
	return w1+w2;
}
void solve()
{
	long l=1,ans=0;
	tp=0;
	fo(i,1,tl[0]-1) {
		memset(tree,0,sizeof(tree));
		while (l<=tl[1] && p[1][l].d[1]<=p[0][i].d[0]) {
			pp[++tp].d[1]=p[1][l].d[2],
			pp[tp].d[0]=p[1][l++].d[0];
		}
		sort(pp+1,pp+tp+1,cmp2);
		fo(j,1,tp)
			pos=pp[j].d[0], w=1, ins(0,maxm-1,1);
		long ii=1;
		fo(j,i+1,tl[0]) {
			while (ii<=tp && pp[ii].d[1]<p[0][j].d[0]) {
                pos=pp[ii++].d[0], w=-1,
				ins(0,maxm-1,1);
			}
		   ll=p[0][i].d[1]>p[0][j].d[1]?p[0][i].d[1]:p[0][j].d[1];
		   rr=p[0][i].d[2]<p[0][j].d[2]?p[0][i].d[2]:p[0][j].d[2];
		   if (ll<rr) {
			   long now=cal(0,maxm-1,1);
			   ans+=now*(now-1)/2;
		   }
		}
	}
	printf("%d\n",ans);
}
int main()
{
	scanf("%d",&t);
	while (t--) {
	   init();
	   sort(p[0]+1,p[0]+tl[0]+1,cmp1);
	   sort(p[1]+1,p[1]+tl[1]+1,cmp2);
	   solve();
	}
	return 0;
}
