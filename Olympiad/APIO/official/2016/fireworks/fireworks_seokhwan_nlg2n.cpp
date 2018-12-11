/*
 * Author: Seokhwan Choi
 * Time Complexity: O((N+M) (log (N+M))^2 )
 */

#include<stdio.h>
#include<queue>
#define MAXN 300100
int n,m;
int p[MAXN];
int c[MAXN];
struct ndata{//contains data for subtree (y=f(x), where y is minimum cost when distance to all leaf node is x
	long long int a,b;//y=ax+b at large x
	std::priority_queue<long long int> *pq;//saves slope changing points, slope change by 1 at each element
	ndata operator+(ndata r){//merge two data by adding them
		ndata s;//result(merged data)
		s.a=a+r.a;
		s.b=b+r.b;
		if(pq->size()>r.pq->size()){//merge smaller priority queue to larger priority queue
			s.pq=pq;
			while(r.pq->size()!=0){
				s.pq->push(r.pq->top());
				r.pq->pop();
			}
		}
		else{
			s.pq=r.pq;
			while(pq->size()!=0){
				s.pq->push(pq->top());
				pq->pop();
			}
		}
		return s;
	}
};
ndata d[MAXN];
int main(){
	int i;
	scanf("%d%d",&n,&m);
	for(i=2;i<=n+m;i++){
		scanf("%d%d",&p[i],&c[i]);
	}
	for(i=n+m;i>0;i--){//initiallize
		d[i].a=0;
		d[i].b=0;
		d[i].pq=new std::priority_queue<long long>;
	}
	for(i=n+m;i>n;i--){//leaf nodes
		d[i].a=1;
		d[i].b=-c[i];
		d[i].pq->push(c[i]);//slope is -1 if x<c[i], 1 if x>c[i]
		d[i].pq->push(c[i]);//slope changes by 2
		d[p[i]]=d[p[i]]+d[i];//add the data to parent node
	}
	for(i=n;i>1;i--){
		//add edge to parent node
		while(d[i].a>1){//slope over 1 is useless because we can increase only one edge(edge toward parent node)
			d[i].a--;//slope decrease by 1
			d[i].b+=d[i].pq->top();//y=ax+b=(a-1)x+(b+x) at slope changing point
			d[i].pq->pop();
		}
		long long int ta=d[i].pq->top();//increase length of slope -1 part by c[i]
		d[i].pq->pop();
		long long int tb=d[i].pq->top();
		d[i].pq->pop();
		d[i].pq->push(tb+c[i]);//move location of slope 0, 1 part by c[i]
		d[i].pq->push(ta+c[i]);
		d[i].b-=c[i];//y is decreased by c[i] at sufficiently large x (slope 1 part)
		d[p[i]]=d[p[i]]+d[i];//add the data to parent node
	}
	while(d[1].a>0){//root node, y at slope 0 is the answer because it is minimum y
		d[1].a--;
		d[1].b+=d[1].pq->top();
		d[1].pq->pop();
	}
	printf("%lld\n",d[1].b);
	return 0;
}
