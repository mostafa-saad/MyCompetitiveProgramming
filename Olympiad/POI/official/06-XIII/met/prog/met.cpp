/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MET (Metro)                                    *
 *   Plik:                met.cpp                                        *
 *   Autor:               Szymon Wasik                                   *
 *   Opis:                Rozwiazanie wzorcowe.                          *
 *                        Zlozonosc obliczeniowa: O(n)                   *
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
int level[MAXN];
int son[MAXN];
int count[MAXN];
int nodes[MAXN];

// Wczytuje dane wejsciowe i zeruje zmienne
void read()
{
  int a, b;
  
  scanf("%d %d", &n, &l);
  g = new vector<int>[n];
  for (int i = 0; i < n - 1; i++)
  {
    scanf("%d %d", &a, &b);
    a--;
    b--;
    g[a].push_back(b);
    g[b].push_back(a);
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
      if (level[*i] + 1 > level[node])
        son[node] = *i, level[node] = level[*i] + 1;
    }
  count[level[node]]++;
}

// Sortuje wieszcholki po poziomach przez zliczanie
void counting_sort()
{
  for (int i = 1; i < n; i++)
    count[i] += count[i-1];
  for (int i = 0; i < n; i++)
    nodes[--count[level[i]]] = i;
}

// Glowna petla algorytmu
int solve()
{
  int result = 0, pos = n-1;
  
  for (int i = 0; i < 2*l-1 && result < n; i++)
  {
    while (used[nodes[pos]]) pos--;
    int act = nodes[pos];
    while (act != -1)
      result++, used[act] = true, act = son[act];
  }
  return result;
}

int main()
{
  int foo, bar;

  read();
  root = longest_path(0, foo, bar);
  memset(used, false, sizeof(used));
  memset(count, 0, sizeof(count));
  make_tree(root);
  counting_sort();
  memset(used, false, sizeof(used));
  printf("%d\n", solve());
  return 0;
}
