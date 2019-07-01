/*************************************************************************
 *                                                                       *
 *                    XX Olimpiada Informatyczna                         *
 *                                                                       *
 *   Zadanie:              Multidrink                                    *
 *   Autor:                Przemyslaw Horban                             *
 *   Zlozonosc czasowa:    O(n)                                          *
 *   Opis:                 Rozwiazanie wzorcowe,                         *
 *                         programowanie dynamiczne                      *
 *                                                                       *
 *************************************************************************/

#include<iostream>
#include<set>
#include<iomanip>
#include<sstream>
#include<fstream>
#include<stack>
#include<cstdio>
#include<cmath>
#include<cassert>
#include<queue>
#include<vector>
#include<list>
#include<algorithm>
#include<map>
#include<cstring>
#include<cctype>

#define DEBUG 0
#define deb(x) if(DEBUG) { cout << #x << " = " << (x) << endl; }

using namespace std;
#define fe(e,C) for(__typeof((C).begin()) e = (C).begin(); e != (C).end(); e++)
#define foreach(VAR_DEF, C) \
    fe(__varname, C) \
        for(bool run_once = true; run_once; ) \
            for(VAR_DEF = *(__varname); run_once; run_once = false)
#define fi(i,n) for(int (i) = 0, __end = (n); (i) < __end; i++)
#define iterate_until(i,s,n) for(int (i) = (s), __end = (n); (i) < __end; i++)
#define iterate_to(i,a,b) ft(i,a,b)
#define ft(i,a,b) for(int (i) = (a), __end = (b); (i) <= __end; (i)++)
#define ALL(V) (V).begin(), (V).end()
#define SET(T, c) memset(T, c, sizeof(T))
#define UNIQUE(V) (V).erase(unique(ALL(V)), (V).end())

class Drzewo {
public:
    vector<vector<int> > E;

    Drzewo(FILE *input, int zmniejszenieIndeksow) {
        int n;
        if(1 != scanf("%d", &n))
            exit(-1);
        E.clear();
        E.resize(n);

        iterate_until(i, 0, n-1) {
            int u, v;
            if(2 != scanf("%d%d", &u, &v))
                exit(-1);
            u -= zmniejszenieIndeksow;
            v -= zmniejszenieIndeksow;
            E[u].push_back(v);
            E[v].push_back(u);
        }
    }

    vector<int> sciezka(int u, int v) const {
        assert(0 <= u && u < rozmiar());
        assert(0 <= v && v < rozmiar());
        assert(v != u);

        vector<int> sciezka;
        sciezka.push_back(u);

        if(przedluzDo(&sciezka, v))
            return sciezka;
        else
            return vector<int>();
    }

    int rozmiar() const {
        return E.size();
    }

private:
    bool przedluzDo(vector<int> *sciezkaPtr, int cel) const {
        vector<int> &sciezka = *sciezkaPtr;

        assert(!sciezka.empty());

        int koniec = sciezka.back();
        int przedOstatni = (sciezka.size() > 1 ? *(sciezka.end() - 2) : -1);

        if(koniec == cel)
            return true;

        foreach(int nast, E[koniec]) {
            if(nast != przedOstatni) {
                sciezka.push_back(nast);
                if(przedluzDo(sciezkaPtr, cel))
                    return true;
                sciezka.pop_back();
            }
        }
        return false;
    }
};


class Rozpiecie {
public:
    vector<vector<int> > synowie;
    vector<int> korzenie;

    Rozpiecie(const Drzewo &D, int u, int v) {
        synowie.clear();
        synowie.resize(D.rozmiar());

        korzenie = D.sciezka(u, v);

        iterate_until(i, 0, korzenie.size()) {
            int korzenNaLewo = -1,
                korzen = korzenie[i],
                korzenNaPrawo = -1;
            if(i > 0)
                korzenNaLewo = korzenie[i - 1];
            if(i + 1 < (int)korzenie.size())
                korzenNaPrawo = korzenie[i + 1];

            dodajSynow(korzen, D, korzenNaLewo, korzenNaPrawo);
        }
    }

    size_t dlugosc() const {
        return korzenie.size();
    }

    size_t liczbaWezlow() const {
        return synowie.size();
    }

private:
    void dodajSynow(int korzen, const Drzewo &D,
                    int unikaj1, int unikaj2) {
        foreach(int nast, D.E[korzen]) {
            if(nast != unikaj1 && nast != unikaj2) {
                synowie[korzen].push_back(nast);
                dodajSynow(nast, D, korzen, -1);
            }
        }
    }
};

// Zaczynamy ze zbiorem sciezek jednoelementowych.
// sklej(u, v), laczy konce dwoch sciezek, tworzac jedna
// przejdz(u), zaczyna w u, ktory musi byc poczatkiem sciezki
// i zwraca wektor zawierajacy jej elementy.
class SciezkiDwukierunkowe {
    vector<char> liczbaSklejen;
    vector<int> nastepnikoPoprzednik;

public:
    SciezkiDwukierunkowe(int rozmiar)
        : liczbaSklejen(rozmiar, 0), nastepnikoPoprzednik(rozmiar, 0) {}

    void sklej(int u, int v) {
        assert(liczbaSklejen[u] < 2);
        assert(liczbaSklejen[v] < 2);

        liczbaSklejen[u] += 1;
        liczbaSklejen[v] += 1;

        nastepnikoPoprzednik[u] ^= v;
        nastepnikoPoprzednik[v] ^= u;
    }

    vector<int> przejdz(int u) const {
        assert(0 <= u && u < (int)liczbaSklejen.size());
        assert(liczbaSklejen[u] < 2);

        vector<int> sciezka;
        sciezka.push_back(u);

        if(liczbaSklejen[u] == 0)
            return sciezka;

        // liczbaSklejen[u] == 1
        sciezka.push_back(nastepnikoPoprzednik[u]);
        while(liczbaSklejen[sciezka.back()] == 2) {
            int przedOstatni = *(sciezka.end() - 2);
            int ostati = sciezka.back();
            int nastepny = nastepnikoPoprzednik[ostati] ^ przedOstatni;
            sciezka.push_back(nastepny);
        }
        return sciezka;
    }
};

enum TypSciezkiPoDrzewie {
    Z1Do1 = 0, // pojedynczy wezel
    Z1Do2 = 1, // z korzenia do potomka
    Z2Do2 = 2, // miedzy 2 potomkami korzenia
    Z0Do0 = 3  // nie istnieje zadne powyzsze
};
const int LICZBA_TYPOW_SCIEZEK = 4;

class SciezkiRozpiecia {
public:
    SciezkiRozpiecia(const Rozpiecie &R): sciezki(R.liczbaWezlow()) {
        foreach(int korzen, R.korzenie)
        sciezkiWDrzewach.push_back(wyznaczSciezke(R, korzen));
    }

    TypSciezkiPoDrzewie sciezkaPo(int nrDrzewa, vector<int> *sciezkaWsk) const {
        assert(0 <= nrDrzewa && nrDrzewa < (int)sciezkiWDrzewach.size());

        sciezkaWsk->clear();

        int poczatek = sciezkiWDrzewach[nrDrzewa].poczatek;
        if(poczatek >= 0) {
            *sciezkaWsk = sciezki.przejdz(poczatek);
            assert(sciezkaWsk->back() == sciezkiWDrzewach[nrDrzewa].koniec);
        }
        else {
            assert(sciezkiWDrzewach[nrDrzewa].typ == Z0Do0);
        }

        return sciezkiWDrzewach[nrDrzewa].typ;
    }

private:
    struct Sciezka {
        Sciezka(TypSciezkiPoDrzewie typ, int pocz, int kon)
            : typ(typ), poczatek(pocz), koniec(kon) {}
        TypSciezkiPoDrzewie typ;
        int poczatek, koniec;
    };

    // Zawiera przebiegi sciezek o poczatkach i koncach
    // w sciezkiWDrzewach.
    SciezkiDwukierunkowe sciezki;

    vector<Sciezka> sciezkiWDrzewach;

    Sciezka wyznaczSciezke(const Rozpiecie &R, int korzen) {
        vector<Sciezka> sciezkiTypu[LICZBA_TYPOW_SCIEZEK];

        foreach(int syn, R.synowie[korzen]) {
            const Sciezka &s = wyznaczSciezke(R, syn);
            sciezkiTypu[s.typ].push_back(s);
        }

        // W pierwszych trzech przypadkach, nie da sie
        // skonstuowac sciezki w poddrzewie
        if(!sciezkiTypu[Z0Do0].empty())
            return Sciezka(Z0Do0, -1, -1);

        if(!sciezkiTypu[Z2Do2].empty())
            return Sciezka(Z0Do0, -1, -1);

        if(sciezkiTypu[Z1Do2].size() > 2)
            return Sciezka(Z0Do0, -1, -1);

        if(sciezkiTypu[Z1Do2].size() == 2) {
            // - zaczynamy 1 w dol
            // - z 2 w dol do korzenia
            // - z korzenia 2 w dol
            // - konczymy 1 w dol
            // - przeskakujemy jedynki

            Sciezka &z1Do2a = sciezkiTypu[Z1Do2][0];
            Sciezka &z1Do2b = sciezkiTypu[Z1Do2][1];

            Sciezka s(Z2Do2, -1, -1);

            s.poczatek = z1Do2a.poczatek;
            sciezki.sklej(z1Do2a.koniec, korzen);
            sciezki.sklej(korzen, z1Do2b.koniec);
            int ostatniKoniec = z1Do2b.poczatek;

            foreach(Sciezka &z1Do1, sciezkiTypu[Z1Do1]) {
                sciezki.sklej(ostatniKoniec, z1Do1.poczatek);
                ostatniKoniec = z1Do1.koniec;
            }

            s.koniec = ostatniKoniec;
            return s;
        }

        if(sciezkiTypu[Z1Do2].size() +
                sciezkiTypu[Z1Do1].size() > 0) {
            // - zaczynamy w korzeniu
            // - idziemy do poddrzewa 1-2, konczac w jego korzeniu
            // - przechodzimy jedynki

            Sciezka s(Z1Do2, -1, -1);

            s.poczatek = korzen;

            int ostatniKoniec = korzen;
            if(!sciezkiTypu[Z1Do2].empty()) {
                sciezki.sklej(korzen, sciezkiTypu[Z1Do2][0].koniec);
                ostatniKoniec = sciezkiTypu[Z1Do2][0].poczatek;
            }

            foreach(Sciezka &z1Do1, sciezkiTypu[Z1Do1]) {
                sciezki.sklej(ostatniKoniec, z1Do1.poczatek);
                ostatniKoniec = z1Do1.koniec;
            }

            s.koniec = ostatniKoniec;
            return s;
        }

        return Sciezka(Z1Do1, korzen, korzen);
    }
};

vector<int> znajdzSciezkePoRozpieciu(const Rozpiecie &R) {
    vector<int> sciezka;
    bool koniecWKorzeniu = false;

    SciezkiRozpiecia sciezkiDrzew(R);

    iterate_until(nrDrzewa, 0, R.dlugosc()) {
        vector<int> fragment;
        TypSciezkiPoDrzewie typ = sciezkiDrzew.sciezkaPo(nrDrzewa, &fragment);
        deb(typ);

        if(typ == Z0Do0)
            return vector<int>();

        if(typ == Z1Do1) {
            sciezka.insert(sciezka.end(), ALL(fragment));
            koniecWKorzeniu = true;
        }

        if(!koniecWKorzeniu) {
            if(typ == Z2Do2)
                return vector<int>();

            if(typ == Z1Do2) {
                sciezka.insert(sciezka.end(), ALL(fragment));
                koniecWKorzeniu = false;
            }
        }
        else {
            if(typ == Z2Do2) {
                sciezka.insert(sciezka.end(), ALL(fragment));
                koniecWKorzeniu = false;
            }

            if(typ == Z1Do2) {
                sciezka.insert(sciezka.end(), fragment.rbegin(), fragment.rend());
                koniecWKorzeniu = true;
            }
        }
    }

    if(koniecWKorzeniu)
        return sciezka;
    else
        return vector<int>();
}

void wypisz(const vector<int> &wartosci, int przesuniecie) {
    foreach(int w, wartosci)
    printf("%d\n", w + przesuniecie);
}

int main() {
    Drzewo D(stdin, 1);

    int pierwszyBar = 0,
        ostatniBar = D.rozmiar() - 1;

    Rozpiecie R(D, pierwszyBar, ostatniBar);

    vector<int> sciezka = znajdzSciezkePoRozpieciu(R);

    if(!sciezka.empty())
        wypisz(sciezka, +1);
    else
        puts("BRAK");

    return 0;
}

