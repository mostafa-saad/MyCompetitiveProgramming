/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Najdzielniejszy dzielnik (NAJ)                            *
 *   Plik:     najb12.cpp                                                *
 *   Autor:    Bartlomiej Wolowiec                                       *
 *   Opis:     Rozwiazanie bledne.                                       *
 *             Rozwiazanie zaklada, ze liczby >10^6 sa pierwsze          *
 *             oraz D < 2^31                                             *
 *                                                                       *
 *************************************************************************/

/* - */
#include <iostream>
#include <map>
#include <cstdio>
#define VAR(i,a) __typeof(a) i = (a)
#define REP(i,n) for(int i=0, _n=(n); i<_n; ++i)
#define FORE(i,a) for(VAR(i,(a).begin()); i!=(a).end(); ++i)
#define LL long long
using namespace std;
/* * */

#define MAXN 1000
#define MAXP 100000
#define MAX_SITO 1000000

int n, pn=0;
int liczby[MAXN];
int pierwsze[MAXP];
int sito[MAX_SITO];
map<int, int> N;

int main(void){
    pierwsze[pn++] = 2;
    for(int i=3; i<MAX_SITO; i+=2){
        if(sito[i]) continue;
        pierwsze[pn++] = i;
        for(int j=i; j<MAX_SITO; j+=2*i) sito[j]=i;
    }

    scanf("%i", &n);
    REP(i, n){
        LL a;
        scanf("%lld", &a);
        REP(i, pn)
            while(!(a%pierwsze[i])){
                N[pierwsze[i]]++;
                a/=pierwsze[i];
            }
        if(a!=1)
            N[a]++;
    }
    int k=0, D=1;
    FORE(it, N){
        if(it->second > k){
            k = it->second;
            D=1;
        }else if(it->second == k){
            D++;
        }
    }
    printf("%i\n%i\n", k, (1<<D)-1);
    return 0;
}
