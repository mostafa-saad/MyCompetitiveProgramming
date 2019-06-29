/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Stacja (STA)                                              *
 *   Plik:     stas2.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie nieoptymalne, o zlozonosci czasowej O(n^4),   *
 *             dla kazdej propozycji polozenia Bitowic i dla kazdej pary *
 *             roznych wierzcholkow wyznacza koszt przejazdu miedzy nimi *
 *             sprawdzajac, czy w drzewie ukorzenionym w Bitowicach      *
 *             jeden z nich jest przodkiem drugiego.                     *
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
    bfs(bit);
    long long akt = 0LL;
    for (int i = 0; i < n; i++)
      for (int j = i + 1; j < n; j++)
      {
        int v = i;
        bool sciezka = false;
        while (v != bit)
        {
          v = par[v];
          if (v == j)
            sciezka = true;
        }
        v = j;
        while (v != bit)
        {
          v = par[v];
          if (v == i)
            sciezka = true;
        }
        if (sciezka)
          akt++;
        else
          akt += 2;
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
