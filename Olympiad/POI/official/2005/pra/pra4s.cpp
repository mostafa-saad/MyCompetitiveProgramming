/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PRA (Prawoskrêtny wielb³ad)                    *
 *   Plik:                pra4s.cpp                                      *
 *   Autor:               Piotr Stañczyk                                 *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                        Z³o¿onosæ czasowa: O(n^3)                      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
#define DET(a, b, c) ((b.x - a.x)*(c.y - a.y) - (b.y - a.y)*(c.x - a.x))
#define N 1000
#define PB push_back
#define INF 2000000000
#define FOR(a,b,c) for(int a = b; a < c; a++)
#define FORD(a,b,c) for(int a = b; a >= c; a--)

using namespace std;

struct point {
  int x, y;
};
vector < point > l;
vector < point > tmpl;
int res[N][N];
bool przec[N][N];

int sgn(int a)
{
  if (a == 0)
    return 0;
  return (a > 0) ? 1 : -1;
}

bool cmp(const point & a, const point & b)
{
  return DET(l[0], a, b) < 0;
}

int main()
{
  int n;
  point p;
  scanf("%d", &n);
  FOR(x, 0, n) FOR(y, 0, n)
      res[x][y] = -INF;

  FOR(x, 0, n) {
    scanf("%d %d", &p.x, &p.y);
    if (l.size() < 2 || DET(l[0], l[1], p) < 0)
      l.PB(p);
    else
      tmpl.PB(p);
  }
  sort(&l[2], &l[l.size()], cmp);
  sort(tmpl.begin(), tmpl.end(), cmp);

  FORD(x, l.size() - 1, 2) FORD(y, tmpl.size() - 1, 0)
      if (DET(l[x], tmpl[y], l[0]) > 0)
    przec[x][l.size() + y] = przec[l.size() + y][x] = true;
  FOR(x, 0, tmpl.size())l.PB(tmpl[x]);
  res[1][0] = 1;
  FOR(x, 1, n) FOR(y, x + 1, n) if (!przec[x][y])
    FORD(z, x - 1, 0)
        if (DET(l[y], l[x], l[z]) > 0)
      res[y][x] = max(res[y][x], res[x][z] + 1);

  int wynik = 0;
  FOR(x, 0, n) FOR(y, 0, n)
      wynik = max(wynik, res[x][y]);
  printf("%d\n", wynik);
  return 0;
}
