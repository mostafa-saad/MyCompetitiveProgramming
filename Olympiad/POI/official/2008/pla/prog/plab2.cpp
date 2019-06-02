/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Plakatowanie (PLA)                                        *
 *   Plik:     plab2.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie niepoprawne O(n*log n) - wypisuje sume        *
 *             (l+1/2) dla l budynkow tej samej wysokosci, po wszystkich *
 *             wysokosciach.                                             *
 *                                                                       *
 *************************************************************************/
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <algorithm>

using namespace std;

#define REP(i,n) for( int i = 0; i<int(n); ++i)
#define FOR(i,a,b) for (int i = a ;i<=int(b); ++i)
#define FORD(i,a,b) for (int i = a ;i>=int(b); --i)

const int MAX=270000;

int input[MAX];
int ile[MAX];
int n,result,dump,k,akt,nx,t,ok,m;

int comp(const void *a,const void *b){
    return ((*(int *) a)-(*(int *)b));
}

int main(){
    scanf("%d\n",&n);
    REP(i,n){scanf("%d %d\n",&dump,&input[i]);}
    qsort(input,n,sizeof(int),comp);
    akt=1; m=0;
    REP(i,n-1){
        if (input[i]!=input[i+1]){ile[m++]=akt; akt=1;} else {akt++;}
    }
    ile[m++]=akt;
    REP(i,m){
        result+=((ile[i]+1)>>1);
    }
    printf("%d\n",result);
    return 0;
}
