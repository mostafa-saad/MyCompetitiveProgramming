/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Szklana pulapka (SZK)                                     *
 *   Plik:     szkb2.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Heurystyka parzystosciowa, wersja 2.                      *
 *                                                                       *
 *************************************************************************/
#include <cstdlib>
#include <cstdio>
#include <cmath>

#define REP(i,n) for( int i = 0; i<int(n); ++i)
#define FOR(i,a,b) for (int i = a ;i<=int(b); ++i)
#define FORD(i,a,b) for (int i = a ;i>=int(b); --i)
#define SP struct point

const int MAX1=150000;
const int MAX2=510000;

int even[MAX1];
int odd[MAX1];
int ec,oc,n,a,b;

int main(){
    scanf("%d\n",&n);
    printf("%d\n",n/2);
    FOR(i,1,n){
        scanf("%d %d\n",&a,&b);
        if ((a+b)%2){odd[oc++]=i;} else {even[ec++]=i;}
    }
    REP(i,oc/2) printf("%d %d\n",odd[i],odd[i+oc/2]);
    REP(i,ec/2) printf("%d %d\n",even[i],even[i+ec/2]);
    return 0;
}
