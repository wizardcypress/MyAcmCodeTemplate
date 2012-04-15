#include<cstdio>
#include<cstring>
#define maxn 10010
#define inf 1000000000
using namespace std;
int n;
/*link*/
int dep[maxn],link_num[maxn];
int link_len[maxn];
int from[maxn];/*the direct father*/
int edge2point[maxn];
int fa[maxn];
int nlink;
/*lca*/
int dfn[maxn*2];
int rmq[maxn*2][14];
int fst_pos[maxn];
int dfn_len;
/*graph*/
struct edge{
	int v,c,id,next;
}e[maxn*2];
int val[maxn];/*value of the point*/
int ne;
int beg[maxn];
/*segment tree*/
struct seg_node{
	int max;
	seg_node *left,*right;
};
seg_node *seg[maxn];
int ll,rr;
//
void add(int u,int v,int c,int id)
{	
	e[ne].v=v;
	e[ne].next=beg[u];
	e[ne].c=c;
	e[ne].id=id;
	beg[u]=ne++;
}
void input()
{
	int x,y,c;
	memset(beg,255,sizeof(beg));
	ne=0;
	scanf("%d",&n);
	for(int i=1;i<n;++i)
	{
		scanf("%d%d%d",&x,&y,&c);
		add(x,y,c,i);
		add(y,x,c,i);
	}
}
int dfs(int x,int fat,int depth)/*return link size*/
{
	int max_size=0,n_son=-1;
	dep[x]=depth;
	dfn[dfn_len]=x;
	fst_pos[x]=dfn_len++;	
	fa[x]=x;
	for(int i=beg[x];i!=-1;i=e[i].next)
		if(e[i].v!=fat){
			edge2point[e[i].id]=e[i].v;
			from[e[i].v]=x;
			val[e[i].v]=e[i].c;
			int tmp=dfs(e[i].v,x,depth+1);
			dfn[dfn_len++]=x;
			if(tmp>max_size) max_size=tmp,n_son=e[i].v;
		}
	if(n_son!=-1) fa[n_son]=x;
	return max_size+1;
}
void cal_rmq()
{
	dfn_len=0;
	nlink=0;
	val[1]=0;
	dfs(1,-1,1);
	
	for(int i=0;i<dfn_len;++i)
		rmq[i][0]=dfn[i];
	for(int j=1;(1<<j)<=dfn_len;++j)	
		for(int i=0;i<dfn_len-(1<<j)+1;++i)
			if(dep[rmq[i][j-1]]<=dep[rmq[i+(1<<(j-1))][j-1]])
				rmq[i][j]=rmq[i][j-1];
			else 
				rmq[i][j]=rmq[i+(1<<(j-1))][j-1];
}
int find_head(int x)
{
	if(fa[x]==x) return x; 
		else return fa[x]=find_head(fa[x]);
}
seg_node * get_segnode()
{
	seg_node *tmp=new seg_node();
	tmp->left=tmp->right=NULL;
	tmp->max=-inf;
	return tmp;
}
int Max(seg_node *x,seg_node *y)
{
	if(x==NULL) return y->max;
	if(y==NULL) return x->max;
	return x->max>y->max?x->max:y->max;
}
void change(seg_node *&x,int l,int r,int pos,int new_val)
{
	if(x==NULL) x=get_segnode();
	if(l==r){
		x->max=new_val;
	}else {
		if(pos<=(l+r)/2) change(x->left,l,(l+r)/2,pos,new_val);
		else change(x->right,(l+r)/2+1,r,pos,new_val);
		x->max=Max(x->left,x->right);
	}
}
int find(seg_node *x,int l,int r)
{
	if(r<ll || rr<l) return -inf;
	if(ll<=l && r<=rr) return x->max;	
	int d1=find(x->left,l,(l+r)/2);
	int d2=find(x->right,(l+r)/2+1,r);
	return d1>d2?d1:d2;
}
void cal_link()
{
	/*union set*/
	for(int i=1;i<=n;++i)
		if(fa[i]!=i) fa[i]=find_head(i);
	/*label the link*/
	int lab[maxn];
	nlink=0;
	memset(lab,0,sizeof(lab));	
	memset(link_len,0,sizeof(link_len));
	for(int i=1;i<=n;++i) 
		if(fa[i]==i) lab[i]=++nlink;	
	for(int i=1;i<=n;++i)
		link_num[i]=lab[fa[i]];
	for(int i=1;i<=n;++i)
		link_len[link_num[i]]++;
	/*construct segment tree*/
	memset(seg,0,sizeof(seg));
	for(int i=1;i<=n;++i)
	change(seg[link_num[i]],1,link_len[link_num[i]],dep[i]-dep[fa[i]]+1,val[i]);
}
int lca(int x,int y)
{
	int k;
	x=fst_pos[x];
	y=fst_pos[y];
	if(x>y) { x=x^y; y=x^y;  x=x^y; }
	for(k=0;1<<k<=y-x+1;++k) ;
	k--;
	if(dep[rmq[x][k]]<dep[rmq[y-(1<<k)+1][k]])	return rmq[x][k];
	else return rmq[y-(1<<k)+1][k];
}
int find_max(int x,int z)
{
	if(link_num[x]==link_num[z])
	{
		ll=dep[z]-dep[fa[z]]+2;
		rr=dep[x]-dep[fa[x]]+1;
		return find(seg[link_num[x]],1,link_len[link_num[x]]);
	}else{
		ll=1;
		rr=dep[x]-dep[fa[x]]+1;
		int d1=find(seg[link_num[x]],1,link_len[link_num[x]]);
		int d2=find_max(from[fa[x]],z);
		return d1>d2?d1:d2;
	}
}
void answer()
{
	char task[20];
	int x,y,z;
	int ans,tmp;
	while(scanf("%s",task),strcmp(task,"DONE"))
	{
		scanf("%d%d",&x,&y);
		if(task[0]=='C'){
			x=edge2point[x];
			change(seg[link_num[x]],1,link_len[link_num[x]],dep[x]-dep[fa[x]]+1,y);
		}else {
			if(x==y) {
				printf("0\n");			
				continue;
			}
			z=lca(x,y);			
			ans=tmp=-inf;
			if(x!=z) ans=find_max(x,z);
			if(y!=z) tmp=find_max(y,z);
			if(tmp>ans) ans=tmp;
			printf("%d\n",ans);
		}
	}
}
void clear(seg_node *x)
{
	if(x==NULL) return ;
	clear(x->left);
	clear(x->right);
	delete x;
}
void clear_segtree()
{
	for(int i=1;i<=nlink;++i)
		clear(seg[i]);
}
int main()
{
	freopen("s357.in","r",stdin);
	int cs;
	scanf("%d",&cs);
	while(cs--)
	{
		input();
		cal_rmq();
		cal_link();
		answer();
		clear_segtree();		
	}
	return 0;
}
