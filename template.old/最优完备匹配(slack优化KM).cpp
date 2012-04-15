/*
朴素的实现方法，时间复杂度为O(n^4)——需要找O(n)次增广路，每次增广最多需要修改O(n)次顶标，
每次修改顶标时由于要枚举边来求min值，复杂度为O(n^2)。实际上KM算法的复杂度是可以做到O(n^3)的。
我们给每个Y顶点一个“松弛量”函数slack，每次开始找增广路时初始化为无穷大。
在寻找增广路的过程中，检查边(i,j)时，如果它不在相等子图中，
则让slack[j]变成原值与lx[i]+ly[j]-g[i][j]的较小值。
这样，在修改顶标时，取所有不在交错树中的Y顶点的slack值中的最小值作为d值即可。
但还要注意一点：由于修改顶标后，所有在交错树中的lx[i]都减d，因此要把所有的slack值都减去d。
*/
#include<iostream>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=201;
const long inf=1000000000;

long w[maxn];
long lx[maxn],ly[maxn];
bool bx[maxn],by[maxn];
long n,g[maxn][maxn];
long slack[maxn];

void init()
{
	fo(i,1,n) 
		fo(j,1,n) scanf("%d",&g[i][j]);
}
bool find(long x)
{
	bx[x]=1;
	fo(i,1,n) {
		if (!by[i] && lx[x]+ly[i]==g[x][i]) {
		   by[i]=1;
		   if (!w[i] || find(w[i])) {
			   w[i]=x;
			   return 1;
		   }
		   continue;
	    }
		if (lx[x]+ly[i]>g[x][i]) slack[i]=slack[i]<lx[x]+ly[i]-g[x][i]?slack[i]:lx[x]+ly[i]-g[x][i];
	}
	return 0;
}
void solve()
{
	fo(i,1,n) {
		lx[i]=ly[i]=0;
		fo(j,1,n) 
			if (g[i][j]>lx[i]) lx[i]=g[i][j];
	}
	memset(w,0,sizeof(w));
	for (long l=1,min; l<=n; ++l) {
		fo(i,1,n) slack[i]=inf;
		for (;;) {
			memset(bx,0,sizeof(bx));
			memset(by,0,sizeof(by));
			if (find(l)) break;
			min=inf;
			fo(i,1,n) 
				if (!by[i]) min=min<slack[i]?min:slack[i];
			/*fo(i,1,n) if (bx[i]) 
				fo(j,1,n) if (!by[j])
				    min=lx[i]+ly[j]-g[i][j]<min?lx[i]+ly[j]-g[i][j]:min;*/
			fo(i,1,n) {
				if (bx[i]) lx[i]-=min;
				if (by[i]) ly[i]+=min;
				slack[i]-=min;
			}
		}
	}
	long ans=0;
	fo(i,1,n) ans+=g[w[i]][i];
	printf("%d\n",ans);
}
int main()
{
	while (scanf("%d",&n),n!=0) {
		init();
		solve();
	}
	return 0;
}
