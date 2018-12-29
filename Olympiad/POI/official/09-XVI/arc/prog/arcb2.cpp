/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arcb2.cpp                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie nieefektywne czasowo i pamieciowo.             *}
{*            Zlozonosc obliczeniowa: O(n * k)                           *}
{*            Zlozonosc pamiecowa: O(n + k)                              *}
{*            Realizuje pomysl rozwiazania alternatywnego i wybiera      *}
{*            maksimum z przedzialu w czasie liniowym wzgledem jego      *}
{*            dlugosci.                                                  *} 
{*                                                                       *}
{*************************************************************************/

#include<cstdio>

#include "carclib.h"

#define MAX_N 8000000

int n, k, is, il, max_num, seq[MAX_N + 1];

int main()
{
    k = inicjuj();
    n = 0;
    while((n < MAX_N) && ((seq[n++] = wczytaj()) != 0));
    seq[n] = 0;
    n--;
    is = 0;
    for(int i = 0; i < k; ++i) {
        max_num = 0;
        for(int j = is; j < n - k + i + 1; ++j)
            if(seq[j] > max_num) {
                il = j;
                max_num = seq[j];
            }
        is = il + 1;
        wypisz(max_num);
    }    
    return 0;
}
