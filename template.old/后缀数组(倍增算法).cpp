#include<iostream>
#include<cstdio>
#include<cstring>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
#define fod(i,u,d) for (long i=(u); i>=(d); --i)
using namespace std;

const long maxn=20001;
const long maxt=1000001;

long sa[maxn],sa2[maxn],ra[maxn],ra2[maxn];
long height[maxn],n;
long s[maxn];

void init()
{
	scanf("%d",&n);
	fo(i,1,n) scanf("%d",&s[i]); s[0]=s[n+1]=-1;
}
void cal_sa_ra()
{
	long tong[maxt],p,m=0,tmp;
	memset(tong,0,sizeof(tong));
	fo(i,1,n) 
		++tong[s[i]], m=m>s[i]?m:s[i];
	fo(i,1,m)
		tong[i]+=tong[i-1];
	fo(i,1,n) 
		sa[tong[s[i]]--]=i;
	ra[sa[1]]=1, p=1;
	fo(i,2,n)
		if (s[sa[i]]==s[sa[i-1]]) ra[sa[i]]=p; else ra[sa[i]]=++p;

	for (long l=1, m=p; p<n; m=p, l*=2) {
		memset(tong,0,sizeof(tong));
		fo(i,1,n) 
			++tong[ra[i]];
		fo(i,1,m)
			tong[i]+=tong[i-1];
		//将包含第二关键字的排序
		fod(i,n,1) 
			if (sa[i]>l) sa2[tong[ra[sa[i]-l]]--]=sa[i]-l;
		//将不包含第二关键字的排序
		fo(i,n-l+1,n)
			sa2[tong[ra[i]]--]=i;
		p=1, ra2[sa2[1]]=1;
		//统计排序后不同的rank个数
		fo(i,2,n)
			if (ra[sa2[i-1]]==ra[sa2[i]] && ra[sa2[i-1]+l]==ra[sa2[i]+l]) ra2[sa2[i]]=p; 
		    else ra2[sa2[i]]=++p;
		fo(i,1,n) sa[i]=sa2[i], ra[i]=ra2[i];
	}
}
void cal_height()
{
	long k,i,j;
	for (k=0, i=1; i<=n; height[ra[i++]]=k)
      for (k?--k:0, j=sa[ra[i]-1]; s[i+k]==s[j+k]; ++k);
}
int main()
{
	init();
	cal_sa_ra();
	cal_height();
	return 0;
}
