/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:              Jedynki (JED)                                 *
 *   Plik:                 jed3.cpp                                      *
 *   Autor:                Pawel Parys                                   *
 *   Opis:                 Rozwiazanie weryfikujace.                     *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Zlozonosc pamieciowa: O(n)                                          *
 *                                                                       *
 *************************************************************************/

#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

typedef vector<int> vi;

template<class T> inline int size(const T &t) { return t.size(); }

#define PB push_back
#define REP(a, n) for (int a = 0; a<(n); ++a)


/////////////////////////////////////////

// u mnie reprezentacje zaczynaja sie od najmlodszych bitow (czyli odwrotnie niz na wejsciu)
// pierwsza liczba to liczba zer (moze byc =0)



vi spakuj(const vi &xxx) { // usuwa zbedne zera z reprezentacji
    vi wyn;
    int p = 0;
    while (p<size(xxx)) {
        if (!wyn.empty() && xxx[p]==0) { // mam 0 (nie na poczatku)
            if (p+1<size(xxx)) { 
                wyn.back() += xxx[p+1];
            }
            p += 2; // ostatnie zero po prostu pomijamy
        }
        else // nie 0
            wyn.PB(xxx[p++]);
    }
    if (size(wyn)%2) 
        wyn.pop_back();
    return wyn;
}


vi odejmij(const vi &n1, int od) { // odejmuje od liczby danej reprezentacja zwykla liczbe
    int p1 = 0, o1 = 0, prz = 0;
    vi wyn;
    while (od || o1==n1[p1]) {
        if (o1==n1[p1]) { o1 = 0; ++p1; continue; }
        int x = 2+p1%2-od%2-prz;
        prz = x<2;
        if (x%2) { wyn.PB(0); wyn.PB(1); } // wstaw 1
        else { wyn.PB(1); wyn.PB(0); } // wstaw 0
        ++o1;
        od /= 2;
    }
    if (prz) {
        if (p1%2==0) {  // mamy zera
            wyn.PB(0);
            wyn.PB(n1[p1]-o1); // wstaw jedynki
            o1 = 0; ++p1;
        }
        wyn.PB(1); wyn.PB(0);  // wstaw 0
        ++o1;
    }
    if (p1%2==1) wyn.PB(0); // teraz sa jedynki
    wyn.PB(n1[p1]-o1);
    ++p1;
    while (p1<size(n1))
        wyn.PB(n1[p1++]);
    return spakuj(wyn);
}


vi dodaj(const vi &n1, const vi &n2) { // dodaje dwie liczby dane reprezentacjami
    vi wyn;
    int p1 = 0, o1 = 0, p2 = 0, o2 = 0, prz = 0;
    while (p1<size(n1) || p2<size(n2)) {
        int x1 = p1<size(n1) ? n1[p1]-o1 : 2000000000;
        int x2 = p2<size(n2) ? n2[p2]-o2 : 2000000000;
        int ile = min(x1, x2);
        if (ile==0) {
            if (!x1) { o1 = 0; ++p1; continue; }
            if (!x2) { o2 = 0; ++p2; continue; }
        }
        if (p1%2==0 && p2%2==0) {
            if (prz) { wyn.PB(0); wyn.PB(1); wyn.PB(ile-1); wyn.PB(0); }
            else { wyn.PB(ile); wyn.PB(0); }
            prz = 0;
        } else
        if (p1%2==1 && p2%2==1) {
            if (prz) { wyn.PB(0); wyn.PB(ile); prz = 1; }
            else { wyn.PB(1); wyn.PB(ile-1); prz = 1; }
        } else
        if (prz) {
            wyn.PB(ile); wyn.PB(0); prz = 1; 
        } else {
            wyn.PB(0); wyn.PB(ile); prz = 0;
        }
        o1 += ile;
        o2 += ile;
    }
    if (prz) { wyn.PB(0); wyn.PB(1); }
    return spakuj(wyn);
}


vi liczba;
vi wynik;
int dl = 0;

int main() {
    // wczytaj
    int N;
    scanf("%d", &N);
    REP(a, N) {
        int x;
        scanf("%d", &x);
        liczba.PB(x);
        dl += x;
    }
    if (N%2==1)
        liczba.PB(0);
    reverse(liczba.begin(), liczba.end());
    // poczatek
    if (liczba.back()==1 && liczba[size(liczba)-2]>=1) { // zaczyna sie od 10
        wynik = vi(liczba.begin(), liczba.end()-2); // odetnij poczatkowe 10
        vi jeden; // 1
        jeden.PB(0);
        jeden.PB(1); 
        wynik = dodaj(wynik, jeden); // dodaj 1
        vi d2n1;  // 2^{dl-2}
        d2n1.PB(dl-2);
        d2n1.PB(1);
        wynik = dodaj(wynik, d2n1);
        
    } else {
        wynik.PB(dl-1);
        wynik.PB(1);
        // 2^{dl-1}
    }
    vi prz = liczba; // liczba/2
    if (prz[0]) --prz[0]; else --prz[1];
    wynik = dodaj(wynik, prz);
    wynik = odejmij(wynik, dl-(N+1)/2); // dodaj liczbe blokow jedynek, odejmij liczbe cyfr
    
    // wypisz
    int N2 = size(wynik);
    if (!wynik[0])
        --N2;
    printf("%d\n", N2);
    REP(a, N2)
        printf("%d%c", wynik[size(wynik)-1-a], a==N2-1 ? '\n' : ' ');
}
