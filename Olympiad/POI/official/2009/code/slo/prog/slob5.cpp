/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Slonie (SLO)                                              *
 *   Plik:     slob5.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie niepoprawne. Zamienia wszystkie slonie        *
 *             z najlzejszym.                                            *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <climits>
#include <cstdlib>
#include <cstring>

using namespace std;
    
#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)

#define LL long long

#define MAX 1000000

int r(){
    int x;
    scanf("%d\n", &x);
    return x;
}

int s1[MAX], s2[MAX], weights[MAX];
LL result = 0;
LL lowest = INT_MAX;

int main(){
    int n = r();
    
    REP(i,n){						/* wczytujemy wagi 			*/
	weights[i] = r();
	if (lowest > weights[i]) lowest = (LL) weights[i];
    }
	
    REP(i,n)						/* wczytujamy pierwsza permutacje	*/
	s1[i] = r() - 1;
	
    REP(i,n)						/* wczytujemy druga permutacje		*/
	s2[i] = r() - 1;
    
    REP(i,n)
	if (s1[i] != s2[i]) result += (LL) weights[s1[i]] + lowest;

    result -= 2 * lowest;				/* najlżejszy słoń "powinien" być na swoim miejscu */
    
    printf("%lld\n", result);
    
    return 0;
}
