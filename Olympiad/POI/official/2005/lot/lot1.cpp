/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: LOT (Lot na Marsa)                             *
 *   Plik:                lot1.cpp                                       *
 *   Autor:               Marek Cygan                                    *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                        Algorytm o zlozonosci czasowej O(n)            *
 *                        i pamieciowej O(n). Wkorzystujacy kolejke do   *
 *                        znajdowania minimow                            *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <deque>
#include <utility>
using namespace std;

typedef pair < int, int >PII;

#define ALL(x) x.begin(),x.end()
#define REP(i,n) for (int i=0; i<n; ++i)
#define PB push_back
#define MP(a,b) make_pair(a,b)
#define ST first
#define ND second

const int N = 1000000;
bool czy[N];
int n, fuel[N], dist[N];
deque < PII > miny;

void licz(int krok, int skad)
{
  miny.clear();
  int acc = 0, pos = 0;
  REP(i, n) {
    acc += fuel[pos];
    acc -= dist[(pos + skad) % n];
    while (!miny.empty() && miny.back().ST >= acc)
      miny.pop_back();
    miny.PB(MP(acc, pos));
    pos += krok;
    pos %= n;
  }
  int glob = 0;
  int calk = acc;
  if (calk < 0)
    return;                     //za malo paliwa zeby przejechac cale kolko
  pos = 0;
  REP(i, n) {
    if (miny.front().ST - glob >= 0)
      czy[pos] = true;
    int foo = fuel[pos] - dist[(pos + skad) % n];
    glob += foo;
    if (miny.front().ND == pos)
      miny.pop_front();
    int ile = calk + glob;
    while (!miny.empty() && miny.back().ST >= ile)
      miny.pop_back();
    miny.PB(MP(ile, pos));
    pos = (pos + krok) % n;
  }
}

int main()
{
  scanf("%d", &n);
  REP(i, n) scanf("%d %d", &fuel[i], &dist[i]);
  licz(1, 0);
  licz(n - 1, n - 1);
  REP(i, n) printf("%s\n", czy[i] ? "TAK" : "NIE");
  return 0;
}
