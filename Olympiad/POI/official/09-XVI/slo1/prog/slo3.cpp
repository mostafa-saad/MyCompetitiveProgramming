/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Slonie (SLO)                                              *
 *   Plik:     slo3.cpp                                                  *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie wzorcowe O(n)                                 *
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

int s1[MAX], s2[MAX], p[MAX], vis[MAX], weights[MAX];
LL result = 0;
LL lowest = INT_MAX;

/* funkcja liczaca nadwyzke potrzebna do zjedzenia cyklu ponad sume wag sloni - zwraca ta nadwyzke */
LL get_cycle(int g){					
    LL without_lowest;
    LL with_lowest;
    LL cycle_lowest = INT_MAX;
    LL cycle_size = 0;
    while (!vis[g]){
	vis[g] = true;
	cycle_size++;
	if (cycle_lowest > weights[s1[g]]) cycle_lowest = (LL) weights[s1[g]];
	g = p[g];
    }
    without_lowest = (cycle_size - 2) * cycle_lowest;
    with_lowest = (cycle_size + 1) * lowest + cycle_lowest;
    if (without_lowest < with_lowest) return without_lowest;
    return with_lowest;
}

int main(){
    int n = r();
    
    memset(vis, false, sizeof(vis));
    
    REP(i,n){						/* wczytujemy wagi 			*/
	result += (LL) (weights[i] = r());
	if (lowest > weights[i]) lowest = (LL) weights[i];
    }
	
    REP(i,n)						/* wczytujamy pierwsza permutacje	*/
	s1[i] = r() - 1;
	
    REP(i,n)						/* wczytujemy druga permutacje odwrotnie*/
	s2[r() - 1] = i;
    
    REP(i,n)						/* obliczamy docelowa permutacje	*/
	p[i] = s2[s1[i]];

    REP(i,n)						/* liczymy wynik			*/
	if (!vis[i]) result += get_cycle(i);
	
    printf("%lld\n", result);
    
    return 0;
}
