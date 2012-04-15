//avl--利用原来的sbt框架 
#include<stdio.h>
#include<algorithm>
      #define Type int    //此处定义Type的类型 
      #define MAXN 100010   //点数范围 
      #define MAXM 100010   //查询数范围 
using namespace std;
struct avl
{
  int size; //size是数据的规模，n是当前树中的节点数
  int s[MAXN],left[MAXN],right[MAXN],bal[MAXN];   //bal是平衡因子 
  bool solve;//solve是一个树中的一个信号，表示子树操作是否会对当前树的平衡造成威胁 
  Type data[MAXN];    
   avl (){  left[0]=right[0]=s[0]=bal[0]=size=0;data[0]=0;}  //构造函数，初始化 
    //各个函数的用法 
    /* void leftrotate(int &);    //左右旋转 
    void rightrotate(int &);
    void insert(int &,Type &);     //插入操作 
    Type Delete(int &,Type );//delete开头要大写，否则和关键字delete冲突 
    void maintain(int &,bool);  
	Type find_th(int &x,int w); //找出树中第w个的值 
	int find_pos(int &x,Type &w); //找出w在树中的位置，不存在则返回-1  
	*/
//左旋转操作
void leftrotate(int &x)
{
   int y=right[x];
   right[x]=left[y];
   left[y]=x;
   s[y]=s[x];
   s[x]=s[left[x]]+s[right[x]]+1;
   x=y;
} 
//右旋转操作
void rightrotate(int &x)
{
    int y=left[x];
    left[x]=right[y];
    right[y]=x;
    s[y]=s[x];
    s[x]=s[left[x]]+s[right[x]]+1;
    x=y;
} 
//tran操作，方便了平衡因子的计算
inline int tran(int x,int step)
{  int tmp[]={1,-1,0,1,-1},*p=tmp+2;
   if (x==0) return 0;    //如果left[right[x]] 或right[left[x]]平衡因子为0
   else return p[x+step];// 那么旋转之后x,和left[x]或right[x]平衡因子都为0 
}                         //否则按照找出的规律来计算    
//核心操作：maintain
void maintain(int &x)
{
	int y;
   if (bal[x]==-2)
   {
       if (bal[left[x]]==-1) {    //直接右旋转 
	      bal[x]=bal[left[x]]=0;   
	     rightrotate(x);	     
       }else if (bal[left[x]]==1) {
       	   y=right[left[x]];	 //先按照规律计算旋转后的平衡因子，再旋转 
		    bal[left[x]]=tran(bal[y],1);
			bal[x]=tran(bal[y],-1);	 
			bal[y]=0;  
		  leftrotate(left[x]);
		  rightrotate(x);  
        }else {    //如果不需要删除，此步不需要，但是当进行删除操作之后
		           //会导致这种情况的发生，需要进行考虑                
		   bal[x]=-1;bal[left[x]]=1;
		   rightrotate(x);
		}
   }
   else {
       if (bal[right[x]]==1){
       	  bal[x]=bal[right[x]]=0;
       	  leftrotate(x);	   
	   } else if (bal[right[x]]==-1){
	       y=left[right[x]];	       
	       bal[right[x]]=tran(bal[y],-1);
	       bal[x]=tran(bal[y],1);
	       bal[y]=0;
	       rightrotate(right[x]);
	       leftrotate(x);
	   } else {
	      bal[x]=1;bal[right[x]]=-1;
	      leftrotate(x);
	   }
    }   
}
 //插入节点
void  insert(int &x,Type &w) 
    {
	   if (x==0){
		   x=++size;
		   data[x]=w;
		   left[x]=right[x]=bal[x]=0;
		   s[x]=1;  
		   solve=false;      //刚插入后可能会导致不平衡 
		} else { 
		    ++s[x]; 
		    if (w<data[x])  insert(left[x],w);
		     else insert(right[x],w);
		   if (!solve){     //如果插入操作对当前的平衡造成威胁，进行处理 
               bal[x]+=(w>=data[x])-(w<data[x]);//修改平衡因子 
              if (bal[x]>1||bal[x]<-1) maintain(x);
		                      //调整平衡后一定不对父节点造成威胁 
			  solve=bal[x]==0;//如果加入点后进行调整或加1减1使当前的树平衡，
			 }                 //那么也不会对父节点造成威胁	   			  	 			 	       
		}
    }
//删除操作 
Type Delete(int &x,Type w)
{   
    Type tmp;
    --s[x];
    if (data[x]==w||w<data[x]&&left[x]==0||w>data[x]&&right[x]==0)
     {
	    tmp=data[x];
	     if (left[x]==0||right[x]==0){    //直接删除，并且可能对父节点造成威胁 
	       x=left[x]+right[x],solve=false;            
	     }else {
		    data[x]=Delete(left[x],data[x]); //转嫁节点来间接删除 
	       if (!solve){        
	       	  if (++bal[x]>1) maintain(x);//不平衡则调整。但是这里与插入操作不同， 
                         //平衡操作之后当前树的高度会减小，是会威胁到父节点的平衡 
	       	  solve=bal[x]!=0;//如果因为删除而平衡因子由0变为1或-1，那么树的高度
                             //是不变的，不会对父节点造成威胁,相反，如果通过调整
							//或直接加1或减1达到0的话，树的高度就减小了，有威胁		  			
			}		  
         }        
	 }
     else {
    	tmp=w<data[x]?Delete(left[x],w):Delete(right[x],w);
		if (!solve){
		  bal[x]+=(w<data[x])-(w>=data[x]);//修改平衡因子，但是要记住插入和删除的不同 
		  if (bal[x]>1||bal[x]<-1)  maintain(x);//调整，解释和上面一样 
		  solve=bal[x]!=0; 
		}   	    	
     }
   return tmp; 
}
//查找树中第w个 
Type find_th(int &x,int w)
{
   if (w==s[left[x]]+1)  return data[x];
   else if (w<=s[left[x]])	return find_th(left[x],w);
   else return find_th(right[x],w-s[left[x]]-1); 	
}
//找出w在树中的位置
int find_pos(int &x,Type &w)
{
    if (x==0||w<data[x]&&left[x]==0||w>data[x]&&right[x]==0)return -1;
      else if (w==data[x])return s[left[x]]+1;
	  	else {
	      int tmp=find_pos(w<data[x]?left[x]:right[x],w);
         if (tmp==-1) return -1;
          else  return tmp+(w<data[x]?0:s[left[x]]+1);
	  }
} 
};
//实际运行程序 
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
   avl zoo;
    int i,j;
	  scanf("%d%d",&n,&m);      
	  for( i=0;i<n;++i) scanf("%d",&abl[i+1]);	
	  for( i=0;i!=m;++i) scanf("%d%d%d",&itr[i].x,&itr[i].y,&itr[i].z),itr[i].num=i;
      sort(itr,itr+m,cmp);

	  root=0;
	 for ( i=itr[0].x;i<=itr[0].y;++i)
	      zoo.insert(root,abl[i]);
       for ( i=1;i<m;++i)
	   {
	   	  ans[itr[i-1].num]=zoo.find_th(root,itr[i-1].z);
	       for ( j=itr[i-1].x;j<=min(itr[i-1].y,itr[i].x-1);++j)
	           zoo.Delete(root,abl[j]);
	       for ( j=max(itr[i-1].y+1,itr[i].x);j<=itr[i].y;++j)
		       zoo.insert(root,abl[j]);     
	   }      
      ans[itr[m-1].num]=zoo.find_th(root,itr[m-1].z);
	  for ( i=0;i<m;++i)	
		  printf("%d\n",ans[i]);		  
   return 0;
}

