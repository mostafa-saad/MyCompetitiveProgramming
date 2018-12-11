/*
 * Author: Gyeonggeun Kim(kriii)
 * Time Complexity: O(N lg^2 N)
 */
#include <stdio.h>
#include <algorithm>
#include <queue>
using namespace std;

const int maxn = 300003;

priority_queue<long long> *Q[maxn];
int N,M,V,P[maxn],C[maxn],D[maxn]; long long E[maxn];

int main()
{
	scanf ("%d %d",&N,&M);
	V = N + M;
	
	for (int i=2;i<=V;i++) scanf ("%d %d",&P[i],&C[i]);
	for (int i=1;i<=V;i++) Q[i] = new priority_queue<long long>;

	for (int i=V;i>=2;i--){
		long long p = 0, q = 0;
		if (D[i]){
			for (int j=1;j<D[i];j++){
				E[i] += Q[i]->top(); Q[i]->pop();
			}
			p = Q[i]->top(); Q[i]->pop();
			q = Q[i]->top(); Q[i]->pop();
		}
		Q[i]->push(p+C[i]);
		Q[i]->push(q+C[i]);
		E[i] -= C[i];

		priority_queue<long long> *&a = Q[i], *&b = Q[P[i]];
		if (a->size() > b->size()) swap(a,b);
		while (!a->empty()){
			b->push(a->top()); a->pop();
		}
		E[P[i]] += E[i];
		D[P[i]]++;
	}

	long long ans = E[1];
	for (int i=0;i<D[1];i++){
		ans += Q[1]->top(); Q[1]->pop();
	}
	printf ("%lld\n",ans);

	return 0;
}