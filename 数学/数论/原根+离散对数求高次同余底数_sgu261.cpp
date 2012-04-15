/*
	x^k mod p=a;给出p,k,a求x
*/

#include<cstdio>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<vector>
#define MOD  1000003
const int T=100000000;
typedef long long ll;
using namespace std;
struct 	NODE{
	NODE(int _bx=0,int _x=0,int _next=0):bx(_bx),x(_x),next(_next){}
	ll bx,x;
	int next;
};
// hash部分，写成类形式。
class Hash{
	int beg[MOD];
	vector<NODE> hash;
	public:
	Hash(){		
	  flush();
	}
	void flush(){
		memset(beg,255,sizeof(beg));
		hash.resize(0,0);
	}
	void insert(ll bx,ll x)	
	{
		int pos=bx%MOD;
		if(get(bx)==-1)
		{	
			hash.push_back(NODE(bx,x,beg[pos]));
			beg[pos]=hash.size()-1;
		}
	}
	ll get(ll bx)
	{
		int pos=bx%MOD;
		for(int i=beg[pos];i!=-1;i=hash[i].next)
			if(hash[i].bx==bx) return hash[i].x;
		return -1;
	}
};
Hash tab;

ll p,k,a,g,d,remain;
int prime[40000],np;
int pri[40000],npri;
bool isPrime[40000];
vector<int> ans;
int zero=0;
void pre()  // 线性素数筛选。
{
	np=0;
	memset(isPrime,1,sizeof(isPrime));
	for(int i=2;i<40000;++i)
	if(isPrime[i]){
		prime[++np]=i;
		for(int j=i*i;j<40000;j+=i)		
			isPrime[j]=false;
	}
}
void Div(int p)  //将p进行质因数分解
{
	int tm=p-1;
	npri=0;
	for(int i=1;i<=np && tm>=prime[i] ;++i)
	if(tm%prime[i]==0)
	{
		pri[++npri]=prime[i];
		while(tm%prime[i]==0) tm/=prime[i];
	}
	if(tm>1) pri[++npri]=tm;
}
inline ll mod(ll x,ll y,ll p)//输出x*y%p
{
	ll c=y/T,d=y%T;
	return (x*c%p*T%p+x*d%p)%p;		
	
}
ll pow_mod(ll b,ll x,ll p)//输出 b^x mod p
{
	ll ret=1;
	while(x)
	{
		if(x&1) ret=mod(ret,b,p);
		b=mod(b,b,p);
		x>>=1;
	}
	return ret;
}
void extend_gcd(int a,int b,ll &d,ll &x,ll &y) //扩展gcd
{
	if(!b) {  d=a; x=1; y=0;  return ; }
	else{
		extend_gcd(b,a%b,d,y,x);
		y-=a/b*x;
	}	
}
int find_root(int p)  //枚举r，寻找p的原根，要求p为1，2，4，p^e,或者2p^e,p为奇素数。
{
	if(p==2) return 1;
	for(int r=2;;r++)
	{
		bool flag=true;
		for(int j=1;j<=npri;++j)  //如果对所有r^((p-1)/pri[j]) mod p!=1，那么r是p的原根。
			if(pow_mod(r,(p-1)/pri[j],p)==1) {  //pri[j]是p-1的素数因子
				flag=false;
				break;
			}
		if(flag) return r;
	}
}
void solve()
{
	ll x,y,t,tm;
	extend_gcd(k,p-1,d,x,y);
	t=(p-1)/d;
	ans.resize(0,0);
	if(remain%d) return ;
	x=x*remain/d%(p-1);		
	for(int i=0;i<d;++i)
	{		
		if(x<0) tm=x+p-1; else tm=x;
		ans.push_back((int)pow_mod(g,tm,p));
		x=(x+t)%(p-1);
	}
}
void output()
{
	sort(ans.begin(),ans.end());
	printf("%d\n",ans.size());
	if(ans.size()>0){
	for(int i=0;i<ans.size()-1;++i) 	
		printf("%d ",ans[i]);	
	printf("%d\n",ans[ans.size()-1]);
	}
}
ll discrete_log(ll b,ll n,ll p)//离散对数，这里只考虑p为素数的情况
{
	tab.flush();
	ll m=ceil(sqrt(p*1.0));
	ll bm=1;
	for(int i=0;i<m;++i)
	{
		tab.insert(bm,i);
		bm=mod(bm,b,p);
	}	
	ll tx,ty,d,ind,t,e;	
	extend_gcd(bm,p,d,t,ty);//assume p is prime,t=b^(-mi)
	t=(t%p+p)%p;
	for(int i=0;i<m;++i)
	{
		if((ind=tab.get(n))!=-1) return ind+m*i;
		n=n*t%p;
	}	
	return -1;
}
/*//求离散对数的加强版，可以对b和p不互质情况进行处理。
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
		extend_gcd(bmi,p,d,tx,ty); //bmi=b^(m*i),求出tx,使得bmi*tx=n (mod p),
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
*/
int main()
{
	//freopen("sgu261.in","r",stdin);
	//freopen("sgu261.out","w",stdout);
	pre();
	while(cin>>p>>k>>a)
	{
		a=a%p;
		if(a==0) {
			cout<<"1"<<endl;
			cout<<"0"<<endl;
			continue;
		}
		Div(p);
		g=find_root(p);
		remain=discrete_log(g,a,p);		
		solve();
		output();		
	}
	return 0;	
}
