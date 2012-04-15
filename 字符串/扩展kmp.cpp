#include<cstdio>
#include<cstring>
#define MAXN 10010
using namespace std;
/*
    函数extend[i] = |T与T(i,m)的最长公共前缀|，这里2<=i<=m。	    
   	函数Bi = |T与S(i,n)的最长公共前缀|，这里1<=i<=n。	
*/
struct ExtKmp{ //start from 1
    const char *t, *s;
    int *b;
    int extend[MAXN];
    int m,n;
    void cal(char *_t, int _m, char *_s, int _n, int *_b)  //len_t = m
    {
       t = _t;      
       n = _n; 
       s = _s;       
       m = _m;
       b = _b;
       count_extend();
       count_b();
    }
    void count_extend()
    {
        int j=0,len,l,k;
        while(j<=m-2&&t[1+j]==t[2+j]) ++j;
        extend[1]=m;
        extend[2]=j;
        k=2;
        for(int i=3;i<=m;++i)
        {
            len=k+extend[k]-1;
            l=extend[i-k+1];
            if(l<len-i+1) extend[i]=l;
            else{
                j=max(0,len-i+1);
                while(i+j<=m&&t[1+j]==t[i+j]) ++j;
                extend[i]=j;
                k=i;
            }
        }
    }
    void count_b()
    {
        int j=0,len,l,k;
        while(j<m&&t[1+j]==s[1+j]) ++j;
        b[1]=j;
        k=1;
        for(int i=2;i<=n;++i)
        {
            len=k+b[k]-1;
            l=extend[i-k+1];
            if(l<len-i+1) b[i]=l;
            else {
                j=max(0,len-i+1);
                while(j<m&&i+j<=n&&t[1+j]==s[i+j]) ++j;
                b[i]=j;
                k=i;
            }
        }
    }
};

