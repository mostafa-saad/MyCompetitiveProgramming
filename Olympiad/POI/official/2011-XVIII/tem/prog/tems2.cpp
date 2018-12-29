/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Temperatura                                      *
 *   Autor:             Bartlomiej Wolowiec                              *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie powolne                              *
 *                      rozwiazanie O(n|Q|), gdzie |Q| to maksymalny     *
 *                      rozmiar kolejki, ktory moze byc rzedu O(n)       *
 *                                                                       *
 *************************************************************************/

/* - */
#include <iostream>
#include <algorithm>
#include <queue>
#include <cassert>
#include <cstdio>
#define PII pair<int, int>
using namespace std;
/* * */

#define MAX_N 1000000
int Tmin[MAX_N];
int Tmax[MAX_N];

#define TEMP second
#define POZ first

int main(void){
    int n, wynik=0;

    int sum=0;
    int pp = scanf("%i", &n);
    for(int i=0; i<n; i++)
        pp = scanf("%i%i", &Tmin[i], &Tmax[i]);

    deque<PII> Q;
    for(int i=0; i<n; i++){
        int a=Tmin[i], b=Tmax[i];
        int naj = 0;
        while(!Q.empty() && Q.front().TEMP <= a){
            naj = max(naj, Q.front().POZ);
            Q.pop_front();
        }
        Q.push_front(PII(naj, a));
        while(!Q.empty() && Q.back().TEMP > b){
            wynik = max(wynik, Q.back().POZ);
            Q.pop_back();
        }

        for(deque<PII>::iterator it=Q.begin(); it!=Q.end(); ++it)
            it->POZ++;
    }
    while(!Q.empty()){
        wynik = max(wynik, Q.back().POZ);
        Q.pop_back();
    }
    printf("%i\n", wynik);
    assert(2*n>=sum);
    return 0;
}
