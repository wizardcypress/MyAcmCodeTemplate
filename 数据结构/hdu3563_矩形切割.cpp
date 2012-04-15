#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXD 12
#define MOD 14121413
using namespace std;
typedef long long cord_t;//cordinate type
struct REG{
	cord_t st[MAXD],ed[MAXD];
	REG *pre,*next;	
};
REG *head,*tail,*cur;
int n;
int dim;
cord_t ans;
bool cross(REG &x,REG &y)
{
	for(int i=0;i<dim;i++)
	{
		if(x.ed[i]<=y.st[i] || y.ed[i]<=x.st[i])
			return false;
	}
	return true;
}
void add(REG &x)
{
	REG *cur=new REG;
	*cur=x;
	cur->pre=head;
	cur->next=head->next;
	head->next->pre=cur;
	head->next=cur;
}
void cut(REG x,REG y)
{
	for(int i=0;i<dim;++i)
	{
		cord_t tmp;
		cord_t k1=max(x.st[i],y.st[i]);		
		cord_t k2=min(x.ed[i],y.ed[i]);
		if(x.st[i]<k1) {
			tmp=x.ed[i];
			x.ed[i]=k1;
			add(x);
			x.ed[i]=tmp;
		}
		if(k2<x.ed[i]) {
			tmp=x.st[i];
			x.st[i]=k2;
			add(x);
			x.st[i]=tmp;
		}
		x.st[i]=k1;
		x.ed[i]=k2;
	}
}
void init()
{
	head=new REG;
	tail=new REG;
	head->pre=tail->next=NULL;
	head->next=tail;
	tail->pre=head;	
}
void solve()
{
	cur=new REG;
	for(int i=1;i<=n;++i)
	{				
		for(int j=0;j<dim;j++)	scanf("%I64d",&cur->st[j]);
		for(int j=0;j<dim;j++)	scanf("%I64d",&cur->ed[j]);
		
		for(int j=0;j<dim;j++)
		{
			int d1=cur->st[j];
			int d2=cur->ed[j];
			cur->st[j]=min(d1,d2);
			cur->ed[j]=max(d1,d2);
		}
		for(REG *q=head->next;q!=tail;q=q->next)
		{			
			if(cross(*q,*cur)){
				cut(*q,*cur);
				/* delete q */
				q->pre->next=q->next;
				q->next->pre=q->pre;
				delete q;
			}	
		}
		/* add cur before tail */
		add(*cur);
	}
	
	ans=0;
	for(REG *q=head->next;q!=tail;q=q->next)
	{
		cord_t sum=1;
		for(int i=0;i<dim;++i)		
			sum=(sum*((q->ed[i]-q->st[i])%MOD))%MOD;
		ans=(ans+sum)%MOD;
	}
	printf("%I64d\n",ans);
}
void clear()
{
	for(REG *q=head->next;q!=tail;q=q->next)
		delete q->pre;
	delete tail;
}
int main()
{	
	freopen("hdu3563.in","r",stdin);	
	while(scanf("%d%d",&n,&dim)!=EOF)
	{
		init();
		solve();
		clear();		
	}
	return 0;
}
