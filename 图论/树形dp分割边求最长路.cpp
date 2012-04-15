/*
  sicily 2469  树DP，分割边求最长路
       给出一棵树，对于每一条边，问切掉这条边之后，再增加某条边连起来，使得新的树的最长路最短。
       首先假如已经知道这两部分的最长路，那么要最短就连中点就可以了。现在就需要知道分开的两部分的最长路。
       类似求树最长路一样，分两部分来做，第一次dfs求出x为根的一些信息值，maxpath[x]表示不一定连接到根的子树最长路，mostpath[x][3]表示连接到根的最长路前3个。mpath[x][2]表示那些不一定连接到根的最长路的前2个（这个会在跌入次dfs中用到）。
       然后第二次dfs的时候，需要记录fmaxpath表示不一定和x节点连接的父亲那一堆点的最长路，flpath表示连接到x的从父亲部分过来的最长的那条路，那么假设现在要删除x到v的边，那么v子树的最长路显然是maxpath[v]，那么对x-v分割的x这一边的最长路就比较复杂了，主要有原来的fmaxpath,还有flpath和除v以外的其他儿子相连的路（这些路经过x），或者x的某两个儿子相连的路径，或者x的某个儿子的mpath（不一定经过该儿子的路径）。那么对于这几个取最大值就是下个递归的fmaxpath了。
       这个算法的一个大优点在于可以在线性时间内求出一条边分割后的两部分的分别最长路。
 */
#include<cstdio>
#include<cstring>
#include<algorithm>
#define maxn 50010
using namespace std;

struct edge{
    int v,next;
    int id;
};
edge e[2*maxn];
int beg[maxn],ne;
int n;
int mpath[maxn][2],mwho[maxn][2],maxpath[maxn];
int mostpath[maxn][3],mostwho[maxn][3];
int ans[maxn];
bool chkmax(int &x,int y)
{
    if(y>x){
        x=y;
        return true;
    }else return false;
}
bool chkmin(int &x,int y)
{
    if(y<x){
        x=y;
        return true;
    }else return false;
}
void add(int x,int y,int id)
{
    e[ne].v=y;
    e[ne].next=beg[x];
    e[ne].id=id;
    beg[x]=ne++;
}
void input()
{
    ne=0;
    memset(beg,255,sizeof(beg));
        //scanf("%d",&n);
    for(int  i=0;i<n-1;i++)
    {
        int x,y;
        scanf("%d%d",&x,&y);
        x--; y--;
        add(x,y,i);
        add(y,x,i);
    }
}
//用newval更新most[]使之有序
void update(int most[],int newval,int who[],int someone,int lim)
{
    for(int i=0;i<lim;i++)
        if(most[i]<newval)
        {
            for(int j=lim-1;j>i;j--) most[j]=most[j-1],who[j]=who[j-1];
            most[i]=newval;
            who[i]=someone;
                break;
        }
}
void dfs1(int fa,int x)
{
    maxpath[x]=0;
    memset(mostpath[x],0,sizeof(mostpath[x]));
    memset(mostwho[x],0,sizeof(mostwho[x]));
    memset(mpath[x],0,sizeof(mpath[x]));
    memset(mwho[x],0,sizeof(mwho[x]));
    for(int i=beg[x];i!=-1;i=e[i].next)
        if(e[i].v!=fa){
            int v=e[i].v;
            dfs1(x,v);
            chkmax(maxpath[x],maxpath[v]);
            update(mpath[x],maxpath[v],mwho[x],v,2); //要记录儿子最长路的前2个
            update(mostpath[x],mostpath[v][0]+1,mostwho[x],v,3); //求最长路前3个
        }
    chkmax(maxpath[x],mostpath[x][0]+mostpath[x][1]);//有可能最长路是两个儿子相连
}
//选取most中不是v的前2个
void selectmost2(int most[],int who[],int v,int d[])
{
    int cnt=0;
    d[0]=d[1]=0;
    for(int i=0;i<3 && cnt<2 ;i++)
        if(who[i]!=v)   d[cnt++]=most[i];
}
void refresh(int id,int len1,int len2)
{
    len1++; len2++;
    int maxval=max(len1-1,len2-1);
    maxval=max(maxval,len1/2+len2/2+1);
    ans[id]=maxval;
}
void dfs2(int fa,int x,int fmaxpath,int flpath)
{
    for(int i=beg[x];i!=-1;i=e[i].next)
        if(e[i].v!=fa)
        {
            int v=e[i].v;
            int d[2];
            selectmost2(mostpath[x],mostwho[x],v,d);
            int val=max(flpath+d[0],d[0]+d[1]); //更新x这边的最长路
            val=max(val,fmaxpath);
            if(v==mwho[x][0]) val=max(val,mpath[x][1]); //也许某个儿子的子树最长路最长
            else val=max(val,mpath[x][0]);
            refresh(e[i].id,val,maxpath[v]);
            dfs2(x,v,val,max(flpath,d[0])+1);
        }
}
void output()
{
    for(int i=0;i<n-1;i++)
        printf("%d\n",ans[i]);
}
int main()
{
//    freopen("test.in","r",stdin);
    int cs;
       scanf("%d",&cs);
    while(cs--)
    {
        scanf("%d",&n);
        input();
        dfs1(-1,0);
        dfs2(-1,0,0,0);
        output();
    }
    return 0;
}
