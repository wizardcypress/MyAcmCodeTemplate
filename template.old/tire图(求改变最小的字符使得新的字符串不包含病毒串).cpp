/*直接按照病毒序列构造tire图，然后在tire上dp
（相当于在tire图上走len步，且不包含有标记的点，
尽量多的包含原来给的串）*/
#include<iostream>
#include<cstdio>
#include<cstring>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=10001;
const long maxm=21;
const long maxw=4;
const long root=0;
const char DNA[4]={'A', 'T', 'C', 'G'};
const long inf=1001;

long tire[maxn][maxw],suffix[maxn],lab[maxn],tt;
long n,t=0;

long hao(char c)
{
	fo(i,0,3)
		if (DNA[i]==c) return i;
}
/****************************************************/
void make_tire()
{
	char s[maxm];
	fo(i,0,maxw-1) tire[root][i]=0; lab[root]=0;
	tt=0;

	fo(l,1,n) {
		scanf("%s",s);
		long len=strlen(s)-1,p=root, h;

		fo(i,0,len) {
			h=hao(s[i]);
			if (tire[p][h]==0) {
				tire[p][h]=++tt, lab[tt]=0;
				fo(j,0,maxw-1) tire[tt][j]=0;
			}
			p=tire[p][h];
		}

	     lab[p]=1;
	}
}

void make_tiregraph()
{
	long q[maxn],p,st=0,ed=0;

	suffix[root]=0;
	fo(i,0,maxw-1)
		if (tire[root][i]) q[ed++]=tire[root][i], suffix[tire[root][i]]=0;

	for (; st<ed; ++st) {
		p=q[st];
		fo(i,0,maxw-1)
			if (tire[p][i]) {
			   q[ed++]=tire[p][i];
			   suffix[tire[p][i]]=tire[suffix[p]][i];
			   if (lab[suffix[tire[p][i]]]) lab[tire[p][i]]=1;
		    } else 
				tire[p][i]=tire[suffix[p]][i];
	}

}
/*****************************************************************/
void solve()
{
	char s[maxn];
	scanf("%s",s);
	long len=strlen(s)-1, w=0, f[2][maxn];

//dp，f[i][j]表示长度为i到达状态j时最小的修改数使得不包含病毒段，具体做的时候用滚动数组
    f[0][0]=0;
	fo(i,1,tt) f[0][i]=inf;

	fo(l,0,len) {
		fo(i,0,tt) f[w^1][i]=inf;
		fo(i,0,tt) if (f[w][i]!=inf) 
			fo(j,0,maxw-1) if (lab[tire[i][j]]==0) {
			    if (hao(s[l])==j) 
					f[w^1][tire[i][j]]=f[w][i]<f[w^1][tire[i][j]]?f[w][i]:f[w^1][tire[i][j]];
				else 
					f[w^1][tire[i][j]]=f[w][i]+1<f[w^1][tire[i][j]]?f[w][i]+1:f[w^1][tire[i][j]];
		    }
		w^=1;
	}
	long ans=inf;
	fo(i,0,tt) 
		ans=f[w][i]<ans?f[w][i]:ans;

    printf("Case %d: ",++t);
	if (ans<inf) printf("%d\n",ans);
	else printf("-1\n");
}
int main()
{
	while (scanf("%d",&n),n!=0) {
		make_tire();
		make_tiregraph();
		solve();
	}
	return 0;
}
