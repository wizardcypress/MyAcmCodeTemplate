#include<iostream>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=101;

struct fnum //分数struct
{
	long fz,fm;
	fnum(){}
	fnum(long fz, long fm) 
	{
		this->fz=fz; this->fm=fm;
	}
} f[maxn][maxn],g[maxn][maxn];

long n;

long ab(long x)
{
	return x<0?-x:x;
}
long gcd(long x, long y)
{
	if (y==0) return x;
	return gcd(y,x%y);
}
void yue(fnum &p) //约分
{
	long d=gcd(p.fz,p.fm);
	p.fz/=d; p.fm/=d;
}
fnum dec(fnum p1, fnum p2)
{
	fnum p;
	p.fz=p1.fz*p2.fm-p2.fz*p1.fm;
	p.fm=p1.fm*p2.fm;
	yue(p);
	return p;
}
fnum chen(fnum p1, fnum p2)
{
	fnum p;
	p.fz=p1.fz*p2.fz;
	p.fm=p1.fm*p2.fm;
	yue(p);
	return p;
}
fnum div(fnum p1, fnum p2)
{
	fnum p;
	p.fz=p1.fz*p2.fm;
	p.fm=p1.fm*p2.fz;
	yue(p);
	return p;
}
void init()
{
	scanf("%d",&n);
	long x;
	fo(i,1,n)
		fo(j,1,n) scanf("%d",&x), f[i][j]=fnum(x,1);
}
void solve()//将矩阵f化为单位阵同时把单位阵g化为逆矩阵
{
	fo(i,1,n) fo(j,1,n)
		if (i==j) g[i][j]=fnum(1,1); else g[i][j]=fnum(0,1);

    fnum tmp;
	fo(l,1,n) {
		fo(i,l,n)
			if (f[i][l].fz!=0) { //找出非零元
			   fo(j,1,n) {
				   tmp=f[l][j], f[l][j]=f[i][j], f[i][j]=tmp;
			       tmp=g[l][j], g[l][j]=g[i][j], g[i][j]=tmp;
			   }
		       break;
		    }
		fo(i,1,n) { //f消第l列，g同时做出改变
			if (i==l) continue;
			tmp=div(f[i][l],f[l][l]);
			fo(j,1,n) 
				f[i][j]=dec(f[i][j],chen(f[l][j],tmp)), g[i][j]=dec(g[i][j],chen(g[l][j],tmp));
		}
		tmp=f[l][l];
		fo(i,1,n) f[l][i]=div(f[l][i],tmp), g[l][i]=div(g[l][i],tmp);
	}
}
void print()
{
	printf("\n\n");
	long pd, c;
	fo(i,1,n)  {
		fo(j,1,n) {
			c=g[i][j].fz*g[i][j].fm;
			if (c==0 || c/ab(c)==1) pd=1; else pd=-1;
			if (pd==1) printf("%d / %d   ",ab(g[i][j].fz),ab(g[i][j].fm));
			else printf("-%d / %d   ",ab(g[i][j].fz),ab(g[i][j].fm));
		}
		printf("\n\n");
	}
}
int main()
{
	init();
	solve();
	print();
	return 0;
}
