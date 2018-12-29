/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Slowa (SLO)                                               *
 *   Plik:     slo3.cpp                                                  *
 *   Autor:    Wojciech Tyczynski                                        *
 *   Opis:     Rozwiazanie alternatywne O(S)                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <queue>
#include <deque>

using namespace std;

#define MAX_N 100000
#define PB push_back
#define SIZE(x) (int)x.size()

#define REP(i,n) for(int i=0; i<(n); i++)


int n;
int T[MAX_N];


inline bool zly() {
	REP(i,n-1)
		if (T[i+1]==0 && (T[i]!=1 && T[i]!=3)) return true;
	return false;
}


inline void poczatek() {
	if (T[0]==0) T[0]=2;
}


inline void koniec() {
	if (T[n-1]==3) T[n-1]=2;
	if (T[n-1]==1) n--;
}


inline void wszystkie() {
	/* zamienia wystapienia 1,0 na 2 */
	int i=0,j=0;
	while (i<n) {
		if (i<n-1 && T[i]==1 && T[i+1]==0)
			T[j++]=2,i+=2;
		else
			T[j++]=T[i++];
	}
	n=j;
		
	/* zamienia wystapienia 3,0 na 2,2 */
	REP(j,n-1) 
		if (T[j]==3 && T[j+1]==0)
			T[j]=T[j+1]=2;
}


inline void zmniejsz() {
	REP(i,n)	T[i]--;
}


int main() {
	int test;
	scanf("%d",&test);

	while (test--) {
		scanf("%d",&n);
		REP(i,n) scanf("%d",&T[i]);

		bool result=true;

		while (n>1) {
			if (zly()) {
				result=false;
				break;
			}

			poczatek();
			koniec();
			wszystkie();

			zmniejsz();
		}

		printf("%s\n",result?"TAK":"NIE");
	}

	return 0;
}
