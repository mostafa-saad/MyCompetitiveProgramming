/*************************************************************************}
{*                                                                       *}
{*                     XVI Olimpiada Informatyczna                       *}
{*                                                                       *}
{*   Zadanie: Architekci (ARC)                                           *}
{*   Plik:    arc1.cpp                                                   *}
{*   Autor:   Bartosz Gorski                                             *}
{*   Opis:    Rozwiazanie wzorcowe.                                      *}
{*            Zlozonosc obliczeniowa: O(n + k)                           *}
{*            Rozwiazanie wykorzystuje STLa.                             *}
{*                                                                       *}
{*************************************************************************/

#include<cstdio>
#include<list>

#include "carclib.h"
using namespace std;

int k, a;
list<int> sub;
list<int>::iterator cen, nex;

int main()
{
    k = inicjuj();
    sub.clear();
    for(int i = 0; i < k; ++i)
        sub.push_back(0);
    cen = sub.end();
    cen--;
    while((a = wczytaj()) != 0)
    {
        sub.push_back(a);
        nex = cen;
        nex++;
        while(nex != sub.end()) {
            if(*cen < *nex)
                break;
            cen++;
            nex++;
        }
        if(cen != sub.begin()) {
            nex = cen;
            nex--;
        }
        sub.erase(cen);
        cen = nex;
    }
    for(list<int>::iterator it = sub.begin(); it != sub.end(); ++it)
        wypisz(*it);
    return 0;
}
