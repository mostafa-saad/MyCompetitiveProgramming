/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: MET (Metro)                                    *
 *   Plik:                met4.cpp                                       *
 *   Autor:               Jakub Radoszewski                              *
 *   Opis:                Rozwiazanie optymalne.                         *
 *                        Zlozonosc obliczeniowa: O(n)                   *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <utility>
#include <list>
using namespace std;

#define MAX_N 1000000

int n, l;
vector<int> t[MAX_N]; /* drzewo */
int rozm[MAX_N];

void odczyt()
{
  int a, b;
  scanf("%d%d", &n, &l);
  for (int i = 0; i < n - 1; i++)
  {
    scanf("%d%d", &a, &b);
    a--; b--;
    t[a].push_back(b);
    t[b].push_back(a);
  } /* for */
  for (int i = 0; i < n; i++)
    rozm[i] = (int)t[i].size();
} /* odczyt */


/* ------------------------------------------------------------------------- */
/* Znajdowanie wierzcho³ka na jednym z koñców ¶rednicy drzewa */

int wyn = 0, wynw;
bool uzyty[MAX_N];

/* Funkcja sprawdza, czy osi±gnêli¶my lepszy wynik. */
void spr(pair<int, int> p)
{
  if (p.first > wyn)
  {
    wyn = p.first;
    wynw = p.second;
  } /* if */
} /* spr */


/* Funkcja zwraca parê (wynik, jeden z wierzcho³ków koñcowych na ¶cie¿ce). */
pair<int, int> licz_sr(int v)
{
  int ile = 0;
  pair<int, int> tmp;
  uzyty[v] = true;
  for (int i = 0; i < rozm[v]; i++)
    if (!uzyty[t[v][i]])
      ile++;
  /* ile == 0 */
  if (!ile)
  {
    spr(make_pair(1, v));
    return make_pair(1, v);
  } /* if */
  /* ile == 1*/
  if (ile == 1)
    for (int i = 0; i < rozm[v]; i++)
      if (!uzyty[t[v][i]])
      {
        tmp = licz_sr(t[v][i]);
        spr(make_pair(tmp.first + 1, tmp.second));
        return make_pair(tmp.first + 1, tmp.second);
      } /* if */
  /* ile >= 2 */
  int mx1 = 0, mx2 = 0, wx1;
  for (int i = 0; i < rozm[v]; i++)
    if (!uzyty[t[v][i]])
    {
      tmp = licz_sr(t[v][i]);
      if (tmp.first > mx1)
      {
        mx1 = tmp.first;
        wx1 = tmp.second;
      } /* if */
      else if (tmp.first > mx2)
        mx2 = tmp.first;
    } /* if */
  spr(make_pair(mx1 + mx2 + 1, wx1));
  return make_pair(mx1 + 1, wx1);
} /* licz_sr */

int srednica()
{
  for (int i = 0; i < n; i++)
    uzyty[i] = false;
  licz_sr(0);
  return wynw;
} /* srednica */


/* ------------------------------------------------------------------------- */
/* Numerowanie wierzcho³ków po g³êboko¶ciach */

int gl[MAX_N];
vector<int> kol[MAX_N];

inline int wpisz(int wart, int v)
{
  kol[wart].push_back(v);
  return wart;
} /* wpisz */

/* "Przy okazji" wierzcho³ki zapamiêtywane na listach po swojej
 * g³êboko¶ci - funkcja wpisz. */
int licz_gl(int v)
{
  int w = 0;
  bool zm = false;
  gl[v] = 0;
  for (int i = 0; i < rozm[v]; i++)
    if (gl[t[v][i]] < 0)
    {
      zm = true;
      w = max(w, licz_gl(t[v][i]));
    } /* if */
  if (zm)
    gl[v] =  w + 1;
  return wpisz(gl[v], v);
} /* licz_gl */



/* ------------------------------------------------------------------------- */
/* Wyrzucanie pewnej najd³u¿szej ¶cie¿ki */

void wyrzuc(int v)
{
  uzyty[v] = true;
  for (int i = 0; i < rozm[v]; i++)
    if (!uzyty[t[v][i]] && gl[t[v][i]] + 1 == gl[v])
    {
      wyrzuc(t[v][i]);
      break;
    } /* if */
} /* wyrzuc */



int main()
{
  odczyt();
  int v = srednica();
  for (int i = 0; i < n; i++)
    gl[i] = -1;
  licz_gl(v);
 
  for (int i = 0; i < n; i++)
    uzyty[i] = false;
  int wynik = 0, ile_lisci = 1, najw = n - 1;
  while (ile_lisci < 2 * l)
  {
    while (najw >= 0 && kol[najw].empty())
      najw--;
    if (najw < 0)
      break;
    int akt = kol[najw].back();
    if (uzyty[akt])
    {
      kol[najw].pop_back();
      continue;
    } /* if */
    wynik += gl[akt] + 1;
    wyrzuc(akt);
    kol[najw].pop_back();
    ile_lisci++;
  }
  printf("%d\n", wynik);
  return 0;
} /* main */
