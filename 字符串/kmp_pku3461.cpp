#include<cstdio>
#include<cstring>

using namespace std;

int n,m;
char s[10010],t[1000010];
int pre[10010];
void cal_pre()
{
	int j=-1;
	n=strlen(s);
	for(int i=0;i<n;++i)
	{
		pre[i]=j;
		while(j>=0 && s[i]!=s[j])
			j=pre[j];
		j++;
	}
	pre[n]=j;
}
int cal_match()
{
	m=strlen(t);
	int j=0;
	int cnt=0;
	for(int i=0;i<m;++i)
	{
		while(j>=0 && s[j]!=t[i])  //跳出循环后，s[j]==t[i]，而且默认s[-1]是任意通配符
			j=pre[j];
		if(j==n-1)	cnt++,j=pre[j+1];
		else j++;
	}
	return cnt;
}
int main()
{
	freopen("pku3461.in","r",stdin);
	int cs;
	scanf("%d",&cs);
	while(cs--)
	{
		scanf("%s%s",s,t);
		cal_pre();
		int ans=cal_match();
		printf("%d\n",ans);
	}
	return 0;
}
