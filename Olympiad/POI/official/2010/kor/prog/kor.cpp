/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Korale (KOR)                                  *
 *   Plik:                 kor.cpp                                       *
 *   Autor:                Wojciech Tyczynski                            *
 *   Opis:                 Rozwiazanie wzorcowe.                         *
 *   Zlozonosc czasowa:    O(n * (log n)^2)                              *
 *   Zlozonosc pamieciowa: O(n * log n)                                  *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_N=200000;
const int MAX_LOG=19;

#define REP(i,n) for(int i=0; i<n; i++)
#define FOR(i,a,b) for(int i=(a); i<=(b); i++)

#define PB push_back
#define ALL(x) x.begin(),x.end()
#define MP make_pair
#define FI first
#define SE second
#define PI pair<int,int>


int n;
int T[MAX_N];
int W[2][MAX_LOG][MAX_N];
int ilosc,size;
vector<PI> K;
int co[MAX_N+1];
PI E[MAX_N];
int wynik[MAX_N+1],w;


inline PI KMR(int x, int dl) {
	int d=co[dl];
	PI a=MP(W[0][d][x],W[0][d][x+dl-(1<<d)]);
	PI b=MP(W[1][d][x+dl-(1<<d)],W[1][d][x]);
	return min(a,b);
}


inline int znajdz(PI e) {
	int l=0,r=size-1,q;
	while (l<r) {
		q=(l+r)/2;
		if (e<=K[q]) r=q;
		else l=q+1;
	}
	return l;
}


int main() {
	scanf("%d",&n);
	REP(i,n) scanf("%d",&T[i]);

	ilosc=n;
	int u=1,v=-1;
	FOR(i,1,n) {
		if (i==u) v++,u*=2;
		co[i]=v;
	}

	int p=0,dl=1;
	REP(i,n)
		W[0][0][i]=W[1][0][i]=T[i];
	dl*=2,p++;

	PI e;
	vector<PI>::iterator it;
	while (dl<=n) {
		K.clear();
		REP(i,n-dl+1) {
			e=MP(W[0][p-1][i],W[0][p-1][i+dl/2]);
			K.PB(e);

			e=MP(W[1][p-1][i+dl/2],W[1][p-1][i]);
			K.PB(e);
		}

		sort(ALL(K));
		it=unique(ALL(K));
		size=it-K.begin();

		REP(i,n-dl+1) {
			e=MP(W[0][p-1][i],W[0][p-1][i+dl/2]);
			W[0][p][i]=ilosc+znajdz(e);

			e=MP(W[1][p-1][i+dl/2],W[1][p-1][i]);
			W[1][p][i]=ilosc+znajdz(e);
		}

		dl*=2,p++,ilosc+=size;
	}


	int result=0;
	w=0;
	FOR(i,1,n) {
		REP(j,n/i) E[j]=KMR(i*j,i);
		sort(E,E+(n/i));
		int ile=1;
		FOR(j,1,n/i-1) if (E[j]!=E[j-1]) ile++;
		if (result<ile)
			result=ile,w=0;
		if (result==ile)
			wynik[w++]=i;
	}

	printf("%d %d\n",result,w);
	REP(i,w-1) printf ("%d ",wynik[i]);
	printf("%d\n", wynik[w-1]);
	return 0;
}
