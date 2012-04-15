//堆
#include<iostream>
#include<map>
   #define Type int  //定义对节点数据类型 
   #define MIN_HEAP  //定义最大最小堆 
   #define EXTREME -1 //关于大小堆的极端值定义，在删除操作中要用到 

using namespace std;
class heap
{
   private:
     struct HeapNode {
      Type d;         //节点值 
      map<Type,int>::iterator pos;
	  //指向map中以该节点值为关键字的那个点的迭代器(实际上就是指针) 
	 };
     int size,len; //size是数据规模，在初始化时要给出具体规模值
	              //len是当前堆中的节点数 
     HeapNode *hp;  //hp就是堆节点集 
     map<Type,int> rpos; //rpos是一个map，第一个是堆中节点值，第二个
	                     //是该节点值在堆中位置 
    public:
     heap(int);
     void insert(Type &);    
     void pop();             //删除堆顶值 
     void Delete(Type &);    //删除值为Type的节点 
     void down(int);     
     void up(int);
     void swap(HeapNode &,HeapNode &);
     Type top();             //返回堆顶值 
     bool comp(Type &x,Type &y) //最大最小堆的比较，
	 {
	 	#ifdef MIN_HEAP
	     return x<y;
        #else ifdef MAX_HEAP
         return x>y;
        #endif;
	 }
};
heap::heap(int InitSize)
{
	size=InitSize+1;
	len=0;
	hp=new HeapNode[size+1];	
}
void heap::insert(Type &x)
{
	hp[++len].d=x;
	hp[len].pos=(rpos.insert(pair<Type,int>(x,len)).first);   
	up(len); 
}
void heap::pop()
{
    if (len>0)
    {
	    rpos.erase(hp[1].pos);
	    hp[len].pos->second=1;
	    hp[1]=hp[len--];
	    down(1);
	}
}
void heap::Delete(Type &x)
{
   int w=rpos[x];
   hp[w].d=EXTREME;
   up(w);
   pop();   
}
void heap::swap(HeapNode &x,HeapNode &y)
{
	HeapNode tmp=x;x=y;y=tmp;   
}
Type heap::top()
{
   if (len>0) return hp[1].d;
    else return -1;
}
void heap::down(int x)
{
    int y;
	if (x*2<=len) {
    if (x*2==len) y=x*2;
     else if (comp(hp[x*2].d,hp[x*2+1].d))  y=x*2;
      else y=x*2+1;
     if (comp(hp[y].d,hp[x].d)) {
     	hp[x].pos->second=y;
     	hp[y].pos->second=x;
     	swap(hp[x],hp[y]);
     	down(y);
	 }else return;
	}
}
void heap::up(int x)
{
  if (x>1){
     int y=x/2;
     if (comp(hp[x].d,hp[y].d)) {
     	hp[x].pos->second=y;
     	hp[y].pos->second=x;
     	swap(hp[x],hp[y]);
     	up(y);
	 }else return;
  }
}
int main()
{
	heap a(100000);
	for(int i=1;i<=100000;++i)
	   a.insert(i);
     for (int i=1;i<=100000;++i)
	    a.pop();
     cout<<a.top()<<endl;
   return 0;
} 

