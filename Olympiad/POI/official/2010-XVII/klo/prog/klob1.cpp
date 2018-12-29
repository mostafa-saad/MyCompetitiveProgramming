/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:           Klocki (KLO)                                     *
 *   Plik:              klob1.cpp                                        *
 *   Autor:             Michal Pilipczuk                                 *
 *   Opis:              Rozwiazanie niepoprawne.                         *
 *                      Heureza zachlanna.                               *
 *   Zlozonosc czasowa: O(n * m)                                         *
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
LL HT[MAX];

int oblicz(){
    REP(i,n) HT[i]=H[i]-k;
    int c=0;
    int best;
    LL sum=0,s=0;
    REP(i,n){
	sum+=HT[i];
	if (sum>=0) {
	    c=i+1;
	    s=sum;
	}
    }
    best=c-0;
    REP(i,n){
	s-=HT[i];
	while (c<i || ((c<n)&&(s+HT[c]>=0))){
	    s+=HT[c];
	    c++;
	}
	if ((s>=0) && (c-(i+1)>best)) best=c-(i+1);
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
