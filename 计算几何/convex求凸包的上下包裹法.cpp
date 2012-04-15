//convex
//中大资料集数据\二\第二章\2.3_凸边形外壳
#include<stdio.h>
#include<algorithm>
#define MAXN 100010
using namespace std;
struct point
{
    int x,y;
    point(int ix,int iy):x(ix),y(iy){}
    point(){}
	int operator*(const point &that)
	{
	    return x*that.y-that.x*y;
	}   
	point operator-(const point &that)
	{
	    return point(x-that.x,y-that.y);
	}
	bool operator==(const point &that)
    {
	   return x==that.x&&y==that.y;
	}
};
int n;
point dot[MAXN];
point stk1[MAXN],stk2[MAXN];
bool cmp(const point &p1,const point &p2)
{
   return p1.x<p2.x||p1.x==p2.x&&p1.y<p2.y;
}
void graham_scan()
{
   stk1[1]=dot[1]; stk1[2]=dot[2];
   stk2[1]=dot[1]; stk2[2]=dot[2];
   int top1=2,top2=2;
    for (int i=3;i<=n;++i)   
     {
	     while (top1>1&&(dot[i]-stk1[top1-1])*(stk1[top1]-stk1[top1-1])<=0)
	        top1--;
         stk1[++top1]=dot[i];
         while (top2>1&&(dot[i]-stk2[top2-1])*(stk2[top2]-stk2[top2-1])>=0)
             top2--;
         stk2[++top2]=dot[i];
	 }   
   for (int i=1;i<=top2;++i)
      dot[i]=stk2[i];
   for (int i=top1-1;i>1;--i)
      dot[top2+top1-i]=stk1[i];
   n=top2+top1-2; 
}
void area()
{
	 int ans=0;	 	
    for (int i=1;i<n;++i)
       ans+=dot[i]*dot[i+1];
    ans+=dot[n]*dot[1];
    printf("%.1lf\n",double(ans)/2);
}
int main()
{
   freopen("convex.in","r",stdin);
   freopen("convex.out","w",stdout);
   int t;
      scanf("%d",&t);
      while (t--)      
      {
	      scanf("%d",&n);
	       for (int i=1;i<=n;++i)
	         scanf("%d%d",&dot[i].x,&dot[i].y);
         sort(dot+1,dot+n+1,cmp);
           graham_scan();
          area();
	  }
   return 0;
}
