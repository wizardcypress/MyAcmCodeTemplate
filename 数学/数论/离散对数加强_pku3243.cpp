#include<cstdio>
#include<cstring>
#include<cmath>
#define TAB_SIZE  150000
#define MOD  1000007
typedef long long ll;
const ll T=100000000;
using namespace std;
struct 	NODE{
	ll bx,x;
	int next;
};
class Hash{
	int beg[MOD];
	NODE hash[TAB_SIZE];
	int nH;
	public:
	Hash(){	
	  flush();
	}
	void flush(){
		memset(beg,0,sizeof(beg));
		nH=0;
	}
	void insert(ll bx,ll x)	
	{
		int pos=bx%MOD;
		if(get(bx)==-1)
		{		
			nH++;
			hash[nH].bx=bx;
			hash[nH].x=x;			
			hash[nH].next=beg[pos];
			beg[pos]=nH;
		}
	}
	ll get(ll bx)
	{
		int pos=bx%MOD;
		for(int i=beg[pos];i;i=hash[i].next)
			if(hash[i].bx==bx) return hash[i].x;
		return -1;
	}
};
Hash tab;
ll mod(ll x,ll y,ll z)  //cal x*y%z
{
	ll c=y/T,d=y%T;
	return (x*c%z*T%z+x*d%z)%z;
}
void extend_gcd(ll a,ll b,ll &d,ll &x,ll &y)
{
	if(!b){  x=1; y=0 ; d=a ;}
	else {
		extend_gcd(b,a%b,d,y,x);
		y-=a/b*x;
	}
}
ll baby_giant_setp(ll b,ll n,ll p)
{
	ll m=ceil(sqrt(p*1.0));
	ll bm=1;
	for(int i=0;i<m;++i)
	{
		tab.insert(bm,i);
		bm=mod(bm,b,p);
	}
	ll tx,ty,d,ind,bmi=1,e;
	for(int i=0;i<m;++i)
	{
		extend_gcd(bmi,p,d,tx,ty);
		if(n%d) continue;
		e=(tx*(n/d)%p+p)%p;
		for(int j=0;j<d;++j)		
		{
			if((ind=tab.get(e))!=-1)
				return ind+m*i;
			e=(e+p/d)%p;
		}
		bmi=mod(bmi,bm,p);
	}
	return -1;
}
int main()
{
	ll b,n,p;
	while(scanf("%lld%lld%lld",&b,&p,&n),b+n+p)
	{
		tab.flush();
		ll ans=baby_giant_setp(b,n,p);
		if(ans==-1)		 printf("No Solution\n");
		else printf("%lld\n",ans);
	}
	return 0;
}

