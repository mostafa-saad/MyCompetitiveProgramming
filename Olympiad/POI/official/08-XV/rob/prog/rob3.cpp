/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Robinson (ROB)                                            *
 *   Plik:     rob3.cpp                                                  *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie o zlozonosci czasowej O(n^2), zgodne z idea   *
 *             rozwiazania autorskiego.                                  *
 *                                                                       *
 *************************************************************************/

#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <utility>
#include <algorithm>
using namespace std;

#define MAX_N 2000

char lodz[MAX_N][MAX_N + 1];
int n;
vector<int> odc; /* odcinki skladajace sie na lodke */

int minx, miny, maxx, maxy;
int sr; /* srodek lodki */
int polsz;

/* Sprawdzanie poprawnosci ulozenia lodki */
bool lodka()
{
  minx = n; miny = n; maxx = -1; maxy=-1;
  odc.clear();
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      if (lodz[i][j] == 'r')
      {
        minx = min(minx, i);
        maxx = max(maxx, i);
        miny = min(miny, j);
        maxy = max(maxy, j);
      }
  sr = (maxx + minx) / 2;
  polsz = (maxx - minx) / 2;
  for (int j = miny; j <= maxy; j++)
  {
    int i1 = 0, i2 = 0; /* ile kawalkow pod osia symetrii, a ile nad */
    for (int i = minx; i <= maxx; i++)
    {
      if (lodz[i][j] == 'r')
      {
        if (i < sr)
          i1++;
        if (i > sr)
          i2++;
      }
    }
    if (i1 != i2)
      /* Lodka nie jest symetryczna */
      return false;
    odc.push_back(i1);
  }
  return true;
}

vector<int> polowka;

int przekroj[MAX_N]; /* dla danego promienia trzymamy numer
                        najwiekszego mieszczacego sie przekroju */

void policz_przekroj(int rozm)
{
  /* Liczymy tablice przekroj */
  int i = 0;
  for (int j = 0; j < n; j++)
  {
    i = max(i, 0);
    while (i < rozm && polowka[i] <= j)
      i++;
    i--;
    przekroj[j] = i;
  }
}



int pole[3 * MAX_N][MAX_N]; /* jaki najwiekszy numer przekroju polowki
                               miesci sie w danym polu */
int gora[3 * MAX_N], dol[3 * MAX_N];

void policz_przekroje_pol(int rozm)
{
  /* Liczymy tablice pole */
  for (int j = 0; j < n; j++)
  {
    gora[0] = n;
    for (int i = 1; i < 3 * n; i++)
      if (i >= n && i < 2 * n && lodz[i - n][j] == 'X')
        gora[i] = 0;
      else
        gora[i] = min(gora[i - 1] + 1, n);
    
    dol[3 * n - 1] = n;
    for (int i = 3 * n - 2; i >= 0; i--)
      if (i >= n && i < 2 * n && lodz[i - n][j] == 'X')
        dol[i] = 0;
      else
        dol[i] = min(dol[i + 1] + 1, n);

    for (int i = 0; i < 3 * n; i++)
    {
      int wlk = min(gora[i], dol[i]) - 1;
      if (wlk < 0)
        pole[i][j] = -1;
      else
        pole[i][j] = przekroj[wlk];
    }
  }
}


bool zabr[3 * MAX_N][3 * MAX_N]; /* pola zabronione */

void policz_polowke(int przesuniecie, bool na_odwrot)
{
  int rozm = polowka.size();
  policz_przekroj(rozm);
  policz_przekroje_pol(rozm);
  
  /* Glowny algorytm szukania pol zabronionych */
  for (int i = 0; i < 3 * n; i++)
  {
    int numer = rozm - 1; /* numer poprzedniego najlepszego przekroju */
    int przekr; /* numer najlepszego biezacego przekroju */
    for (int j = n; j < 3 * n; j++)
    {
      if (j < 2 * n)
        przekr = pole[i][j - n];
      else
        /* jestesmy poza plansza - a tam tylko woda */
        przekr = rozm - 1;
      if (numer == rozm - 1)
        numer--;
      /* Obliczamy najlepszy biezacy numer */
      numer = min(numer + 1, przekr);

      if (numer != rozm - 1)
      {
        /* Mamy pole zabronione */
        if (na_odwrot)
          zabr[i][3 * n - 1 - j - przesuniecie] = true;
        else
          zabr[i][j - przesuniecie] = true;
      }
    }
  }
}


void zabronione()
{
  /* Lewa polowka */
  int i = 0;
  polowka.push_back(odc[i]);
  while (odc[i] < polsz)
  {
    i++;
    polowka.push_back(odc[i]);
  }
  int wlk0 = (int)polowka.size() - 1;
  policz_polowke(wlk0, false);

  /* Prawa polowka */
  polowka.clear();
  do
  {
    polowka.push_back(odc[i]);
    i++;
  } while (i < (int)odc.size());
  
  /* Odwracamy polowke i lodz */
  reverse(polowka.begin(), polowka.end());
  for (i = 0; i < n; i++)
    reverse(lodz[i], lodz[i] + n);
  policz_polowke(wlk0, true);
}


pair<int, int> przedzial[2 * MAX_N + 1];

/* Funkcja zwraca przykladowy pusty przedzial (obustronnie domkniety). */
inline pair<int, int> pusty()
{
  return make_pair(1, 0);
}

/* Dla kazdego b liczy, w jakim przedziale musi sie znajdowac a,
 * zeby lodka o poczatku w polu (a,b) byla wewnatrz planszy. */
void licz_przedzialy()
{
  /* lodka przed plansza */
  int p = n - (int)odc.size();
  for (int i = 0; i <= p; i++)
    przedzial[i] = pusty();
  
  /* lodka nad/pod plansza */
  int mx = *max_element(odc.begin(), odc.end());
  for (int i = p + 1; i < 2 * n; i++)
    przedzial[i] = make_pair(n - mx, 2 * n - 1 + mx);

  /* lodka dochodzi do planszy */
  int j = 0;
  while (j < (int)odc.size() - 1 && odc[j] <= odc[j + 1])
  {
    p++;
    przedzial[p] = make_pair(n - odc[j], 2 * n - 1 + odc[j]);
    j++;
  }

  /* lodka odchodzi od planszy */
  int k = 2 * n - 1;
  j = (int)odc.size() - 1;
  while (j > 0 && odc[j] <= odc[j - 1])
  {
    przedzial[k] = make_pair(n - odc[j], 2 * n - 1 + odc[j]);
    j--;
    k--;
  }

  /* lodka za plansza */
  przedzial[2 * n] = pusty();
}

inline bool wyplynela(int a, int b)
{
  return a < przedzial[b].first || a > przedzial[b].second;
}

queue<pair<int, int> > kol;
int odl[3 * MAX_N][2 * MAX_N];

int x[] = {1, -1, 0, 0};
int y[] = {0, 0, 1, -1};

/* BFS zaczynajacy od punktu (x0,y0). */
int bfs(int x0, int y0)
{
  for (int i = 0; i < 3 * n; i++)
    for (int j = 0; j < 2 * n; j++)
      odl[i][j] = -1;
  odl[x0][y0] = 0;
  kol.push(make_pair(x0, y0));

  int a, b;
  while (!kol.empty())
  {
    pair<int, int> p = kol.front();
    kol.pop();
    for (int i = 0; i < 4; i++)
    {
      a = p.first + x[i]; b = p.second + y[i];
      /* Wyszlismy poza plansze - sukces */
      if (wyplynela(a, b))
        return odl[p.first][p.second] + 1;
      if (odl[a][b] == -1 && !zabr[a][b])
      {
        odl[a][b] = odl[p.first][p.second] + 1;
        kol.push(make_pair(a, b));
      }
    }
  }
  return -1;
}

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%s", lodz[i]);
  if (!lodka()) /* czy lodka zorienowana poziomo */
  {
    /* Odbij wszystko wzgledem osi y=x */
    for (int i = 0; i < n; i++)
      for (int j = 0; j < i; j++)
        swap(lodz[i][j], lodz[j][i]);
    lodka(); /* no to lodka zorientowana pionowo */
  }
  zabronione();
  reverse(odc.begin(), odc.end());
  licz_przedzialy();
  int wynik = bfs(n + sr, n + miny);
  if (wynik < 0)
    puts("NIE");
  else
    printf("%d\n", wynik);
  return 0;
}
