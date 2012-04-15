#include<cstdio>
#include<cstring>
#include<set>
#include<vector>
#include<algorithm>
#define maxn 200010
using namespace std;
struct TASK{
  int task; /*1 add; 2 remove; 3 find*/
  int x,y;
  int idx,idy;
};
struct HNODE{
  int val;
  int id;
  bool operator<(const HNODE &that)const 
  {
    return val<that.val;
  }
};

TASK tlst[maxn];
HNODE hx[maxn],hy[maxn];
int px[maxn],py[maxn];
set<int> st[maxn];
int maxy[maxn*4];
int mdx;
int n;

void input()
{
  char cmd[100];
  int x,y;
  for(int i=0;i<n;i++) st[i].clear();
  for(int i=0;i<n;i++)
    {
      scanf("%s%d%d",cmd,&x,&y);
      if(strcmp(cmd,"add")==0) tlst[i].task=1;
      else if(strcmp(cmd,"remove")==0) tlst[i].task=2;
      else tlst[i].task=3;
      
      tlst[i].x=x;
      tlst[i].y=y;
      
      hx[i].id=i;
      hx[i].val=x;

      hy[i].id=i;
      hy[i].val=y;
    }
  
  sort(hx,hx+n);
  sort(hy,hy+n);

  int idx=0,idy=0;
  mdx=0;
  for(int i=0;i<n;i++)
    {
      if(i!=0 && hx[i].val!=hx[i-1].val) idx++;
      if(i!=0 && hy[i].val!=hy[i-1].val) idy++;
      
      tlst[hx[i].id].idx=idx;
      px[idx]=hx[i].val;
      
      tlst[hy[i].id].idy=idy;
      py[idy]=hy[i].val;
    }
  mdx=idx;
}
void insert(int v,int l,int r,int &x,int &y)
{
  if(x<l || r<x) return ;
  if(l==r){
  	st[l].insert(y);
    if(y>maxy[v]) maxy[v]=y;
  }else {
    if(x<=(l+r)/2) insert(v*2,l,(l+r)/2,x,y);
    else insert(v*2+1,(l+r)/2+1,r,x,y);
    if(maxy[v*2]>maxy[v*2+1]) maxy[v]=maxy[v*2];
    else maxy[v]=maxy[v*2+1];
  }
  
}
void remove(int v,int l,int r,int &x,int &y)
{
  if(x<l || r<x) return ;
   if(l==r){
	st[l].erase(y);
	if(st[l].size()==0) maxy[v]=-1;
	else {
		set<int>::iterator it=st[l].end();
		it--;
		maxy[v]=*it;
	}
  }else {
    if(x<=(l+r)/2) remove(v*2,l,(l+r)/2,x,y);
     else remove(v*2+1,(l+r)/2+1,r,x,y);
      if(maxy[v*2]>maxy[v*2+1]) maxy[v]=maxy[v*2];
     else maxy[v]=maxy[v*2+1];
  }
}
bool find(int v,int l,int r,int &x,int &y,int &retx,int &rety)
{
  if(x>=r) return false;
  if(maxy[v]<=y) return false;
  if(l==r)
  {
    set<int>::iterator it=st[l].upper_bound(y);
    if(it==st[l].end()) return false;
    retx=l;
    rety=*it;
    return true;
  }else{
    if(find(v*2,l,(l+r)/2,x,y,retx,rety)) return true;
    else return find(v*2+1,(l+r)/2+1,r,x,y,retx,rety);
  }
}
void solve()
{
  memset(maxy,255,sizeof(maxy));
  for(int i=0;i<n;i++)
    {
      if(tlst[i].task==1) insert(1,0,mdx,tlst[i].idx,tlst[i].idy);
      else if(tlst[i].task==2) remove(1,0,mdx,tlst[i].idx,tlst[i].idy);
      else {
        int x=-1,y=-1;
        if(!find(1,0,mdx,tlst[i].idx,tlst[i].idy,x,y))
          printf("-1\n");
        else printf("%d %d\n",px[x],py[y]);
      }
    }
}
int main()
{
  freopen("hdu3627.in","r",stdin);
  int cs=0;
  while(scanf("%d",&n),n)
    {
    	if(cs!=0) printf("\n");
      printf("Case %d:\n",++cs);
      input();
      solve();
    }
  return 0;
}

