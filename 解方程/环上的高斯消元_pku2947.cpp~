#include<cstdio>
#include<iostream>
#include<cstring>
#define MOD 7
using namespace std;
const char week[7][4]={"MON","TUE","WED","THU","FRI","SAT","SUN"};
int n,m;
int a[310][310];
int x[310];
const int ni[7]={0,1,4,5,2,3,6};
int zero=0;
void input()
{
	int howMany,kind,nst,nen;
	char st[4],en[4];
	memset(a,0,sizeof(a));
	for(int i=0;i<m;++i)
	{
		scanf("%d",&howMany);
		scanf("%s %s",st,en);
		for(nst=0;nst<7;++nst) if (strcmp(st,week[nst])==0) break;
		for(nen=0;nen<7;++nen) if (strcmp(en,week[nen])==0) break;		
		a[i][n]=nen-nst+1;
		for(int j=0;j<howMany;++j){
			scanf("%d",&kind);		
			a[i][kind-1]++;
		}
		for(int j=0;j<=n;++j) a[i][j]=(a[i][j]%MOD+MOD)%MOD;
	}
}
void swap(int &x,int &y)
{
	int tm=x; x=y;  y=tm;
}
void eculid(int x,int y,int z)
{
	int r;
	while(a[y][z])
	{
		r=a[x][z]/a[y][z];
		for(int i=z;i<=n;++i)
			a[x][i]=(a[x][i]-a[y][i]*r)%MOD;
		swap(x,y);
	}
}
void extend_gcd(int a,int b,int &d,int &x,int &y)
{
	if(!b) { d=a;  x=1;  y=0; }
	else{
		extend_gcd(b,a%b,d,y,x);
		y-=a/b*x;
	}
}
void module(int a,int b,int &x,int n)
{
	int d,y,t;
	extend_gcd(a,b,d,x,y);
	t=b/d;
	x=x*n/d;
	x=(x%t+t)%t;
}
int gauss()
{
	//output();
	int t=0,zhi;  //zhi是矩阵的秩，t是最左边非零的列
	for(int i=0;i<n;++i)
	if(t>=n)break;
	else{
		bool flag=false;
		for(int j=i;j<m;++j)//寻找一个该位不为0的行
			if(a[j][t])
			{
				flag=true;
				if(j!=i)  for(int k=t;k<=n;++k) swap(a[i][k],a[j][k]);
				break;
			}
		if(!flag) i--;//当前列找不到，继续在该行找下一个
		else{
		zhi=i;//zhi记录最后一个不空的行,也就是秩
			for(int j=i+1;j<m;++j)//将所有行的t列清除
				if(a[j][t]){
					eculid(i,j,t);//辗转相除，直到其中一个为0，建立在需要mod某一个数的基础上，否则只能高精度
					if(!a[i][t]) for(int k=t;k<=n;++k) swap(a[i][k],a[j][k]);
				}
		}
		t++;		
	}
	for(int i=m-1;i>zhi;--i)   if(a[i][n]) return -1;  //若zhi行之后的a[i][n]不是0，则显然无解。
	if(zhi<n-1) return 0; //秩<n的话则有无数解
	for(int i=zhi;i>=0;--i)
	{
		for(int j=i+1;j<n;++j) a[i][n]=a[i][n]-a[i][j]*x[j];  //翻回求解
		a[i][n]=(a[i][n]%MOD+MOD)%MOD;
		a[i][i]=(a[i][i]%MOD+MOD)%MOD;
		module(a[i][i],7,x[i],a[i][n]);	//求逆，x[i]*a[i][i]==a[i][n] (mod 7)	
//		x[i]=a[i][n]*ni[a[i][i]]%MOD;
		if(x[i]<3) x[i]+=7;   //题目要求在3～9之间
	}
	return 1;	//唯一解
}
int main()
{
	freopen("g1.in","r",stdin);
	//freopen("g0.out","w",stdout);
	while(scanf("%d%d",&n,&m),n+m)	
	{
		input();
		int ret=gauss();
		if(ret==-1) printf("Inconsistent data.\n");
		else if(ret==0) printf("Multiple solutions.\n");
		else{
			for(int i=0;i<n-1;++i) printf("%d ",x[i]);			
			printf("%d\n",x[n-1]);
		}
	}
	return 0;
}
