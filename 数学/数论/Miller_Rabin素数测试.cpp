/*
	该函数对2^64以内的数都能有效辨别。
*/
const int cstPrime[10]={2,3,5,7,11,13,17,19,23,29};
bool Miller_Rabin(ll a,ll n)
{
	ll r=0,s=n-1;
	while(!(s&1)) r++,s>>=1;   //n-1==2^r*s
	ll as=pow_mod(a,s,n);   //as=a^s%n
	if(as==1 || as==n-1) return true;    //if as==1 or as^i%n==n-1 then it is likely	be prime
	for(int i=1;i<r;i++)
	{	
		as=mod(as,as,n);//as=as*as%n;
		if(as==1) return false;//if as==1,it's no use to do the rest.
		if(as==n-1) return true;
	}
	return false;
}
bool isPrime(ll n)  //true if n is prime
{
	for(int i=0;i<10;++i)//test all 10 base
	if(n==cstPrime[i])return true;
	else{
		if(n%cstPrime[i]==0) return false;
		if(!Miller_Rabin(cstPrime[i],n)) return false;
	}
	return true;
}

