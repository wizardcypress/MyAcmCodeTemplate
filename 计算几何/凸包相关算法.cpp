//凸包的graham算法
#include<stdio.h>
#include<math.h>
#include<algorithm>
#define MAXN 100010             
#define MAXNUM 2000000000
using namespace std;
typedef long long  int64;     //重定义，以防数据溢出 
struct  point
      { 
	     int x,y;	      
	     point(int ix,int iy):x(ix),y(iy){} //构造函数，便于生成临时对象 
	     point():x(0),y(0){}      //补充的构造函数，否则开数组时会发生错误 
		  int64 operator * (const point &that) const{  //叉积
		      return (int64)x*that.y-(int64)y*that.x;
		  }
		  point operator-(const point &that) const{	 	 
             return  point(x-that.x,y-that.y);		 
		  }
		  point operator+(const point &that)  const{
             return  point(x+that.x,y+that.y);            
		  }
	  };

point dot[MAXN],stack[MAXN];//dot是点的数组，stack是graham scan时的临时堆栈 
int n;
inline  int64 sqr(int x) {return (int64)x*x; } 
inline int64 dist(const point &p1,const point &p2)
   { return sqr(p1.x-p2.x)+sqr(p1.y-p2.y);   }
void init()
{
   point zero(MAXNUM,MAXNUM);  //用于寻找最下最左点的临时对象 
   int loca,x,y;           //loca是那个最点的位置 
   scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
       scanf("%d%d",&x,&y);
       dot[i].x=x;dot[i].y=y;
        if (dot[i].y<zero.y||dot[i].y==zero.y&&dot[i].x<zero.x)    
           zero=dot[i],loca=i;
    }
    zero=dot[loca];  dot[loca]=dot[0];  dot[0]=zero;     
}    
bool cmp(const point &p1,const point &p2)    
{    								    //sort的比较函数，在逆时针或更短的优先 
    int64 m=p1*p2;
    return m>0||
	m==0&&sqr(p1.x)+sqr(p1.y)<sqr(p2.x)+sqr(p2.y);
}
void graham()
{
    int top,i;   
    if (n<=2) return ;
    for (i=1;i<n;++i)  dot[i]=dot[i]-dot[0];
    sort(dot+1,dot+n,cmp);         //极角排序，按照cmp的定义，排完之后是逆时针的         
    for (i=1;i<n;++i)  dot[i]=dot[i]+dot[0];    
      stack[0]=dot[0];stack[1]=dot[1];      
       top=1;
       for (i=2;i<n;++i)  //此处遍历第2到第0的每一个
          {
		      while (top>0&&(dot[i]-stack[top-1])*(stack[top]-stack[top-1])>=0)    
		         --top;					// 记得此处是while 
              stack[++top]=dot[i];
		  }	
    n=top+1;
	for (i=0;i<n;++i) dot[i]=stack[i];   //把凸包复制到dot中去 
}
//***************************************************************
void area()   //求面积
{
   int next,i;
   int64 area=0;      
   for ( i=0;i<n;++i)   
   {
       area+=(dot[i]*dot[(i+1)%n])/2;         	         
   }
   printf("%d\n",area/50);  //逆时针，所以是正值 
}
//*****************************************************************
//求最远距离 
double height(const point &p1,const point &p2,const point &p3)
{
    double area=(p2-p1)*(p3-p1);  
    double len=sqr(p1.x-p2.x)+sqr(p1.y-p2.y);
    len=sqrt(len);
    return area/len;
}
template<class Type>
inline Type max(Type &p1,Type &p2)
{
   return p1>p2;
}
void farpair()    
{
    int64 maxl=0;
    int i,j,k;
    if (n==1)maxl=0; 
	 else if (n==2) maxl=dist(dot[0],dot[1]);
	 else {
	 	k=2;
        for (int i=0;i<n;++i)
        {
		   while (height(dot[i],dot[(i+1)%n],dot[k])<height(dot[i],dot[(i+1)%n],dot[(k+1)%n]))
		     k=(k+1)%n;
            maxl=max(maxl,max(dist(dot[i],dot[k]),dist(dot[(i+1)%n],dot[k])));            
         }
	 }    
   printf("%.2lf",sqrt(double(maxl)));
}
//*****************************************************************
int main()
{
    //freopen("farcow.in","r",stdin);
    // freopen("farcow.out","w",stdout);   
    init();	 
    graham();
   // farpair(); 
    return 0;
}
