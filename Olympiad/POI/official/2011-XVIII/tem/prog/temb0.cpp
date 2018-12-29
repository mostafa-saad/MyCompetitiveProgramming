/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Temperatura                                      *
 *   Autor:             Bartlomiej Wolowiec                              *
 *   Opis:              Rozwiazanie bledne                               *
 *                      naiwne liniowe szukanie najdluzszego odcinka     *
 *                      rosnacych temperatur                             *
 *                                                                       *
 *************************************************************************/

/* - */
#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
/* * */

#define INF 2000000000
#define MAX_N 1000000
int Tmin[MAX_N];
int Tmax[MAX_N];

int main(void){
    int n, wynik=0;

    int pp = scanf("%i", &n);
    for(int i=0; i<n; i++)
        pp = scanf("%i%i", &Tmin[i], &Tmax[i]);
    int stemp=-INF, k=0;
    for(int i=0; i<n; i++){
        if(Tmax[i]<=stemp){
            k=1;
        }else{
            k++;
        }
        stemp = Tmin[i];
        wynik = max(wynik, k);
    }
    printf("%i\n", wynik);
    return 0;
}
