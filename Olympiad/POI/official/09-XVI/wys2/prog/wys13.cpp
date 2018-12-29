/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wyspa (WYS)                                               *
 *   Plik:     wys13.cpp                                                 *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie wzorcowe O(n+m)                               *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <cmath>

using namespace std;

#define REP(a, n) for (int a = 0; a<(n); ++a)
#define FOR(a, b, c) for (int a = (b); a<=(c); ++a)
#define FORD(a, b, c) for (int a = (b); a>=(c); --a)
#define VAR(a, v) __typeof(v) a = (v)
#define FOREACH(a, v) for (VAR(a, (v).begin()); a!=(v).end(); ++a)

#define PB push_back
#define MP make_pair

template<class T>
inline int size(const T &t) { return t.size(); }


/////////////// punkty:

struct Punkt {
    double x, y;
    inline double len() {
        return sqrt(x*x+y*y);
    }
};

inline double operator*(Punkt a, Punkt b) {
    return a.x*b.y-a.y*b.x;
}

inline Punkt operator*(Punkt p, double k) {
    p.x *= k;
    p.y *= k;
    return p;
}

inline Punkt operator+(Punkt a, Punkt b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

inline Punkt operator-(Punkt a, Punkt b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}


Punkt pkt_przec(Punkt a, Punkt b, Punkt c, Punkt d) { // punkt przeciecia linii a-b z c-d
    double k = (a-c)*(d-c)/(double)((a-b)*(d-c)); // (pole trojkata a-c-d)/(pole czworokata a-b-c-d)   [poniewaz * to il_wek ]
    return a+(b-a)*k; // tutaj * to mnozenie przez stala
}

////////////// program wlasciwy:

#define MAX_N 100000
//#define MAX_M 100000

// wszystkie numeracje od 0

Punkt punkty[MAX_N];

vector<int> brakujace[MAX_N]; // krawedzie, ktorych nie ma (czyli te z wejscia)

int ostatni[MAX_N]; // najwiekszy wierzcholek, do ktorego mamy krawedz
    // lub -1 jesli nie zadnego wiekszego niz ostatni dla wczesniejszych wierzcholkow

bool czy_obstawiana[MAX_N]; // tablica tymczasowa: czy krawedz z aktualnego jest blokowana

vector<pair<int, Punkt> > stos; // trasa
  // w parze sa: poczatek krawedzi (koniec jest w ostatni[]), punkt przeciecia z poprzednia (dla pierwszej punkt startowy)

bool czy_na_lewo(Punkt p, int a, int b) {
    return (p-punkty[a])*(punkty[b]-punkty[a])<0;  // * to iloczyn wektorowy
}

int main() {
    // wczytywanie
    int N, M;
    scanf("%d%d", &N, &M);
    REP(a, N)
        scanf("%lf%lf", &punkty[a].x, &punkty[a].y);
    REP(a, M) {
        int i, j;
        scanf("%d%d", &i, &j);
        --i, --j;
        brakujace[i].PB(j);
    }
    
    // znajdowanie krawedzi po ktorych w ogole warto chodzic
    int max_ost = 0;
    int ile_potrz = 0;
    REP(a, N) {
        FOREACH(it, brakujace[a])
            czy_obstawiana[*it] = true;
        ostatni[a] = -1;
        FORD(b, N-1, max_ost+1)
            if (czy_obstawiana[b])
                czy_obstawiana[b] = false;
            else
                ostatni[a] = max_ost = b; // (czyli konczymy petle, dalej nie trzeba zerowac)
        if (ostatni[a]>=0)
            ++ile_potrz;
        // wewnetrzna petla zrobi w sumie najwyzej M obrotow
    } 
    
    // szukanie trasy
    // (z zalozenia jakas trasa istnieje)
    stos.PB(MP(0, punkty[0]));
    FOR(a, 1, N-1) {
        if (ostatni[a]<0) 
            continue;
        for (;;) {
            int ost = stos.back().first;
            Punkt prz = pkt_przec(punkty[ost], punkty[ostatni[ost]], punkty[a], punkty[ostatni[a]]);
//            printf("punkt przeciecia %d z %d to %f %f\n", a, ost, prz.x, prz.y);
            // na pewno proste nie sa rownolegle (z zalozenia)
            if (size(stos)>1) {
                int poprz = stos[size(stos)-2].first; // przedostatni
                if (czy_na_lewo(prz, poprz, ostatni[poprz])) { // ostatnia krawedz na stosie niepotrzebna
                    stos.pop_back();
//                    printf("zdejmuje\n");
                    continue;
                }
            }
            stos.PB(MP(a, prz));
            break;
        }
    }
    
    // liczenie dlugosci trasy
    stos.PB(MP(N-1, punkty[N-1])); // wstawiamy ostatni punkt
    double len = 0;
    REP(a, size(stos)-1) {
        len += (stos[a+1].second-stos[a].second).len();
        //printf("%d %f %f\n", stos[a].first, stos[a].second.x, stos[a].second.y);
    }
    fprintf(stderr, "(Drog potrzebnych %d, dlugosc trasy %d) ", ile_potrz, size(stos)-1);
    printf("%lf\n", len);
}
