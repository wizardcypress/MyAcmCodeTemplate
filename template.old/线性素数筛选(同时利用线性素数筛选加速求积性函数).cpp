#include <iostream>
#include <memory>
#include <stdio.h>
using namespace std;

const long maxn=120000;
long long prime[maxn],n,tot;
bool isprime[maxn];

long long sp[maxn],div_sum[maxn]; 
//div_num[i]正因数和函数，sp[i]用于记录i的pm^am(pm为m的最小素因子),具体递推的公式通过正因子求和公式∏(pi^(ai+1)-1)/(pi-1) (pi为因式分解后的素因子，ai为对应指数)

void cal_prime()
{
	memset(isprime,0,sizeof(isprime));
	long num;
	tot_prime=0;
	fo(i,2,n) {
		if (!isprime[i]) {
			prime[++tot_prime]=i;
			//div_sum[i]=i+1;
			//sp[i]=i;
		}
		for (long j=1; j<=tot_prime && i*prime[j]<n; ++j) {
			num=i*prime[j];
			isprime[num]=1;
			if (i%prime[j]==0) {
				//sp[num]=sp[i]*prime[j];
				//div_sum[num]=div_sum[i]*(prime[j]-1)/(sp[num]-1)*(sp[num]*prime[j]-1)/(prime[j]-1);
				break;
			} else {
				//sp[num]=prime[j];
				//div_sum[num]=div_sum[i]*(prime[j]+1);
			}
		}
	}
}
int main()
{


}
