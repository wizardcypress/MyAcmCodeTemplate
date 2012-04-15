/*
2-sat，注意边编号
*/
#include<iostream>
#include<stdio.h>
#include<memory>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
#define max(u,d) (u)>(d)?(u):(d)
using namespace std;

const long maxn=5001;
const long maxm=5000000;

long next[maxm],node[maxm],tt; //链表
long head[maxn],la[maxn];//原图中每个点的邻接表链头，每个强连通分量包含点的链表的链头 
long vis[maxn],cl[maxn],d[maxn];//每个点所属的强连通分量标记，染色的标记，缩点后的图每个点的度数
long high[maxn],num[maxn],e[maxm][2];//求强连通分量时的辅助标记，每条边
long st[maxn],top;//求强连通分量时的辅助栈
long op[maxn];//每个点的对立点
long n,m,tot,dfsn; //点数，边数，

//在链头为head的链表中添加节点y
void add(long &head, long y)
{
	node[++tt]=y; next[tt]=head; head=tt;
}
void init()
{

}
void make() //构图，按必选关系连边，注意x的对立点要用op[x]来记录
{
	memset(head,0,sizeof(head)), tt=0;
}
void find(long x) //求强连通分量
{
	high[x]=dfsn; num[x]=dfsn--; st[++top]=x;
	for (long i=head[x]; i; i=next[i]) 
		if (!num[node[i]]) {
		   find(node[i]);
		   high[x]=max(high[x],high[node[i]]);
	    } else if (!vis[node[i]]) high[x]=max(high[x],num[node[i]]);
	
	if (num[x]==high[x]) {
		vis[x]=++tot;
		while (st[top]!=x)
			vis[st[top--]]=tot;
		--top;
	}
}
void zip() //缩点
{
	memset(head,0,sizeof(head)), tt=0; //构造缩点后的图
	memset(d,0,sizeof(d));
	long x,y;
	fo(i,1,m) {
		x=vis[e[i][0]]; y=vis[e[i][1]];
		if (x!=y) 
			add(head[y],x), ++d[x]; //把缩点后的图反向连边
	}
	memset(la,0,sizeof(la));
	fo(i,1,2*n)
		add(la[vis[i]],i); //将同一个强连通分量中的点，
}
void color() 
/*
按拓扑关系染色，把0度点标记选，与该点矛盾的所有点及儿子均标记不选
cl[x]==0表示未决定，cl[x]==1表示选，cl[x]==2表示不选
*/
{
	memset(cl,0,sizeof(cl));
	long que[maxn],st,ed=0,x,y;
    fo(i,1,tot)
		if (d[i]==0) que[ed++]=i;
	for (x=que[st=0]; st<ed; x=que[++st]) {
		if (!cl[x]) {
			cl[x]=1;
			for (long i=la[x], y=vis[op[node[i]]]; i; i=next[i], y=vis[op[node[i]]]) {
				cl[y]=2; //把与x中的点矛盾的强连通分量标记为2
			    for (long j=head[y]; j; j=next[j]) cl[node[j]]=2; //把矛盾的强连通分量的后继也标记为2
			}
		}
		//把x的后继进队
		for (long i=head[x]; i; i=next[i]) 
			if (--d[node[i]]==0) que[ed++]=node[i];
	}
}
void solve()
{
	memset(high,0,sizeof(high));
	memset(num,0,sizeof(num));
	memset(vis,0,sizeof(vis));
	tot=0; top=0; dfsn=2*n;
	fo(i,1,2*n)
		if (!vis[i]) find(i);
    zip();
    color();
}
int main()
{
	init();
	solve();
	return 0;
}
