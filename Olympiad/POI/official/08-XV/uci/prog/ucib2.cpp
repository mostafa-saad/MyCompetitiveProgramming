/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Ucieczka (UCI)                                            *
 *   Plik:     ucib2.cpp                                                 *
 *   Autor:    Filip Wolski                                              *
 *   Opis:     Rozwiazanie niepoprawne.                                  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <algorithm>

#define MXN 40

using namespace std;

int n, m, x, y, mod;
bool police[MXN][MXN];
char cg[MXN+1];

int step[4][2] = { {-1,0}, {0,1}, {1,0}, {0,-1} };
int memoize[4][MXN][MXN][MXN][MXN];

inline int compute(int dir, int l0, int l1, int l2, int l3)
{
  if (memoize[dir][l0][l1][l2][l3])
    return memoize[dir][l0][l1][l2][l3]-1;
  int cura = y-1 + step[(dir+3)%4][0] * l0;
  int curb = x-1 + step[(dir+3)%4][1] * l0;
  int mva = step[dir][0];
  int mvb = step[dir][1];
  bool clear = true;

  for (int a = 0; a < l3; a++ )
  {
    cura -= mva;
    curb -= mvb;
    clear &= !police[cura][curb];
  }

  if (!clear)
  {
    memoize[dir][l0][l1][l2][l3] = 1;
    return 0;
  }
  if (l0 == 0)
  {
    memoize[dir][l0][l1][l2][l3] = 2;
    return 1;
  }

  int ret = 0;
  cura = y-1 + step[(dir+3)%4][0] * l0;
  curb = x-1 + step[(dir+3)%4][1] * l0;
  for (int a = 0; a <= l1 && (clear &= !police[cura][curb]); a++ )
  {
    ret = (ret + compute((dir+1)%4, a, l2, l3, l0-1)) % mod;
    cura += mva;
    curb += mvb;
  }
  memoize[dir][l0][l1][l2][l3] = ret+1;
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
  printf("%i\n", compute(0, x-1, y-1, m-x, n-y));
  return 0;
}
