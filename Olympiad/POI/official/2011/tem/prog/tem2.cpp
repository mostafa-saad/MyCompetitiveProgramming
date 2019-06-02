/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Temperatura                                      *
 *   Autor:             Bartlomiej Wolowiec                              *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *   Zlozonosc czasowa: O(n*lg(n))                                       *
 *                                                                       *
 *************************************************************************/

/* - */
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
/* * */

#define MAX_N (1<<20)
int Tmax[MAX_N];

int Drzewo[2*MAX_N];
int *Tmin = Drzewo + MAX_N;

#define TEMP second
#define POZ first

const int INF = 1100000000;
int Maks(int p, int k) {
    int ret = -INF;
    p+=MAX_N;
    k+=MAX_N;
    while(p<=k){
        if((p&1)==1) ret = max(ret, Drzewo[p]);
        if((k&1)==0) ret = max(ret, Drzewo[k]);
        p = (p+1)/2;
        k = (k-1)/2;
    }
    return ret;
}

int main(void){
    int n, wynik=0;

    int pp = scanf("%i", &n);
    for(int i=0; i<n; i++)
        pp = scanf("%i%i", &Tmin[i], &Tmax[i]);

    for(int i=MAX_N-1; i>0; i--)
        Drzewo[i] = max(Drzewo[i*2], Drzewo[i*2+1]);

    int j=1;
    for(int i=0; i<n; i++){
        while(j<n && Maks(i,j-1)<=Tmax[j]) j++;
        wynik = max(wynik, j-i);
    }
    printf("%i\n", wynik);
    return 0;
}
