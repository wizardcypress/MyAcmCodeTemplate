/*
基于定理：一个图无向图是弦图当且仅当它有完美消除序列。
首先找出消除序列：
0.i=n
1.找到一个u∈{j|label[j]=max{label[k]}(k为未标号点)},seq[u]=i
2.--i,所有与u相邻的v且++label[v],回到1
也就是说，每次找现有未标号的点中，与已标号的点相邻最多的那个，标号。
然后判断该序列是否是完美消除序列(vi即为seq[i])：
for 0~n-1对于每一个vi，找到{vi+1,vi+2,…,vn}中与vi相邻的标号最小的点vj，判断其它{vi+1,vi+2,…,vn}中与vi相邻的点是否与vj相邻，若不相邻则不是完美消除序列。
*/
#include<cstdio>
#include<cstring>
#define maxn 1010
using namespace std;
int n,m;
bool go[maxn][maxn],vis[maxn];
int lab[maxn],seq[maxn];
int tmp[maxn];
void input()
{
	int x,y;
	memset(go,0,sizeof(go));
	for(int i=0;i<m;i++)
	{
		scanf("%d%d",&x,&y);
		x--; y--; //base from 0
		go[x][y]=go[y][x]=true;
	}	
}
void perf_seq()
{
	memset(lab,0,sizeof(lab));
	memset(vis,0,sizeof(vis));
	for(int i=n-1;i>=0;i--)
	{
		int x=-1;
		for(int j=0;j<n;j++)
			if(!vis[j] && (x==-1 || lab[j]>lab[x] )) x=j;
		seq[i]=x;
		vis[x]=true;
		for(int j=0;j<n;++j)
			if(!vis[j] && go[x][j]) lab[j]++;
	}
}
bool check()/* 检查seq是否是一个完美序列 */
{
	int tmpl;
	for(int i=0;i<n;i++)
	{
		tmpl=0;
		for(int j=i+1;j<n;j++)
			if(go[seq[i]][seq[j]]) tmp[tmpl++]=seq[j];
		for(int j=1;j<tmpl;j++)
			if(!go[tmp[0]][tmp[j]]) return false;
	}
	return true;
}
int main()
{
	//freopen("zju1015.in","r",stdin);
	while(scanf("%d%d",&n,&m),n+m)
	{
		input();
		perf_seq();
		if(check()) printf("Perfect\n");
		else printf("Imperfect\n");
		printf("\n");
	}
	return 0;
}
