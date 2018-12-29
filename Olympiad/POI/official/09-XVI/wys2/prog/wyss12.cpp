/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Wyspa (WYS)                                               *
 *   Plik:     wyss12.cpp                                                *
 *   Autor:    Pawel Parys                                               *
 *   Opis:     Rozwiazanie wolne O(n^4*log n). Znajduje wszystkie punkty *
 *             przeciecia i laczy je krawedziami (kazdy ma max 4 sas.)   * 
 *             a nastepnie szuka najkrotszej sciezki.                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
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

inline double k_przec(Punkt a, Punkt b, Punkt c, Punkt d) { // jak procentowo wypada punkt przeciecia linii a-b z c-d na linii a-b
    return (a-c)*(d-c)/(double)((a-b)*(d-c)); // (pole trojkata a-c-d)/(pole czworokata a-b-c-d)   [poniewaz * to il_wek ]
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
    vector<int> sas;
    double dist;
    Pkt_przec(Punkt p_) : p(p_), dist(INF) {}
};

vector<Pkt_przec> przec;

struct Krawedz {
    int w1, w2;
    vector<pair<double, int> > przec;
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
    
    przec.PB(Pkt_przec(punkty[0]));
    przec.PB(Pkt_przec(punkty[N-1]));
    bool byl0 = false, bylN1 = false;
    REP(b, N)
        REP(a, b)
            if (jest_kraw[a][b]) {
                kraw.PB(Krawedz(a, b));
                if (a==0 && !byl0) { 
                    kraw.back().przec.PB(MP(0., 0));
                    byl0 = true;
                }
                if (b==N-1 && !bylN1) {
                    kraw.back().przec.PB(MP(1., 1));
                    bylN1 = true;
                }
            }
    
    REP(k2, size(kraw))
        REP(k1, k2) {
            // zawsze k2.w2>=k1.w2 z kolejnosci krawedzi
            if (kraw[k2].w1>=kraw[k1].w1 && kraw[k2].w1<=kraw[k1].w2) { // przecinaja sie
                Punkt prz = pkt_przec(punkty[kraw[k1].w1], punkty[kraw[k1].w2], punkty[kraw[k2].w1], punkty[kraw[k2].w2]);
                double prz_na_k1 = k_przec(punkty[kraw[k1].w1], punkty[kraw[k1].w2], punkty[kraw[k2].w1], punkty[kraw[k2].w2]);
                double prz_na_k2 = k_przec(punkty[kraw[k2].w1], punkty[kraw[k2].w2], punkty[kraw[k1].w1], punkty[kraw[k1].w2]);
                kraw[k1].przec.PB(MP(prz_na_k1, size(przec)));
                kraw[k2].przec.PB(MP(prz_na_k2, size(przec)));
                przec.PB(Pkt_przec(prz));
            }
        }
    REP(k, size(kraw)) {
        sort(kraw[k].przec.begin(), kraw[k].przec.end());
        REP(x, size(kraw[k].przec)-1) {
            int p1 = kraw[k].przec[x].second;
            int p2 = kraw[k].przec[x+1].second;
            przec[p1].sas.PB(p2);
            przec[p2].sas.PB(p1);
        }
    }
    kraw.clear(); // juz niepotrzebne
    
    // inicjalizacja
    zmniejsz(0, 0);

    while (!Q.empty()) {
        double dQ = -Q.top().first;
        int pp = Q.top().second;
        Q.pop();
        if (pp==1)
            break;
        if (dQ>przec[pp].dist)
            continue;
        REP(a, size(przec[pp].sas)) {
            int p2 = przec[pp].sas[a];
            double d = przec[pp].dist+dist(przec[pp].p, przec[p2].p);
            zmniejsz(p2, d);
        }
    }

    printf("%lf\n", przec[1].dist);
}
