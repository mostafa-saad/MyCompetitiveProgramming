/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arcb8.cpp                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie niepoprawne.                                   *}
{*            Niekontroluje dlugosci szukanego podciagu.                 *}
{*            Zlozonosc obliczeniowa: O(n + k)                           *}
{*                                                                       *}
{*************************************************************************/

#include<cstdio>

#include "carclib.h"

#define MAX_K 1000000 // maksymalna dlugosc szukanego podciagu

int a, k,
    buf[MAX_K], // kolejka reprezentujaca bufor
    ib, ie, // wskazniki na pierwszy i ostatni element w kolejce
    cou, // ilosc elementow znajdujacych sie w kolejce
    sub[MAX_K], // stos reprezentujacy szukany podciag
    is; // wskaznik na szczyt stosu
bool is_end; // czy zakonczylismy juz wczytywanie ciagu

/* Uzupelnia bufor tak aby znajdowalo sie w nim [k] elementow jesli to mozliwe
 * (jesli wczytywany ciag jeszcze sie nie skonczyl) */
void fill_buffer() {
    if(is_end || cou == k)
        return;
    int a;
    while(cou < k) {
        a = wczytaj();
        if(a == 0) {
            is_end = true;
            return;
        }
        buf[ie++] = a;
        cou++;
        if(ie == MAX_K)
            ie = 0;
    }
}

int main()
{
    k = inicjuj();
    ib = ie = cou = 0;
    is = 0;
    is_end = false;
    fill_buffer();
    while(cou > 0) {
        a = buf[ib++];
        cou--;
        if(ib == MAX_K)
            ib = 0;
        while(is > 0 && is < k && sub[is-1] < a)
            is--;
        if(is < k)
            sub[is++] = a;
        fill_buffer();
    }
    for(int i = 0; i < k; ++i)
        wypisz(sub[i]);
    return 0;
}
