/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arcs0.cpp                                                  *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie nieefektywne czasowo.                          *}
{*            Szukajac najwiekszego leksykograficznie podciagu dlugosci  *}
{*            k sprawdza wszystkie podciagi dlugosci k - 1.              *}
{*            Zlozonosc obliczeniowa: O(n * k ^ 2)                       *}
{*                                                                       *}
{*************************************************************************/

#include<cstdio>

#include "carclib.h"

#define MAX_K 1000000 // maksymalna dlugosc szukanego podciagu

int k, a;
int sub[MAX_K], tmp[MAX_K][2];

int main()
{
    k = inicjuj();
    for(int i = 0; i < k; ++i)
        sub[i] = 0;
    while((a = wczytaj()) != 0) {
        for(int i = 0; i < k; ++i)
            tmp[i][0] = sub[i];
        for(int i = 0; i < k; ++i) {
            for(int j = 0; j < i; ++j)
                tmp[j][1] = sub[j];
            for(int j = i + 1; j < k; ++j)
                tmp[j - 1][1] = sub[j];
            tmp[k - 1][1] = a;
            for(int j = 0; j < k; ++j) {
                if(tmp[j][0] < tmp[j][1]) {
                    for(int l = 0; l < k; l++)
                        tmp[l][0] = tmp[l][1];
                    break;
                }
                if(tmp[j][0] > tmp[j][1])
                    break;
            }
        }
        for(int i = 0; i < k; ++i)
            sub[i] = tmp[i][0];
    }
    for(int i = 0; i < k; ++i)
        wypisz(sub[i]);
    return 0;
}
