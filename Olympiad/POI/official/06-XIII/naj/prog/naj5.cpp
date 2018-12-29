/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: NAJ (Najazd)                                   *
 *   Plik:                naj5.c                                         *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie wzorcowe O(nm log n + n^3)         *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <utility>
using namespace std;

#define MAX_N 600

typedef pair<int, int> pkt;

int t[MAX_N][MAX_N]; /* tablica t */
pkt w[MAX_N]; /* wyspa-wielok±t */
int n, m;
int suma = 0; /* suma wszystkich zysków */


/* Iloczyn wektorowy */
inline int wekt(pkt p0, pkt p1, pkt p2)
{
  return (p1.first - p0.first) * (p2.second - p0.second)-
    (p2.first - p0.first) * (p1.second - p0.second);
}

/* Czy przechodz±c przez wspólny koniec odcinków p0p1 i p1p2 skrêcamy
 * w lewo (skret<0), prawo (skret>0) czy idziemy prosto (skret=0). */
inline int skret(pkt p0, pkt p1, pkt p2)
{
  return wekt(p0, p2, p1);
}

void odczyt()
{
  /* Prawie ca³y odczyt */
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d%d", &(w[i].first), &(w[i].second));
  scanf("%d", &m);
}

void zeruj()
{
  /* Zerujemy tablicê t */
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      t[i][j] = 0;
}

void analizuj_fabryki()
{
  /* Analizujemy wszystkie fabryki */
  for (int i = 0; i < m; i++)
  {
    /* rozwa¿amy i-t± fabrykê */
    int x, y, zysk;
    scanf("%d%d%d", &x, &y, &zysk);
    pkt p = make_pair(x, y);
    suma += zysk;
    for (int v = 0; v < n; v++)
    {
      /* rozwa¿amy wierzcho³ek wyspy v */
      if (p == w[v])
        continue;
      int a = v + 1, b = v + n - 1;
      /* wyszukujemy binarnie dobry wierzcho³ek koñcowy krawêdzi */
      while (a < b)
      {
        int c = (a + b) / 2;
        if (skret(w[v], w[c % n], p) >= 0) /* skrêcamy w prawo lub prosto */
          a = c + 1;
        else
          b = c;
      }
      /* i powiêkszamy sumê w pewnej pó³p³aszczy¼nie */
      if (skret(w[v], w[a % n], p))
        t[v][a % n] += zysk;
    }
  }
  
  /* Wyliczamy sumy czê¶ciowe */
  for (int v = 0; v < n; v++)
    for (int i = 2; i < n; i++)
      t[v][(v + i) % n] += t[v][(v + i - 1) % n];
}

void licz_wynik()
{
  /* Wyliczamy ostateczny wynik */
  int wyn = -2000000000;
  for (int i = 0; i < n - 2; i++)
    for (int j = i + 1; j < n - 1; j++)
      for (int k = j + 1; k < n; k++)
      {
        int tmp = suma - t[i][j] - t[j][k] - t[k][i];
        if (tmp > wyn)
          wyn = tmp;
      }
  printf("%d\n", wyn);
}

int main()
{
  odczyt();
  zeruj();
  analizuj_fabryki();
  licz_wynik();
  return 0;
}
