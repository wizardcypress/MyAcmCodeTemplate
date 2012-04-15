#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#define N 1010
using namespace std;

struct POINT{
	double data;
	int pos;
}point[4*N];//用来离散化
int np;
///
struct 	INTERVAL{//添加进线段树上的线段
	int x,y1,y2;
	int add;
	INTERVAL(int _x=0,int _y1=0,int _y2=0,int _add=0):x(_x),y1(_y1),y2(_y2),add(_add){}
}line[2*N];
int nl;


POINT cord[N][4];//坐标
int c[N*16];
double cl1[N*16],cl2[N*16];//覆盖了一次和两次的长度值
int n,m;
int ll,rr;

bool cmp(const POINT &x,const POINT &y)
{
	return x.data<y.data;
}
bool cmp2(const INTERVAL &x,const INTERVAL &y)
{
	return x.x<y.x;
}
void input()
{
	np=-1;
	scanf("%d",&n);		
	for(int i=0;i<n;++i)
	{
		scanf("%lf%lf%lf%lf",&cord[i][0].data,&cord[i][1].data,&cord[i][2].data,&cord[i][3].data);
		for(int j=0;j<4;++j)
		{
			np++;
			point[np].data=cord[i][j].data;
			point[np].pos=i*1000+j;
		}
	}
	np++;
	
	sort(point,point+np,cmp);
	//discrete
	for(int i=0;i<np;++i)
	{
		int d1=point[i].pos/1000;
		int d2=point[i].pos%1000;
		cord[d1][d2].pos=i;
	}
	//add line
	nl=-1;
	for(int i=0;i<n;++i)
	{	
		nl++;			
		line[nl]=INTERVAL(cord[i][0].pos,cord[i][1].pos,cord[i][3].pos,1);
		nl++;
		line[nl]=INTERVAL(cord[i][2].pos,cord[i][1].pos,cord[i][3].pos,-1);
	}
	nl++;
	
	sort(line,line+nl,cmp2);
}
void cal_cl1(int x,int l,int r)
{
	if(c[x]>0){
		cl1[x]=point[r].data-point[l].data;
	}else{
		if(l<r-1) cl1[x]=cl1[x*2]+cl1[x*2+1];
		else cl1[x]=0;
	}
}
void cal_cl2(int x,int l,int r)
{
	if(c[x]>1){
		cl2[x]=point[r].data-point[l].data;		
	}else if(c[x]==1){
		if(l<r-1) cl2[x]=cl1[x*2]+cl1[x*2+1];
		else cl2[x]=0;
	}else {
		if(l<r-1) cl2[x]=cl2[x*2]+cl2[x*2+1];
		else cl2[x]=0;
	}
}
void insert(int x,int l,int r,int add)
{
	if(rr<=l || ll>=r) return ;
	if(ll<=l && r<=rr)
	{
		c[x]+=add;
		cal_cl1(x,l,r);
		cal_cl2(x,l,r);
	}else{
		insert(x*2,l,(l+r)/2,add);
		insert(x*2+1,(l+r)/2,r,add);
		cal_cl1(x,l,r);
		cal_cl2(x,l,r);
	}
}
void solve()
{
	double ans=0;
	memset(c,0,sizeof(c));	
	memset(cl1,0,sizeof(cl1));
	memset(cl2,0,sizeof(cl2));
	ll=line[0].y1;
	rr=line[0].y2;
	insert(1,0,np-1,line[0].add);
	for(int i=1;i<nl;++i)
	{
		ans+=(point[line[i].x].data-point[line[i-1].x].data)*(cl2[1]);
		ll=line[i].y1;
		rr=line[i].y2;
		insert(1,0,np-1,line[i].add);
	}
	printf("%.2f\n",ans);
}
int main()
{
	freopen("hdu1255.in","r",stdin);	
	int cs;
	scanf("%d",&cs);
	while(cs--)
	{
		input();
		solve();		
	}
	return 0;
}
