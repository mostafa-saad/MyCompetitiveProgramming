/**************************************************************************}
{*                                                                        *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                            *}
{*   Plik:    carclib.c                                                   *}
{*   Autor:   Bartosz Gorski                                              *}
{*   Opis:    Biblioteka dla zawodnikow.                                  *}
{*                                                                        *}
{**************************************************************************/

#include <stdlib.h>
#include <stdio.h>

#include "carclib.h"

#define MIN_K 1
#define MAX_K 1000000
#define MIN_P 1
#define MAX_P 1000000000

static int K, P, ile_wypisano_liczb, koniec_ciagu, zainicjowano = 0;

static void  blad(char *com)
{
    printf("%s\n", com);
    exit(0);
}

int inicjuj()
{
    if(zainicjowano == 1)
        blad("Program zawodnika moze wywolac funkcje inicjuj tylko raz!!!");
    scanf("%d", &K);
    if(K < MIN_K || K > MAX_K)
        blad("Niepoprawna wartosc k!!!");
    zainicjowano = 1;
    ile_wypisano_liczb = 0;
    koniec_ciagu = 0;
    return K;
}

int wczytaj()
{
    if(zainicjowano == 0)
        blad("Program zawodnika nie wywolal funkcji inicjuj!!!");
    if(koniec_ciagu == 1)
        blad("Program zawodnika wywolal funkcje wczytaj po otrzymaniu informacji o koncu ciagu!!!");
    scanf("%d", &P);
    if(P == 0) {
        koniec_ciagu = 1;
        return 0;
    }
    if(P < MIN_P || P > MAX_P)
        blad("Nieprawidlowa jakosc projektu");
    return P;
}

void wypisz(int jakoscProjektu)
{
    if(zainicjowano == 0)
        blad("Program zawodnika nie wywolal funkcji inicjuj!!!");
    printf("%d\n", jakoscProjektu);
    if(++ile_wypisano_liczb == K)
        exit(0);
}
