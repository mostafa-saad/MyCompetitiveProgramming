/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Ucieczka (UCI)                                            *
 *   Plik:     ucis3.cpp                                                 *
 *   Autor:    Filip Wolski                                              *
 *   Opis:     Rozwiazanie nieoptymalne.                                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>

#define MXN 100

using namespace std;

int step[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };
bool police[MXN][MXN];
int n, m, mod, x, y;

int count(int a, int b, int dir)
{
  if (a+1 == y && b+1 == x)
    return 1;
  int res = 0;
  police[a][b] = true;
  for (int cnt = 0; cnt < 2; cnt++ )
  {
    int aa = a + step[dir][0];
    int bb = b + step[dir][1];
    if (0 <= aa && aa < n && 0 <= bb && bb < m && !police[aa][bb])
      res = (res + count(aa,bb,dir)) % mod;
    dir = (dir+1)%4;
  }
  police[a][b] = false;
  return res;
}

char cg[MXN+1];

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
  printf("%i\n", count(n-1,0,0));
  return 0;
}
