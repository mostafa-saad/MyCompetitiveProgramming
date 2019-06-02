/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ZAB (¯aby)                                     *
 *   Plik:                zab.cpp                                        *
 *   Autor:               Piotr Stañczyk                                 *
 *   Opis:                Rozwi¹zanie wzorcowe.                          *
 *                        Zlozonosc O(wx*wy*log(wx*wy)).                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <set>

using namespace std;

typedef long long LL;

#define FOR(x,b,e) for(int x=b;x<=(e);++x)
#define FORD(x,b,e) for(int x=b;x>=(e);--x)
#define REP(x,n) for(int x=0;x<(n);++x)
#define ST first
#define ND second
const int INF = 2000000;
typedef pair<int,int> PII;
typedef pair<LL,LL> PLL;
#define MP make_pair
inline int sqr(int a) {return a*a;}

const int MAXW = 1002;
const int offset = 10;
const int mask = 1023;
int pole[MAXW][MAXW]; // Tablica uzywana do wyznaczania odleglosci pol od odstraszaczy
int dij[MAXW][MAXW];  // Tablica uzywana do umieszczania wyniku dzialania algorytmu Dijkstry
bool vis[MAXW][MAXW]; // Tablica uzywana przez algorytm Dijkstry do zaznaczania odwiedzonych pol

int buf[MAXW]; // Pomocnicze tablice wykorzystywane przez funkcje Calc
int res[MAXW];
int q[MAXW];

// Funkcja wylicza x'owa wspolrzedna punktu przeciecia funkcji (x+e1)^2 + buf[e1] oraz (x+e2)^2 + buf[w2]
inline PLL DCross(int e1, int e2) {
  if (!e2) return PII(-1, 1);
  return MP(buf[e1] - buf[e2] + LL(e1) * LL(e1) - LL(e2) * LL(e2), 2 * (e1 - e2));
}

inline bool Wieksze(PLL a, PLL b) {
  return a.ST * b.ND > a.ND * b.ST;
}

// Funkcja rozwiazuje jednowymiarowy problem wyznaczania odleglosci od odstraszaczy
void Calc(int l) {
  q[0] = 1;
  FOR(x, 2, l) {
    while(q[0]) {
      PLL c1 = DCross(x, q[0]);
      if (Wieksze(PLL(1, 1), c1) || (q[q[0]] && !Wieksze(c1, DCross(q[0], q[q[0]]))))
        q[0] = q[q[0]];
      else
        break;
    }
    q[x] = q[0];
    q[0] = x;
  }
  int el = q[0];
  PLL ch = DCross(el, q[el]);
  FORD(x, l, 1) {
    while (q[el] && Wieksze(ch, PLL(x, 1))) {
      el = q[el];
      ch = DCross(el, q[el]);
    }
    res[x] = sqr(el - x) + buf[el];
  }
}

int main() {
// Wczytywanie danych
  int w, h, pw, ph, kw, kh, n, ww, wh;
  scanf("%d %d", &w, &h);
  scanf("%d %d %d %d", &pw, &ph, &kw, &kh);
  scanf("%d", &n);
// Odpowiednia inicjalizacja tablic
  REP(x, w+2) REP(y, h+2) {
    pole[x][y] = INF;
    vis[x][y] = (x==0 || x==w+1 || y==0 || y==h+1);
    dij[x][y] = 0;
  }
  REP(x, n) {
    scanf("%d %d", &ww, &wh);
    pole[ww][wh] = 0;
  }
// Wyznaczenie odleglosci od odstraszaczy w jednym wymiarze
  FOR(x, 1, w) {
    FOR(y, 1, h) buf[y] = pole[x][y];
    Calc(h);
    FOR(y, 1, h) pole[x][y] = res[y];
  }
// Wyznaczenie odleglosci od odstraszaczy w drugim wymiarze (wykorzystujac dane z pierwszej fazy)
  FOR(y, 1, h) {
    FOR(x, 1, w) buf[x] = pole[x][y];
    Calc(w);
    FOR(x, 1, w) pole[x][y] = res[x];
  }
// Wykorzystanie algorytmu Dijkstry do wyznaczenia drogi zaby
  set<PII> que;
  que.insert(MP(-(dij[pw][ph] = pole[pw][ph]), (pw<<offset) + ph));
  vis[pw][ph] = true;

#define Odw(px, py) \
  if (!vis[px][py] && dij[px][py] < min(pole[px][py], -t.ST)) { \
    que.erase(MP(-dij[px][py], ((px) << offset) + py)); \
    que.insert(PII(-(dij[px][py] = min(pole[px][py], -t.ST)), ((px) << offset) + py)); \
  }

  while(!que.empty()) {
    PII t = *(que.begin());
    que.erase(t);
    int zx = t.ND >> offset;
    int zy = (t.ND & mask);
    vis[zx][zy] = true;
    Odw(zx, zy + 1);
    Odw(zx, zy - 1);
    Odw(zx + 1, zy);
    Odw(zx - 1, zy);
  }
  printf("%d\n", dij[kw][kh]);
  return 0;
}
