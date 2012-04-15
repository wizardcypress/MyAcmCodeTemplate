#define TYPE int
struct edge{
    int u, v;
    TYPE d;
    edge(){}
    edge(int _u, int _v, TYPE _d):u(_u),v(_v),d(_d) {}
};
edge e[MAXM];
int prev[MAXN];
TYPE in[MAXN];
int vis[MAXN],id[MAXN];
int n,m, ne;
//

void input()
{
    int x, y;
    for(int i=0; i<n; i++) //base 0
        scanf("%d%d", cord[i], cord[i]+1);
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
dis[i][j] = dis[j][i] = dist(cord[i][0], cord[i][1], cord[j][0],cord[j][1]);
    
    int cnt = 0;
    for(int i=0; i<m; i++)
    {
        scanf("%d%d", &x, &y);
        x--;
        y--;
        if(x == y) continue;
        e[cnt++] = edge(x, y, dis[x][y]);
    }
    m = cnt;
}
TYPE dirmst(int root, int nv, int ne) 
{
    TYPE ret = 0;
    while(1)
    {
        //find the smallest in-arc
        fill(in, in+nv, INF);
        for(int i=0; i<ne; i++) {
            int u = e[i].u;
            int v = e[i].v;
            if(e[i].d < in[v] && u != v) {
                in[v] = e[i].d;
                prev[v] = u;
            }
        }
        for(int i=0; i<nv; i++) {
            if(i == root)  continue;
            if(in[i] >= INF) return -1; //no answer
        }

        fill(vis, vis+nv, -1);
        fill(id, id+nv, -1);
        in[root] = 0;
        int cnt = 0;
        for(int i=0; i<nv; i++)
        { 
            ret += in[i];
            int j = i;
            while(vis[j] != i && id[j] == -1 && j != root ) {
                vis[j] = i;
                j = prev[j];
            }
            if(j != root && id[j] == -1) { 
                for(int k=prev[j]; k!=j; k = prev[k])
                    id[k] = cnt;
                id[j] = cnt++;
            } 
        }
        if(cnt == 0) break; //no circle
        for(int i=0; i<nv; i++)
            if(id[i] == -1) id[i] = cnt++;
        for(int i=0; i<ne; i++) { //compress the circles
            int v = e[i].v;
            e[i].u = id[e[i].u];
            e[i].v = id[e[i].v];
            if(e[i].u != e[i].v)
               e[i].d -= in[v];
        }
        nv = cnt;
        root = id[root];
    }
    return ret;
}

