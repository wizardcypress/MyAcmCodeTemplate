#include<iostream>
using namespace std;

const int maxn=/*行列式大小*/ 
const int mo=/*答案取余*/ 

int det[maxn][maxn],n,ans;

void make_det()
{
    /*构造行列式*/ 
}


void cal_det()/*转化为阶梯阵求行列式*/ 
{
     int i,j,k,t,swap;
     ans=1;  
     
     for (i=0; i!=n; ++i)
       for (j=0; j!=n; ++j) det[i][j]%=mo;
       
     for (i=0; i!=n; ++i) { /*列*/ 
       for (j=i+1; j!=n; ++j) /*行*/
         while (det[j][i]!=0) { /*辗转减消元*/ 
           t=det[i][i]/det[j][i];
           ans=-ans; /*交换行后行列式值变负*/ 
           for (k=i; k!=n; ++k) {
             det[i][k]-=det[j][k]*t;
             
             /*交换行*/ 
             swap=det[i][k];
             det[i][k]=det[j][k];
             det[j][k]=swap;
           }
       }
       if (det[i][i]==0) {
         ans=0;
         break;
       } else ans=(ans*det[i][i])%mo;
     }    
     cout << ans << endl;    
}

int main()
{

    make_det();
    cal_det();

}
