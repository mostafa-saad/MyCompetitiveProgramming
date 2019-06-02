/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wyspa (WYS)                                               *
 *   Plik:     wyss12.cpp                                                *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie wzorcowe O(n+m)                               *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <math.h>

/////////////// punkty:

struct Punkt {
    double x, y;
};

inline double len(struct Punkt p) {
  return sqrt(p.x*p.x+p.y*p.y);
}

inline double il_wek(struct Punkt a, struct Punkt b) {
    return a.x*b.y-a.y*b.x;
}

inline struct Punkt razy_stala(struct Punkt p, double k) {
    p.x *= k;
    p.y *= k;
    return p;
}

inline struct Punkt dodaj(struct Punkt a, struct Punkt b) {
    a.x += b.x;
    a.y += b.y;
    return a;
}

inline struct Punkt odejmij(struct Punkt a, struct Punkt b) {
    a.x -= b.x;
    a.y -= b.y;
    return a;
}


struct Punkt pkt_przec(struct Punkt a, struct Punkt b, struct Punkt c, struct Punkt d) { // punkt przeciecia linii a-b z c-d
    double p1 = il_wek(odejmij(a, c), odejmij(d, c)); // pole trojkata a-c-d
    double p2 = il_wek(odejmij(a, b), odejmij(d, c)); // pole czworokata a-b-c-d
    double k = p1/p2;
    return dodaj(a, razy_stala(odejmij(b, a), k)); // a-(b-a)*k
}

////////////// program wlasciwy:

#define MAX_N 60000
#define MAX_M 1000000

// wszystkie numeracje od 0

struct Punkt punkty[MAX_N];

// krawedzie, ktorych nie ma (czyli te z wejscia)
int brakujace_tab[MAX_M]; // dokad krawedz
int brakujace_next[MAX_M]; // wskaznik na nastepna krawedz z tego wierzcholka (lub -1)
int brakujace_first[MAX_N]; // wskaznik na pierwsza krawedz z tego wierzcholka (lub -1)

int ostatni[MAX_N]; // najwiekszy wierzcholek, do ktorego mamy krawedz
    // lub -1 jesli nie zadnego wiekszego niz ostatni dla wczesniejszych wierzcholkow

int czy_obstawiana[MAX_N]; // tablica tymczasowa: czy krawedz z aktualnego jest blokowana

// trasa
int ile_stos = 0;
int stos_nr[MAX_N];  // poczatek krawedzi (koniec jest w ostatni[])
struct Punkt stos_prz[MAX_N]; // punkt przeciecia z poprzednia (dla pierwszej punkt startowy)

int czy_na_lewo(struct Punkt p, int a, int b) {
    return il_wek(odejmij(p, punkty[a]), odejmij(punkty[b], punkty[a]))<0;
}

int main() {
    // wczytywanie
    int N, M;
    int a, b, i, j;
    scanf("%d%d", &N, &M);
    for (a = 0; a<N; ++a) {
        scanf("%lf%lf", &punkty[a].x, &punkty[a].y);
        brakujace_first[a] = -1;
    }
    for (a = 0; a<M; ++a) {
        scanf("%d%d", &i, &j);
        --i, --j;
        brakujace_tab[a] = j;
        brakujace_next[a] = brakujace_first[i];
        brakujace_first[i] = a;
    }
    
    // znajdowanie krawedzi po ktorych w ogole warto chodzic
    int max_ost = 0;
    for (a = 0; a<N; ++a) {
        for (i = brakujace_first[a]; i>=0; i = brakujace_next[i])
            czy_obstawiana[brakujace_tab[i]] = 1;
        ostatni[a] = -1;
        for (b = N-1; b>max_ost; --b)
            if (czy_obstawiana[b])
                czy_obstawiana[b] = 0;
            else
                ostatni[a] = max_ost = b; // (czyli konczymy petle, dalej nie trzeba zerowac)
        // wewnetrzna petla zrobi w sumie najwyzej M obrotow
    } 
    
    // szukanie trasy
    // (z zalozenia jakas trasa istnieje)
    stos_nr[0] = 0;
    stos_prz[0] = punkty[0];
    ile_stos = 1;
    for (a = 1; a<N; ++a) {
        if (ostatni[a]<0) 
            continue;
        for (;;) {
            int ost = stos_nr[ile_stos-1];
            struct Punkt prz = pkt_przec(punkty[ost], punkty[ostatni[ost]], punkty[a], punkty[ostatni[a]]);
//            printf("punkt przeciecia %d z %d to %f %f\n", a, ost, prz.x, prz.y);
            // na pewno proste nie sa rownolegle (z zalozenia)
            if (ile_stos>1) {
                int poprz = stos_nr[ile_stos-2]; // przedostatni
                if (czy_na_lewo(prz, poprz, ostatni[poprz])) { // ostatnia krawedz na stosie niepotrzebna
                    --ile_stos;
//                    printf("zdejmuje\n");
                    continue;
                }
            }
            stos_nr[ile_stos] = a;
            stos_prz[ile_stos] = prz;
            ++ile_stos;
            break;
        }
    }
    
    // liczenie dlugosci trasy
    stos_prz[ile_stos] = punkty[N-1]; // wstawiamy ostatni punkt
    double dl = 0;
    for (a = 0; a<ile_stos; ++a) {
        dl += len(odejmij(stos_prz[a+1], stos_prz[a]));
//        printf("%d %f %f\n", stos[a].first, stos[a].second.x, stos[a].second.y);
    }
    
    printf("%lf\n", dl);
    return 0;
}
