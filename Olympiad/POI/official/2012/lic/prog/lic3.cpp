/*************************************************************************
 *                                                                       *
 *                    XIX Olimpiada Informatyczna                        *
 *                                                                       *
 *   Zadanie:           Licytacja                                        *
 *   Autor:             Alan Kutniewski                                  *
 *   Zlozonosc czasowa: O(n log^3 n)                                     *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <iostream>
#include "cliclib.h"
#define MAXN 30000
#define MAX_IND 250
#define MAX_2 16

using namespace std;

int n;

int pozycja[MAXN + 1][MAX_IND];
int optymalny_ruch[MAXN + 1][MAX_IND];
int pula, stawka;

int oblicz_indeks(int staw){
    int i2 = 0, i3 = 0;
    while(staw % 2 == 0){
        ++i2;
        staw /= 2;
    }
    while(staw % 3 == 0){
        ++i3;
        staw /= 3;
    }
    return i3 * MAX_2 + i2;
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
    int istawka = oblicz_indeks(astawka);
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
    int x = optymalny_ruch[pula][oblicz_indeks(stawka)];
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
