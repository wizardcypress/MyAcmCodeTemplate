#include<cstdio>
#include<iostream>
#include<cstring>
#define MAX_LOG 16   //最大可能的log值，注意中间运算的结果可能会超出题目数据范围，所以这个值最好设大点
#define MAX(x,y) ((x)>(y)?(x):(y))
using namespace std;
int n;
int f[MAX_LOG][MAX_LOG];  //记录2^x(X)2^y的值
//declaration
int nim_mul_normal(int x,int y);
int nim_mul_power(int x,int y);
//
int nim_mul_power(int x,int y) //求2^x和2^y的nim积
{	
	int ret=1;
	if(x==0) return 1<<y;
	if(y==0) return 1<<x;
	for(int i=0;x>0 || y>0;++i,x>>=1,y>>=1)
	{
		if((x&1)+(y&1)==1)		
			ret=ret*(1<<(1<<i));		
		if((x&1)+(y&1)==2)
			ret=nim_mul_normal(ret,(1<<(1<<i))/2*3);  //如果有相同的，要用一般nim积来算
	}
	return ret;
}
int nim_mul_normal(int x,int y)  //求一般数的nim积
{	
	int ret=0;		
	if(x==1) return y;
	if(y==1) return x;	
	for(int i=0;(1<<i)<=x;++i)
		if(x&(1<<i))
		for(int j=0;(1<<j)<=y;++j)
			if(y&(1<<j))
				ret^=f[i][j];
	return ret;		
}
void pre_cal_f()  //预先计算出所有2^i(X)2^j的值
{
	memset(f,255,sizeof(f));
	for(int i=0;i<MAX_LOG;++i) f[i][0]=f[0][i]=(1<<i);
	
	for(int i=1;i<MAX_LOG;++i)
		for(int j=i;j<MAX_LOG;++j)
			f[i][j]=f[j][i]=nim_mul_power(i,j);
}
void solve()
{
	int ans=0;	
	for(int i=0;i<n;++i)
	{
		int x,y,z;
		scanf("%d%d%d",&x,&y,&z);		
		ans^=nim_mul_normal(nim_mul_normal(x,y),z);
	}
	if(ans==0)   printf("Yes\n"); //先手必败
	else printf("No\n");
}
int main()
{
	freopen("pku3533.in","r",stdin);
	pre_cal_f();
	while(scanf("%d",&n)!=EOF)	
		solve();	
	return 0;
}
