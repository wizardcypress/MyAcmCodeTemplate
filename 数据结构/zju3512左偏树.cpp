/*
  左偏树，zju3512，关键操作是merge，所有其他操作都以其为核心。
 */
#include<cstdio>
#include<cstring>
#include<algorithm>
#define MAXN 50010

using namespace std;
typedef long long ll;
struct node{
    int left,right;
    int key;
    int dist;
};
int n;
node nd[MAXN];
int stk[MAXN];
int top;
int q[MAXN],fa[MAXN];
ll ans;

int myabs(int x) { return x<0? -x : x; }
int merge(int a,int b) //合并堆
{
    if(a == 0) return b;
    if(b == 0) return a;
    if (nd[a].key < nd[b].key) swap(a,b);
    nd[a].right = merge(nd[a].right, b);
    if(nd[nd[a].left].dist < nd[nd[a].right].dist)    swap(nd[a].left, nd[a].right);
    nd[a].dist = nd[nd[a].right].dist + 1;
    return a;
}
void Delete(int x) 
{
    int q = fa[x];
    int p = merge(nd[x].left, nd[x].right);
    fa[p] = q;
    if( q!=0 && nd[q].left == x)  nd[q].left = p;
    if( q!=0 && nd[q].right == x) nd[q].right = p;
    while(q != NULL) {
        if(nd[nd[q].left].dist < nd[nd[q].right].dist)
            swap(nd[q].left, nd[q].right);
        if(nd[nd[q].right].dist + 1 == nd[q].dist ) break;
        nd[q].dist = nd[nd[q].right].dist + 1;
        q = fa[q];
    }
}
int main()
{
    while(scanf("%d",&n) , n)
    {
        q[0] = 0;
        top =0; 
        for(int i=1; i<=n; i++)
        {
            scanf("%d", &nd[i].key);
            nd[i].left = nd[i].right = nd[i].dist=0;
            stk[++top] = i;
            q[top] = i;
            while(top > 1 && nd[stk[top-1]].key > nd[stk[top]].key) {
                stk[top-1] = merge(stk[top-1], stk[top]);           
                top --;
                if (((q[top+1] - q[top])&1) && ((q[top] - q[top-1])&1)) {
                    stk[top] = merge(nd[stk[top]].left, nd[stk[top]].right);
                }
                q[top ] = q[top+1];
            }
        }

        ans = 0;
        for(int i=1; i<=top; i++)
        {
            for(int j=q[i-1]+1; j<=q[i]; j++)
                ans+=myabs(nd[j].key - nd[stk[i]].key);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
