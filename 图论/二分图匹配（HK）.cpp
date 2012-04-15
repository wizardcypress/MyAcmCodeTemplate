#include <cstdio>
#include <cstring>
#define N 10010
#define M 1000010
#define INF 2000000000
using namespace std;
struct EDGE
{
	int v,next;
};
EDGE e[M];
int n,en;
int beg[N];
int lx[N],ly[N];
int que[N];
int dx[N],dy[N];
void add(int x,int y)
{
	en++;
	e[en].v=y;
	e[en].next=beg[x];
	beg[x]=en;
}
void input()
{
	int num,x,y;		
	en=0;
	memset(beg,0,sizeof(beg));
	for(int l=1;l<=n;++l)
	{
	scanf("%d",&x);	
	x++;	
	while(getchar()!=':');
	while(getchar()!='(');
	scanf("%d",&num);
	while(getchar()!=')');
	for(int i=1;i<=num;++i)
	{
		scanf("%d",&y);
		y++;
		y-=n;
		add(x,y);
	}
	}
}
bool bfs()
{
	int st=1,ed=0;
	bool flag=false;
	memset(dx,0,sizeof(dx));
	memset(dy,0,sizeof(dy));
	for(int i=1;i<=n;++i)
		if(!lx[i]) que[++ed]=i;
	for(;st<=ed;++st)
	{
		int cur=que[st];
		for(int i=beg[cur];i;i=e[i].next)
		{
			int v=e[i].v;
			if(!dy[v]) 
			{
				dy[v]=dx[cur]+1;
				if(!ly[v]) flag=true;
				else dx[ly[v]]=dy[v]+1,que[++ed]=ly[v];
			}
		}
	}	
	return flag;
}
bool dfs(int x)
{
	for(int i=beg[x];i;i=e[i].next)
	{
		int y=e[i].v;
		if(dy[y]==dx[x]+1)
		{
			dy[y]=0;
			if(!ly[y] || dfs(ly[y]))
			{
				ly[y]=x;
				lx[x]=y;
				return true;
			}
		}
	}
	return false;
}
void solve()
{
	memset(lx,0,sizeof(lx));
	memset(ly,0,sizeof(ly));
	int ans=0;
	while(bfs())
	{
		for(int i=1;i<=n;++i)
			if(!lx[i] && dfs(i)) ++ans;	
	}
	printf("%d\n",ans);
}
int main()
{
	freopen("C.IN","r",stdin);
	while(scanf("%d",&n)!=EOF)
	{
		input();
		solve();
	}
	return 0;
}
