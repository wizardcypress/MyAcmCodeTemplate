#include<cstdio>
#include<cstring>
using namespace std;
int n;
int euler(int n)
{
   int phi=n;
   for(int i=2,j=4;j<=n;i++,j+=i+i-1)//这里使得j=i*i 
	   if(!(n%i)){
        phi=phi/i*(i-1);
		while(!(n%i)) n/=i;
   }
   if(n>1) phi=phi/n*(n-1);
   return phi;
}
int main()
{
	scanf("%d",&n);
	int ans=euler(n);
	printf("%d\n",ans);
	return 0;
}
