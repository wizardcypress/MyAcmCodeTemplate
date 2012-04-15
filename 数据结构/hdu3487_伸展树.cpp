//伸展树
#include<cstdio>
#include<algorithm>
#include<vector>
#define MAXN 300010
#define MAXM 300010
#define Type int
using namespace std;

int n,m,a,b,c,cnt;
char task[20];

    int size,root;  // 树的大小和根的编号
    int s[MAXN],left[MAXN],right[MAXN];  //儿子个数，左儿子，右儿子
    Type data[MAXN];   //节点的值
    int rev[MAXN];  //是否翻转
    int fa[MAXN];    //父亲值
    //splayTree ()  { clear(); }  
    void clear() {
    	s[0]=left[0]=right[0]=rev[0]=fa[0]=root=size=0; 
    }
	void leftrotate(int x)  //左旋转
	{ 
		int y=right[x];
		if(x==left[fa[x]]) left[fa[x]]=y;
		else right[fa[x]]=y;
		fa[y]=fa[x];  fa[x]=y; fa[left[y]]=x;
		right[x]=left[y]; 	left[y]=x;
		s[y]=s[x];
		s[x]=s[left[x]]+s[right[x]]+1;		
	}
	void rightrotate(int x)  //右旋转
	{
	   int y=left[x];
	   if(x==left[fa[x]]) left[fa[x]]=y;
	   else right[fa[x]]=y;
	   fa[y]=fa[x];   fa[x]=y;	fa[right[y]]=x;
	   left[x]=right[y];    right[y]=x;
	   s[y]=s[x];
	   s[x]=s[left[x]]+s[right[x]]+1;	   
	}
	void pushDown(int &x) //向下传递翻转消息
	{
		if(x && rev[x]){
			if(left[x]) rev[left[x]]^=1;
			if(right[x]) rev[right[x]]^=1;
			rev[x]=0;
			int tmp=left[x];	left[x]=right[x]; 	right[x]=tmp;
		}
	}
	int select(int x,int kth) //返回第kth个的编号
	{		
		int cnt=0;
		pushDown(x);
		pushDown(left[x]);
		pushDown(right[x]);
		while(s[left[x]]+1!=kth){
			cnt++;
			ensure(cnt<=n);			
			if(kth<=s[left[x]]) x=left[x];
			else {
				kth=kth-(s[left[x]]+1);
				x=right[x];
			}
			pushDown(x);
			pushDown(left[x]);
			pushDown(right[x]);
		}
		return x;
	}
	//先求得第kth个的编号，然后从下而上的旋转，避免递归导致栈溢出
	//splay(x,kth)的含义为把第kth个旋转到x上
	void splay(int &x,int kth)
	{
		int z=select(x,kth); //find the kth num
		int fx=fa[x]; //super root
		int y,g;
		while(fa[z]!=fx){
			y=fa[z];
			g=fa[y];  
			if(fa[z]==x){  
				if(left[x]==z) rightrotate(x);
				else leftrotate(x);
			}else if(left[y]==z && left[g]==y){
				rightrotate(g);
				rightrotate(y);
			}else if(right[y]==z && left[g]==y){
				leftrotate(y);
				rightrotate(g);				
			}else if(right[y]==z && right[g]==y){
				leftrotate(g);
				leftrotate(y);				
			}else if(left[y]==z && right[g]==y){
				rightrotate(y);
				leftrotate(g);				
			}
		}
		x=z; 
	}	
void build(int &x,int l,int r)
{
	if(l>r) return ;
	int mid=(l+r)>>1;
	x=++size;
	data[x]=mid;
	left[x]=right[x]=rev[x]=fa[x]=0;  
	  
    build(left[x],l,mid-1);
    if(l<=mid-1) fa[left[x]]=x;
    
    build(right[x],mid+1,r);
    if(mid+1<=r) fa[right[x]]=x;
    
    s[x]=s[left[x]]+s[right[x]]+1;
}
void travel(int x)
{
	pushDown(x);
	if(left[x]) travel(left[x]);
	cnt++;
	if(cnt>1) printf(" ");
	printf("%d",data[x]);
	if(right[x]) travel(right[x]);
}
int main()
{
	//freopen("hdu3487.in","r",stdin);
	while(scanf("%d%d",&n,&m),n>0 && m>0)
	{	
		
		clear();
		build(root,1,n);
		for(int i=1;i<=m;i++)
		{
			scanf("%s",task);
			if(task[0]=='C'){
				scanf("%d%d%d",&a,&b,&c); //cut a~b and insert after c
				if(a==1 && b==n) continue;
				int rec;
				if(a==1){				
					splay(root,b+1);
					rec=left[root];
					s[root]-=s[rec];
					left[root]=0;
				}else if(b==n){
					splay(root,a-1);
					rec=right[root];
					s[root]-=s[rec];
					right[root]=0;
				}else {									
					splay(root,a-1);					
					splay(right[root],b-s[left[root]]);
					rec=left[right[root]];
					left[right[root]]=0;
					s[root]-=s[rec];
					s[right[root]]-=s[rec];					
				}
				if(c==0){
					splay(root,1);
					left[root]=rec;
					s[root]+=s[rec];
					fa[rec]=root;					
				}else if(c==s[root]){
					splay(root,c);
					right[root]=rec;
					s[root]+=s[rec];
					fa[rec]=root;
				}else{
					splay(root,c);
					splay(right[root],c-s[left[root]]);
					left[right[root]]=rec;					
					fa[rec]=right[root];
					s[right[root]]+=s[rec];
					s[root]+=s[rec];					
				}
			}else { 
				scanf("%d%d",&a,&b); //flip a~b
				if(a==1 && b==n) rev[root]^=1;
				else if(a==1){
					splay(root,b+1);
					rev[left[root]]^=1;
				}else if(b==n){
					splay(root,a-1);
					rev[right[root]]^=1;
				}else {
					splay(root,a-1);
					splay(right[root],b-s[left[root]]);
					rev[left[right[root]]]^=1;
				}
			}
		}
		cnt=0;		
		travel(root);
		printf("\n");
	}
	return 0;
}
