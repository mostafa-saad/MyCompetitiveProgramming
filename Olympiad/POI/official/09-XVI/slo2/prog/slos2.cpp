/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Slowa (SLO)                                               *
 *   Plik:     slob8.cpp                                                 *
 *   Autor:    Wojciech Tyczynski                                        *
 *   Opis:     Nieefektywna implementacja rozwiazania alternatywnego     *
 *             z uzyciem STL-a                                           *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <queue>
#include <deque>
using namespace std;

#define MAX_N 100000
#define PB push_back

#define REP(i,n) for(int i=0; i<(n); i++)


int n;
deque<int> K;


inline bool zly() {
	REP(i,n-1)
		if (K[i+1]==0 && (K[i]!=1 && K[i]!=3)) return true;
	return false;
}


inline void poczatek() {
	if (K[0]==0) K[0]=2;
}


inline void koniec() {
	if (K[n-1]==3) K[n-1]=2;
	if (K[n-1]==1) K.pop_back(),n--;
}


inline void wszystkie() {
	/* zamienia wystapienia 1,0 na 2 */
	deque<int>::iterator q;
	int i=0;
	while (i<n-1) {
		if (K[i]==1 && K[i+1]==0) {
			K[i]=2;
			q=K.begin()+i+1;
			K.erase(q),n--;
		}
		i++;
	}

	/* zamienia wystapienia 3,0 na 2,2 */
	REP(i,n-1)
		if (K[i]==3 && K[i+1]==0)
			K[i]=K[i+1]=2;
}


inline void zmniejsz() {
	REP(i,n) K[i]--;
}


int main() {
	int test;
	scanf("%d",&test);

	while (test--) {
		K.clear();
		scanf("%d",&n);

		int x;
		REP(i,n) {
			scanf("%d",&x);
			K.PB(x);
		}

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

