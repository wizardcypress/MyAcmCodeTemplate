#include<cstdio>
#include<cstring>

using namespace std;
struct EDGE{
	int v,next;
	int opp;
	bool able;	
}e[1200];
int beg[210];
int nE;
int n,m;
int deep[210];
bool keyPoint[210];
void add(int x,int y)
{
	nE++;
	e[nE].v=y;
	e[nE].able=true;
	e[nE].opp=nE+1;
	e[nE].next=beg[x];
	beg[x]=nE;
	
	nE++;
	e[nE].v=x;
	e[nE].able=true;
	e[nE].opp=nE-1;
	e[nE].next=beg[y];
	beg[y]=nE;
}
void input()
{
	int x,y;
	scanf("%d%d",&n,&m);
	nE=0;
	memset(beg,0,sizeof(beg));
	for(int i=0;i<m;++i)
	{
		scanf("%d%d",&x,&y);
		if(x==y) //自环		
		   add(x,++n); 
		else add(x,y);  //bidirection
	}
}
int dg(int x,int dep)
{
	int ret=0;
	deep[x]=dep;
	for(int i=beg[x];i;i=e[i].next)
	if(e[i].able){
		e[i].able=e[e[i].opp].able=false;		
		if(deep[e[i].v])
		{			
			keyPoint[e[i].v]=true;
			if((deep[x]-deep[e[i].v]+1)&1) return -1; //-1表示奇圈
			else return -2; //偶圈
		}
		else{					
			int tm=dg(e[i].v,dep+1);
			if(tm>=0) ret^=(tm+1);
			else {
				if(keyPoint[x])
				{ //连接环的关键点要进行运算
					if(tm==-1)	ret^=1;
					//keyPoint[x]=false;
				}else return tm;  //环中点直接返回
			}
		}
	}
	return ret;
}
int main()
{
	freopen("pku3710.in","r",stdin);
	int cs;
	int ans;
	while(scanf("%d",&cs)!=EOF)
	{
		ans=0;
		for(int t=1;t<=cs;++t)
		{
			input();
			memset(deep,0,sizeof(deep));
			memset(keyPoint,0,sizeof(keyPoint)); //链接环的关键点
			deep[1]=1;
			ans^=dg(1,1);
		}
		if(ans==0) printf("Harry\n");
		else printf("Sally\n");				
	}
	return 0;
}
