/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Skalniak (SKA)                                             *}
{*   Plik:    skab3.cpp                                                  *}
{*   Autor:   Jakub Radoszewski, Marek Cygan                             *}
{*   Opis:    Rozwiazanie bledne. W rozwiazaniu nie rozwazamy jednego    *}
{*            z 4 przypadkow postaci plotu.                              *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX_N 1000000
#define MIN_XY 0
#define MAX_XY 1000000000
#define MAX_W 2000

int n;
int x[MAX_N], y[MAX_N], m[MAX_N];
bool przestaw[MAX_N];

void odczyt()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d%d%d", x + i, y + i, m + i);
}

inline bool miesci_sie(int x, int dol, int gora)
{
  return x >= dol && x <= gora;
}

/* Funkcja próbuje zach³annie ustawiaæ punkty tak, by zmie¶ci³y
 * siê w prostok±cie [amin,amax] x [bmin,bmax]. */
int licz(int amin, int amax, int bmin, int bmax)
{
  int wyn = 0;
  for (int i = 0; i < n; i++)
  {
    if (miesci_sie(x[i], amin, amax) && miesci_sie(y[i], bmin, bmax))
    {
      przestaw[i] = false;
      continue;
    }
    if (miesci_sie(y[i], amin, amax) && miesci_sie(x[i], bmin, bmax))
    {
      przestaw[i] = true;
      wyn += m[i];
      continue;
    }
    return MAX_W * MAX_N + 1; /* nie da siê tego ustawienia uzyskaæ */
  }
  return wyn;
}

int main()
{
  odczyt();
  /* Wyznaczamy jakiekolwiek rozwi±zanie */
  int xmin = MAX_XY, xmax = MIN_XY, ymin = MAX_XY, ymax = MIN_XY;
  for (int i = 0; i < n; i++)
  {
    int a = x[i], b = y[i];
    if (a > b)
      swap(a, b);
    xmin = min(xmin, a); xmax = max(xmax, a);
    ymin = min(ymin, b); ymax = max(ymax, b);
  }
  /* Szukamy najlepszego rozwi±zania - rozwa¿amy 3 przypadki (powinny byc 4)*/
  int wyn = licz(xmin, xmax, ymin, ymax), ktore = 0, tmp;
  if ((tmp = licz(xmin, ymax, ymin, xmax)) < wyn)
  {
    ktore = 2; wyn = tmp;
  }
  if ((tmp = licz(ymin, xmax, xmin, ymax)) < wyn)
  {
    ktore = 3; wyn = tmp;
  }
  switch (ktore)
  {
    case 0: licz(xmin, xmax, ymin, ymax); break;
    case 2: licz(xmin, ymax, ymin, xmax); break;
    case 3: licz(ymin, xmax, xmin, ymax); break;
  }
  printf("%u %d\n", 2 * (xmax - xmin + ymax - ymin), wyn);
  for (int i = 0; i < n; i++)
    printf("%d", przestaw[i]);
  printf("\n");
  return 0;
}
