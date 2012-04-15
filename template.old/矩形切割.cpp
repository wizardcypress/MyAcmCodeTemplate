/*矩形切割，适用于任意维数的矩形，具体是一某一矩形为基准，把其他矩形在各维进行
切割*/
#include<iostream>
#include<stdio.h>
#include<memory>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=200000;
const long maxd=2;//矩形维数

struct retan
{
	double d1[maxd],d2[maxd];//d1，d2分别表示左上角和右下角的各维坐标
} p[2][maxn],pp;

long n,m,t[2],tt=0,pd=1;

double max(double x, double y)
{
	return x>y?x:y;
}
double min(double x, double y)
{
	return x<y?x:y;
}
void fz(retan &p1, retan p2)
{
	fo(i,0,maxd-1) {
		p1.d1[i]=p2.d1[i];
		p1.d2[i]=p2.d2[i];
	}
}
long cut(retan &p1, retan p2, long l)//按第l维切割，以p2为基准切p1
{
	double k1,k2;
	k1=max(p1.d1[l],p2.d1[l]);
	k2=min(p1.d2[l],p2.d2[l]);
	if (k1>=k2) return 1;
	if (p1.d2[l]>k2) {
		++t[m^1];
        fz(p[m^1][t[m^1]],p1);
		p[m^1][t[m^1]].d1[l]=k2;
        p[m^1][t[m^1]].d2[l]=p1.d2[l];
	}
	if (p1.d1[l]<k1) {
		++t[m^1];
		fz(p[m^1][t[m^1]],p1);
		p[m^1][t[m^1]].d1[l]=p1.d1[l];
        p[m^1][t[m^1]].d2[l]=k1;
	}
	p1.d1[l]=k1;
	p1.d2[l]=k2;
	return 0;
}
void solve()
{
    m=0; t[0]=0; 
	fo(i,1,n) {
		scanf("%lf%lf%lf%lf",&pp.d1[0],&pp.d1[1],&pp.d2[0],&pp.d2[1]);
		t[m^1]=0;
		fo(j,1,t[m]) 
			fo(l,0,maxd-1) 
			   if (cut(p[m][j],pp,l)) {
			       ++t[m^1]; 
	 	            fz(p[m^1][t[m^1]],p[m][j]);
					break;
		       }
		++t[m^1]; 
		fz(p[m^1][t[m^1]],pp);
		m^=1;
	}
}
int main()
{
	while (scanf("%d",&n),n!=0) 
		solve();
	return 0;
}
