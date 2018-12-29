/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wyspa (WYS)                                               *
 *   Plik:     wyss11.cpp                                                *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie wolne O(n^6*log n). Znajduje wszystkie punkty *
 *             przeciecia i laczy krawedziami pary lezace na tej samej   * 
 *             drodze a nastepnie szuka najkrotszej sciezki.             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <queue>
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

#define INF 1000000000


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


inline Punkt pkt_przec(Punkt a, Punkt b, Punkt c, Punkt d) { // punkt przeciecia linii a-b z c-d
    double k = (a-c)*(d-c)/(double)((a-b)*(d-c)); // (pole trojkata a-c-d)/(pole czworokata a-b-c-d)   [poniewaz * to il_wek ]
    return a+(b-a)*k; // tutaj * to mnozenie przez stala
}

inline double dist(Punkt a, Punkt b) {
    return (a-b).len();
}

////////////// program wlasciwy:

#define MAX_N 100000

// wszystkie numeracje od 0

Punkt punkty[MAX_N];

vector<vector<bool> > jest_kraw; // czy krawedz bezpieczna

struct Pkt_przec {
    Punkt p;
    int k1, k2;
    double dist;
    Pkt_przec(Punkt p_, int k1_, int k2_) : p(p_), k1(k1_), k2(k2_), dist(INF) {}
};

vector<Pkt_przec> przec;

struct Krawedz {
    int w1, w2;
    vector<int> przec;
    Krawedz(int w1_, int w2_) : w1(w1_), w2(w2_) {}
};

vector<Krawedz> kraw;

priority_queue<pair<double, int> > Q;

void zmniejsz(int p, double newd) {
    if (newd<przec[p].dist) {
        przec[p].dist = newd;
        Q.push(MP(-newd, p));
    }
}


/////////////

void zbadaj(int pp, int kr) {
    if (kr<0)
        return;
    REP(a, size(kraw[kr].przec)) {
        int p2 = kraw[kr].przec[a];
        double d = przec[pp].dist+dist(przec[pp].p, przec[p2].p);
        zmniejsz(p2, d);
    }
}


int main() {
    // wczytywanie
    int N, M;
    scanf("%d%d", &N, &M);
    jest_kraw.resize(N, vector<bool>(N, true));
    REP(a, N)
        scanf("%lf%lf", &punkty[a].x, &punkty[a].y);
    REP(a, M) {
        int i, j;
        scanf("%d%d", &i, &j);
        --i, --j;
        jest_kraw[i][j] = false;
    }
    
    przec.PB(Pkt_przec(punkty[0], -1, -1));
    przec.PB(Pkt_przec(punkty[N-1], -1, -1));
    REP(b, N)
        REP(a, b)
            if (jest_kraw[a][b]) {
                kraw.PB(Krawedz(a, b));
                if (a==0 && przec[0].k2<0) { 
                    kraw.back().przec.PB(0);
                    przec[0].k2 = size(kraw)-1;
                }
                if (b==N-1 && przec[1].k2<0) {
                    kraw.back().przec.PB(1);
                    przec[1].k2 = size(kraw)-1;
                }
            }
    
    REP(k2, size(kraw))
        REP(k1, k2) {
            // k2.w2>=k1.w2 z kolejnosci krawedzi
            if (kraw[k2].w1>=kraw[k1].w1 && kraw[k2].w1<=kraw[k1].w2) { // przecinaja sie
                Punkt prz = pkt_przec(punkty[kraw[k1].w1], punkty[kraw[k1].w2], punkty[kraw[k2].w1], punkty[kraw[k2].w2]);
                kraw[k1].przec.PB(size(przec));
                kraw[k2].przec.PB(size(przec));
                przec.PB(Pkt_przec(prz, k1, k2));
            }
        }
    
    // inicjalizacja
    zmniejsz(0, 0);

    while (!Q.empty()) {
        double dist = -Q.top().first;
        int pp = Q.top().second;
        Q.pop();
        if (pp==1)
            break;
        if (dist>przec[pp].dist)
            continue;
        zbadaj(pp, przec[pp].k1);
        zbadaj(pp, przec[pp].k2);
    }

    printf("%lf\n", przec[1].dist);
}
