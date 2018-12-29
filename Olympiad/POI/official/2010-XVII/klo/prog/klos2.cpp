/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Klocki (KLO)                                     *
 *   Plik:              klos2.cpp                                        *
 *   Autor:             Michal Pilipczuk                                 *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Algorytm brutalny z sumami prefiksowymi.         *
 *   Zlozonosc czasowa: O(m * n^2)                                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>

using namespace std;
    
#define REP(i,n) for(int _n=(n),i=0; i<_n; ++i)
#define FOR(i,a,b) for(int _b=(b),i=(a); i<=_b; ++i)
#define FORD(i,a,b) for(int _b=(b),i=(a); i>=_b; --i)

#define LL long long

#define MAX 1001000

int n,m;
LL k;
LL H[MAX];
LL SH[MAX];

int oblicz(){
    SH[0]=0;
    REP(i,n) SH[i+1]=SH[i]+H[i]-k;
    int best=0;
    REP(j,n+1) REP(i,j) if (j-i>best && SH[i]<=SH[j]) best=j-i;
    return best;
}

int main(){
    scanf("%d %d",&n,&m);
    REP(i,n) scanf("%lld",&H[i]);
    REP(i,m) {
	scanf("%lld",&k);
	if (i) printf(" ");
	printf("%d",oblicz());
    }
    printf("\n");
    return 0;
}
