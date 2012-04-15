/*
　设f(u, v ) = B(u, v) + g(u, v ) (*)，显然0 <= g(u, v ) <= C(u, v) - B(u, v)。将(*)代入流量平衡条件中，则得到∑[B(u, i) + g(u, i)] = ∑[ B(i, v) + g(i, v)] => ∑g(i, v) - ∑g(u, i) = ∑B(u, i) - ∑B(i, v)。如果设M(i) = ∑B(u, i) - ∑B(i, v)，即M(i)为流入结点i的下界总和减去流出i的下界总和。
　　至此，可如此构造一个只有流量上界的附加网络：增加附加源S'和附加汇T'，原网络中M(i)非负，则C'(S', i) = M(i)，否则C'(i, T') = -M(i)；原网络中任意有弧相连的结点u和结点v在附加网络中的弧C'(u, v) = C(u, v) - B(u, v)。

　　这样，如果附加网络满流，则在原网络中就存在一个与之对应的可行流。而想判断附加网络能否满流可通过求解附加网络的最大流进行判断。如果满流，则有解；否则无解。

　　这个问题弄明白后，就可以进行下一步的求解有上下界网络中的最大流和最小流问题了。

　　增加一条弧(T, S)，使原网络变成一个无源汇的网络。如果求最大流，则B(T, S) = a，C(T, S) = inf；如果求解最小流，则B(T, S) = 0，C(T, S) = a。可以通过二分法枚举a，按上文提到的方法构造附加网络，判断附加网络中是否有可行流即可。最终，a即为所求。

　　这种方法实现起来较为简单，所需的代价是多次求解最大流。复杂度为O(logF Maxflow(V, E))。
*/
#include<cstdio>
#include<cstring>
#include<vector>
#define maxn 1010
#define inf 1000000000
using namespace std;

struct edge{
	int v,c,next;
	int base;
	int rc;
};
vector<edge> e;
int beg[maxn];
//
int last[maxn];
int M[maxn];
int full;
int d[maxn],cnt_d[maxn];
//
int n,m,st,ed;
void add(int x,int y,int c,int base=0)
{
	int nE=e.size();
	e.push_back(edge());
	e[nE].v=y;
	e[nE].c=e[nE].rc=c;
	e[nE].base=base;
	e[nE].next=beg[x];
	beg[x]=nE;
}
void input()
{
	int x,y,low,high;
	e.resize(0);
	memset(beg,255,sizeof(beg));
	memset(M,0,sizeof(M));
	scanf("%d%d",&n,&m);
	st=0;ed=n+1;
	for(int i=1;i<=m;++i)
	{
		scanf("%d%d%d%d",&x,&y,&low,&high);
		M[x]-=low;
		M[y]+=low;
		add(x,y,high-low,low);
		add(y,x,0);
	}
	full=0;
	for(int i=1;i<=n;++i)
		if(M[i]>0) add(st,i,M[i]),add(i,st,0),full+=M[i];
		else if(M[i]<0) add(i,ed,-M[i]),add(ed,i,0);
	n++;
	for(int i=0;i<=n;++i) last[i]=beg[i];	
}
int Min(int x,int y)
{
	return x<y?x:y;
}
int sap(int x,int now)
{	
	if(x==ed) return now;
	int i=last[x],minD=n;
	int ext;	
	if(i!=-1)
	do{		
		if(e[i].c){		
			if(d[x]==d[e[i].v]+1){
				if((ext=sap(e[i].v,Min(now,e[i].c))))
				{
					e[i].c-=ext;
					e[i^1].c+=ext;
					last[x]=i;
					return ext;
				}
				if(d[st]>n) return 0;
			}
			minD=Min(minD,d[e[i].v]);
		}
		i=e[i].next==-1?beg[x]:e[i].next;
	}while(i!=last[x]);
	if(--cnt_d[d[x]]==0) d[st]=n+1;
	d[x]=minD+1;
	cnt_d[d[x]]++;
	return 0;
}
void max_flow()
{
	int ans=0;
	memset(d,0,sizeof(d));	
	memset(cnt_d,0,sizeof(cnt_d));
	while(d[st]<=n)
		ans+=sap(st,inf);
	if(ans==full){
		printf("YES\n");
		for(int i=0;i<2*m;i+=2)
			printf("%d\n",e[i].rc-e[i].c+e[i].base);
		printf("\n");
	}else printf("NO\n\n");
}
int main()
{
	freopen("zju2314.in","r",stdin);
	int cs;
	scanf("%d",&cs);
	while(cs--)
	{
		input();
		max_flow();		
	}
	return 0;
}

