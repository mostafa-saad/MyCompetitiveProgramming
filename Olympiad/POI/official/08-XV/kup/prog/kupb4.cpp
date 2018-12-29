/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Kupno gruntu (KUP)                                        *
 *   Plik:     kupb4.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie niepoprawne. Poprawnie wyznacza prostokat do  *
 *             wykrawania, ale kroi go nieudacznie.                      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
using namespace std;

const int MAX_N = 2000;

int k, n;
int mapa[MAX_N][MAX_N];

long long sumy[MAX_N][MAX_N];

void licz_sumy()
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      sumy[i][j] = mapa[i][j] + (j > 0 ? sumy[i][j - 1] : 0);
  for (int j = 0; j < n; j++)
    for (int i = 0; i < n; i++)
      sumy[i][j] += (i > 0 ? sumy[i - 1][j] : 0);
}

inline long long suma(int x1, int y1, int x2, int y2)
{
  long long wyn = sumy[x2][y2];
  if (x1 > 0)
    wyn -= sumy[x1 - 1][y2];
  if (y1 > 0)
    wyn -= sumy[x2][y1 - 1];
  if (x1 > 0 && y1 > 0)
    wyn += sumy[x1 - 1][y1 - 1];
  return wyn;
}

/* wdol[i][j] oznacza ile pol w dol od danego mozna isc, nie natrafiwszy
 * na pole o wartosci wiekszej niz 2*k. */
int wdol[MAX_N + 1][MAX_N];

/* wlewo[j] (dla wiersza i-tego) oznacza najwiekszy numer a<j pola mapa[i][a],
 * ktore jest mniejsze od mapa[i][j]. wprawo[j] -- analogicznie, ale w prawo.
 */
int wlewo[MAX_N], wprawo[MAX_N];

inline bool duze(int pole)
{
  return pole > 2 * k;
}

bool dzialka(int &x1, int &y1, int &x2, int &y2)
{
  /* wdol */
  for (int j = 0; j < n; j++)
  {
    wdol[n][j] = 0;
    for (int i = n - 1; i >= 0; i--)
      if (duze(mapa[i][j]))
        wdol[i][j] = 0;
      else
        wdol[i][j] = wdol[i + 1][j] + 1;
  }
  for (int i = 0; i < n; i++)
  {
    /* wlewo */
    wlewo[0] = -1;
    for (int j = 1; j < n; j++)
    {
      int pop = j - 1;
      while (pop >= 0 && wdol[i][pop] >= wdol[i][j])
        pop = wlewo[pop];
      wlewo[j] = pop;
    }
    /* wprawo */
    wprawo[n - 1] = n;
    for (int j = n - 2; j >= 0; j--)
    {
      int nast = j + 1;
      while (nast < n && wdol[i][nast] >= wdol[i][j])
        nast = wprawo[nast];
      wprawo[j] = nast;
    }
    for (int j = 0; j < n; j++)
      if (wdol[i][j] &&
          suma(i, wlewo[j] + 1, i + wdol[i][j] - 1, wprawo[j] - 1) >= (long long)k)
      {
        x1 = i; y1 = wlewo[j] + 1;
        x2 = i + wdol[i][j] - 1; y2 = wprawo[j] - 1;
        return true;
      }
  }
  return false;
}

inline bool siedzi(long long x)
{
  return x >= (long long)k && x <= (long long)(2 * k);
}

/* Przycina przysporawy prostokat, ale tylko cieciami pionowymi
 * lub tylko cieciami poziomymi. */
void tnij(int &x1, int &y1, int &x2, int &y2)
{
  for (int ya = y1; ya < y2; ya++)
    for (int yb = ya + 1; yb <= y2; yb++)
      if (siedzi(suma(x1, ya, x2, yb)))
      {
        y1 = ya; y2 = yb;
        return;
      }
  for (int xa = x1; xa < x2; xa++)
    for (int xb = xa + 1; xb <= x2; xb++)
      if (siedzi(suma(xa, y1, xb, y2)))
      {
        x1 = xa; x2 = xb;
        return;
      }
}

int main()
{
  scanf("%d%d", &k, &n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      scanf("%d", mapa[i] + j);
  int x1, y1, x2, y2;
  licz_sumy();
  if (!dzialka(x1, y1, x2, y2))
  {
    puts("NIE");
    return 0;
  }
  tnij(x1, y1, x2, y2);
  x1++; y1++; x2++; y2++;
  printf("%d %d %d %d\n", y1, x1, y2, x2);
  return 0;
}
