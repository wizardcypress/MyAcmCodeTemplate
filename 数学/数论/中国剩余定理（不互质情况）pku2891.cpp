
ll chinese_remain(vector<pair<ll, ll> > &vec)
{
    ll m1, a1, m2, a2;
    ll y, z, d; 
    a1 = vec[0].first;
    m1 = vec[0].second;
    for(int i=1; i<vec.size(); i++)
    {
        a2 = vec[i].first;
        m2 = vec[i].second;
        ext_gcd(m1, m2, d, y, z);
        if((a2 - a1) % d) return -1; //无解
        y = (a2 - a1)/d * y;
        a1 = a1 + m1 * y;
        m1 = m1  / d * m2; 
        a1 = a1 % m1;
    }
    a1 = (a1 % m1 + m1) % m1;
    return a1;
}


