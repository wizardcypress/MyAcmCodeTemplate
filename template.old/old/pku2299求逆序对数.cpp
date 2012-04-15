#include <stdio.h>
#include<string.h>
using namespace std;
int n;
int a[500010],tmp[500010];
long long ans;
void mergsort(int l,int r)
{
   if(l<r)
   {
       mergsort(l,(l+r)/2);
	   mergsort((l+r)/2+1,r);
	   int *a1=a+l-1;
	   int *a2=a+(l+r)/2;
	   int *a3=tmp+l-1;
	   int l1=1,l2=1,l3=0,c1=(l+r)/2-l+1,c2=r-(l+r)/2;
       while(l3<r-l+1) 
	   {
	       if((l1>c1||a1[l1]>a2[l2])&&(l2<=c2))
		   {
		      a3[++l3]=a2[l2++];
			  ans+=c1-l1+1;		  
		   }
		   else if((l2>c2||a1[l1]<a2[l2])&&(l1<=c1))
		   {
		       a3[++l3]=a1[l1++];			  
		   }else{
		       if (l1>c1) a3[++l3]=a2[l2++];
			   else a3[++l3]=a1[l1++];
		   }
	   }
	   for(int i=l;i<=r;++i)
		   a[i]=tmp[i];
   }
}
int main()
{
	freopen("test.in","r",stdin);
	scanf("%d",&n);
	int x;
	while(n!=0)
	{         
		for(int i=1;i<=n;++i)
           scanf("%d",&a[i]);
		ans=0;
		mergsort(1,n);
		printf("%lld\n",ans);
	   scanf("%d",&n);
	}
	return 0;
}
