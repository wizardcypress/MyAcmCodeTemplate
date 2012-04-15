inline int hashcode(const int *v)
{
	int s = 0;
	for(int i=0; i<k; i++)
		s=((s<<2)+(v[i]>>4))^(v[i]<<10);
	s = s % M;
	s = s < 0 ? s + M : s;
	return s;
}
