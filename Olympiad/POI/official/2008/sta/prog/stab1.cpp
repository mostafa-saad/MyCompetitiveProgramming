/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Stacja (STA)                                              *
 *   Plik:     stab1.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie bledne, zaczyna z kilku losowych wierzcholkow *
 *             i przemieszcza sie z nich w kierunku lisci tak, zeby      *
 *             isc zawsze ku poddrzewu o mniejszej liczbie wierzcholkow. *
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
int d[MAX_N];
vector<int> kol;
int deg[MAX_N];

void bfs(int v)
{
  for (int i = 0; i < n; i++)
    d[i] = INFTY;
  d[v] = 0;
  kol.clear();
  kol.reserve(n);
  kol.push_back(v);
  for (int j = 0; j < (int)kol.size(); j++)
  {
    int w = kol[j];
    for (int i = 0; i < deg[w]; i++)
      if (d[t[w][i]] == INFTY)
      {
        d[t[w][i]] = d[w] + 1;
        kol.push_back(t[w][i]);
      }
  }
}

int losowy()
{
  return (int)((double)n * (rand() / (RAND_MAX + 1.0)));
}

int wierzch[MAX_N];
int par[MAX_N];

void dfs(int v)
{
  wierzch[v] = 1;
  int w;
  for (int i = 0; i < deg[v]; i++)
  {
    w = t[v][i];
    if (!wierzch[w])
    {
      dfs(w);
      par[w] = v;
      wierzch[v] += wierzch[w];
    }
  }
}

int main()
{
  scanf("%d", &n);
  srand(n);
  for (int i = 0; i < n - 1; i++)
  {
    int a, b;
    scanf("%d%d", &a, &b);
    a--; b--;
    t[a].push_back(b);
    t[b].push_back(a);
    deg[a]++;
    deg[b]++;
  }
  par[0] = -1;
  dfs(0);
  long long wyn = 0LL, akt;
  int res = 0;
  int ile = min(5000000 / n, 10 * n);
  for (int licznik = 0; licznik < ile; licznik++)
  {
    /* Idziemy "po gradiencie" w kierunku liscia */
    int v = losowy();
    while (deg[v] != 1)
    {
      int mi = n, nowy = 0;
      for (int i = 0; i < deg[v]; i++)
      {
        int w = t[v][i], dzieci;
        if (par[w] == v)
          dzieci = wierzch[w];
        else
          dzieci = n - wierzch[v];
        if (dzieci < mi)
        {
          mi = dzieci;
          nowy = w;
        }
      }
      v = nowy;
    }
    bfs(v);
    akt = 0LL;
    for (int i = 0; i < n; i++)
      akt += d[i];
    if (akt > wyn)
    {
      wyn = akt;
      res = v;
    }
  }
  printf("%d\n", res + 1);
  return 0;
}
