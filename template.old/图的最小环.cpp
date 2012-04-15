/*flody改进，注意路径记录*/
#include<iostream>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=101;
const long inf=100000000;

long g[maxn][maxn],f[maxn][maxn],r[maxn][maxn],n,m,ii,jj,ll;
long da[maxn],len;

long min(long x, long y)
{
	return x<y?x:y;
}
void init()
{
	scanf("%d%d",&n,&m);
	fo(i,1,n) fo(j,1,n) g[i][j]=inf, f[i][j]=inf;
	long x,y,d;
	fo(i,1,m) {
		scanf("%d%d%d",&x,&y,&d);
		g[x][y]=min(g[x][y],d);
		g[y][x]=g[x][y];
		f[x][y]=g[x][y], f[y][x]=g[x][y];
	}
}
void cal(long ii, long jj)
{
	if (r[ii][jj]) cal(ii,r[ii][jj]);
	if (r[ii][jj]) da[++len]=r[ii][jj];
	if (r[ii][jj]) cal(r[ii][jj],jj);
}
void solve()
{
	long ans=inf;
	memset(r,0,sizeof(r));
	fo(l,1,n) {
       fo(i,1,l-1) 
		   fo(j,i+1,l-1) 
		      if (ans>f[i][l]+f[l][j]+g[i][j]) {
		         ans=f[i][l]+f[l][j]+g[i][j];
                 da[1]=l, da[2]=i, len=2, cal(i,j), da[++len]=j;
	          }
		fo(i,1,n) if (i!=l)
		   fo(j,1,n) if (j!=l && j!=i) 
		       if (g[i][j]>g[i][l]+g[l][j]) 
			      g[i][j]=g[i][l]+g[l][j], r[i][j]=l;
	}
	if (ans==inf) printf("No solution.\n");
	else {
		printf("%d",da[1]);
		fo(i,2,len) printf(" %d",da[i]);
		printf("\n");
	}
}
int main()
{
	init();
	solve();
	return 0;
}
