/*
  一張圖上每條邊都有權重，最小平均值環是「權重除以邊數」最小的環，可能有許多只。
最小平均值環也可以視作是最小比率環的特例，當每條邊的第二組權重都等於 1 的時候。

  令V為圖上的所有點構成的集合，n為圖上的點數。
圖上任意取一個點作為起點，d(k, i)為起點走k條邊到達i的最短路徑。
                                     d(n, i) - d(k, i)
平均權重 = min  max   ─────────────────
           i∊V 0≤k≤n-1      n - k
如果圖上有不連通的部分，可以使用最短路徑 Johnson's Algorithm 所提到的技巧，在圖上另外新增一個起點，並且增加起點連到圖上其他點的邊，其權重皆設為零。如此一來，圖上的每一個點都可以由起點走到，而且最小平均值環也不會改變。

uva 11090
 */
#include<cstdio>
#include<cstring>
#define maxm 2600
#define maxn 55
#define inf 1000000000
typedef long long ll;
using namespace std;

struct edge{
  int u,v,c,next;  
}e[maxm];
int beg[maxn];
int n,cs,ne,st,m;
ll d[maxn][maxn];
int c[maxn][maxn];
int dis[maxn];
void add(int u,int v,int c)
{
  e[ne].u=u; e[ne].v=v;
  e[ne].c=c;
  e[ne].next=beg[u];
  beg[u]=ne++;
}
double solve()
{
  bool flag=false;
    int u,v;
    memset(dis,0,sizeof(dis)); //先判是否有环
  for(int i=1;i<=n;i++)
    for(int j=0;j<ne;j++)
      {
            u=e[j].u; v=e[j].v;
          if(dis[u]-1<dis[v])        dis[v]=dis[u]-1;
      }
    for(int j=0;j<ne;j++)
      {
            u=e[j].u; v=e[j].v;
            if(dis[u]-1<dis[v])      {
              flag=true;
              break;
            }
      }
    if(!flag) return  -1; //

    
  st=n+1;
  for(int i=1;i<=n;i++) add(st,i,0);   //增加一个点,到所有点权值为0,对结果不影响
  n++;
  for(int k=0;k<=n;k++)
    for(int i=1;i<=n+1;i++) d[k][i]=inf;
  d[0][st]=0;    //d[k][i]表示从st到i走过k条边的最短路径
  for(int k=1;k<=n;k++)
    {
    for(int i=0;i<ne;i++)
      {
        int u=e[i].u,v=e[i].v;
        if(d[k-1][u]+e[i].c<d[k][v]) d[k][v]=d[k-1][u]+e[i].c;  //d[k][j]=min{d[k-1][i]+c[i][j]}
      }
    }  
  double minr=1e100,maxr,tmr; //ans=min{  max { (d[n][j]-d[k][j])/(n-k)  | k in [0,n-1] } | j  in [1,n] }
        for(int j=1;j<=n;j++)
       {
         maxr=-1e100;
         for(int k=0;k<n;k++)
           {
             tmr=1.0*(d[n][j]-d[k][j])/(n-k);
             if(tmr>maxr)      maxr=tmr;
           }
         if(maxr<minr) minr=maxr;
       }
    return minr;
}
void input()
{
  int x,y,cost;
  scanf("%d%d",&n,&m);
  memset(beg,255,sizeof(beg));
  ne=0;
  for(int i=1;i<=n;i++)
    for(int  j=1;j<=n;j++) c[i][j]=inf;
  
  for(int i=0;i<m;i++) {
        scanf("%d%d%d",&x,&y,&cost);
        if(cost<c[x][y]) c[x][y]=cost;
  }
  for(int i=1;i<=n;i++)
    for(int j=1;j<=n;j++)
      if(c[i][j]!=inf) add(i,j,c[i][j]);
}
int main()
{
  //freopen("11090.in","r",stdin);
  scanf("%d",&cs);
  for(int t=1;t<=cs;t++)
    {
      printf("Case #%d: ",t);
      input();
      double ans=solve();
      if(ans<0) {
        printf("No cycle found.\n");
        if(ans!=-1) while(1) ;
      }
      else printf("%.2lf\n",ans);
    }
  return 0;
}

