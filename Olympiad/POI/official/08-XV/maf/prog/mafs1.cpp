/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Mafia (MAF)                                               *
 *   Plik:     mafs1.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie wolne. Dla kazdej slabo spojnej skladowej     *
 *             probujemy wszystkie permutacje jej wierzcholkow jako      *
 *             kolejnosc strzelania i... strzelamy.                      *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 1000000

int s[MAX_N], n, nr;
int col[MAX_N];
vector<int> skl[MAX_N + 1];

void szukaj_skl()
{
  vector<int> pom;
  for (int i = 0; i < n; i++)
  {
    if (!col[i])
    {
      pom.clear();
      nr++;
      int v = i;
      while (!col[v])
      {
        pom.push_back(v);
        col[v] = nr;
        v = s[v];
      }
      if (col[v] != nr)
        for (int j = 0; j < (int)pom.size(); j++)
          col[pom[j]] = col[v];
    }
    skl[col[i]].push_back(i);
  }
}

int min_ofiar, max_ofiar;
int zyje[MAX_N];

/* Analizuje x-ta skladowa. */
void analizuj(int x)
{
  int w_min = n, w_max = 0, l = skl[x].size();
  sort(skl[x].begin(), skl[x].end());
  do
  {
    /* Strzelamy w kolejnosci skl[x] */
    for (int i = 0; i < l; i++)
      zyje[skl[x][i]] = 1;
    for (int i = 0; i < l; i++)
      if (zyje[skl[x][i]])
        zyje[s[skl[x][i]]] = 0;
    int akt = 0;
    for (int i = 0; i < l; i++)
      if (!zyje[skl[x][i]])
        akt++;
    w_min = min(w_min, akt);
    w_max = max(w_max, akt);
  } while (next_permutation(skl[x].begin(), skl[x].end()));
  min_ofiar += w_min; max_ofiar += w_max;
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    scanf("%d", s + i);
    s[i]--;
  }
  szukaj_skl();
  for (int i = 1; i <= nr; i++)
    analizuj(i);
  printf("%d %d\n", min_ofiar, max_ofiar);
  return 0;
}
