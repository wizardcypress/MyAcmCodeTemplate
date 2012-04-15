#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<cassert>
#define maxa 256

static const char cb64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

using namespace std;

struct node{
	int fail,next[maxa];
	int lab;
	node(){
		fail=0;
		memset(next,0,sizeof(next));
		lab=0;
	}
};
node a[40000];
bool collect[40000];
int root,size;
//
int n,m;
int keyword[2200];
int word[2200];
bool ans[520];
char str[2200];
void err()
{
	int zero=0;
	zero=1/zero;
}
int eval(char ch)
{
	for(int i=0;cb64[i];i++)
		if(cb64[i]==ch) return i;	
	err();			
}
void decode(char *str,int res[])
{	
	int buf=0,cnt=0;
	for(int i=0;str[i] && str[i]!='=';i++)
	{
		if(i>=64) err();
		int val=eval(str[i]);
		for(int j=5;j>=0;j--){
			cnt++;
			assert(val<64);
			if(val & (1<<j)) buf=buf*2+1;
			else buf=buf*2;
			if(cnt%8==0){
				if(buf>=256) err();
				res[cnt/8-1]=buf;
				buf=0;
			}			
		}
	}
	res[cnt/8]=-1;
}
void insert(int p,int str[],int num)
{
	for(int i=0;str[i]!=-1;i++){
		if(i>=64) err();
		if(str[i]>=256) err();
		int idx=str[i];
		if(!a[p].next[idx]) {
			a[++size]=node();
			p=a[p].next[idx]=size;
		}else p=a[p].next[idx];
	}
	a[p].lab=num;
}
void input()
{
	root=1;
	size=1;
	a[1]=node();
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str);
		if(strlen(str)>64) err();
		decode(str,keyword);
		insert(root,keyword,i);
	}
}
void cal_fail()
{
	queue<int> que;
	que.push(root);
	a[root].fail=0;
	while(!que.empty()){
		int p=que.front();
		que.pop();
		for(int i=0;i<maxa;i++)
			if(a[p].next[i]){
				int q;
				for(q=a[p].fail;q && !a[q].next[i]; q=a[q].fail) ;
				int nextq=a[a[p].next[i]].fail=(!q?root:a[q].next[i]);
				if(!a[a[p].next[i]].lab && a[nextq].lab)
					a[a[p].next[i]].lab=a[nextq].lab;
				que.push(a[p].next[i]);
			}else {
				int q;
				for(q=a[p].fail;q && !a[q].next[i]; q=a[q].fail) ;
				a[p].next[i]=(!q?root:a[q].next[i]);
			}
	}
}

void cal_count()
{
	int p=root;
	for(int i=0;word[i]!=-1;i++)
	{
		int idx=word[i];
		p=a[p].next[idx];
		int q=p;
		while(q && a[q].lab && !collect[q]){
			ans[a[q].lab]=true;
			collect[q]=true;
			q=a[q].fail;
		}
	}
}
void solve()
{
	scanf("%d",&m);
	for(int i=1;i<=m;i++)
	{
		scanf("%s",str);
		decode(str,word);
		memset(ans,0,sizeof(ans));
		memset(collect,0,sizeof(collect));		
		cal_count();
		int cnt=0;
		for(int i=1;i<=n;i++) cnt+=ans[i];
		printf("%d\n",cnt);
	}
}
int main()
{
	freopen("zju3430.in","r",stdin);	
	while(scanf("%d",&n)!=EOF)
	{		
		input();
		cal_fail();
		solve();
		printf("\n");
	}
	return 0;
}

