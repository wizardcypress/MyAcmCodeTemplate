#include<iostream>
#define fo(i,u,d) for (long i=(u); i<=(d); ++i)
using namespace std;

const long maxn=10000;

char s[maxn],ss[maxn];
long next[maxn],len;

void make_next()
{
	long j;
	next[0]=-1;
	len=strlen(s);
	fo(i,1,len) {
		for (j=next[i-1]; j>=0 && s[j]!=s[i-1]; j=next[j]);
		next[i]=j+1;
	}
}
void solve()
{

	while (scanf("%s",ss)!=EOF) {
		long j=0, ans=0;
		fo(i,1,len) {
			while (j>=0 && s[i-1]!=ss[j]) j=next[j];
			++j;
			ans=ans<j?j:ans;
		}
		printf("%d\n",ans);
	}		
}
int main()
{
	scanf("%s",s);
	make_next();
	solve();
	return 0;
}
