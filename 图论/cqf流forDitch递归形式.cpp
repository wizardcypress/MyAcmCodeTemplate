//cqf_flow_demo_for_ditch
#include<stdio.h> 
#include<memory>
#define MAXN 60005      
#define MAXM 1000001    
#define MAXNUM 2000000000
using namespace std;
  struct node
  {  int v,c,f,next;}org_node[2*MAXM+1]; 
int n,m,num=0,s,t,remain=0,xp;
int unq[MAXN];
node *edge=&org_node[MAXM];
int beg[MAXN],rec[MAXN],next[MAXN];
int a[MAXM],b[MAXM],c[MAXM];
void init()
{
    scanf("%d%d",&m,&n);
    for (int i=0;i<m;++i)
	{	scanf("%d%d%d",&a[i],&b[i],&c[i]),--a[i],--b[i],remain+=c[i]; }
	memset(beg,0,sizeof(beg));	
	memset(unq,0,sizeof(unq));
}
void insert(int x,int y,int c)
{ 
   ++num;
   edge[num]=(node){y,c,0,beg[x]};
   beg[x]=num;
   edge[-num]=(node){x,0,0,beg[y]};
   beg[y]=-num;
}
void buildgraph()
{
    for (int i=0;i<m;++i)
      insert(a[i],b[i],c[i]);
    for (int i=0;i<n;++i)
        rec[i]=beg[i];
}
bool flow(int x,int now)
{
	if (x==t){  xp=now;  return true;}
	unq[x]=remain;
    for (int i=rec[x];;)
	{
	   if (edge[i].f<edge[i].c&&unq[edge[i].v]!=remain)	  
             if (flow(edge[i].v,min(now,edge[i].c-edge[i].f)))
             {
			    edge[i].f+=xp;
			    edge[-i].f=-edge[i].f;
			    rec[x]=i;
			    return true;
			 }   
	    i=edge[i].next==0?beg[x]:edge[i].next;
          if (i==rec[x]) return false;
	}
}
void maxflow()
{
    while (flow(s,MAXNUM)) remain-=xp;
}
void print()
{
    long long  sum=0;
    for (int i=beg[s];i!=0;i=edge[i].next)
        sum+=edge[i].f;
    printf("%d\n",sum);
}
int main()
{
   freopen("ditch.in","r",stdin);
   freopen("ditch.out","w",stdout);
   init();
   s=0;t=n-1;
   buildgraph();      
   maxflow();       
   print();
   fclose(stdin);
   fclose(stdout);
   return 0;
}
