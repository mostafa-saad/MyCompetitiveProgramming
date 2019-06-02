/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Licytacja                                        *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n log^2 n)                                     *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <iostream>
#include "cliclib.h"
#define MAXN 30000
#define MAX_IND 250

using namespace std;

int n;

int pozycja[MAXN + 1][MAX_IND];
int indeks_stawki[MAXN + 1];
int optymalny_ruch[MAXN + 1][MAX_IND];
int pula, stawka;

void oblicz_indeksy(int maxn){
    int aind = 0;
    for(int i = 1; i <= maxn; i *= 2){
        for(int j = 1; i * j <= maxn; j *= 3){
            indeks_stawki[i * j] = aind++;
        }
    }
}

void wykonaj_ruch(int x){
    if(x == 1){
        pula += stawka;
        stawka = 1;
    }
    if(x == 2){
        stawka *= 2;
    }
    if(x == 3){
        stawka *= 3;
    }
}

int spr_poz(int apula, int astawka){
    if(apula + astawka >= n){
        return 1;
    }
    int istawka = indeks_stawki[astawka];
    if(pozycja[apula][istawka])return pozycja[apula][istawka];
    int ruch = spr_poz(apula + astawka, 1);
    if(ruch == 1){
        pozycja[apula][istawka] = 2;
        optymalny_ruch[apula][istawka] = 1;
        return 2;
    }
    ruch = spr_poz(apula, astawka * 2);
    if(ruch == 1){
        pozycja[apula][istawka] = 2;
        optymalny_ruch[apula][istawka] = 2;
        return 2;
    }
    ruch = spr_poz(apula, astawka * 3);
    if(ruch == 1){
        pozycja[apula][istawka] = 2;
        optymalny_ruch[apula][istawka] = 3;
        return 2;
    }
    pozycja[apula][istawka] = 1;
    return 1;
}

void wybierz_ruch(){
    spr_poz(pula, stawka);
    int x = optymalny_ruch[pula][indeks_stawki[stawka]];
    wykonaj_ruch(x);
    alojzy(x);
}

int main(){
    n = inicjuj();
    oblicz_indeksy(n);
    stawka = 1;
    while(true){
        wybierz_ruch();
        wykonaj_ruch(bajtazar());
    }
    return 0;
}
