/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arcb4.cpp                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie nieefektywne czasowo i pamieciowo.             *}
{*            Zlozonosc obliczeniowa: O(k log n)                         *}
{*            Zlozonosc pamiecowa: O(n + k)                              *}
{*            Realizuje pomysl rozwiazania alternatywnego i wybiera      *}
{*            maksimum z przedzialu w czasie logarytmicznym wzgledem     *}
{*            jego dlugosci.                                             *} 
{*                                                                       *}
{*************************************************************************/

#include<cstdio>

#include "carclib.h"

#define MAX_N 2097153

int n, k, seq[MAX_N + 1], tre[2 * MAX_N + 2], it, is, il;

void update(int a) {
    int tmp1 = tre[2 * a], tmp2 = tre[2 * a + 1];
    if(seq[tmp1] >= seq[tmp2])
        tre[a] = tmp1;
    else
        tre[a] = tmp2;
}

void init_tre() {
    it = 1;
    while(it < n)
        it *= 2;
    for(int i = 0; i < it; ++i)
        if(i < n)
            tre[i + it] = i;
        else
            tre[i + it] = n;
    for(int i = it - 1; i > 0; --i)
        update(i);
}

int get_max(int a, int b) {
    int res = n;
    a += it;
    b += it;
    if(seq[tre[a]] > seq[res])
        res = tre[a];
    if(seq[tre[b]] > seq[res])
        res = tre[b];
    while(a / 2 != b / 2) {
        if(a % 2 == 0 && seq[tre[a + 1]] > seq[res])
            res = tre[a + 1];
        if(b % 2 == 1 && seq[tre[b - 1]] > seq[res])
            res = tre[b - 1];
        b /= 2;
        a /= 2;
    }
    return res;
}

int main()
{
    k = inicjuj();
    n = 0;
    while((n < MAX_N) && ((seq[n++] = wczytaj()) != 0));
    seq[n] = 0;
    n--;
    init_tre();
    is = 0;
    for(int i = 0; i < k; ++i) {
        il = get_max(is, n - k + i);
        is = il + 1;
        wypisz(seq[il]);
    }    
    return 0;
}
