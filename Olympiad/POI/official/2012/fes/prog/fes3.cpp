/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Festyn                                           *
 *   Autor:             Pawel Parys                                      *
 *   Zlozonosc czasowa: O(n^3)                                           *
 *   Opis:              Rozwiazanie weryfikujace                         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>
#include <vector>

#define REP(a,n) for (int a = 0; a<(n); ++a)
#define INIT(v,a) __typeof(a) v = (a)
#define FOREACH(i,v) for (INIT(i, (v).begin()); i!=(v).end(); ++i)

#define PB push_back

#define INF 1000000000

using namespace std;

typedef vector<int> vi;

///////////////////////////////

int N;
int prz[600][600]; // pol[y]<=pol[x]+prz[x][y]
bool ok[600];

int main() {
  int m1, m2;
  scanf("%d%d%d", &N, &m1, &m2);
  REP(a, N) {
    REP(b, N)
      prz[a][b] = INF;
    prz[a][a] = 0;
  }
  REP(a, m1+m2) {
    int x, y;
    scanf("%d%d", &x, &y);
    --x; --y;
    if (a<m1) { 
      prz[x][y] = min(prz[x][y], 1);
      prz[y][x] = min(prz[y][x], -1);
    }
    else
      prz[y][x] = min(prz[y][x], 0);
  }
  REP(k, N)
    REP(i, N)
      REP(j, N)
          prz[i][j] = min(prz[i][j], prz[i][k]+prz[k][j]);
  REP(a, N)
    if (prz[a][a]<0) {
      printf("NIE\n");
      return 0;
    }
  int wyn = 0;
  REP(a, N)
    if (!ok[a]) {
      vi skl;
      REP(b, N)
        if (prz[a][b]<INF/2 && prz[b][a]<INF/2) {
          ok[b] = 1;
          skl.PB(b);
        }
      int md = 0;
      FOREACH(i, skl)
        FOREACH(j, skl)
          md = max(md, prz[*i][*j]);
      wyn += md+1;
    }
  printf("%d\n", wyn);
}
