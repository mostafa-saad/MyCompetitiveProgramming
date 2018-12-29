/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Ucieczka (UCI)                                            *
 *   Plik:     uci.cpp                                                   *
 *   Autor:    Filip Wolski                                              *
 *   Opis:     Rozwiazanie wzorcowe.                                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <algorithm>

#define MXN 100

using namespace std;

int n, m, x, y, mod;
bool police[MXN][MXN];
char cg[MXN+1];

int step[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };
int res[4][MXN][MXN][MXN][2];
bool clear[4][MXN][MXN][MXN];

int dir, l0, l1, l2, l3, sz;

inline int compute()
{
  int cura = y-1 + step[(dir+3)%4][0] * l0;
  int curb = x-1 + step[(dir+3)%4][1] * l0;
  int mva = step[dir][0];
  int mvb = step[dir][1];
  clear[dir][l0][l1][l3] = (!police[cura + mva * l1][curb + mvb * l1]) && (!police[cura - mva * l3][curb - mvb * l3]);
  if (l1)
    clear[dir][l0][l1][l3] &= clear[dir][l0][l1-1][l3];
  if (l3)
    clear[dir][l0][l1][l3] &= clear[dir][l0][l1][l3-1];
  if (!clear[dir][l0][0][l3])
    return 0;
  if (l0 == 0)
    return 1;
  int ret = 0;
  if (l1)
    ret += res[dir][l0][l1-1][l2][(sz-1)%2];
  if (clear[dir][l0][l1][l3])
    ret += res[(dir+1)%4][l1][l2][l3][(sz-1)%2];
  return ret;
}

int main()
{
  scanf("%i%i%i", &n, &m, &mod);
  scanf("%i%i", &x, &y);
  for (int a = 0; a < n; a++ )
  {
    scanf("%s", cg);
    for (int b = 0; b < m; b++ )
      police[a][b] = cg[b] == '*';
  }
  for (sz = 2; sz <= n+m; sz++ )
    for (int szn = max(1,sz-m); szn <= n && szn < sz; szn++ )
      for (int a = 0; a + szn <= n; a++ )
        for (int b = 0; b + sz-szn <= m; b++ )
        {
          l0 = x-1 - b;
          l1 = y-1 - a;
          l2 = b+sz-szn - x;
          l3 = a+szn - y;
          if (l0 < 0 || l1 < 0 || l2 < 0 || l3 < 0)
            continue;
          for (dir = 0; dir < 4; dir++ )
          {
            res[dir][l0][l1][l2][sz%2] = compute() % mod;
            int tmp = l0; l0 = l1; l1 = l2; l2 = l3; l3 = tmp;
          }
        }
  printf("%i\n", res[0][x-1][y-1][m-x][(n+m)%2]);
  return 0;
}

