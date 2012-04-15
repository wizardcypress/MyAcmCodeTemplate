#include<cstdio>
#include<cstring>
#define maxn 30
//male-optimal,谁求婚则谁优先
using namespace std;
int ra[maxn][maxn],rb[maxn][maxn]; //ra[i][j] i对j的排名，1最高
int ach[maxn],bch[maxn]; //a，b的选择配偶
int list[maxn][maxn]; //b的求婚队列
bool deny[maxn][maxn]; //deny[i][j]表示i是否拒绝过j
int n,cs;
void input()
{
	char str[40];
	scanf("%d",&n);
	for(int i=1;i<=2*n;i++)
		scanf("%s",str);
	memset(ra,0,sizeof(ra));
	memset(rb,0,sizeof(rb));
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str);
		//printf("%s\n",str);
		int u=str[0]-'a'+1;		
		for(int j=2;str[j];j++)
			ra[u][str[j]-'A'+1]=j-1;
	}
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str);
		int u=str[0]-'A'+1;
		for(int j=2;str[j];j++)
			rb[u][str[j]-'a'+1]=j-1;
	}
}
void stable_marriage()
{
	memset(ach,0,sizeof(ach));
	memset(bch,0,sizeof(bch));
	memset(deny,0,sizeof(deny));
	bool all_married;	
	do{
		all_married=true;		
		for(int i=1;i<=n;i++) list[i][0]=0;
		//for male
		for(int i=1;i<=n;i++)  //每轮所有男士对尚未拒绝他的女士中选出最喜欢的求婚
			if(!ach[i]){
				all_married=false;
				int rank=n+1,who=-1;
				for(int j=1;j<=n;j++)
					if(!deny[j][i] && ra[i][j]<rank) rank=ra[i][j],who=j;					
				list[who][++list[who][0]]=i;
			}
		if(all_married) break;
		//for femal
		for(int i=1;i<=n;i++) //女士处理求婚队列，如果有更好则拒绝其他。
		{ 
			for(int j=1;j<=list[i][0];j++)
				if(bch[i]==0 || rb[i][list[i][j]]<rb[i][bch[i]]){
					if(bch[i]==0){
						bch[i]=list[i][j];
						ach[list[i][j]]=i;
					}else {
						deny[i][bch[i]]=true;
						ach[bch[i]]=0;
						ach[list[i][j]]=i;
						bch[i]=list[i][j];
					}
				}else deny[i][list[i][j]]=true;				
		}							
	}while(!all_married);
	
}
void print()
{	
	for(int i=1;i<=n;i++)	
		printf("%c %c\n",i+'a'-1,ach[i]+'A'-1);
}
int main()
{
	freopen("pku3487.in","r",stdin);
	scanf("%d",&cs);
	while(cs--)
	{
		input();
		stable_marriage();
		print();
		if(cs!=0) printf("\n");
	}
	return 0;
}
