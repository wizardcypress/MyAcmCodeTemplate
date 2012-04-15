/*
	给出n个模式串Si，然后给出一个字符串T，问模式串中有多少个Si是T字串（出现是指正或反向出现）
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxa 26
using namespace std;

struct node{
	int next[maxa];	
	int lab,fail; 
	bool collect; //这个点是否被收集过
	node(){
		memset(next,0,sizeof(next));
		fail=lab=collect=0;
	}
};
node a[250010];
int root,size; //root为1，0是个特殊点

int cs,n;
int que[250010],head,tail;
char _word[5100010],word[5100010];
int len;
bool ans[255];

void insert(int x,char *str,int num)
{
	int idx;
	while(*str){
		idx=str[0]-'A';
		if(a[x].next[idx]) x=a[x].next[idx];
		else {
			a[++size]=node();			
			x=a[x].next[idx]=size;
		}
		str++;
	}	
	a[x].lab=num;
}
void extra(char *str1,char *str2)
{
	len=0;
	int tmp=0;
	for(int i=0;str1[i];i++)
	{
		if(str1[i]=='['){
			tmp=0;
			for(i++;str1[i]>='0' && str1[i]<='9';i++)
				tmp=tmp*10+str1[i]-'0';
			while(tmp--) str2[len++]=str1[i];
			i++;
		}else str2[len++]=str1[i];
	}
	str2[len]=0;
}
void input()
{
	scanf("%d",&n);
	root=size=1;	
	a[0]=a[root]=node();
	for(int i=1;i<=n;i++)
	{
		scanf("%s",word);
		insert(root,word,i);
	}
	scanf("%s",_word);	
	extra(_word,word);		
}
void cal_fail()
{
	head=0,tail=1;
	que[0]=root;
	for(;head<tail;head++)
	{
		int p=que[head];
		for(int i=0;i<maxa;i++)
			if(a[p].next[i]){
				int q;
				for(q=a[p].fail; q && !a[q].next[i];q=a[q].fail) ;
				int nextq=a[a[p].next[i]].fail=(!q?root:a[q].next[i]);
				if(!a[a[p].next[i]].lab && a[nextq].lab) //某个字符串可能是当前点的后缀
					a[a[p].next[i]].lab=a[nextq].lab;
				que[tail++]=a[p].next[i];
			}else{  //加了这个就是trie图了，不加就是ac自动机,
				int q;
				for(q=a[p].fail; q && !a[q].next[i];q=a[q].fail) ;
				a[p].next[i]=(!q?root:a[q].next[i]); //这里直接指定p的儿子的位置
			}
	}
}
void cal_count(char *str)
{
	int p=root;
	int idx;
	for(int i=0;str[i];i++)
	{
		idx=str[i]-'A';
		p=a[p].next[idx]; //因为已经构成了一个DFA自动机，所以只需要直接转移就可以了		
		for(int q=p;q && a[q].lab && !a[q].collect;q=a[q].fail)
		{
			ans[a[q].lab]=true;
		    a[q].collect=true;
		}
	}
}
void solve()
{
	memset(ans,0,sizeof(ans));
	//first	
	cal_count(word);	
	
	//reset
	for(int i=0;i<=size;i++)
		a[i].collect=false;	
	reverse(word,word+len);
	
	//second
	cal_count(word);	
	
	int cnt=0;
	for(int i=1;i<=n;i++) cnt+=ans[i];
	printf("%d\n",cnt);
}
int main()
{	
	freopen("f.in","r",stdin);
	scanf("%d",&cs);
	while(cs--)
	{
		input();
		cal_fail();
		solve();
	}
	return 0;
}
