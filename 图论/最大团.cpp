#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
struct MaxClique //base from 0
{
	static const int MAXN=51; 
	int n,ne,max;
	int best[MAXN],rec[MAXN];
	bool link[MAXN][MAXN];
	
	MaxClique(int _n)
	{
		n=_n;
		clear();
	}
	void setn(int _n){ n=_n; }
	void clear()
	{
		memset(link,0,sizeof(link));		
	}
	void insert(int u,int v)
	{
		link[u][v]=link[v][u]=true;
	}
	bool dfs(int n,int u[],int size,int ret[])
	{
		if(n)
		{
			if(size+best[u[0]]<=max) return false;
			int v[MAXN],vn,i,j;
			for(i=0;i<size+n-max && i<n; i++)
			{
				for(vn=0,j=i+1;j<n;j++)
					if(link[u[i]][u[j]]) v[vn++]=u[j];
				rec[size]=u[i];
				if(dfs(vn,v,size+1,ret)) return true;				
			}
		}else if(size>max){
			max=size;
			for(int i=0;i<size;i++)
				ret[i]=rec[i];
			return true;
		}
		return false;
	}
	int max_clique(int ret[])
	{
		int v[MAXN],vn,i,j;
		max=0;
		for(i=n-1;i>=0;i--)
		{
			for(vn=0,j=i+1;j<n;j++)
				if(link[i][j]) v[vn++]=j;
			dfs(vn,v,1,ret);
			best[i]=max;
		}
		return max;
	}
};
