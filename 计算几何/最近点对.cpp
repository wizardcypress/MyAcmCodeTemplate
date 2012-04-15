#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#define N 200010
typedef long long ll;
const ll inf=(ll)1000000001*1000000001;
using namespace std;
struct PPOINT{
	int x,y;	
};
PPOINT P[N],Q[N],tm[N],tm2[N];
int n;
ll d;
void input()
{
	scanf("%d",&n);
	for(int i=0;i<n;++i)
	{
		int x,y;
		scanf("%d%d",&x,&y);
		P[i].x=x; P[i].y=y;
		Q[i].x=x; Q[i].y=y;
	}
}
void merge(PPOINT *src,int l1,int r1,int l2,int r2,PPOINT *dest)
{
	int len=0;
	while(l1<=r1 || l2<=r2)
	{
		if(l2>r2) { dest[len++]=src[l1++];continue;}
		if(l1>r1) { dest[len++]=src[l2++];continue;}
		if(src[l1].y<src[l2].y) dest[len++]=src[l1++];
		else dest[len++]=src[l2++];
	}	
}
bool cmp(const PPOINT &a,const PPOINT &b)
{
	return a.x<b.x;
}
inline ll dob(ll x)
{
	return x*x;
}
inline ll distance(PPOINT &x,PPOINT &y)
{
	return dob(x.x-y.x)+dob(x.y-y.y);
}
ll cloest_pair(int l,int r)
{
	if(l<r)
	{
		ll best;
		ll delta=cloest_pair(l,(l+r)/2);
		ll delta2=cloest_pair((l+r)/2+1,r);
		if(delta2<delta) delta=delta2;
		best=delta;
		
		merge(Q,l,(l+r)/2,(l+r)/2+1,r,tm);                                
		memcpy(Q+l,tm,sizeof(PPOINT)*(r-l+1));		
		
		ll mid=P[(l+r)/2].x;
		int last=0;
		for(int i=l;i<=r;++i) if(dob(Q[i].x-mid)<=delta) tm[last++]=Q[i];
		for(int i=1;i<last;++i)
			for(int j=i-1;j>=0;--j)
				if(dob(tm[i].y-tm[j].y)>delta) break;	else
				{
					if((d=::distance(tm[i],tm[j]))<best)
						best=d;
				}
		return best;
	}
	return inf;
}
int main()
{
	freopen("clopair.in","r",stdin);
		input();
		sort(P,P+n,cmp);
		sort(Q,Q+n,cmp);
		ll ans=cloest_pair(0,n-1);
		printf("%.2f\n",sqrt(ans*1.0));
	return 0;
}
