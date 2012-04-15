#include<cstdio>
#include<cstring>
#define SETTING_OF_BASE 10000  //缩位

#define LIM 100		//最大位数
#define MAX(x,y) ((x)>(y)?(x):(y));
using namespace std;
typedef long long LL;
//**********************************************************************
class BigNumber
{	
	public:
	int a[LIM];		
	static int BASE;	
	public:
	//constructor
	BigNumber();
	BigNumber(int);
	BigNumber(const BigNumber &);
	//
	BigNumber& operator=(const int);
	BigNumber& operator=(const BigNumber &);
	//comparision operations
	int cmp(const BigNumber &);
	bool operator>(const BigNumber &);	
	bool operator<(const BigNumber &);
	bool operator==(const BigNumber &);
	bool operator>=(const BigNumber &);	
	bool operator<=(const BigNumber &);
	//print function with a string at the end
	void print(const char *) const ;
	//operator on int	
	void operator+=(int);		
	void operator-=(int);//Assume the result is nonegative
	void operator*=(int);	
	bool operator/=(int);//Return true if there's no remain.False wtherwise.
	//operator with BigNumber
	void operator+=(const BigNumber &);
	void operator-=(const BigNumber &);
	void operator*=(const BigNumber &);
	bool operator/=(const BigNumber &);//The same with operator on int.
};
//**********************************************************************
BigNumber::BigNumber()
{
	memset(a,0,sizeof(a));
}
BigNumber::BigNumber(int initVal)
{
	memset(a,0,sizeof(a));
	while(initVal>0)
	{
		a[++a[0]]=initVal%BASE;
		initVal/=BASE;
	}
}
BigNumber::BigNumber(const BigNumber &rhs)
{
	memset(a,0,sizeof(a));
	memcpy(a,rhs.a,sizeof(a));
}
BigNumber& BigNumber::operator=(const int R)
{
	*this=BigNumber(R);
	return *this;
}
BigNumber& BigNumber::operator=(const BigNumber &R)
{
	memcpy(a,R.a,sizeof(int)*(R.a[0]+1));
	return *this;
}
//**********************************************************************
int BigNumber::BASE=SETTING_OF_BASE;
//**********************************************************************
int BigNumber::cmp(const BigNumber & that)
{
	if(a[0]>that.a[0]) return 1;
	if(a[0]<that.a[0]) return -1;
	int i=a[0];
	while(i>0 && a[i]==that.a[i]) --i;
	return a[i]-that.a[i];
}
bool BigNumber::operator>(const BigNumber & that)
{
	return cmp(that)>0;
}
bool BigNumber::operator<(const BigNumber & that)
{
	return cmp(that)<0;
}
bool BigNumber::operator==(const BigNumber & that)
{
	return cmp(that)==0;
}
bool BigNumber::operator>=(const BigNumber &that)
{
	return cmp(that)>=0;
}
bool BigNumber::operator<=(const BigNumber &that )
{
	return cmp(that)<=0;
}
//**********************************************************************
void BigNumber::operator+=(int add)
{		
	this->operator+=(BigNumber(add));
}	
void BigNumber::operator-=(int add)
{	
	this->operator-=(BigNumber(add));
}
void BigNumber::operator*=(int mult)
{
	this->operator*=(BigNumber(mult));
}
bool BigNumber::operator/=(int dv)
{
	LL tm=0;	
	for(int i=a[0];i>0;--i)
	{
		tm=tm*BASE+a[i];
		a[i]=tm/dv;
		tm%=dv;
	}
	while(a[0]>0 &&  a[a[0]]==0) --a[0];
	
	if(tm!=0) return false;
	else return true;
}
//**********************************************************************
void BigNumber::operator+=(const BigNumber &that)
{
	int add=0,w=MAX(a[0],that.a[0]);			
	for(int i=1;i<=w;++i)
	{
		a[i]+=that.a[i]+add;
		add=a[i]/BASE;
		a[i]%=BASE;
		if(i>that.a[0] && add==0) break;
	}
	a[0]=w;
	while(add)
	{
		a[++a[0]]=add%BASE;
		add/=BASE;
	}
}
void BigNumber::operator-=(const BigNumber &that)
{	
	for(int i=1,add=0;i<=a[0];++i)
	{
		a[i]-=(that.a[i]+add);
		add=0;
		if(a[i]<0)
		{
			a[i]+=BASE;
			add=1;
		}
	}
	while(a[0]>0 &&  !a[a[0]]) --a[0];
}
void BigNumber::operator*=(const BigNumber &that)
{
	int z[LIM];
	int add=0,w=0;
	memset(z,0,sizeof(z));
	for(int i=1;i<=a[0];++i)
	{
		for(int j=1;j<=that.a[0];++j)
		{
			z[i+j-1]+=a[i]*that.a[j]+add;
			add=z[i+j-1]/BASE;
			z[i+j-1]%=BASE;
		}
	  w=i+that.a[0]-1;
	  while(add)	
	  {
		w++;
		z[w]+=add;
		add=z[w]/BASE;
		z[w]%=BASE;
	  }
	}
	z[0]=a[0]+that.a[0];
	while(z[0]>0 && z[z[0]]==0)  z[0]--;
	memset(a,0,sizeof(a));
	memcpy(a,z,sizeof(int)*(z[0]+1));
}
bool BigNumber::operator/=(const BigNumber &that)
{
	if(this==&that)
	{
		*this=BigNumber(1);
		return true;
	}	
	BigNumber l(0),r=*this;
	BigNumber mid,tm;
	while(l<r)
	{
		mid=l;   mid+=r;   mid/=2;   mid+=1; //mid=(l+r)/2+1
		tm=mid;
		tm*=that;
		if(tm<=*this) l=mid;
		else 
		{
			r=mid;	//r=mid-1
			r-=1;
		}
	}
	l*=that;
	if(l==*this) {	*this=r;   return true;	}
	else{	*this=r;    return false;  	}
}
//**********************************************************************
void BigNumber::print(const char *str="") const 
{  
	printf("%d",a[a[0]]);
	for(int i=a[0]-1;i>0;--i)
		printf("%04d",a[i]);	
	printf("%s",str);
}
//**********************************************************************
int main()
{

}
