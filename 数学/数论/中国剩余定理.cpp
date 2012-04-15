#include<cstdio>
#include<cstring>
#define MAXN 10010
using namespace std;
int m[MAXN],M;
int a[MAXN];
int ans,n;
void extend_gcd(int a,int b,int &d,int &x,int &y)
{
  if(!b) { d=a;x=1;y=0; }
   else {
      extend_gcd(b,a%b,d,y,x);
	  y-=x*(a/b);
   }
}
int china(int n,int a[],int m[])
{
   int x,y,wi,d;
   int ret=0;
   M=1;
   for(int i=1;i<=n;++i) M*=m[i];
   for(int i=1;i<=n;++i)
   {
       wi=M/m[i];
	   extend_gcd(wi,m[i],d,x,y);
	   ret=(ret+wi*a[i]*x)%M;
   }
   return ret;
}
int main()
{
	freopen("test.in","r",stdin);
	   scanf("%d",&n);	    
	   for(int i=1;i<=n;++i)    	
	      scanf("%d%d",a+i,m+i);
	   ans=china(n,a,m);
	   printf("%d\n",ans);
	return 0;
}
