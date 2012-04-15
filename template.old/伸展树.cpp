//伸展树
#include<stdio.h>
#include<algorithm>
      #define MAXN 100010
      #define MAXM 100010
      #define Type int
using namespace std;
struct splayTree{
    int size,root;  // 树的大小和根的编号
    int s[MAXN],left[MAXN],right[MAXN];  //儿子个数，左儿子，右儿子
    Type data[MAXN];   //节点的值
    splayTree () { s[0]=left[0]=right[0]=size=0; root=0; }  
    /*
    void leftrotate(int &);
    void rightrotate(int &);
    int splay(int &,int );
    void insert(int &,int ,Type &w);
    Type Delete(int &,Type &);   
    Type find_th(int &,Type &)
    */
void leftrotate(int &x)  //左旋转
{ 
    int y=right[x];
    right[x]=left[y];
	left[y]=x;
	s[y]=s[x];
	s[x]=s[left[x]]+s[right[x]]+1;
	x=y;	
}
void rightrotate(int &x)  //右旋转
{
   int y=left[x];
   left[x]=right[y];
   right[y]=x;
   s[y]=s[x];
   s[x]=s[left[x]]+s[right[x]]+1;
   x=y;  
}
int splay(int &x,int kth)  //核心部分  返回第kth个值，并且把它旋转到根
{
	int y,z;
    if (s[left[x]]+1==kth)  return x;
    if (kth<=s[left[x]]){
	    y=left[x];
		if (kth==s[left[y]]+1) return rightrotate(x),y;
	    if (kth<=s[left[y]])  {
		   z=splay(left[y],kth);
		   rightrotate(left[x]);
		   rightrotate(x);  
		   return z;
		}else {
		  z=splay(right[y],kth-s[y]-1);
		  leftrotate(left[x]);
		  rightrotate(x);
		  return z;
		}
	} else {
	  y=right[x];
	  kth=kth-s[left[x]]-1;
	  if (kth==s[left[y]]+1)  return leftrotate(x),y;
	  if (kth<=s[left[y]]) {
	  	  z=splay(left[y],kth);
	  	  rightrotate(right[x]);
	  	  leftrotate(x);
	  	  return z;
	  } else {
	    z=splay(right[y],kth-s[left[y]-1]);
	    leftrotate(right[x]);
	    leftrotate(x);
	    return z;
	  }	  
	}
}
void  insert(int &x,int kth,Type &w)  //插入w，并且得到w的位置，然后把w转到根处
{
   if (x==0){
       x=++size;
       data[x]=w;
	   left[x]=right[x]=0;
	   s[x]=1;       
      splay(root,kth+1);
   } else  {
   	++s[x];
   if (w<data[x])  insert(left[x],kth,w);
      else insert(right[x],kth+s[left[x]]+1,w);
   }
}
Type Delete(int &x,Type &w)  //删除w,借鉴sbt的删除方法
{
   --s[x];
   if (data[x]==w||w<data[x]&&left[x]==0||w>data[x]&&right[x]==0)
   {   	  
       Type tmp=data[x];
       if (left[x]==0||right[x]==0)   
	      x=left[x]+right[x];
        else data[x]=Delete(left[x],data[x]);
     return tmp;
   }else  if (w<data[x]) return Delete(left[x],w);
    else return Delete(right[x],w); 
}
Type find_th(int &x,int w)   //找出w排第几
{
    if (s[left[x]]+1==w)  return data[x];
     else if (w<data[x])  return find_th(left[x],w);
      else return find_th(right[x],w-s[left[x]]-1);
}
}; 
//以上为splay树的主要部分


struct interval{
     int x,y,z,num; 
  };
int root=0,n,m,i,l,r,j;
int abl[MAXN];
interval itr[MAXM];
int ans[MAXM];
 
bool cmp(const interval &p1,const interval &p2) 
{  return p1.x<p2.x;   }
inline int  max(int x,int y) {  return x>y?x:y;}
inline int  min(int x,int y)  {  return x<y?x:y;}
int main()
{    
   freopen("zoo.in","r",stdin);
   freopen("zoo.out","w",stdout);
   splayTree zoo;
    int i,j;
	  scanf("%d%d",&n,&m);      
	  for( i=0;i<n;++i) scanf("%d",&abl[i+1]);	
	  for( i=0;i!=m;++i) scanf("%d%d%d",&itr[i].x,&itr[i].y,&itr[i].z),itr[i].num=i;
      sort(itr,itr+m,cmp);
	
	 for ( i=itr[0].x;i<=itr[0].y;++i)
	      zoo.insert(zoo.root,0,abl[i]);
       for ( i=1;i<m;++i)
	   {
	   	  ans[itr[i-1].num]=zoo.find_th(zoo.root,itr[i-1].z);
	       for ( j=itr[i-1].x;j<=min(itr[i-1].y,itr[i].x-1);++j)
	           zoo.Delete(zoo.root,abl[j]);
	       for ( j=max(itr[i-1].y+1,itr[i].x);j<=itr[i].y;++j)
		       zoo.insert(zoo.root,0,abl[j]);     
	   }      
      ans[itr[m-1].num]=zoo.find_th(zoo.root,itr[m-1].z);
	  for ( i=0;i<m;++i)	
		  printf("%d\n",ans[i]);		  
   return 0;
}

