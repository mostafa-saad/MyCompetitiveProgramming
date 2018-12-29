/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Temperatura                                      *
 *   Autor:             Bartlomiej Wolowiec                              *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                      Zawiera heurystyke ktora przyspiesza dla wielu   *
 *                      przypadkow                                       *
 *                                                                       *
 *************************************************************************/

/* - */
#include <iostream>
#include <algorithm>
#include <cassert>
#include <cstdio>
using namespace std;
/* * */

#define MAX_N 1000000
int Tmin[MAX_N];
int Tmax[MAX_N];

int main(void){
    int n, wynik=0;

    scanf("%d", &n);
    for(int i=0; i<n; i++)
        scanf("%d%d", &Tmin[i], &Tmax[i]);
    for(int i=0; i<n; i++){
        int temp=Tmax[i], k, a;
        for(k=i+1; k<n; k++){
            if(temp>Tmax[k])
                break;
            temp = max(temp, Tmin[k]);
        }
        temp = Tmax[k-1];
        for(a=k-1; a>=0; a--){

            if(temp<Tmin[a])
                break;
            temp = min(temp, Tmax[a]);
        }
        wynik = max(wynik, k-a-1);
        i=k-1;
    }
    printf("%i\n", wynik);
    return 0;
}
