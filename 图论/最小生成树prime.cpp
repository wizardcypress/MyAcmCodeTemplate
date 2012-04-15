//最小生成树，用优先队列优化 
#include<iostream>
#include<cstdio>
#include<vector>
#include<queue>
     #define MAXN 30000
     #define Type int
using namespace std;
struct dijk_p
{
    Type dist; int p;	
};
bool operator < ( const dijk_p& p1, const dijk_p& p2 )
{
		return p1.dist > p2.dist;
}
vector< pair<int,Type> > road[MAXN];
Type v[ MAXN ];
priority_queue<dijk_p> que; 
int n, m,start,final;   
void read()
{
	int x, y;
    Type c;
   scanf("%d %d", &n, &m);
    for (int i = 0; i < m; i++ )
    {        
        scanf("%d %d %d", &x, &y, &c);
				road[--x].push_back(make_pair(--y, c));
    }
}
void prime(int st)
{
   int x,y;
   Type dis;
   que.push( (dijk_p){ 0, st } );
    memset( v, 0xff, sizeof(v) );
    v[ st ] = 0;
    while ( !que.empty() )
    {
        x= que.top().p; dis = que.top().dist; que.pop();
        if ( v[ x ] != dis ) continue;
        for (int i = 0; i < road[ x ].size(); i++)
        {
            y= road[ x ][ i ].first;
            dis = road[ x ][ i ].second;
            if ( v[ y ] == -1 || dis < v[ y ])
            {
                v[ y ] = dis ;
                que.push( (dijk_p){ v[y] , y } );
            }
        }
    }
}
int main()
{
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout); 
    read();
    start=0;  //起点     
    prime(start);
      Type MinPath=0;  
	  for (int i=0;i<n;++i) MinPath+=v[i];	  
    printf("%d\n",MinPath);
    return 0;
}
