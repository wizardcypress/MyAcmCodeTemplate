#include<iostream>
#include<math.h>
using namespace std;

int sgn(double d){
	if(fabs(d)<0.0000001)return 0;
	return d>0?1:-1;
}

typedef struct {double x,y;}P;

double det(double x1,double y1,double x2,double y2){
	return x1*y2-x2*y1;
}

double cross(P a,P b,P c){
	return det(b.x-a.x,b.y-a.y,c.x-a.x,c.y-a.y);
}

double min(double a,double b){
	return a<b?a:b;
}

double max(double a,double b){
	return a>b?a:b;
}

int xyCmp(double p,double min,double max){
	return sgn(p-min)*sgn(p-max);
}

int betweenCmp(P a,P b,P c){    //a是否在bc范围内
	if(fabs(b.x-c.x)>fabs(b.y-c.y))return xyCmp(a.x,min(b.x,c.x),max(b.x,c.x));
	else return xyCmp(a.y,min(b.y,c.y),max(b.y,c.y));
}

double segcross(P a,P b,P c,P d,P &p){    //判相交求交点
	double s1,s2,s3,s4;int d1,d2,d3,d4;
	d1=sgn(s1=cross(a,b,c));
	d2=sgn(s2=cross(a,b,d));
	d3=sgn(s3=cross(c,d,a));
	d4=sgn(s4=cross(c,d,b));
	if((d1^d2)==-2 && (d3^d4)==-2){
		p.x=(c.x*s2-d.x*s1)/(s2-s1);
		p.y=(c.y*s2-d.y*s1)/(s2-s1);
		return 1;
	}
	if(d1==0 && betweenCmp(c,a,b)<=0 || d2==0 && betweenCmp(d,a,b)<=0 ||
		d3==0 && betweenCmp(a,c,d)<=0 || d4==0 && betweenCmp(b,c,d)<=0)return 2;
	return 0;
}

double dis(P a,P b){          //两点间距
	return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}

double parea(P*p,long n){   //求多边形面积，逆时针为正，顺时针为负
	double a;
	for(long i=1;i<n;i++)
		a+=det(p[i-1].x,p[i-1].y,p[i].x,p[i].y)/2;
	return a;
}

void inc(P a,P b,P c,P&i){    //三角形内心
	double a1=dis(b,c),b1=dis(a,c),c1=dis(a,b);
	i.x=(a1*a.x+b1*b.x+c1*c.x)/(a1+b1+c1);
	i.y=(a1*a.y+b1*b.y+c1*c.y)/(a1+b1+c1);
}

void cir(P a,P b,P c,P&i){	//三角形外心
	i.x=((c.y-a.y)*b.x*b.x+(b.y-c.y)*a.x*a.x+(a.y-b.y)*c.x*c.x-(a.y-b.y)*(b.y-c.y)*(c.y-a.y))/(2*cross(a,b,c));
	i.y=-((c.x-a.x)*b.y*b.y+(b.x-c.x)*a.y*a.y+(a.x-b.x)*c.y*c.y-(a.x-b.x)*(b.x-c.x)*(c.x-a.x))/(2*cross(a,b,c));
}

void swap(P q[],long a,long b){
	P k;
	k=q[a];q[a]=q[b];q[b]=k;
}

void sort1(P q[],long p,long r){  //按y，x坐标排序
	if(p<r){
		swap(q,p,(p+r)/2);
		long i=p,j=r+1;
		while(1){
			while(q[++i].y<q[p].y ||(q[i].y==q[p].y && q[i].x<q[p].x));
			while(q[--j].y>q[p].y ||(q[j].y==q[p].y && q[j].x>q[p].x));
			if(i>=j)break;
			swap(q,i,j);
		}
		swap(q,p,j);
		sort1(q,p,j-1);
		sort1(q,j+1,r);
	}
}

void bag1(long bg[],long&ln,P q[],long n){        //无删平行点凸包
	if(n==1){ln=2;bg[1]=1;bg[2]=1;return;}
	ln=2;
	long i;
	bg[1]=1;bg[2]=2;
	for(i=3;i<=n;i++){
		while(cross(q[bg[ln-1]],q[bg[ln]],q[i])<0 && ln>1)ln--;
		bg[++ln]=i;
	}
	for(i=n-1;i>0;i--){
		while(cross(q[bg[ln-1]],q[bg[ln]],q[i])<0 && ln>1)ln--;
		bg[++ln]=i;
	}
}

void bag2(long bg[],long&ln,P q[],long n){        //删平行点凸包
	if(n==1){ln=2;bg[1]=1;bg[2]=1;return;}
	ln=2;
	long i,j;
	bg[1]=1;bg[2]=2;
	for(i=3;i<=n;i++){
		while(cross(q[bg[ln-1]],q[bg[ln]],q[i])<=0 && ln>1)ln--;
		bg[++ln]=i;
	}
	j=ln;
	for(i=n-1;i>0;i--){
		while(cross(q[bg[ln-1]],q[bg[ln]],q[i])<=0 && ln>j)ln--;
		bg[++ln]=i;
	}
}

int isin(P q[],long n,P v){
	long i,j;
	for(i=1;i<=n;i++)
		if(v.x==q[i].x && v.y==q[i].y)return 3;
	for(i=1;i<n;i++)
		if(sgn(cross(q[i],q[i+1],v))==0){
			if(betweenCmp(v,q[i],q[i+1]))return 2;
			else return 0;
		}
	j=sgn(cross(q[1],q[2],v));
	for(i=1;i<n;i++)
		if(sgn(cross(q[i],q[i+1],v))!=j)return 0;
	return 1;
}

long sort2(P q[],long p,long r,P h){  //按极坐标排序
	if(p<r){
		swap(q,p,(p+r)/2);
		long i=p,j=r+1;
		while(1){
			while(sgn(cross(h,q[p],q[++i])>0));
			while(sgn(cross(h,q[p],q[--j])<0));
			if(i>=j)break;
			swap(q,i,j);
		}
		swap(q,p,j);
		sort2(q,p,j-1,h);
		sort2(q,j+1,r,h);
		return j;
	}
	return p;
}

int main(){
	return 0;
}
