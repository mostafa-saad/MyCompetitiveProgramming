/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wyspa (WYS)                                               *
 *   Plik:     wys2.cpp                                                  *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie alternatywne O(n+m)                           *
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


////////////// program wlasciwy:

double proc_pkt_przec(Punkt a, Punkt b, Punkt c, Punkt d) { // w jakiej czesci odcinka a-b jest punkt przeciecia linii a-b z c-d
    return (a-c)*(d-c)/(double)((a-b)*(d-c)); // (pole trojkata a-c-d)/(pole czworokata a-b-c-d)   [poniewaz * to il_wek ]
}

#define MAX_N 100000
//#define MAX_M 100000

// wszystkie numeracje od 0

Punkt punkty[MAX_N];

vector<int> brakujace[MAX_N]; // krawedzie, ktorych nie ma (czyli te z wejscia)

int ostatni[MAX_N]; // najwiekszy wierzcholek, do ktorego mamy krawedz
    // lub -1 jesli nie zadnego wiekszego niz ostatni dla wczesniejszych wierzcholkow

bool czy_obstawiana[MAX_N]; // tablica tymczasowa: czy krawedz z aktualnego jest blokowana

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
    REP(a, N) {
        FOREACH(it, brakujace[a])
            czy_obstawiana[*it] = true;
        ostatni[a] = -1;
        FORD(b, N-1, max_ost+1)
            if (czy_obstawiana[b])
                czy_obstawiana[b] = false;
            else
                ostatni[a] = max_ost = b; // (czyli konczymy petle, dalej nie trzeba zerowac)
        // wewnetrzna petla zrobi w sumie najwyzej M obrotow
    } 
    
    // szukanie trasy
    // (z zalozenia jakas trasa istnieje)
    double dl = 0;
    Punkt cur_pkt = punkty[0];
    int cur = 0;
    while (ostatni[cur]<N-1) {
        double min_k = 2; // k sa z zakresu od 0 do 1
        int next = 0; // cokolwiek
        // szukamy najwczesniejszej krawedzi, z ktora sie przecinamy
        FOR(a, cur+1, ostatni[cur]) { // bez obecnego, ale z jego drugim koncem
            if (ostatni[a]<0)
                continue;
            double k = proc_pkt_przec(punkty[cur], punkty[ostatni[cur]], punkty[a], punkty[ostatni[a]]);
            if (k<min_k) {
                min_k = k;
                next = a;
            }
        }
        Punkt pkt = punkty[cur]+(punkty[ostatni[cur]]-punkty[cur])*min_k; // nowy punkt przeciecia
        dl += (pkt-cur_pkt).len();
        cur_pkt = pkt;
        cur = next;
    }
    dl += (punkty[N-1]-cur_pkt).len();
    
    printf("%lf\n", dl);
}
