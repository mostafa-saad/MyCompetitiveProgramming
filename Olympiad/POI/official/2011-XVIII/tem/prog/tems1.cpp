/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Temperatura                                      *
 *   Autor:             Bartlomiej Wolowiec                              *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/

/* - */
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
/* * */

#define MAX_N 1000000
int Tmin[MAX_N];
int Tmax[MAX_N];

int main(void){
    int n, wynik=0;

    int pp = scanf("%i", &n);
    for(int i=0; i<n; i++)
        pp = scanf("%i%i", &Tmin[i], &Tmax[i]);
    for(int i=0; i<n; i++){
        int temp=Tmin[i], k;
        //printf("------------- %i %i\n", i, j);
        for(k=i+1; k<n; k++){
            if(temp>Tmax[k])
                break;
            temp = max(temp, Tmin[k]);
            //printf("%i %i\n", k, temp);
        }
        wynik = max(wynik, k-i);
    }
    printf("%i\n", wynik);
    return 0;
}
