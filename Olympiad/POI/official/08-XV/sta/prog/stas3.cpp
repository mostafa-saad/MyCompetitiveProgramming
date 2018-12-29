/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Stacja (STA)                                              *
 *   Plik:     stas3.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie nieoptymalne, o zlozonosci czasowej O(n^3),   *
 *             dla kazdej propozycji polozenia Bitowic i dla kazdej      *
 *             stacji wyznaczamy liczbe wierzcholkow drzewa na sciezce   *
 *             od niej do Bitowic - to sa te wierzcholki, dla ktorych    *
 *             odleglosc od rozwazanej stacji to 1; dla reszty to jest 2.*
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

#define MAX_N 1000000
#define INFTY 100000000

int n;
vector<int> t[MAX_N];
int d[MAX_N], par[MAX_N];
queue<int> kol;

void bfs(int v)
{
  for (int i = 0; i < n; i++)
    d[i] = INFTY;
  d[v] = 0;
  kol = queue<int>();
  kol.push(v);
  while (!kol.empty())
  {
    int w = kol.front();
    kol.pop();
    for (int i = 0; i < (int)t[w].size(); i++)
      if (d[t[w][i]] == INFTY)
      {
        d[t[w][i]] = d[w] + 1;
        par[t[w][i]] = w;
        kol.push(t[w][i]);
      }
  }
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    t[a].push_back(b);
    t[b].push_back(a);
  }
  long long wyn = 1000000000000000000LL, best = -1;
  for (int bit = 0; bit < n; bit++)
  {
    long long akt = (long long)n * (n - 1) / 2LL;
    for (int i = 0; i < n; i++)
    {
      bfs(i);
      akt -= d[bit];
    }
    if (akt < wyn)
    {
      wyn = akt;
      best = bit;
    }
  }
  printf("%lld\n", best + 1);
  return 0;
}
