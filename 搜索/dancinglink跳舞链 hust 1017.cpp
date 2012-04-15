#include<cstdio>
#include<algorithm>
#include<cstring>
#define INF 1000000000
#define N 1010
using namespace std;
int n,m;
int a[N][N],b[N][N];
int l[N*N],r[N*N],c[N*N],u[N*N],d[N*N],name[N*N];
//c是表示该点所属的列，name则表示该节点的一些属性，可以是行，也可以是所代表的取的值。
bool used[N*N]; 
int s[N],o[N];
int h,tot;
void add(int x,int &head,int flag) /*add x to head,flag==0 add row*/
{
	if(flag==0){ //row
		if(head==-1) //行的第一个
		{
			head=x;
			l[x]=r[x]=x;
		}
		l[x]=l[head];
		r[l[head]]=x;
		r[x]=head;
		l[head]=x;
	}else{
		u[x]=u[head];
		d[u[head]]=x;
		d[x]=head;
		u[head]=x;
	}
}
void input()
{
	int x;
	tot=h=0;
	l[h]=r[h]=h;
	for(int j=1;j<=m;j++)
	{
		add(++tot,h,0);
		u[tot]=d[tot]=c[tot]=tot;
	}
	memset(s,0,sizeof(s));
	for(int i=1;i<=n;i++)
	{
		int curhead=-1,num;
		scanf("%d",&num);
		for(int j=1;j<=num;j++)
		{
			scanf("%d",&x);			
			if(j==1) {
				add(++tot,curhead,0);
				add(tot,x,1);
				c[curhead]=x; s[x]++; name[curhead]=i; //这里不要忘记了添加c,name,s的值
			}else{
				tot++;
				c[tot]=x; name[tot]=i; s[x]++;
				add(tot,curhead,0);
				add(tot,c[tot],1);
			}
		}
	}
	memset(used,0,sizeof(used));
}

void cover(int col)
{
	  r[l[col]]=r[col];
	  l[r[col]]=l[col];
	  for(int row=d[col];row!=col;row=d[row])
	  	for(int j=r[row];j!=row;j=r[j])
	  	{
			   u[d[j]]=u[j];
			   d[u[j]]=d[j];
			   s[c[j]]--;
		}  
}
void uncover(int col)
{    
	for(int row=u[col];row!=col;row=u[row])
		for(int j=l[row];j!=row;j=l[j])	
		{     
			 u[d[j]]=j;
			 d[u[j]]=j;
			 s[c[j]]++;
		 }			 
     l[r[col]]=col;
     r[l[col]]=col;
}
void output()
{
	int num=0;
	for(int i=1;i<=n;i++)
		num+=used[i];
    printf("%d",num);
    for(int i=1;i<=n;++i)
     if(used[i]) printf(" %d",i);
     printf("\n");
} 
bool search()
{
	 if(r[h]==h) {
		     output();		  
		     return true;
	 }else{
			 //select minimal column
		    int mm=INF,col;		    
		    for(int i=r[h];i!=h;i=r[i])
		    	if(s[i]<mm) mm=s[i],col=i;
		    	
		     //cover that column
		     cover(col);
		     for(int row=d[col];row!=col;row=d[row])
		     {		     
				 used[name[row]]=true;
				 for(int j=r[row];j!=row;j=r[j]) cover(c[j]);			     
			     if(search()) return true;
			     for(int j=l[row];j!=row;j=l[j]) uncover(c[j]);
         		 used[name[row]]=false;	             
			 }
			 uncover(col);
			return false;
	}
}
bool check()
{
	for(int j=1;j<=m;j++)
		if(s[j]==0) return false;
	return true;
}
int main()
{
	freopen("hust1017.in","r",stdin);
		  while(scanf("%d%d",&n,&m)!=EOF)
		  {
	       input();	       
	       if(!check() || !search()) printf("NO\n");
          }
	  return 0;
	}
