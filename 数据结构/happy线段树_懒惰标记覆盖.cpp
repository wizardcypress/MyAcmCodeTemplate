#include<cstdio>
#include<cstring>
#define size 2*131072
#define INF 2000000000
using namespace std;
int n,m,ll,rr,z,r1,r2;
char tsk;
int mx[size],num[size],c[size];
void build(int x,int l,int r)
{
   if(l==r)
	{
      mx[x]=0;num[x]=l;c[x]=0;
   }else {
      build(x*2,l,(l+r)/2);
	  build(x*2+1,(l+r)/2+1,r);
	  mx[x]=c[x]=0;
	  num[x]=num[x*2];
   }
}
void insert(int x,int l,int r,int add)
{
   if(r<ll||l>rr) return ;
   if(ll<=l&&rr>=r) {
      c[x]+=add;
	  mx[x]+=add;
   }else {
      insert(x*2,l,(l+r)/2,add);
	  insert(x*2+1,(l+r)/2+1,r,add);
	  if(l<r){
	     if(mx[x*2]>=mx[x*2+1]) mx[x]=mx[x*2]+c[x],num[x]=num[x*2];
		  else mx[x]=mx[x*2+1]+c[x],num[x]=num[x*2+1];
	  }
   }
}
int find(int x,int l,int r,int &r2)
{
   if(r<ll||l>rr) return -INF;
   if(ll<=l&&rr>=r)
   {	
	   r2=num[x];
	   return mx[x];
   }else {
	  int d1,d2,t1,t2;
	   d1=find(x*2,l,(l+r)/2,t1);
	   d2=find(x*2+1,(l+r)/2+1,r,t2);
	   if(d1>=d2) {
		   r2=t1;
		   return d1+c[x];
	   }else{
		   r2=t2;
		   return d2+c[x];
	   }
   }
}
int main()
{
	freopen("happy.in","r",stdin);
	freopen("happy.out","w",stdout);
	 while(scanf("%d%d\n",&n,&m),n+m)
	{
		 memset(c,0,sizeof(c));
		 memset(num,0,sizeof(num));
		 memset(mx,0,sizeof(mx));		
		 build(1,1,n);
	    for(int i=1;i<=m;++i)     
		{
		  scanf("%c",&tsk);
		  if(tsk=='I') {
		     scanf("%d%d%d\n",&ll,&rr,&z);
			 insert(1,1,n,z);			
		  }
		  else{
			  scanf("%d%d\n",&ll,&rr);			 
		     r1=find(1,1,n,r2);			
			 printf("%d\n",r1);			
			 ll=rr=r2;
			 insert(1,1,n,-r1);
		  }
		}
	}
	return 0;
}
