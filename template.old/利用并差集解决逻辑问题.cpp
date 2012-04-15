/*利用并差集做，用rela[x]表示x与其所在并差集的root的关系
然后通过路径压缩来更新关系。为了方便不用每种情况都讨论
，每次询问都将x，y移到并差集的root位置，方便于判断与合并*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=50010;

long fa[maxn],rela[maxn];
long n,m;

//路径压缩，同时更新关系，具体更新关系的规律可通过列表求得
long renew(long x) 
{
	long root;
	if (fa[x]) {
		root=renew(fa[x]);
		if (fa[x]!=root) rela[x]=(rela[x]+rela[fa[x]])%3;//更新与根的关系
		fa[x]=root;
		return root;
	}
	return x;
}
void move_root(long x)//将x移到root的位置，同时处理好关系
{
	if (rela[x]==0) rela[fa[x]]=0;
	else rela[fa[x]]=3-rela[x];
	fa[fa[x]]=x; fa[x]=0;
}
void solve()
{
	long d,x,y,ans=0;
	memset(fa,0,sizeof(fa));
	fo(l,1,m) {
		scanf("%d%d%d",&d,&x,&y);
		if (x>n || y>n) { ++ans;  continue; }
		if (x==y) {
			if (d==2) ++ans;
			continue;
		}
		/*路径压缩后x要不是所在并差集的root下的儿子，要不是就是root，若是儿子则移到root
		处理完后若x，y在同一并差集，则y必为root，x为其儿子*/

		//必需renew后立刻move_root，否则x和y不能形成儿子父亲关系（若x，y在同一并差集）
		renew(x); if (fa[x]) move_root(x); 
		renew(y); if (fa[y]) move_root(y);
		//判断是否为假话
		if (fa[x]==y && ( (d==1 && rela[x]!=0) || (d==2 && rela[x]!=1)) ) {++ans; continue;}
        //由于之前的操作，合并直接处理rela和fa就行
		if (fa[x]!=y) rela[x]=d-1, fa[x]=y;
	}
	printf("%d\n",ans);
}
int main()
{
	scanf("%d%d",&n,&m);
	solve();
	return 0;
}
