#include <iostream>
using namespace std;

const maxn=100;
long b[maxn],m[maxn];

long cal_gcd(long a, long b, long &x, long &y) {//计算ax+by=gcd（a,b)的特解 
    if (b == 0) {
        x = 1; y = 0;
        return a;
    } else {
        long tx, ty, d;
        d = cal_gcd(b, a%b, tx, ty);
        x = ty; y = tx-a/b*ty;
        return d;
    }
}

/*模方程ax≡b（mod m）求出特解x0后可 转换为x≡x0（mod  m')
（其中 m= m'*gcd(a,b)*/

long cal_mo(long a, long b, long m) //计算ax≡b（mod m）的特解 
{
    long x,y,d;
    d=cal_gcd(a,m,x,y);
    if (b%d==0) return (x*(b/d))%m //特解，加减m‘的整数倍得到所有解 
    else return 0;//无解 
}

long cal_no_sys()//计算模线性方程组x≡bi（mod mi）（有n个方程） 
{
    long x,y,d,m0=m[0],b0=b[0],i;
    for (i=1; i!=n; ++i) {//将方程组两两合并,
      d=cal_gcd(m0,m[i],x,y);
      if ((b0-b[i])%d==0){
        b0=x*(b0-b[i])/d+b0;
        m0=m0*m[i]/d; //m0与m[i]的最小公倍数 
        b0=b0%m0; //两个方程合并为x≡b0（mod m0） 
      } else return 0; //无解 
    } 
    return b0; //方程组的特解，加减m0的整数倍得到所有解 
}
int main()
{
    
}
