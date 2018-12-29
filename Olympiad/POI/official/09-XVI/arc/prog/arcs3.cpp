/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Architekci (ARC)                                          *
 *   Plik:     arcs3.cpp                                                 *
 *   Autor:    Bartosz Gorski                                            *
 *   Opis:     Rozwiazanie liniowo szukajace pierwszej niemonotonicznosci*
 *             czas: O(n*k); pamiec: O(k)                                *
 *                                                                       *
 *************************************************************************/

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
    while((a = wczytaj()) != 0) {
        sub.push_back(a);
        nex = cen = sub.begin();
        nex++;
        while(nex != sub.end()) {
            if(*cen < *nex)
                break;
            cen++;
            nex++;
        }
        sub.erase(cen);
    }
    for(list<int>::iterator it = sub.begin(); it != sub.end(); ++it)
        wypisz(*it);
    return 0;
}
