#include<cstdio>
#include<cstring>
#include<complex>  
#include<cmath>
#include<algorithm>
#define MAXN 263010
#define EPS 1e-8

using namespace std;
typedef complex<double> cp;
const double pi = acos(-1.0);

char s1[MAXN],s2[MAXN];
cp x1[MAXN],x2[MAXN];
cp t1[MAXN],t2[MAXN];
cp x3[MAXN];
int ans[MAXN];
int n,m;

void output(cp arr[], int len)
{
    for(int i=0; i<len; i++)
        printf("<%lf, %lf> ", arr[i].real(), arr[i].imag());
    printf("\n");
}
void init_array(char *s, cp a[], int len, int retlen) //初始化IDF数组
{
   for(int i=0; i<len; i++)
       a[len-i-1] = cp(s[i]-'0', 0); //1+a0x+a1x^2+...
   for(int i=len; i<retlen; i++)
       a[i] = cp(0, 0);
}
int rev(int x, int bit)
{
    int ret= 0;
    while(bit--) {
        ret = (ret <<1) | (x & 1);
        x >>= 1;
    }
    return ret;
}
void bit_reverse_copy(cp in[], cp out[], int n, int bitnum)
{
    for(int i=0; i<n; i++) {
        out[rev(i, bitnum)] = in[i];
    }
}
void iterative_fft(cp in[], cp out[], int n, int flip) //flip == 1 or -1
{
    cp wm,w,t, u;
    int bitnum;
    for(bitnum=0; !((1<<bitnum) & n); bitnum++) ; 
    bit_reverse_copy(in, out, n, bitnum);

    for(int m = 2; m<=n;  m*=2)
    {
        wm = cp(cos(2*pi*flip / m), sin(2*pi*flip / m));
        for(int k=0; k<n; k+=m)
        {
            w = cp(1, 0);
            for(int j=0; j<m/2; j++)
            {
               t = w * out[k+j+m/2]; 
               u = out[k+j];
               out[k+j] = u + t;
               out[k+j+m/2] = u - t;
               w = w * wm;
            }
        }
    }
    if(flip == -1)
        for(int i=0; i<n; i++) out[i] /= n;
}
void trans_back(cp x[], int ans[], int &n) 
{
   for(int i=0; i<n; i++) ans[i] = x[i].real() + 0.5;
    for(int i=0; i<n; i++)
    {
        ans[i+1] += ans[i] / 10;
        ans[i] %= 10;
    }
    while(n>0 && ans[n-1] == 0) n--;
}
int main()
{
    while(scanf("%s%s", s1, s2) != EOF)
    {
        int l1 = strlen(s1), l2 = strlen(s2);
        m = l1 + l2;
        for(n =1; n<m; n<<=1) ;
        init_array(s1, x1, l1, n);
        init_array(s2, x2, l2, n);
        iterative_fft(x1, t1, n, 1);// DFT 
        iterative_fft(x2, t2, n, 1);
        for(int i=0; i<n; i++)
            x3[i] = t1[i] * t2[i];
        iterative_fft(x3, x1, n, -1); //IDFT
        fill(ans, ans+n, 0);
        trans_back(x1, ans, n); //把IDFT结果转为高精度形式
        if(n <= 0) printf("0\n");
        else {
            for(int i=n-1; i>=0; i--)
                printf("%d", ans[i]);
            printf("\n");
        }
    }
    return 0;
}
