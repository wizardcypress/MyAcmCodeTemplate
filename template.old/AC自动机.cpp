/*AC自动机（多串匹配），要求出所有可能匹配的单词是要
注意匹配完后利用next函数统计相关的后缀，若存在相同的
单词的时候要特殊处理（这里没作处理）*/
#include<iostream>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
#define fod(i,u,d) for (long i=(u); i>=(d); --i)
using namespace std;

const long maxn=1001;
const long maxm=100000;
const long maxa=26;
const long f[4][3][2]={1,-1,1,1,1,0,  -1,1,1,1,0,1,  -1,1,-1,-1,-1,0,  -1,-1,1,-1,0,-1};
const char c[4][3]={     'B','H','A',       'F','H','G',        'F','D','E',          'D','B','C',};

//next为fail指针
long trie[maxm][maxa],next[maxm],lab[maxm]/*lab[i]表示trie中的i节点所表示的单词是字典中的第几个*/,tt;
long vis[maxn],n,w,h,ans[maxn][3];
char word[maxn][maxn],s[maxn];

void init()
{
	scanf("%d%d%d",&h,&w,&n); --h, --w;
	fo(i,0,h) scanf("%s",word[i]);
}

/*AC自动机的构造************************************************************************/
void make_next()//BFS求next函数
{
	long q[maxm]; q[0]=1;
	for (long st=0, ed=1; st!=ed; st=(st+1)%maxm) 
		fo(i,0,maxa-1) if (trie[q[st]][i]) {
		   for (long pt=next[q[st]]; pt; pt=next[pt])//类似kmp的寻找前缀方式
			   if (trie[pt][i]) {
			      next[trie[q[st]][i]]=trie[pt][i];
				  if (lab[trie[pt][i]] && !lab[trie[q[st]][i]]) lab[trie[q[st]][i]]=lab[trie[pt][i]];
				  //当前trie[q[st]][i]节点所表示的单词可能不是字典中的，但其后缀可能是，所以在算next函数的时候同时，寻找是否有后缀在字典中
				  //该处的作用是解决因单词之间的包含关系而导致漏统计
				  break;
		       }
		   q[ed]=trie[q[st]][i], ed=(ed+1)%maxm;
	   }
}
void make()//构造trie
{
	fo(i,0,maxa-1) trie[1][i]=0;
	tt=1; next[1]=0; lab[1]=0;
	fo(l,1,n) {
		scanf("%s",s);
		long p=1, len=strlen(s)-1;
		fod(i,len,0) {
			if (trie[p][s[i]-'A']==0) {
				trie[p][s[i]-'A']=++tt; next[tt]=1; lab[tt]=0;
				fo(j,0,maxa-1) trie[tt][j]=0;
			}
			p=trie[p][s[i]-'A'];
		}
		lab[p]=l;
	}
	make_next();
}
/****************************************************************************************/
void match(long &p, char c)
{
	for (; p; p=next[p]) {
		if (trie[p][c-'A']) {
		   p=trie[p][c-'A'];
		   return;
	    }
		if (p==1) return;
	}
}
void cal_suffix(long p)//算出所有后缀相同的单词
{
	if (lab[p] && vis[lab[p]]) {
		for (long pt=next[p]; pt; pt=next[pt])
			if (lab[pt] && !vis[lab[pt]]) {
                vis[lab[pt]]=1;
				ans[lab[pt]][0]=ans[lab[p]][0];
				ans[lab[pt]][1]=ans[lab[p]][1];
				ans[lab[pt]][2]=ans[lab[p]][2];
		   }
	}
	fo(i,0,maxa-1) 
		if (trie[p][i]) cal_suffix(trie[p][i]);
}
void solve()
{
	memset(vis,0,sizeof(vis));
	long x,y,p,len;
    fo(l,0,3) {
		if (l%2) len=h; else len=w;
		fo(i,0,len) 
			fo(k,0,2) {
				if (l%2) y=w*(l/2), x=i; else y=i, x=h*(l/2);
				p=1;
				for (; x<=h && x>=0 && y<=w && y>=0; x+=f[l][k][0], y+=f[l][k][1]) {
					   match(p,word[x][y]);
					   if (lab[p] && !vis[lab[p]]) {
						  vis[lab[p]]=1;
						  ans[lab[p]][0]=x, ans[lab[p]][1]=y, ans[lab[p]][2]=c[l][k];
					   }
				}
			}
	}
	cal_suffix(1);
	fo(i,1,n) 
		printf("%d %d %c\n", ans[i][0], ans[i][1], ans[i][2]);
}
int main()
{
	init();
	make();
	solve();
	return 0;
}
