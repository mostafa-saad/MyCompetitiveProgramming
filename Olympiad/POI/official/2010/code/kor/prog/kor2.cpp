/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Korale (KOR)                                  *
 *   Plik:                 kor2.cpp                                      *
 *   Autor:                Wojciech Tyczynski                            *
 *   Opis:                 Rozwiazanie alternatywne.                     *
 *   Zlozonosc czasowa:    O(n * log n)                                  *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;

const int MAX_N=200000;
const int MAX_LOG=19;

#define REP(i,n) for(int i=0; i<n; i++)
#define FOR(i,a,b) for(int i=(a); i<=(b); i++)
#define FORD(i,a,b) for(int i=(a); i>=(b); i--)

#define MP make_pair
#define FI first
#define SE second
#define PI pair<int,int>

const int P=1000000007;

int n;
int T[MAX_N];
int hasz[2][MAX_N+1];
int E[MAX_N];
int pot[MAX_N+1];
int wynik[MAX_N],w;


inline int KMR(int p, int dl) {
	int a=hasz[0][p+dl-1]-(p?hasz[0][p-1]*pot[dl]:0);
	int b=hasz[1][p]-(p<n-1?hasz[1][p+dl]*pot[dl]:0);
	return min(a,b);
}


int main() {
	scanf("%d",&n);
	REP(i,n) scanf("%d",&T[i]);

	pot[0]=1;
	FOR(i,1,n) pot[i]=pot[i-1]*P;

	hasz[0][0]=T[0];
	FOR(i,1,n-1) 
		hasz[0][i]=hasz[0][i-1]*P+T[i];
	hasz[1][n-1]=T[n-1];
	FORD(i,n-2,0)
		hasz[1][i]=hasz[1][i+1]*P+T[i];

	int result=0;
	w=0;
	FOR(i,1,n) {
		REP(j,n/i) E[j]=KMR(i*j,i);
		sort(E,E+n/i);
		int ile=1;
		FOR(j,1,n/i-1) if (E[j]!=E[j-1]) ile++;
		if (result<ile)
			result=ile,w=0;
		if (result==ile)
			wynik[w++]=i;
	}

	printf("%d %d\n",result,w);
	REP(i,w-1) printf("%d ",wynik[i]);
	printf("%d\n",wynik[w-1]);
	return 0;
}
