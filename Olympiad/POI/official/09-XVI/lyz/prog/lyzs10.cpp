/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Lyzwy (LYZ)                                               *
 *   Plik:     lyzs10.cpp                                                *
 *   Autor:    Adam Gawarkiewicz                                         *
 *   Opis:     Rozwiazanie wolniejsze O(n*m). Po kazdym wydarzeniu       *
 *             poprawia ustawienie w sposob zachlanny.                   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <map>
#include <utility>
#include <algorithm>

using namespace std;

typedef map<int, pair<long long, long long> > mapa;

// klucz: rozmiar stopy
// wartosc: poczatek przydzialu, ilosc elementow
mapa czlonkowie;

#define ROZMIAR(iter) iter->first
#define POCZATEK(iter) iter->second.first
#define ILOSC(iter) iter->second.second

int ile_nieprawidlowych = 0;
int n, m, k, d;

int czy_nieprawidlowy(mapa::iterator &iter) {
    return POCZATEK(iter) + ILOSC(iter) - 1 > ((long long)(ROZMIAR(iter)+d))*((long long)k);
}

int main() {
    scanf("%d%d%d%d", &n, &m, &k, &d);
    while (m--) {
        int r, x;
        scanf("%d%d", &r, &x);
        mapa::iterator it; // iterator wskazujacy na wpisy "do poprawki"
        long long poczatek; // najmniejszy mozliwy przydzial
        
        if (x<0) {
            mapa::iterator akt = czlonkowie.find(r);
            ile_nieprawidlowych -= czy_nieprawidlowy(akt);
            ILOSC(akt) += x;
            if (ILOSC(akt)==0) {
                if (akt == czlonkowie.begin())
                    poczatek = 0;
                else {
                    mapa::iterator poprz = akt;
                    poprz--;
                    poczatek = POCZATEK(poprz) + ILOSC(poprz);
                }
                it = akt;
                it++;
                czlonkowie.erase(akt);
            } else {
                ile_nieprawidlowych += czy_nieprawidlowy(akt);
                poczatek = POCZATEK(akt) + ILOSC(akt);
                it = ++akt;
            }
        } else {
            mapa::iterator akt = czlonkowie.find(r);
            if (akt==czlonkowie.end()) {
                czlonkowie[r] = make_pair(((long long)r-1)*((long long)k)+1, x);
                akt = czlonkowie.find(r);
                if (akt!=czlonkowie.begin()) {
                    mapa::iterator poprz = akt;
                    poprz--;
                    POCZATEK(akt) = max(POCZATEK(akt), POCZATEK(poprz) + ILOSC(poprz));
                }
            } else {
                ile_nieprawidlowych -= czy_nieprawidlowy(akt);
                ILOSC(akt) += x;
            }
            ile_nieprawidlowych += czy_nieprawidlowy(akt);
            poczatek = POCZATEK(akt) + ILOSC(akt);
            it = ++akt;
        }
        
        while (it != czlonkowie.end()) {
            poczatek = max(poczatek, ((long long)ROZMIAR(it)-1)*((long long)k)+1);
            if (poczatek == POCZATEK(it))
                break;
            ile_nieprawidlowych -= czy_nieprawidlowy(it);
            POCZATEK(it) = poczatek;
            poczatek += ILOSC(it);
            ile_nieprawidlowych += czy_nieprawidlowy(it);
            it++;
        }
        
        if (ile_nieprawidlowych)
            printf("NIE\n");
        else
            printf("TAK\n");
    }
    return 0;
}
