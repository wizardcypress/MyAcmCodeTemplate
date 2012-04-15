/*
	该函数只返回n的一个因数，可以通过和Miller Rabin配合来进行质因数分解。
*/
ll pollard_rho(ll n)
{
	ll i, x, y, k, d,c;
	while(true)
	{
	c=rand()%(n-1)+1;    //f(x)=x^2-c
    i = 1;
    y=x = rand() % (n-1)+1;
    k = 2;
	while(true)
	{
        i++;
        d = gcd(y-x+n, n);
        if (d > 1 && d < n) return d;
        if (i == k) y = x, k *= 2;
        x = (mod(x, x, n) + n - c) % n;    
       if(x==y) break;
     }     
    }   
}

