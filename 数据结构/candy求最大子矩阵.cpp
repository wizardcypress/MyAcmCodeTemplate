//candy
/*
   请看2003年国家集训队论文  王知昆  
   《浅谈用极大化思想解决最大子矩形问题》 
   用O（NM）来实现求最大子矩阵
   
   我对这个方法的理解：以悬线为中心，向两边扩展，直到卡住悬线为止，卡住的
   位置可能是当前行，也可能是之前的行，那么当所有的悬线都计算一遍后，
   最大的有效子矩阵必然在里面。 
*/
#include<stdio.h>
#include<memory>
#define MAXN 1001   //范围 
using namespace std;
int s[MAXN][MAXN];
int l[MAXN],r[MAXN],height[MAXN];
int n,m,leftmost,rightmost,acc,res,now,i,j;
int main()
{
	freopen("candy.in","r",stdin);
	freopen("candy.out","w",stdout);
	scanf("%d%d",&n,&m);
	 for ( i=1;i<=n;++i)
	     l[i]=1,r[i]=m,height[i]=0; //初始的时候悬线高度都为0，因此可以延伸到两端 
    memset(s,0,sizeof(s));//s是记录以i,j为右下角的矩阵的总值 
		 res=0;
    for ( i=1;i<=n;++i)
    {
	   leftmost=1; 
	   acc=0;
        for ( j=1;j<=m;++j)      
        {
		   scanf("%d",&now);
		   acc+=now;
		   s[i][j]=s[i-1][j]+acc;
		    if (now){             // 如果当前不是障碍点 
			    ++height[j];     //j列的高度+1 
		       if (leftmost>l[j]) l[j]=leftmost; //修改卡住当前悬线的左边位置 
		    	}
				else {          //如果当前是障碍点 
			    height[j]=0;     
			    leftmost=j+1;  //那么j之后的点的悬线可能被j卡住，所以记录下来 
				l[j]=1;r[j]=m;  //既然悬线高度是0，那么就没有可以卡住的点 
     //此处使得可以卡住j的障碍都是在j的height范围以内的点，从height开始重新计算左右边界 
			 }
		 }
	   rightmost=m;
        for (j=m;j>=1;--j)
		{
		    if (height[j]){     //如果不是障碍点 
			   if (rightmost<r[j]) r[j]=rightmost;  // 修改卡住当前悬线右边的位置 
             acc=s[i][r[j]]-s[i-height[j]][r[j]]-s[i][l[j]-1]+s[i-height[j]][l[j]-1];
             //统计子矩阵和 
              if (acc>res)  res=acc;
			}
			 else {
			    rightmost=j-1;//如果是障碍点，记录当前行右边可能被卡住的位置 
			 }
		}
	}
	printf("%d\n",res);
   return 0;
}
