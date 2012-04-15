双连通分量:

  双连通分量分两种，一种是删除一条边仍然连通的，叫做边连通分量，以桥为分割，另外一个是删除一个点仍然连通，以割点为分界叫点连通分量，下面分开来讲。


边连通分量：
	其实把所有的桥都找出来就可以进行划分了。这是对点的划分。
void dfs(int x,int fat)
{
   low[x]=dfn[x]=++len;
   for(int q=beg[x];q!=-1;q=e[q].next)
	if(e[q].v!=fat)
	{
	   int v=e[q].v;
	   if(dfn[v]==0)
		{
	      dfs(v,x);
		  if(low[v]<low[x]) low[x]=low[v];
          if(low[v]>=dfn[x])  key[x]=true; //x 为割点
          if(low[v]>dfn[x])  bridge[x][v]=true; // x-v 为桥
        }  else if(dfn[v]<low[x]) low[x]=dfn[v];
   }
}

点双连通分量：   
	在计算点连通分量的算法中，是以割点为分界的，和边连通分量的求法差不多，不过需要多增加一个栈来记录经过的点，
并且要注意和强连通分量所用的栈的不同，在点连通分量中，割点是可以在多个点连通分量中的，所以这里的退栈是有一些地方
要注意的，详细可以看下面的程序的详细标注。

void dfs(int x,int fa)
{	
	low[x]=pre[x]=++dfn;
	stk[++top]=x;
	for(int i=beg[x];i!=-1;i=e[i].next)
		if(e[i].v!=fa)
		{
			int v=e[i].v;
			if(pre[v]==0) {
				dfs(v,x);
				if(low[v]>=pre[x]){ //we get a cut point
					bcc++;
					BCC[bcc].resize(0);	
					int w;    
					//注意这里的退栈操作，要退到v，不能一直退到x，
					//因为有可能x先访问另外一个儿子u，然后u能连到比x更早的祖先，那么u和u连接的一些
					//节点就仍然在栈中，这时候对v进行访问，如果此时一直退栈到x，那么就会把u也给退栈,就会造成错误										
					do{
						w=stk[top--];
						BCC[bcc].push_back(w);
						inBcc[bcc][w]=true;  //true表示w在编号为bcc的点连通分量中
					}while(w!=v);            
					BCC[bcc].push_back(x); //最后记得把当前割点也加到bcc的分量中。
					inBcc[bcc][x]=true;
				}
				if(low[v]<low[x]) low[x]=low[v];
			}else{
				if(pre[v]<low[x])	 low[x]=pre[v];
			}
		}	
}
