ll baby_gaient_step()
{
	memset(beg,0,sizeof(beg));
	m=ceil(sqrt(p*1.0));
	ll rsl=1;
	nList=0;
	insert(1,0);
	for(int i=1;i<m;++i)
	{
		rsl=rsl*b%p;
		if(!find(rsl)) insert(rsl,i);
	}			
	ll bm=pow_mod(b,p-m-1,p);
	for(int i=0;i<m;++i)
	{
		if(find(n))  return i*m+get(n);
		else n=mod(n,bm,p);
	}
	return -1;	
}
