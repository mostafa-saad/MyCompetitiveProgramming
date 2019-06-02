/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Konduktor (KON)                                           *
 *   Plik:     kon10.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie wzorcowe O(n^2*k)                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 600

int n, k;
int x[MAX_N][MAX_N];

void odczyt()
{
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
      scanf("%d", x[i] + j);
}

/* t[i][j] to najwiekszy mozliwy wynik, jezeli ostatnia kontrola odbyla sie
 * tuz za stacja o numerze i oraz bylo juz lacznie j kontroli.
 * pop[i][j] sluzy do odzyskiwania wyniku -- jest to miejsce poprzedniej
 * kontroli w planie wyznaczonym przez t[i][j].
 */
int t[MAX_N][MAX_N];
int pop[MAX_N][MAX_N];

int main()
{
  odczyt();

  /* Sumy czesciowe */
  for (int i = 0; i < n; i++)
    for (int j = n - 2; j >= 0; j--)
      x[i][j] += x[i][j + 1];

  /* Dynamik */
  for (int i = 0; i < n - 1; i++)
    for (int j = 1; j <= k; j++)
    {
      t[i][j] = 0;
      int suma = 0;
      for (int p = i - 1; p >= 0; p--)
      {
        suma += x[p + 1][i + 1];
        if (t[p][j - 1] + suma > t[i][j])
        {
          t[i][j] = t[p][j - 1] + suma;
          pop[i][j] = p;
        }
      }
      if (j == 1)
      {
        suma += x[0][i + 1];
        t[i][j] = max(t[i][j], suma);
        pop[i][j] = -1; /* cokolwiek */
      }
    }

  /* Znajdowanie najlepszego wyniku */
  int wyn = 0;
  int maxi = -1, maxj = k;
  for (int i = 0; i < n - 1; i++)
    if (t[i][k] > wyn)
    {
      wyn = t[i][k];
      maxi = i;
    }

  /* Odtwarzanie wyniku */
  vector<int> w;
  while (maxj > 0)
  {
    w.push_back(maxi + 1);
    maxi = pop[maxi][maxj];
    maxj--;
  }
  reverse(w.begin(), w.end());
  for (int i = 0; i < (int)w.size(); i++)
  {
    printf("%d", w[i]);
    if (i < (int)w.size() - 1)
      putchar(' ');
    else
      puts("");
  }
  return 0;
}
