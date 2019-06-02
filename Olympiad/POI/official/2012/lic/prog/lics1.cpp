/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Licytacja                                        *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(2^n)                                           *
 *   Opis:              Rozwiazanie powolne: wzorcowka bez spamietywania *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <iostream>
#include "cliclib.h"
#define MAXN 2000

using namespace std;

int n;

int optymalny_ruch[MAXN + 1][MAXN + 1];
int pula, stawka;

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
    int ruch = spr_poz(apula + astawka, 1);
    if(ruch == 1){
        optymalny_ruch[apula][astawka] = 1;
        return 2;
    }
    ruch = spr_poz(apula, astawka * 2);
    if(ruch == 1){
        optymalny_ruch[apula][astawka] = 2;
        return 2;
    }
    ruch = spr_poz(apula, astawka * 3);
    if(ruch == 1){
        optymalny_ruch[apula][astawka] = 3;
        return 2;
    }
    return 1;
}

void wybierz_ruch(){
    spr_poz(pula, stawka);
    int x = optymalny_ruch[pula][stawka];
    wykonaj_ruch(x);
    alojzy(x);
}

int main(){
    n = inicjuj();
    stawka = 1;
    while(true){
        wybierz_ruch();
        wykonaj_ruch(bajtazar());
    }
    return 0;
}
