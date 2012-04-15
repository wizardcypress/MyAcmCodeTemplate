/*
	输入m
	Find out all x (<=m) that x^2 mod m=1
	//中国剩余定理写成类
*/
#include<cstdio>
#include<cstring>
#include<iostream>
#include<vector>
#define N 100
#define VI vector<int>
typedef long long LL;
//typedef vector<int> VI;
using namespace std;

class Chn{	
	public:
	int extend_gcd(int,int,int&,int&);
	int mainProc(VI &x,VI &m);
};
int Chn::extend_gcd(int a,int b,int& x,int& y)
{	
	if(b==0){
		x=1;y=0; return a;
	}else{
		int d=extend_gcd(b,a%b,x,y);
		int rx=x;
		x=y;
		y=rx-a/b*y;
		return d;
	}
}
int Chn::mainProc(VI &x,VI &m)// x为余数，m为mod
{
	int k=x.size();
	int M=1,ans=0;
	for(int i=0;i<k;++i)	M*=m[i];	
	for(int i=0;i<k;++i)	
	{
		int pi,qi;		
		int Mi=M/m[i];	
		extend_gcd(Mi,m[i],pi,qi);
		ans=(ans+(LL)x[i]*Mi*pi)%M;
	}
	if (ans<0) ans+=M;
	return ans;
}
int nP;
int p[N],e[N],pk[N];
int m;
VI X,M;
Chn cn;
void preWork()
{
	nP=-1;
	int tm=m;
	M.clear();
	memset(e,0,sizeof(e));
	for(int i=2;(LL)i*i<=m;++i)
	if(!(tm%i)){
		p[++nP]=i;
		pk[nP]=1;
		while(!(tm%i))
			e[nP]++,tm/=i,pk[nP]*=i;	
		M.push_back(pk[nP]);
	}
	if(tm>1){
		p[++nP]=tm;
		e[nP]=1; pk[nP]=tm;
		M.push_back(tm);
		}
	nP++;
}
void distr(int cur)
{
	if(cur==nP) {
		int ans=cn.mainProc(X,M);
		printf("%d x^2 mod m=%lld\n",ans,(LL)ans*ans%m);
	}
	else{
		if(p[cur]==2)
		{
			X[cur]=1;
			distr(cur+1);			
			if(e[cur]>1)
			{
			X[cur]=pk[cur]-1;
			distr(cur+1);
			}
			if(e[cur]>=3)
			{
				X[cur]=pk[cur]/2+1;
				distr(cur+1);
				X[cur]=pk[cur]/2-1;
				distr(cur+1);	
			}
		}
		else{
			X[cur]=1;
			distr(cur+1);
			X[cur]=pk[cur]-1;
			distr(cur+1);
		}
	}
}
void solve()
{	
	X.resize(nP,0);	
	distr(0);
	printf("\n");
}
int main()
{
	scanf("%d",&m);
	preWork();
	solve();
	return 0;
}

