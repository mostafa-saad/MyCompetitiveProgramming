/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Mafia (MAF)                                               *
 *   Plik:     maf2.cpp                                                  *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie alternatywne, o zlozonosci czasowej O(n),     *
 *             oparte na troche innej idei niz wzorcowe.                 *
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
vector<int> strzaly;
bool zyje[MAX_N];
/* W polejnosci post-order */
void dfs(int v)
{
  for (int i = 0; i < (int)t[v].size(); i++)
    dfs(t[v][i]);
  strzaly.push_back(v);
}
void strzelaj()
{
  /* Strzelamy wg tablicy strzaly */
  for (int i = 0; i < (int)strzaly.size(); i++)
    if (zyje[strzaly[i]])
      zyje[s[strzaly[i]]] = false;
}
void doit(int root)
{
  /* Ide raz po cyklu i go zaznaczam. */
  int v = root;
  do
  {
    col[v] = 1;
    v = s[v];
  } while (v != root);
  strzaly.clear();
  /* Drugi raz po cyklu: wypisujemy post-ordery */
  v = root;
  do
  {
    for (int i = 0; i < (int)t[v].size(); i++)
      if (!col[t[v][i]])
        dfs(t[v][i]);
    v = s[v];
  } while (v != root);
  /* Strzelamy w tej kolejnosci */
  strzelaj();
  /* Szukamy umarlaka na cyklu */
  int pocz = root;
  v = root;
  do
  {
    if (!zyje[v])
    {
      pocz = v;
      break;
    }
    v = s[v];
  } while (v != root);
  /* Wypisujemy strzaly, poczynajac od umarlaka */
  strzaly.clear();
  v = pocz;
  do
  {
    strzaly.push_back(v);
    v = s[v];
  } while (v != pocz);
  /* I wreszcie strzelamy na cyklu */
  strzelaj();
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
      max_ofiar++;
  for (int i = 0; i < n; i++)
  {
    zyje[i] = true;
    col[i] = 0;
  }
  for (int i = 0; i < (int)roots.size(); i++)
  {
    /* Cykl o dlugosci wiekszej niz 1. */
    if (cykl(roots[i]) && s[roots[i]] != roots[i])
      max_ofiar++;
    doit(roots[i]);
  }
  for (int i = 0; i < n; i++)
    if (zyje[i])
      min_ofiar++;
  printf("%d %d\n", n - min_ofiar, n - max_ofiar);
  return 0;
}
