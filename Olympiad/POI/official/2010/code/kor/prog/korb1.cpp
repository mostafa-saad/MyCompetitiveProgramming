/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Korale (KOR)                                  *
 *   Plik:                 korb1.cpp                                     *
 *   Autor:                Wojciech Tyczynski                            *
 *   Opis:                 Rozwiazanie niepoprawne.                      *
 *   Zlozonosc czasowa:    O(n * log n)                                  *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <algorithm>
using namespace std;

#define REP(i,n) for(int i=0; i<(n); i++)
#define FOR(i,a,b) for(int i=(a); i<=(b); i++)

const int MAX_N=200000;

int n;
int T[MAX_N];
int wynik[MAX_N],w;


int main() {
	scanf("%d",&n);
	REP(i,n) scanf("%d",&T[i]);

	int result=0;
	w=0;
	FOR(i,1,10) {
		int ile=0;
		REP(j,n/i) {
			bool f=true;
			REP(k,j) {
				bool g=true;
				REP(l,i) if (T[j*i+l]!=T[k*i+l]) {
					g=false;
					break;
				}
				if (g) {	f=false;	break; }
			}
			REP(k,j) {
				bool g=true;
				REP(l,i) if (T[j*i+l]!=T[(k+1)*i-1-l]) {
					g=false;
					break;
				}
				if (g) {	f=false;	break; }
			}
			if (f) ile++;
		}
		if (result<ile) 
			result=ile,w=0;
		if (result==ile)
			wynik[w++]=i;
	}

	printf("%d %d\n",result,w);
	REP(i,w-1) printf ("%d ",wynik[i]);
	printf("%d\n",wynik[w-1]);
	return 0;
}
