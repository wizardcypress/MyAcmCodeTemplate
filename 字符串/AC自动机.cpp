//n个病毒串构造自动机，然后找出一个长串中有多少种病毒串
#include<cstdio>
#include<cstring>
#include<queue>
#include<vector>
#include<cassert>
#define CHARSET 256
#define NONE -1
#define MAXN 40000

static const char cb64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
using namespace std;
//
int trie[MAXN][CHARSET];
int lab[MAXN];
int fail[MAXN];
bool collect[MAXN];
int root,size;
//
int n,m;
int keyword[2200];
int word[2200];
bool ans[520];
char str[2200];

int eval(char ch)
{
	for(int i=0;cb64[i];i++)
		if(cb64[i]==ch) return i;	
}
void decode(char *str,int res[])
{	
	int buf=0,cnt=0;
	for(int i=0;str[i] && str[i]!='=';i++)
	{
		int val=eval(str[i]);
		for(int j=5;j>=0;j--){
			cnt++;
			assert(val<64);
			if(val & (1<<j)) buf=buf*2+1;
			else buf=buf*2;
			if(cnt%8==0){
     			res[cnt/8-1]=buf;
				buf=0;
			}			
		}
	}
	res[cnt/8]=-1;
}
void insert(int str[],int num) //加入str，标注为num，str以-1结束
{
    int p=root;
	for(int i=0;str[i]!=-1;i++){
		int idx=str[i];
		if(trie[p][idx]==NONE) {
            fill(trie[size],trie[size]+CHARSET,NONE);
            fail[size]=lab[size]=NONE;
			trie[p][idx]=size++;
		}
        p=trie[p][idx];
	}
    lab[p]=num;
}
void input()
{
	root=0;
	size=1;
    fill(trie[0],trie[0]+CHARSET,NONE);
    lab[root]=NONE;  
	for(int i=1;i<=n;i++)
	{
		scanf("%s",str);
    	decode(str,keyword);
		insert(keyword,i);
	}
}
void cal_fail()
{
	queue<int> que;
    fail[root]=0;  
    for(int i=0;i<CHARSET;i++)
        if(trie[root][i]!=-1){
            fail[trie[root][i]]=0;
            que.push(trie[root][i]);
        }else trie[root][i]=0;
    
	while(!que.empty()){
		int p=que.front();  que.pop();
        if(lab[fail[p]]!=NONE && lab[p]==NONE)
            lab[p]=lab[fail[p]];
		for(int i=0;i<CHARSET;i++)
			if(trie[p][i]!=-1){
                fail[trie[p][i]]=trie[fail[p]][i];
                que.push(trie[p][i]);
			}else trie[p][i]=trie[fail[p]][i];
	}
}

void cal_count() //计算有多少个字符串是word的子串
{
	int p=root;
	for(int i=0;word[i]!=-1;i++)
	{
		int idx=word[i];
		p=trie[p][idx];
		int q=p;
		while(q && lab[q]!=NONE && !collect[q]){
			ans[lab[q]]=true;
			collect[q]=true;
			q=fail[q];
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
//	freopen("zju3430.in","r",stdin);	
	while(scanf("%d",&n)!=EOF)
	{		
		input();
		cal_fail();
		solve();
		printf("\n");
	}
	return 0;
}

