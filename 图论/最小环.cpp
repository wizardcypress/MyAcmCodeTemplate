int mincircle = infinity;
Dist = Graph;

for(int k=0;k<nVertex;++k){
    //新增部分:
    for(int i=0;i<k;++i)
        for(int j=0;j<i;++j)
            mincircle = min(mincircle,Dist[i][j]+Graph[j][k]+Graph[k][i]);
    //通常的 floyd 部分:
    for(int i=0;i<nVertex;++i)
        for(int j=0;j<i;++j){
            int temp = Dist[i][k] + Disk[k][j];
            if(temp < Dist[i][j])
                Dist[i][j] = Dist[j][i] = temp;
        }
}
