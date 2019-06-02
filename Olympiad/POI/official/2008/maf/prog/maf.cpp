/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Mafia (MAF)                                               *
 *   Plik:     maf.cpp                                                   *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie wzorcowe o zlozonosci czasowej O(n).          *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX_N 1000000
#define INFTY 100000000

int s[MAX_N], n;
vector<int> roots; /* korzenie skladowych */
vector<int> t[MAX_N]; /* krawedzie wchodzace do wierzcholkow */

/* Przeszukuje slabo spojne skladowe, wyznacza ich korzenie
 * i zle krawedzie. */
int col[MAX_N]; /* "kolory" wierzcholkow */
void koloruj()
{
  int nr = 0;
  for (int i = 0; i < n; i++)
    if (!col[i])
    {
      nr++;
      int v = i;
      /* idziemy az dojdziemy do cyklu albo do odwiedzonego wierzcholka */
      while (!col[v])
      {
        col[v] = nr;
        v = s[v];
      }
      if (col[v]==nr) /* znalezlismy nowy cykl */
        roots.push_back(v); /* arbitralnie wybieramy korzen skladowej */
    }
}

/* Jezeli przyp[v]=1, to wierzcholek v musi nalezec do zbioru niezaleznego;
 * przyp[v]=2 to wierzcholek, ktory do tego zbioru nie moze nalezec,
 * a przyp[v]=0 to wierzcholek nieustalony */
int przyp[MAX_N];

/* tab[v][x] - ile maksymalnie wierzcholkow w zbiorze niezaleznym moze
 * byc w poddrzewie o ojcu v, jezeli v nie jest wziety (x=0) lub jest wziety
 * (x=1). tab[v][x]=-INFTY oznacza, ze dana sytuacja jest niemozliwa
 * (np. wskutek wartosci przyp[v]). */
int tab[MAX_N][2];

int min_ofiar, max_ofiar; /* n - poszukiwane_wyniki */

/* Czy skladowa jest cyklem (tzn. nie wchodzi do niej zadne drzewo). */
bool cykl(int root)
{
  int v = root;
  do
  {
    if ((int)t[v].size() > 1) return false;
    v = s[v];
  } while (v != root);
  return true;
}

/* Wyznaczanie min_ofiar */
vector<int> skladowa;
int root;
/* Liczymy tab[v][jak % 2] (jak=2 oznacza, ze nie bierzemy v). */
int licz(int v, char jak)
{
  /* Rekurencja ze spamietywaniem */
  int &w = tab[v][jak % 2];
  if (w != -1)
    return w;
  skladowa.push_back(v);
  if (przyp[v] && przyp[v] != jak)
    return w = -INFTY;
  if (jak == 1) /* bierzemy v do zbioru */
  {
    w = 1;
    for (int i = 0; i < (int)t[v].size(); i++)
      if (t[v][i] != root)
      {
        int x = licz(t[v][i], 2);
        if (x == -INFTY)
          return w = -INFTY;
        w += x;
      }
    return w;
  }
  else /* nie bierzemy v do zbioru */
  {
    w = 0;
    for (int i = 0; i < (int)t[v].size(); i++)
      if (t[v][i] != root)
      {
        int x = max(licz(t[v][i], 1), licz(t[v][i], 2));
        if (x == -INFTY)
          return w = -INFTY;
        w += x;
      }
    return w;
  }
}
void analizuj(int root_0)
{
  root = root_0;
  int wynik = 0;
  /* Przypadek 1: Korzen bierzemy do zbioru, no to s[korzen] juz nie. */
  skladowa.clear();
  if ((!przyp[root] || przyp[root] == 1) && 
      (!przyp[s[root]] || przyp[s[root]] == 2) &&
      s[root] != root) /* uwaga na cykl jednoelementowy! */
  {
    int ost_root = przyp[root], ost_sroot = przyp[s[root]];
    przyp[root] = 1; przyp[s[root]] = 2;
    wynik = max(wynik, licz(root, char(1)));
    przyp[root] = ost_root; przyp[s[root]] = ost_sroot;
  }
  
  /* Przypadek 2: Korzenia nie bierzemy do zbioru. */
  for (int i = 0; i < (int)skladowa.size(); i++)
    tab[skladowa[i]][0] = tab[skladowa[i]][1] = -1;
  skladowa.clear();
  if (!przyp[root] || przyp[root] == 2)
  {
    int ost_root = przyp[root];
    przyp[root] = 2;
    wynik = max(wynik, licz(root, char(2)));
    przyp[root] = ost_root;
  }
  min_ofiar += wynik;
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
  {
    scanf("%d", s+i);
    s[i]--;
    t[s[i]].push_back(i);
  }
  koloruj();
  /* W max_ofiar zliczamy najpierw liczbe ocalonych, kiedy jest max liczba
   * ofiar. */
  for (int i = 0; i < n; i++)
    if (t[i].empty()) /* lisc */
    {
      max_ofiar++;
      przyp[i] = 1;
      przyp[s[i]] = 2;
    }
  for (int i = 0; i < n; i++)
    tab[i][0] = tab[i][1] = -1;
  for (int i = 0; i < (int)roots.size(); i++)
  {
    /* Cykl o dlugosci wiekszej niz 1. */
    if (cykl(roots[i]) && s[roots[i]] != roots[i])
      max_ofiar++;
    analizuj(roots[i]);
  }
  printf("%d %d\n", n - min_ofiar, n - max_ofiar);
  return 0;
}
