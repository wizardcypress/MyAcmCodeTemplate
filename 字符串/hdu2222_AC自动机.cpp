#include<cstdio>
#include<cstring>
#include<queue>
#define maxa 26  //最大字符集
using namespace std;

struct node{ 
	node *fail; //定义失败指针
	node *next[maxa];  //trie指针
	int count;
	node(){
		fail=NULL;
		count=0;
		memset(next,0,sizeof(next));
	}
};
node *root;
int n,m;
int ans;
char keyword[60];
char word[1000010];
int cs;
void insert(char *str,node *p)  //构造trie
{		
	for(int i=0;str[i];i++)
	{
		int idx=str[i]-'a';
		if(!p->next[idx]) p=p->next[idx]=new node();
		else p=p->next[idx];		
	}
	p->count++;
}
void input()
{		
	scanf("%d",&n);	
	root=new node();
	for(int i=0;i<n;++i)
	{
		scanf("%s",keyword);
		insert(keyword,root);				
	}
	scanf("%s",word);
}
void cal_fail() //bfs计算fail值
{
	queue<node *> que;
	que.push(root);
	root->fail=NULL;
	while(!que.empty())
	{
		node *p=que.front();
		que.pop();
		for(int i=0;i<maxa;++i)		
			if(p->next[i])
			{
				node *q;
				//ac自动机的精华所在，类似于kmp的寻找fail位置一样
				for(q=p->fail;q && !q->next[i] ; q=q->fail) ;	
				p->next[i]->fail=(!q?root:q->next[i]);//如果找到的是一个空指针，那么fail指向根
				que.push(p->next[i]);//加入到队列中
			}
	}
}
void cal_count() //计算某单词出现的次数，实际做的时候根据题目具体情况决定，对于后缀包含的情况要具体而定
{	
	node *p=root;
	ans=0;
	for(int i=0;word[i];++i)
	{
		int idx=word[i]-'a';
		while (p && !p->next[idx]) p=p->fail;
		if(!p) p=root;
		else p=p->next[idx];		
		node *q=p;
		while(q && q->count!=-1){  //把所有被该后缀包含的所有单词都算进去
			ans+=q->count;
			q->count=-1;
			q=q->fail;
		}
	}
}
int main()
{	
	freopen("hdu2222.in","r",stdin);
	scanf("%d",&cs);
	while(cs--)
	{
		input();
		cal_fail();
		cal_count();
		printf("%d\n",ans);
	}
	return 0;
}

