/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Tour de Bajtocja                                 *
 *   Autor:             Igor Adamski                                     *
 *   Zlozonosc czasowa: O((n + m) * log^*(n + m))                        *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                      Find-union bez uzycia STL-a                      *
 *                                                                       *
 *************************************************************************/

#include<stdio.h>

#define MAXN 1000000
#define MAXM 2000000

struct pair {
	int first, second;
};

struct pair ans[MAXM];
int anssize;
struct pair E[MAXM];
int Esize;

int S[MAXN+1];
int R[MAXN+1];

int n, m, k;

int findSet(int x) {
	return S[x] == x ? x : (S[x] = findSet(S[x]));
}

int link(int x, int y) {
	x = findSet(x);
	y = findSet(y);
	if(x == y)
		return 0;
	if(R[x] < R[y]) {
		int tmp = x;
		x = y;
		y = tmp;
	}
	S[y] = x;
	R[x] += R[y];
	return 1;
}

int main(int argc, char *argv[]) {
	scanf("%d %d %d", &n, &m, &k);
	int i;
	for(i=1;i<=n;++i)
		S[i] = i,
		R[i] = 1;
	while(m--)
	{
		struct pair p;
		scanf("%d %d", &p.first, &p.second);
		if(p.second <= k) {
			if(!link(p.first, p.second))
				ans[anssize++] = p;
		}
		else if(p.first > k)
			link(p.first, p.second);
		else
			E[Esize++] = p;
	}
	for(i=0;i<Esize;++i)
		if(!link(E[i].first, E[i].second))
			ans[anssize++] = E[i];
	printf("%d\n", anssize);
	for(i=0;i<anssize;++i)
		printf("%d %d\n", ans[i].first, ans[i].second);
	return 0;
}

