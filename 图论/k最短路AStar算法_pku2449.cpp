#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
#define N 1010
#define M 100010
#define INF 1000000000
using namespace std;
struct EDGE{
	int v,next,len;
}e1[M],e2[M];
struct NODE{
	int v,len;
	NODE(int _v=0,int _len=0):v(_v),len(_len){}
	bool operator<(const NODE &that)const{
		return len>that.len;
	}
};
priority_queue<NODE> que;

int beg1[N],beg2[N],nE1,nE2;
int h[N]; //每个点到t的距离
int cnt[N];
bool mark[N];
int n,m,k;
int s,t;
void add(int x,int y,int l)
{
	nE1++;
	e1[nE1].v=y;   e1[nE1].next=beg1[x];  e1[nE1].len=l; beg1[x]=nE1; 
	nE2++;
	e2[nE2].v=x;   e2[nE2].next=beg2[y];  e2[nE2].len=l; beg2[y]=nE2;
}
void input()
{
	int x,y,l;
	memset(beg1,0,sizeof(beg1));	
	memset(beg2,0,sizeof(beg2));	
	nE1=nE2=0;
	for(int i=0;i<m;++i)	
	{
		scanf("%d%d%d",&x,&y,&l);
		add(x,y,l);
	}
	scanf("%d%d%d",&s,&t,&k);
	if(s==t) k++;
}
void dij()
{
	int u,v,len;
	while(!que.empty()) que.pop();	
	fill(h,h+n+2,INF);
		
	que.push(NODE(t,0));
	h[t]=0;
	while(!que.empty())
	{
		u=que.top().v;
		len=que.top().len;
		que.pop();
		if(len!=h[u]) continue;
		for(int  i=beg2[u];i;i=e2[i].next)
		{
			v=e2[i].v;
			if(h[u]+e2[i].len<h[v])
			{
				h[v]=h[u]+e2[i].len;
				que.push(NODE(v,h[v]));
			}
		}
	}
}
int astar()
{
	int u,len;
	while(!que.empty()) que.pop();
	memset(cnt,0,sizeof(cnt));
		
	if(h[s]==INF) return -1;	
	que.push(NODE(s,h[s]));	
	while(!que.empty())	
	{
		u=que.top().v;
		len=que.top().len;
		que.pop();
		cnt[u]++;
		if(cnt[t]==k) return len;
		if(cnt[u]>k) continue;
		for(int i=beg1[u];i;i=e1[i].next)
		{
			v=e1[i].v;
			que.push(NODE(v,len-h[u]+h[v]+e1[i].len)); //len-h[u]为s到u的标号距离
		}
	}
	return -1;
}
int main()
{
	freopen("pku2449.in","r",stdin);
	while(scanf("%d%d",&n,&m)!=EOF)
	{
		input();
		dij();		
		printf("%d\n",astar());
	}
	return 0;
}
