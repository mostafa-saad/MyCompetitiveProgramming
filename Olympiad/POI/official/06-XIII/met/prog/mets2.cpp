/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MET (Metro)                                    *
 *   Plik:                mets2.cpp                                      *
 *   Autor:               Szymon Wasik                                   *
 *   Opis:                Rozwiazanie nieoptymalne.                      *
 *                        Zlozonosc obliczeniowa: O(n*l)                 *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>

#define MAXN 1000000

using namespace std;

int n, l;
vector<int> *g;
bool used[MAXN];
int root;
int deg[MAXN];
int level[MAXN];
int son[MAXN];
int prev[MAXN];

// Wczytuje dane wejsciowe i zeruje zmienne
void read()
{
  int a, b;
  
  scanf("%d %d", &n, &l);
  memset(deg, 0, sizeof(deg));
  g = new vector<int>[n];
  for (int i = 0; i < n - 1; i++)
  {
    scanf("%d %d", &a, &b);
    a--;
    b--;
    g[a].push_back(b);
    g[b].push_back(a);
    deg[a]++;
    deg[b]++;
  }
  memset(used, false, sizeof(used));
}

/*
 * Oblicza dlugosc najdluzszej sciezki w grafie
 * Zwraca wierzcholek bedacy koncem aktualnie znalezionej
 * najdluzszej sciezki.
 * len - dlugosc najdluzszej sciezki od liscia do wierzcholka
 * lenmax - dlugosc najdluzszej sciezki w poddrzewie
 */
int longest_path(int node, int &len, int &lenmax)
{
  int lmax1 = -1, lmax2 = -1, nmax = node, result = node;  
  
  used[node] = true;
  len = 0;
  lenmax = 0;
  for (vector<int>::iterator i = g[node].begin(); i != g[node].end(); ++i)
    if (!used[*i])
    {
      int n2, len2, lenmax2;
      n2 = longest_path(*i, len2, lenmax2);
      if (len2 > lmax1)
      {
        lmax2 = lmax1;
        lmax1 = len2;
        nmax = n2;
      }
      else if (len2 > lmax2) lmax2 = len2;
      if (lenmax2 > lenmax)
        lenmax = lenmax2, result = n2;
    }
  lmax1++;
  lmax2++;
  if (lmax1 + lmax2 > lenmax)
    lenmax = lmax1 + lmax2, result = nmax;
  len = lmax1;
  return result;
}

// Oblicza wysokosci wierzcholkow w drzewie
void make_tree(int node)
{
  used[node] = true;
  level[node] = 0;
  son[node] = -1;
  for (vector<int>::iterator i = g[node].begin(); i != g[node].end(); ++i)
    if (!used[*i])
    {
      make_tree(*i);
      prev[*i] = node;
      if (level[*i] + 1 > level[node])
        son[node] = *i, level[node] = level[*i] + 1;
    }
}

void mark_lp()
{
  int act = root;
  while (act != -1)
    used[act] = true, act = son[act];
}

int go(int node)
{
  if (used[node]) return 0;
  go(prev[node]);
  level[node] = level[prev[node]] + 1;
  return level[node];
}

void set(int node)
{
  while (!used[node])
    used[node] = true, node = prev[node];
}

// Glowna petla algorytmu
int solve()
{
  int res = 0, mlen, mw;

  for (int i = 0; i < 2*l-2; i++)
  {
    mlen = 0, mw = 0;
    memset(level, 0, sizeof(level));
    for (int i = 0; i < n; i++)
      if (deg[i] == 1 && level[i] == 0)
        if ((res = go(i)) > mlen) mlen = res, mw = i;
    set(mw);
  }
  res = 0;
  for (int i = 0; i < n; i++)
    if (used[i]) res++;
  return res;
}

int main()
{
  int foo, bar;

  read();
  if (l == 0)
  {
    printf("0\n");
    return 0;
  }  
  root = longest_path(0, foo, bar);
  memset(used, false, sizeof(used));
  make_tree(root);
  memset(used, false, sizeof(used));
  mark_lp();
  printf("%d\n", solve());
  return 0;
}
