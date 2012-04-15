#include<cstdio>
#include<cstring>
#define MAXN 101
using namespace std;
double a[MAXN][MAXN+1];
double x[MAXN];
int n,m;
inline double ab(double x)
{
  return x<0?-x:x;
}
void swap(double &x,double &y)
{
   double tm=x;x=y;y=tm;
}
int gaosi()
{
	double mx;
	int w;
	bool flag=true;
   for(int k=1;k<=n;++k)
   {
	   mx=ab(a[k][k]);w=k;
      for(int i=k+1;i<=n;++i)
		  if(ab(a[i][k])>mx){
		  mx=ab(a[i][k]);
		  w=i;
	      }
	  for(int i=k;i<=n+1;++i) swap(a[w][i],a[k][i]);	 
	  for(int i=1;i<=n;++i)
      if(i!=k){
		  for(int j=1;j<=n+1;++j)
			  if(j!=k)			  
			     a[i][j]=a[i][j]*a[k][k]-a[k][j]*a[i][k];
		  a[i][k]=0;
	   }
   }   
   for(int i=1;i<=n;++i)
   {
   	if(!a[i][i]&&a[i][n+1])  return -1;//无解 
   	 else if(!a[i][i]&&!a[i][n+1]) return 0;//无数解 
   	x[i]=a[i][n+1]/a[i][i];
   }
   return 1;
}
int main()
{
	freopen("test.in","r",stdin);
	    scanf("%d",&n);	   
		for(int i=1;i<=n;++i)
	    {
		    for(int j=1;j<=n;++j)		
				scanf("%lf",&a[i][j]);			
			scanf("%lf",&a[i][n+1]);		
		}
		int d=gaosi();
	  if(d==-1) printf("No Answer!\n");
	   else if(d==0) printf("Multiply Answers\n");	   
	   else {
		   for(int i=1;i<=n;++i)
			    printf("x%d = %f\n",i,x[i]);		
	   }
	return 0;
}
