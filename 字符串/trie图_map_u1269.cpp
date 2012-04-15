#include<cstdio>
#include<cstring>
#include<map>
#include<vector>
#include<queue>
using namespace std;
typedef map<int,int>::iterator IT;
struct TRIE{
	int pre,dep;
	int end;
	map<int,int> next;
	TRIE()
	{	
		end=0; 
		dep=0;
		next.clear();
	}
};
vector<TRIE> trie;
int n,m;
void input()
{
	char ch;
	int x,tmp;
	scanf("%d\n",&n);
	trie.resize(2);
	trie[1].end=false;
	trie[1].dep=0;
	for(int i=0;i<n;++i)
	{
		x=1;
		for(ch=getchar();ch=='\0' || ch=='\n' || ch=='\r';ch=getchar()) ;
		do{
			//printf("%c",ch);
			int v=ch<0?ch+256:ch;
			if(trie[x].next.count(v)) x=trie[x].next[v];
			else {
				tmp=trie.size();
				trie.push_back(TRIE());
				trie[x].next[v]=tmp;
				trie[tmp].dep=trie[x].dep+1;
				x=tmp;
			}
			ch=getchar();
		}while(ch!='\0' && ch!='\n' && ch!='\r');		
		//printf("\n");
		trie[x].end=1;
	}
}
int find_pre(int pre_id,int i)
{
	while(pre_id!=1)
	{
		if(trie[pre_id].next.count(i))
			break;
		pre_id=trie[pre_id].pre;
	}
	if(trie[pre_id].next.count(i))
		pre_id=trie[pre_id].next[i];
	return pre_id;
}
void trie_pre_cal()
{
	int pre_id;
	queue<int> que;
	trie[1].pre=1;	
	IT it;
	for(it=trie[1].next.begin();it!=trie[1].next.end();++it)
	{
		trie[it->second].pre=1;
		que.push(it->second);
	}
	while(!que.empty())
	{
		int x=que.front();  que.pop();
		if(trie[x].end) continue;
		for(it=trie[x].next.begin();it!=trie[x].next.end();++it)
		{
			que.push(it->second);
			pre_id=find_pre(trie[x].pre,it->first);
			trie[it->second].pre=pre_id;			
			if(!trie[it->second].end && trie[pre_id].end) 
				trie[it->second].end=2;
		}
	}
}
void solve()
{
	char ch;
	scanf("%d",&m);	
	int line=-1,pos=-1;
	for(int i=0;i<m;++i)
	{
		int x=1;		
		int cnt=0;
		for(ch=getchar();ch=='\0' || ch=='\n' || ch=='\r';ch=getchar()) ;
		do{
			cnt++;
			if(line==-1){
				int v=ch<0?ch+256:ch;
				if(trie[x].next.count(v)) x=trie[x].next[v];
				else x=find_pre(trie[x].pre,v);
				if(trie[x].end){
					line=i;
					if(trie[x].end==1) pos=cnt-trie[x].dep;
					else {
						for(x=trie[x].pre;trie[x].end!=1;x=trie[x].pre) ;
						pos=cnt-trie[x].dep;
					}
				}
			}
			ch=getchar();
		}while(ch!='\0' && ch!='\n' && ch!='\r');
	}
	if(line==-1) printf("Passed\n");
	else printf("%d %d\n",line+1,pos+1);
}
int main()
{
	freopen("u1269.in","r",stdin);	
		input();
		trie_pre_cal();
		solve();
	return 0;
}
