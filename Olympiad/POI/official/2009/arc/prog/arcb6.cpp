/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arcb6.cpp                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie nieefektywne czasowo i pamieciowo.             *}
{*            Zlozonosc obliczeniowa: O(n + k)                           *}
{*            Zlozonosc pamiecowa: O(n + k)                              *}
{*            Realizuje pomysl rozwiazania alternatywnego ale wczytuje   *}
{*            caly ciag do pamieci.                                      *} 
{*                                                                       *}
{*************************************************************************/


#include<cstdio>

#include "carclib.h"
using namespace std;

#define MAX_K 1000000
#define MAX_N 7000000

int k, n, seq[MAX_N + 1], sub[MAX_K], is;

int main()
{
    k = inicjuj();
    n = 0;
    while((n < MAX_N) && ((seq[n++] = wczytaj()) != 0));
    seq[n] = 0;
    n--;
    is = 0;
    for(int i = 0; i < n; ++i) {
        while(is > 0 && (is + n - i) > k && sub[is - 1] < seq[i])
            is--;
        if(is < k)
            sub[is++] = seq[i];
    }
    for(int i = 0; i < k; ++i)
        wypisz(sub[i]);
    return 0;
}
