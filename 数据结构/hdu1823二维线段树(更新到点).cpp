/*
	 更新到点的二维线段树，需要注意的两个地方是：
	 1.更新到点的时候，第一区间的祖先区间都要进行更新。
	 2.在更新第二区间时，因为对于该第二区间所属的第一区间而言，
	   第二区间的一个格子是代表了实际的一行格子
       所以更新时是需要进行更优判断的。
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<iostream>
#define N 4000
using namespace std;
int m;
struct TREE{
	int maxLove[4*N];   //二维线段树
}mm[400];

struct POINT{
	double data;
	int pos;
};

POINT cord[100000][4];

int instr[1000000];
int n;
int tg1,tg2;
int ll1,rr1,ll2,rr2;

void input()
{
	char task;	
	for(int i=0;i<m;++i)
	{
		scanf("%c",&task);	
		if(task=='I'){
			instr[i]=1;
			scanf("%d%lf%lf\n",&cord[i][0].pos,&cord[i][1].data,&cord[i][2].data);			
			cord[i][0].pos-=100;
			cord[i][1].pos=cord[i][1].data*10;
			cord[i][2].pos=cord[i][2].data*10;			
		}else{
			instr[i]=2;
			scanf("%d%d%lf%lf\n",&cord[i][0].pos,&cord[i][1].pos,&cord[i][2].data,&cord[i][3].data);
			cord[i][0].pos-=100;
			cord[i][1].pos-=100;						
			cord[i][2].pos=cord[i][2].data*10;
			cord[i][3].pos=cord[i][3].data*10;			
		}
	}	

}
void insert2(TREE &curT,int x,int l,int r,int keypos)
{
	if(tg2<l || tg2>r) return ;
	if(l==r){
	 //这一句相当重要，因为对于第一区间而言，第二区间的一个格子是代表了实际的一行格子
	 //所以更新时是需要进行判断的。
		if(keypos>curT.maxLove[x]) 
			curT.maxLove[x]=keypos;	
		return ;
	}
	insert2(curT,x*2,l,(l+r)/2,keypos);	
	insert2(curT,x*2+1,(l+r)/2+1,r,keypos);
	curT.maxLove[x]=curT.maxLove[x*2];
	if(curT.maxLove[x*2+1]>curT.maxLove[x]) curT.maxLove[x]=curT.maxLove[x*2+1];
}
void insert1(int x,int l,int r,int key)
{
	if(tg1<l || tg1>r) return ;
	if(l==r){
		insert2(mm[x],1,0,1000,key);
		return ;
	}	//每一个祖先区间都要进行第二区间更新
		insert2(mm[x],1,0,1000,key);//ancestor change
	
		insert1(x*2,l,(l+r)/2,key);
		insert1(x*2+1,(l+r)/2+1,r,key);	
}
int find2(TREE &curT,int x,int l,int r)
{
	if(rr2<l || r<ll2) return -1;
	if(ll2<=l && r<=rr2){
		return curT.maxLove[x];
	}else{
		int d1=find2(curT,x*2,l,(l+r)/2);
		int d2=find2(curT,x*2+1,(l+r)/2+1,r);
		if(d1>d2) return d1;
		else return d2;
	}
}
int find1(int x,int l,int r)
{	
	if(rr1<l || r<ll1) return -1;
	if(ll1<=l && r<=rr1){
		return find2(mm[x],1,0,1000);
	}else{
		int d1=find1(x*2,l,(l+r)/2);
		int d2=find1(x*2+1,(l+r)/2+1,r);
		if(d1>d2) return d1;
		else return d2;
	}
}
void solve()
{
	int ans;
	for(int i=0;i<400;++i)
		memset(mm[i].maxLove,255,sizeof(mm[i].maxLove));
	
	for(int i=0;i<m;++i)
	{
		if(instr[i]==1){
			tg1=cord[i][0].pos;
			tg2=cord[i][1].pos;	
			insert1(1,0,100,cord[i][2].pos);
		}else{
			ll1=cord[i][0].pos;
			rr1=cord[i][1].pos;
			ll2=cord[i][2].pos;
			rr2=cord[i][3].pos;
			if(ll1>rr1) swap(ll1,rr1);
			if(ll2>rr2) swap(ll2,rr2);			
				ans=find1(1,0,100);
				if(ans<0) printf("-1\n");
				else printf("%.1f\n",ans*1.0/10);			
		}
	}
}
int main()
{
	freopen("hdu1823.in","r",stdin);
	while(scanf("%d\n",&m),m)
	{
		input();
		solve();
	}
	return 0;
}
