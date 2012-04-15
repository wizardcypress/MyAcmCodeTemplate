#include<iostream>
#include<stdio.h>
#include<memory>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
#define min(u,d) (u)<(d)?(u):(d)
using namespace std;

const long maxn=1000;
const long maxm=100000;
const long inf=1000000000;

//存储网络的链表，当前弧，弧总数
long head[maxn],next[maxm],node[maxm],la[maxn],tt; 
//残留网
long c[maxm];
//SAP中的距离标号和GAP的各种距离标号数目
long h[maxn],vh[maxn];
//原图点数，边数。构图后的源点汇点
long n,m,st,ed;

 void add(long x, long y, long flow)
 {
	 node[++tt]=y; next[tt]=head[x]; head[x]=tt; la[x]=tt;
	 c[tt]=flow;
 }
 void init()
 {
	 //注意弧的标号从0开始，这样才能保证弧和反向弧一一对应
	 memset(head,255,sizeof(head)), tt=-1;
 }
 long find(long x, long flow)
 {
	if (x==ed) return flow;
	long mi=ed,now,i=la[x];
	if (i!=-1)
	do {
		if (c[i]) {
			if (h[x]==h[node[i]]+1) {
				if (now=find(node[i],min(flow,c[i]))) {
					c[i]-=now;
					c[i^1]+=now;
					la[x]=i;
					return now;
				}
				if (h[st]>ed) return 0;
			}
			mi=min(mi,h[node[i]]);
		}
		i=next[i]>-1?next[i]:head[x];
	} while (i!=la[x]);
	if (--vh[h[x]]==0) h[st]=n+1;
	h[x]=mi+1;
	++vh[h[x]];
	return 0;
 }
 void solve()
 {
	 long ans=0;
	 memset(h,0,sizeof(h));
	 memset(vh,0,sizeof(vh));
	 while (h[st]<=ed)
		 ans+=find(st,inf);
	 printf("%d\n",ans);
 }
 int main()
 {
	 init();
	 solve();
	 return 0;
 }
