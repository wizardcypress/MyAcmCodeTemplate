#include<cstdio>
#include<cstring>
#include<algorithm>
#define N 100010
#define M 200010
#define INF 2000000000
typedef long long LL;
using namespace std;
//QualityPoint
struct NODE{
	int v,d,next;
}e[M];
int beg[N];
int nE;
int p[N];
int FinMin,KeyPoint;
int n,k;
//divTree
struct BEL{
	int dep,bel;
}b[N];
int nB;
int sumBel[N],calBel[N];
LL ans;
bool dead[N];
void add(int x,int y,int len)
{
	nE++;
	e[nE].v=y;
	e[nE].next=beg[x];
	e[nE].d=len;
	beg[x]=nE;
}
void input()
{
	int u,v,l;
	memset(beg,0,sizeof(beg));
	nE=0;	
	for(int i=0;i<n-1;++i)
	{
		scanf("%d%d%d",&u,&v,&l);
		add(u,v,l);
		add(v,u,l);
	}
}
void CalSon(int x,int fa)
{
	p[x]=1;
	for(int i=beg[x];i;i=e[i].next)
	if(e[i].v!=fa && !dead[e[i].v]){
		CalSon(e[i].v,x);		
		p[x]+=p[e[i].v];
	}
}
void DpPoint(int x,int fa,int cntFa)
{
	int max=cntFa;
	int sum=0;	
	for(int i=beg[x];i;i=e[i].next)	
	if(e[i].v!=fa && !dead[e[i].v]) {
		sum+=p[e[i].v];
		if(p[e[i].v]>max) max=p[e[i].v];
	}	
	if(max<FinMin)  
		FinMin=max,KeyPoint=x;			
	for(int i=beg[x];i;i=e[i].next)
		if(e[i].v!=fa && !dead[e[i].v]){
			DpPoint(e[i].v,x,cntFa+sum-p[e[i].v]+1);		
		}
}
void getQualityPoint(int root)
{
	FinMin=INF;
	CalSon(root,-1);
	DpPoint(root,-1,0);
}
void getDepChk(int x,int& flag,int fa)
{	
	int dep=b[nB].dep;
	b[nB++].bel=flag;
	for(int i=beg[x];i;i=e[i].next)
	if(e[i].v!=fa&& !dead[e[i].v])
	{
		b[nB].dep=dep+e[i].d;
		getDepChk(e[i].v,flag,x);
	}
}
inline bool cmp(const BEL &x,const BEL &y)
{
	return x.dep<y.dep || (x.dep==y.dep && x.bel<y.bel);
}
inline void swap(BEL &x,BEL &y)
{
	BEL tm=x; x=y; y=tm;
}
void divTree(int root,int fa)
{
	getQualityPoint(root);//要以质点为根进行剖分才能保证复杂度。
	root=KeyPoint;
	int chkFlag=1;
	nB=1;
	b[0].dep=0;b[0].bel=1;
	for(int i=beg[root];i;i=e[i].next)
	if(e[i].v!=fa && !dead[e[i].v])
	{
		b[nB].dep=e[i].d;
		getDepChk(e[i].v,++chkFlag,root);
	}
	memset(sumBel,0,sizeof(sumBel));
	for(int i=0;i<nB;++i)
		sumBel[b[i].bel]++;
	
	sort(b,b+nB,cmp);
		
	int last=nB;
	b[nB].dep=k+1; 	b[nB].bel=0;
	for(int i=0;i<nB;++i)
	{	
		while(last>=0 && (LL)b[last].dep+b[i].dep>k) {
		sumBel[b[last].bel]--;
		last--;
		}
		ans=ans+last+1-sumBel[b[i].bel];
	}
	dead[root]=true;
	for(int i=beg[root];i;i=e[i].next)
	if(e[i].v!=fa && !dead[e[i].v])
		divTree(e[i].v,root);
}
void solve()
{	
	ans=0;	
	memset(dead,0,sizeof(dead));
	divTree(1,-1);
	printf("%lld\n",ans/2);
}
int main()
{
	//freopen("snail.in","r",stdin);
	while(scanf("%d%d",&n,&k),n!=0 || k!=0)
	{
		input();
		solve();
	}		
	return 0;
}
