#include<cstdio>
#include<cstring>
#define maxn 510
#define inf 1000000000
using namespace std;

int lk[maxn];
int lx[maxn],ly[maxn];
bool sx[maxn],sy[maxn];
int w[maxn][maxn];
bool link[maxn][maxn];
int slack[maxn];
int n,m,nx,ny,e;
int cs;
void input()
{
    int s,r,v;
	memset(w,0,sizeof(w));
    memset(link,0,sizeof(link)); //link 表示是否连通
        for(int i=0;i<e;i++)
    {
        scanf("%d%d%d",&s,&r,&v);
        if(v<0) continue;
        s++; r++;
        w[s][r]=v;
        link[s][r]=true;       
    }
	nx=n;
	ny=m;
}
bool dfs(int cur)
{
	int t;
	sx[cur]=true;
	for(int i=1;i<=ny;++i)
	if(!sy[i] && link[cur][i]){
		if((t=lx[cur]+ly[i]-w[cur][i])==0){//i在相等子图中
		sy[i]=true;  
			if(!lk[i] || dfs(lk[i])){
				lk[i]=cur;
				return true;
			}
		}else if(t<slack[i]) slack[i]=t;
	}
	return false;
}
//n<=m 左右分别有nx,ny个
void KM()
{
	memset(lk,0,sizeof(lk));
	memset(ly,0,sizeof(ly));
	for(int i=1;i<=nx;++i)
	{
		lx[i]=-inf;
		for(int j=1;j<=ny;++j)
			if(w[i][j]>lx[i]) lx[i]=w[i][j];
	}
	for(int i=1;i<=nx;++i)
    {
            for(int j=1;j<=ny;j++) slack[j]=inf;
            for(int l=1;l<=nx;l++)  //最多增加nx条边
        {
			memset(sx,0,sizeof(sx));
			memset(sy,0,sizeof(sy));
			if(dfs(i)) break;
   			int d=inf;
            for(int j=1;j<=ny;++j)
                if(!sy[j] && slack[j]<d) d=slack[j];
			for(int j=1;j<=nx;++j) if(sx[j]) lx[j]-=d;
			for(int j=1;j<=ny;++j){
                if(sy[j]) ly[j]+=d;
                else slack[j]-=d;
            }
		}
    }
}
void output()
{
	int ans=0,cnt=0;
	for(int i=1;i<=ny;++i){
        if(lk[i]) ans+=w[lk[i]][i],cnt++;
    }
    if(cnt!=n) ans=-1;
	printf("%d\n",ans);
}
int main()
{
	freopen("hdu2426.in","r",stdin);
    int cs=0;
    while(scanf("%d%d%d",&n,&m,&e)!=EOF)
    {
        printf("Case %d: ",++cs);
		input();
        if(n<=m && e>0) {
            KM();
     		output();
        }else printf("-1\n");
	}
	return 0;
}
