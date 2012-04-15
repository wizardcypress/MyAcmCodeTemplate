#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<algorithm>
#define MAXN 20010
using namespace std;
typedef long long   LL;
struct point{
  int x,y1,y2;
  int add;
  point(){}
  point(int ix,int iy1,int iy2,int iadd):x(ix),y1(iy1),y2(iy2),add(iadd){}
}a[MAXN];
point tmp;
int n,m,x1,y1,x2,y2,ll,rr,mxy;
int cl[65546],c[65546];
int add;
LL ans;
int mxl=-1;
bool cmp(const point &p1,const point &p2)
{
   return p1.x<p2.x||(p1.x==p2.x&&p1.add<p2.add);
}
void init()
{
    scanf("%d",&n);
	mxy=-1;
	for(int i=1;i<=n;++i)
	{
	   scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
	   y1++;y2++;
	   if(y2>mxy) mxy=y2;
	   if(y1>mxy) mxy=y1;
	   a[i]=point(x1,y1,y2,1);
	   a[i+n]=point(x2,y1,y2,-1);
	}    
	sort(a+1,a+2*n+1,cmp);
}
void insert(int x,int l,int r)
{   
   if(r<ll||rr<l) return ;  
   if(ll<=l&&rr>=r){
      if(add>0) {
		  c[x]++; cl[x]=r-l+1;
		  return ;
	  }else {
		  c[x]--;
		 if(!c[x])		    
		 {
			 if(l<r) cl[x]=cl[x*2]+cl[x*2+1];		  		 
		     else cl[x]=0;
		 }
		  return ;
	  }
   }
      insert(x*2,l,(l+r)/2);
	  insert(x*2+1,(l+r)/2+1,r);
	  if(!c[x]) cl[x]=cl[x*2]+cl[x*2+1];   
}
void work()
{
   memset(cl,0,sizeof(cl));
   memset(c,0,sizeof(c));
   ans=0;
   ll=a[1].y1;rr=a[1].y2-1; add=a[1].add;
   insert(1,1,mxy);   
   for(int i=1;i<2*n;++i)
   {	   
       ans+=(LL)cl[1]*(a[i+1].x-a[i].x);	  	
	   ll=a[i+1].y1; rr=a[i+1].y2-1;
	   add=a[i+1].add;	   
	   insert(1,1,mxy);    
   }
   printf("%lld\n",ans);
}
int main()
{
	freopen("mar.in","r",stdin);
	freopen("mar.out","w",stdout);
	  init();	    
	  work();
	return 0;
}
