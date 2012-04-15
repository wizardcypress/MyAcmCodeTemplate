#include<stdio.h>
#include<math.h>


double romberg(double a, double b, double eps,
        double (*f)(double))
{
#define ROUND 10
    int m, n, i, k;
    double y[ROUND], h, ep, p, x, s, q;
    h = b - a;
    y[0] = h * ((*f)(a) + (*f)(b)) / 2.0;
    m = n = 1;
    ep = eps + 1.0;
    while(ep >= eps && m <= ROUND-1)
    {
        p = 0;
        for(i=0; i<=n-1; i++)
        {
            x = a + (i+0.5) * h;
            p = p + (*f)(x);
        }
        p = (y[0] + h*p) / 2;
        s = 1;
        for(k=1; k<=m; k++)
        {
            s = 4*s;
            q = (s * p - y[k-1]) / (s - 1);
            y[k-1] = p;
            p = q;
        }
        ep = fabs(q - y[m-1]);
        m = m+1;
        y[m-1] = q;
        n = n + n;
        h = h / 2;
    }
    return q;
}
double f(double x)
{
    return x / (4 + x * x );
    //return x*x;
}
int main()
{
    double ans = romberg(0, 1, 0.000001, f);
    printf("%.8lf\n", ans);
    return 0;
}
