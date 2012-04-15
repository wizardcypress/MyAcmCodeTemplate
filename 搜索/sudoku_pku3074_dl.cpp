#include<cstdio>
#include<algorithm>
#include<cstring>
#define INF 1000000000
#define N 300000
using namespace std;
int n,m;
int l[N],r[N],c[N],u[N],d[N],name[N];//c是表示该点所属的列，name则表示所属的行
bool used[N]; 
int s[N];
int h,tot;
char str[100];
int ans[10][10];
void add(int x,int &head,int flag) /*add x to head,flag==0 add row*/
{
	if(flag==0){ //row
		if(head==-1) //行的第一个
		{
			head=x;
			l[x]=r[x]=x;
		}
		l[x]=l[head];
		r[l[head]]=x;
		r[x]=head;
		l[head]=x;
	}else{
		u[x]=u[head];
		d[u[head]]=x;
		d[x]=head;
		u[head]=x;
	}
}
void input()
{
	tot=h=0;
	l[h]=r[h]=h;
	for(int j=1;j<=81*4;j++)
	{
		add(++tot,h,0);
		u[tot]=d[tot]=c[tot]=tot;
	}
	memset(s,0,sizeof(s));
	for(int i=1;i<=81;i++)
	{
		int row=(i-1)/9+1,col=(i-1)%9+1,grid=(row-1)/3*3+(col-1)/3+1;
		//printf("%d %d %d\n",row,col,grid);
		if(str[i-1]!='.'){
			int curhead=-1;
			int j=str[i-1]-'0';
			add(++tot,curhead,0); add(tot,c[(row-1)*9+j],1); c[tot]=(row-1)*9+j;
			s[c[tot]]++;  name[tot]=row*100+col*10+j;
			
			add(++tot,curhead,0); add(tot,c[81+(col-1)*9+j],1); c[tot]=81+(col-1)*9+j;
			s[c[tot]]++;  name[tot]=row*100+col*10+j;
			
			add(++tot,curhead,0); add(tot,c[81*2+(grid-1)*9+j],1); c[tot]=81*2+(grid-1)*9+j;
			s[c[tot]]++;  name[tot]=row*100+col*10+j;
			
			add(++tot,curhead,0); add(tot,c[81*3+i],1); c[tot]=81*3+i;
			s[c[tot]]++;  name[tot]=row*100+col*10+j;
		}else{
			int curhead;
			for(int j=1;j<=9;j++)
			{
			curhead=-1;
			add(++tot,curhead,0); add(tot,c[(row-1)*9+j],1); c[tot]=(row-1)*9+j;
			s[c[tot]]++;  name[tot]=row*100+col*10+j;
			
			add(++tot,curhead,0); add(tot,c[81+(col-1)*9+j],1); c[tot]=81+(col-1)*9+j;
			s[c[tot]]++;  name[tot]=row*100+col*10+j;
			
			add(++tot,curhead,0); add(tot,c[81*2+(grid-1)*9+j],1); c[tot]=81*2+(grid-1)*9+j;
			s[c[tot]]++;  name[tot]=row*100+col*10+j;
			
			add(++tot,curhead,0); add(tot,c[81*3+i],1); c[tot]=81*3+i;
			s[c[tot]]++;  name[tot]=row*100+col*10+j;
			}
		}
	}		
	memset(used,0,sizeof(used));
	memset(ans,0,sizeof(ans));
}

void cover(int col)
{
	  r[l[col]]=r[col];
	  l[r[col]]=l[col];
	  for(int row=d[col];row!=col;row=d[row])
	  	for(int j=r[row];j!=row;j=r[j])
	  	{
			   u[d[j]]=u[j];
			   d[u[j]]=d[j];
			   s[c[j]]--;
		}  
}
void uncover(int col)
{    
	for(int row=u[col];row!=col;row=u[row])
		for(int j=l[row];j!=row;j=l[j])	
		{     
			 u[d[j]]=j;
			 d[u[j]]=j;
			 s[c[j]]++;
		 }			 
     l[r[col]]=col;
     r[l[col]]=col;
}
void output()
{
	int cnt=-1;
	for(int i=1;i<=9;i++)
		for(int j=1;j<=9;j++)
		{
			cnt++;
			if(str[cnt]=='.') str[cnt]=ans[i][j]+'0';
		}
	printf("%s\n",str);
} 
bool search()
{
	 if(r[h]==h) {
		     output();		  
		     return true;
	 }else{
			 //select minimal column
		    int mm=INF,col;		    
		    for(int i=r[h];i!=h;i=r[i])
		    	if(s[i]<mm) mm=s[i],col=i;
		    	
		     //cover that column
		     cover(col);
		     for(int row=d[col];row!=col;row=d[row])
		     {		     
				 //used[name[row]]=true;
				 ans[name[row]/100][name[row]%100/10]=name[row]%10;
				 for(int j=r[row];j!=row;j=r[j]) cover(c[j]);			     
			     if(search()) return true;
			     ans[name[row]/100][name[row]%100/10]=0;
			     for(int j=l[row];j!=row;j=l[j]) uncover(c[j]);
         		 //used[name[row]]=false;	             
			 }
			 uncover(col);
			return false;
	}
}
int main()
{
	//freopen("pku3074.in","r",stdin);
    while(scanf("%s",str),strcmp(str,"end")!=0)
	{
	    input();
	    if(!search()) printf("No solution?\n");
    }
	  return 0;
	}
