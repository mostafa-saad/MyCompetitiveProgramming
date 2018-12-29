/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SKA (Skarbonki)                                *
 *   Plik:                ska2.cpp                                       *
 *   Autor:               Micha³ Adamaszek                               *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                        Znajdujemy liczbe spojnych skladowych w grafie *
 *                        on-line, przy uzyciu find-union z wywazaniem   *
 *                        i kompresja sciezki.                           *
 *                        Zlozonosc: O(n log*(n))                        *
 *************************************************************************/

#include <stdio.h>

#define N 1000000

int p[N];                       /* wskazniki do gory */
int rank[N];                    /* rangi */
int ccCount;                    /* liczba sk³adowych */
int n;

/**
 Inicjalizuje struktury danych 
 */
void init()
{
  int i;
  for (i = 0; i < n; i++)
    p[i] = i, rank[i] = 0;
  ccCount = n;
}

/**
 Do find-union, znajduje korzen zbioru zawierajacego dany wierzcholek
 */
int findSet(int k)
{
  if (p[k] != k)
    p[k] = findSet(p[k]);
  return p[k];
}

/**
 Do find-union, laczy dwa zbiory, jesli sa rowne to nic nie robi, wpp zmniejsza liczbe skladowych.
 */
void link(int a, int b)
{
  a = findSet(a), b = findSet(b);

  if (a == b)
    return;

  if (rank[a] > rank[b])
    p[b] = a;
  else {
    p[a] = b;
    if (rank[a] == rank[b])
      rank[b]++;
  }

  ccCount--;
}

/**
 Program glowny. Wczytuje po kolei krawedzie i laczy skladowe
 */
int main(void)
{

  int v, k;

  scanf("%d", &n);
  init();

  for (k = 0; k < n; k++) {
    scanf("%d", &v);
    link(v - 1, k);
  }

  printf("%d\n", ccCount);

  return 0;
}
