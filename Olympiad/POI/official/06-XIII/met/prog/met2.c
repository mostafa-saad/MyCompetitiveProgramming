/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MET (Metro)                                    *
 *   Plik:                met2.c                                         *
 *   Autor:               Szymon Wasik                                   *
 *   Opis:                Rozwiazanie poprawne.                          *
 *                        Wykorzystuje kolejke priorytetowa.             *
 *                        Zlozonosc obliczeniowa: O(n*log n)             *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXN 1000000
#define true 1
#define false 0

typedef struct _edge {
  struct _edge *next;
  int v;
} edge;
typedef unsigned char bool;


edge *g[MAXN];
int n, l;
bool used[MAXN];
int root;
int level[MAXN];
int son[MAXN];
int q[MAXN+1], pq = 1;

// Czy kolejka jest pusta?
bool empty()
{
  return pq == 1;
}

void swap(int *a, int * b)
{
  int c = *a;
  *a = *b;
  *b = c;
}

// Dodaje element
void add(int node)
{
  int s = pq, o = s / 2;
  q[pq++] = node;
  while (o > 0)
    if (level[q[o]] < level[q[s]])
    {
      swap(q+o, q+s);
      s = o;
      o = s / 2;
    }
    else break;
}

// Usuwa element
int get()
{
  int result = q[1], o = 1, s = 2;  
  
  q[1] = q[--pq];
  while (s <= pq)
  {
    if (s < pq && level[q[s]] < level[q[s+1]]) s++;
    if (level[q[o]] < level[q[s]])
    {
      swap(q+o, q+s);
      o = s;
      s = o * 2;
    }
    else break;        
  }
  return result;
}

// Dodaje krawedz pomiedzy dwoma wierzcholkami
void add_edge(int a, int b)
{
  edge *tmp = (edge *)malloc(sizeof(edge));
  tmp->next = g[a];
  g[a] = tmp;
  g[a]->v = b;
}

// Wczytuje dane wejsciowe i zeruje zmienne
void read()
{
  int a, b, i;
  
  scanf("%d %d", &n, &l);
  for (i = 0; i < n; i++)
    g[i] = NULL;
  for (i = 0; i < n - 1; i++)
  {
    scanf("%d %d", &a, &b);
    a--;
    b--;
    add_edge(a, b);
    add_edge(b, a);
  }
}

/*
 * Oblicza dlugosc najdluzszej sciezki w grafie
 * Zwraca wierzcholek bedacy koncem aktualnie znalezionej
 * najdluzszej sciezki.
 * len - dlugosc najdluzszej sciezki od liscia do wierzcholka
 * lenmax - dlugosc najdluzszej sciezki w poddrzewie
 */
int longest_path(int node, int *len, int *lenmax)
{
  int lmax1 = -1, lmax2 = -1, nmax = node, result = node;  
  edge *act = g[node];
  
  used[node] = true;
  *len = 0;
  *lenmax = 0;
  while (act != NULL)
  {
    int w = act->v;
    if (!used[w])
    {
      int n2, len2, lenmax2;
      n2 = longest_path(w, &len2, &lenmax2);
      if (len2 > lmax1)
      {
        lmax2 = lmax1;
        lmax1 = len2;
        nmax = n2;
      }
      else if (len2 > lmax2) lmax2 = len2;
      if (lenmax2 > *lenmax)
        *lenmax = lenmax2, result = n2;
    }
    act = act->next;
  }
  lmax1++;
  lmax2++;
  if (lmax1 + lmax2 > *lenmax)
    *lenmax = lmax1 + lmax2, result = nmax;
  *len = lmax1;
  return result;
}

// Oblicza wysokosci wierzcholkow w drzewie
void make_tree(int node)
{
  edge *act = g[node];
  
  used[node] = true;
  level[node] = 0;
  son[node] = -1;
  while (act != NULL)
  {
    int w = act->v;
    
    if (!used[w])
    {
      make_tree(w);
      if (level[w] + 1 > level[node])
        son[node] = w, level[node] = level[w] + 1;
    }
    act = act->next;
  }
}

// Glowna petla algorytmu
int solve()
{
  int result = 0, i;
  
  add(root);
  for (i = 0; i < 2*l-1 && result < n; i++)
  {
    int act;
    
    while (used[act = get()]);
    while (act != -1)
    {
      edge *w = g[act];
      while (w != NULL)
      {
        if (!used[w->v] && (w->v != son[act])) add(w->v);
        w = w->next;
      }
      result++, used[act] = true, act = son[act];
    }
  }
  return result;
}

int main()
{
  int foo, bar;

  read();
  root = longest_path(0, &foo, &bar);
  memset(used, false, sizeof(used));
  make_tree(root);
  memset(used, false, sizeof(used));
  printf("%d\n", solve());
  return 0;
}
