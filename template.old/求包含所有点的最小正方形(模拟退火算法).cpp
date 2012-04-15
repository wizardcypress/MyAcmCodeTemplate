/*模拟退火算法，注意多产生几个种子进行模拟退火*/
#include<iostream>
#include<cmath>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=51;
const double jd=1e-8;
const double pi=cos(-1.0);

long p[maxn][2],n,t;

void init()
{
	scanf("%d",&n);
	fo(i,1,n) 
		fo(j,0,1) scanf("%d",&p[i][j]);
}
double cal(double thta)
{
	double ax=1e100,ay=1e100,bx=-1e100,by=-1e100,x,y;
	fo(i,1,n) {
		x=cos(thta)*p[i][0]+sin(thta)*p[i][1];
		y=-sin(thta)*p[i][0]+cos(thta)*p[i][1];
		if (x<ax) ax=x; 
		if (x>bx) bx=x;
		if (y<ay) ay=y;
		if (y>by) by=y;
	}
	if (bx-ax>by-ay) return bx-ax; else return by-ay;
}
void solve()
{
	double det,da,dd, min, now, na, ans=1e100;
	fo(i,0,20) {//20个种子
		da=2.0*pi*i/20.0;
		det=2.0*pi;
		na=1e100;
		while (det>jd) {
			min=1e100;
			if (da+det<2.0*pi && (now=cal(da+det))<min) 
				min=now, dd=det;
			if (da-det>0 && (now=cal(da-det))<min) 
				min=now, dd=-det;
			if (min<na)
				na=min, da+=dd;
			det*=0.8;
		}
		if (ans>na) ans=na;
	}
	printf("%.2lf\n",ans*ans);
}
int main()
{
	scanf("%d",&t);
	while (t--) {
		init();
		solve();
	}
	return 0;
}
