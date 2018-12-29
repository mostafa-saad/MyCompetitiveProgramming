/*************************************************************************}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arczaw.c                                                   *}
{*   Opis:    Rozwiazanie NIEPOPRAWNE obrazujace sposob uzycia           *}
{*            biblioteki. Wczytuje caly ciag a jako rozwiazanie zwraca   *}
{*            pierwsze k elementow.                                      *}
{*                                                                       *}
{*************************************************************************/

#include "carclib.h"

int k, a, p[1000000], ip, i;

int main()
{
    k = inicjuj();
    ip = 0;
    while(1) {
        a = wczytaj();
        if(a == 0)
            break;
        if(ip < 1000000)
            p[ip++] = a;
    }
    for(i = 0; i < k; i++)
        wypisz(p[i]);
    return 0;
}
