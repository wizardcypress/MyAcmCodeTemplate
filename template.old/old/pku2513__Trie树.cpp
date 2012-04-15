#include<cstdio>
#include<cstring>
#define maxn 500010
using namespace std;
struct node
{
   int num;
   node *next[27];
   node()
   {
   	  num=0;
//指针不能memset,因为menset之后并不是NULL,运行时会出错
      for(int i=0;i<27;++i) 
         next[i]=NULL;
   }
};
node *root;
int n;
int id[maxn];
char l[11],r[11];
int fa[maxn];
int x,y;
int find(node *x,char *s)
{
	node *q;	
    if (strlen(s)==0)
	{
	   if (x->num==0)  
		{
	      x->num=++n;
		  return n;
	   }else return x->num;
	}else
	{
		int ptr=s[0]-'a'+1;
	   if(x->next[ptr]==NULL)
		{	
		   q=new node;       
		   x->next[ptr]=q;
		   return find(q,s+1);
	   }else return find(x->next[ptr],s+1);
	}
}
int get(int x)
{	
  int fx,xx;
  fx=x;
  while(fa[fx]!=fx) fx=fa[fx];
  while (x!=fx)
	{
    xx=fa[x];
	fa[x]=fx;
	x=xx;
  }
  return fx;
}
int main()
{
	freopen("test.in","r",stdin);	
	memset(id,0,sizeof(id));
	n=0;	
	root=new node;
	for(int i=1;i<=500000;++i) fa[i]=i;
	 while (scanf("%s %s\n",l,r)!=EOF)
	{
	    x=find(root,l);      
		y=find(root,r);				
		id[x]++;id[y]++;
		x=get(x); y=get(y);
		if(x!=y) fa[x]=y;//用并查集判断连通性
	}
	int id1num=0;
	int anc=get(1);
	 for(int i=1;i<=n;++i)
	{
         if(id[i]%2) ++id1num;
		 if(get(i)!=anc)  //如果不连通
		{
		    id1num=100000000;
			break;
		 }
	}
	 if (id1num<3) printf("Possible\n");
	 else printf("Impossible\n");
	return 0;
}
