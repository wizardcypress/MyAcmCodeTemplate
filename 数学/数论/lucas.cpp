ll lucas(ll n, ll m, ll p)  // C(n, m) % p
{
    if(m == 0) return 1;
    if(m == 1) return n % p;
    ll l2 = lucas(n/p, m/p, p);

    n = n % p;
    m = m % p;
    // up / down = C(n, m)
    ll up = n! % p 
    ll down = m ! * (n - m) ! % p;
    ll x, y;
    ext_gcd(down, p, x, y);
    x = (x % p + p ) % p;
    //down = 1/down (mod p); //求down 的逆
    up = up * x % p;

    return l2 * up % p;
}

