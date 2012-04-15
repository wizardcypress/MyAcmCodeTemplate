#include<cstdio>
#include<cstring>
#define M 10010
using namespace std;
int l[M],r[M],pre[M],next[M],key[M];
int n,len,root,pr,ne;
int x;
void insert(int &x,int num)
{
    if(x==0)
	{
		x=++len;
	    l[x]=r[x]=0;
		pre[x]=pr;
		next[x]=ne;
       //给x的前趋后趋都标志一下
		next[pr]=x;
        pre[ne]=x;
       //
		key[x]=num;
	}
	else{
		if(num<=key[x])	 ne=x,insert(l[x],num);
		else pr=x,insert(r[x],num);
	}
}
void small_big()
{
    int cur=root;
	while(pre[cur]!=0) cur=pre[cur];

     while(cur!=0)
	{
		 printf("%d ",key[cur]);
	    cur=next[cur];
	 }
	printf("\n");
}
void big_small()
{
   int cur=root;
	while(next[cur]!=0) cur=next[cur];

     while(cur!=0)
	{
		 printf("%d ",key[cur]);
	    cur=pre[cur];
	 }
	printf("\n");
}
int main()
{
	freopen("test.in","r",stdin);
	  len=0;
	  root=0;
     scanf("%d",&n);
	 for(int i=1;i<=n;++i)
	{	
		scanf("%d",&x);
		pr=ne=0;
		insert(root,x);
	}
	small_big();
	big_small();
	return 0;
}
