//bob
//中大资料集数据\五\第5章 2004年中山大学集训队内部个人选拔赛\5.20 BOB或BBO bob
#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
using namespace std;
int f[20010][14];
char b[20010];
int rnd[256];
int l2[10011];
int n;
void init()
{
   srand(unsigned(time(NULL)));  	
    for (int i=0;i<=255;++i)
       rnd[i]=rand();       
    l2[0]=-1;
    for (int i=1;i<=10000;++i) l2[i]=l2[i-1]+((i&(-i))==i);
}
bool compare(int x,int y)
{
	int k=l2[n];
	int ix=x;
     while (k>=0)
     {
     	if (x+(1<<k)<=ix+n)
     	{
	     if (f[x][k]==f[y][k])
	     {		 
	        x+=(1<<k);
	        y+=(1<<k);
		 }
     	}
		 k--;		 
	 }
   if (b[x]<b[y]) return true;
   else return false;
}
void work()
{
	memset(f,0,sizeof(f));
    for (int i=1;i<=n;++i)
       f[i][0]=rnd[b[i]];
    for (int j=1;j<=l2[n];++j)
      for (int i=1;i<=n;++i)
         f[i][j]=f[i][j-1]*rnd[j] ^ f[i+(1<<(j-1))][j-1];
    int q=1;
    for (int i=2;i<=n;++i)    
	    if (compare(i,q)) q=i;
	for (int i=q;i<q+n;++i)	
	  printf("%c",b[i]);
	  printf("\n");
}
int main()
{
   freopen("bob.in","r",stdin);
   freopen("bob.out","w",stdout);
   int t;
     scanf("%d\n",&t);	
	 init();     
     while (t--)     
     {
     	b[0]=' ';
	     scanf("%s\n",b+1);   
	     n=strlen(b)-1;
	     for (int i=1;i<=n;++i)	     
	        b[i+n]=b[i];
        b[2*n+1]='\0';
        work();        
	 }
   return 0;
}
