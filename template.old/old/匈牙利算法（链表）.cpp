#include<iostream>
#include<cstdio>
#include<cstring>
#define N 10010
#define M 1000000
using namespace std;

struct EDGE
{
	int v,next;
}e[M];

int en,turn;
int pt[N];
int mark[N];
int beg[N],n;

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
	while(getchar()!=':') ;
	while(getchar()!='(') ;
	scanf("%d",&num);
	while(getchar()!=')') ;
	for(int i=1;i<=num;++i)
	{
		scanf("%d",&y);
		y++;
		y-=n;
		add(x,y);
	}
	}
}
bool dfs(int x)
{	    
	for(int i=beg[x];i;i=e[i].next)
	{
		int v=e[i].v;
		if(mark[v]==turn) continue;		
		mark[v]=turn;
		if(pt[v]==-1 || dfs(pt[v]))
		{		
			pt[v]=x;
			return true;
		}
	}
	return false;
}
void solve()
{
	int ans=0;
	memset(mark,0,sizeof(mark));
	memset(pt,0xff,sizeof(pt));
	for(turn=1;turn<=n;++turn)				
		if (dfs(turn)) ans++;
	printf("%d\n",ans);
}
int main()
{
	freopen("c.in","r",stdin);
	while(scanf("%d",&n)!=EOF)
	{
		input();
		solve();		
	}
	return 0;
}

