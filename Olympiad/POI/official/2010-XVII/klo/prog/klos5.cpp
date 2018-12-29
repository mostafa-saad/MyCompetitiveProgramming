/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Klocki (KLO)                                     *
 *   Plik:              klos5.cpp                                        *
 *   Autor:             Michal Pilipczuk                                 *
 *   Opis:              Rozwiazanie powolne.                             *
 *                      Sortowanie + przeszukiwanie od gory.             *
 *   Zlozonosc czasowa: O(m * n * log n)                                 *
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

#define INF (1000LL*MAX*1000*1000)

#define SI struct info

SI{
    LL h;
    int p;
};

int n,m;
LL k;
LL H[MAX];
SI SH[MAX];

int cmp(const void* a,const void* b){
    SI* aa = (SI*)a;
    SI* bb = (SI*)b;
    if (aa->h != bb->h)
	return ((aa->h < bb->h)?1:(-1));
    else
	if (aa->p == bb->p)
	    return 0;
	else
	    return ((aa->p < bb->p)?1:(-1));
    return 0;
}

int oblicz(){
    
    SH[0].h=0;
    REP(i,n) SH[i+1].h=SH[i].h+H[i]-k;
    REP(i,n+1) SH[i].p=i;
    
    qsort(SH,n+1,sizeof(SI),cmp);
    
    int lst=-1;
    int best=0;
    
    REP(i,n+1){
	if (SH[i].p > lst) lst=SH[i].p;
	if (lst-SH[i].p > best) best=lst-SH[i].p;
    }
    
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
