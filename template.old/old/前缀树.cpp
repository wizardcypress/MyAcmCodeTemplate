/*
  前缀树，用于多串的字符匹配。
  就是说给出一些字符串集合{S1,S2,..}，
  在给出的长串字符T中找出和字符集合中匹配的部分。
  利用kmp原理，通过将字符串集合建成一棵前缀树，就可以在线性时间内
  找出匹配的地方。
  具体参照2004年朱泽园：《多串匹配算法及其启示》
*/
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
#define MAXN 100010
#define MAXM 1010
using namespace std;
struct node{
   int okay;
   node *prefix;
   node *next[26];
   node(){
	 prefix=NULL;
     for(int i=0;i<26;++i) next[i]=NULL;
	 okay=0;
   }
};
queue<node*> que;
int l[MAXM];
char s[MAXM][1010];
char t[100010];
int n,m;
int ans[100010],len;
node *root;
void init()
{
    scanf("%d%d\n",&m,&n);
	for(int i=1;i<=m;++i)
	{
	   scanf("%s\n",s[i]);
	   l[i]=strlen(s[i]);
	}
	scanf("%s\n",t);
}
void construct()
{
	node *q,*p;
	char ch;
    root=new node;
	for(int i=1;i<=m;++i)
	{
	    q=root;
		for(int j=0;j<l[i];++j)		
			if(q->next[ch=s[i][j]-'a']==NULL){
		       q->next[ch]=p=new node;
			   q=p;
		}else q=q->next[ch];	 
	   q->okay=i;
	}
}
void makeprefix()
{
	node *q,*p,*tmp;
	int i;
    que.push(root);
	while(!que.empty())
	{
	   q=que.front();
	   que.pop();
       for(i=0;i<26;++i)
		   if(q->next[i]!=NULL){
			   tmp=q;
			   p=q->next[i];
			   while(q!=root&&(q->next[i]==NULL||q->next[i]==p)) q=q->prefix;
			   if(q->next[i]==NULL||q->next[i]==p) p->prefix=root;
			   else {				   
				   p->prefix=q->next[i];
				   if(!p->okay) p->okay=q->next[i]->okay;
			   }

			   q=tmp;
			   que.push(p);
		   }
	}
}
void match()
{
	node *p,*q;
	char ch;
	q=root;
	len=0;
    for(int i=0;i<n;++i)
	{
		ch=t[i]-'a';
	    while(q!=root&&q->next[ch]==NULL) 
			q=q->prefix;
		 if(q->next[ch]!=NULL) q=q->next[ch];
		 if(q->okay) ans[++len]=i-l[q->okay]+1;		 
	}
}
void print()
{
    sort(ans+1,ans+len+1);
	for(int i=1;i<=len;++i) printf("%d\n",ans[i]+1);
}
int main()
{
	freopen("test.in","r",stdin);
	  init();
	  construct();
	  makeprefix();
	  match();
	  print();
	return 0;
}
