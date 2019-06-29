/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Plakatowanie (PLA)                                        *
 *   Plik:     plas4.cpp                                                 *
 *   Autor:    Michal Pilipczuk                                          *
 *   Opis:     Rozwiazanie nieefektywne O(n^2), implementacja z          *
 *             minimalizowana stala.                                     *
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
int n,result,dump,k,akt,nx,t,ok,j,i;

int main(){
    scanf("%d\n",&n);
    for(i=0;i<n;i++){
        scanf("%d %d\n",&dump,&input[i]);
    }
    for(i=0;i<n;i++){
        ok=1; k=input[i];
        for (j=(i-1);j>=0;j--){
            if (input[j]<k){break;}
            if (input[j]==k){ok=0; break;}
        }
        if (ok){result++;}
    }
    printf("%d\n",result);
    return 0;
}
