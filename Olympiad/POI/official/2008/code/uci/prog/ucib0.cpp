/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Ucieczka (UCI)                                            *
 *   Plik:     ucib0.cpp                                                 *
 *   Autor:    Filip Wolski                                              *
 *   Opis:     Rozwiazanie niepoprawne.                                  *
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
int memoize[MXN][MXN][4];
int vis[MXN][MXN][4];

inline int compute(int a, int b, int dir)
{
  if (a+1 == y && b+1 == x)
    return 1;
  if (vis[a][b][dir])
    return memoize[a][b][dir];
  vis[a][b][dir] = 1;
  int res = 0;
  for (int cnt = 0; cnt < 2; cnt++ )
  {
    int aa = a + step[(dir+cnt)%4][0];
    int bb = b + step[(dir+cnt)%4][1];
    if (0 <= aa && aa < n && 0 <= bb && bb < m && !police[aa][bb])
      res = (res + compute(aa,bb,(dir+cnt)%4)) % mod;
  }
  memoize[a][b][dir] = res;
  vis[a][b][dir] = 2;
  return res;
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
  printf("%i\n", compute(n-1, 0, 0));
  return 0;
}
