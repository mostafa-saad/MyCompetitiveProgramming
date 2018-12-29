/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Plakatowanie (PLA)                                        *
 *   Plik:     plab1.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie niepoprawne O(n*log n) - wypisuje liczbe      *
 *             roznych wysokosci.                                        *
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
int n,result,dump,k,akt,nx,t,ok;

int comp(const void *a,const void *b){
    return ((*(int *) a)-(*(int *)b));
}

int main(){
    scanf("%d\n",&n);
    REP(i,n){scanf("%d %d\n",&dump,&input[i]);}
    qsort(input,n,sizeof(int),comp);
    REP(i,n-1){if (input[i]!=input[i+1]){result++;}}
    printf("%d\n",result+1);
    return 0;
}
