/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Robinson (ROB)                                            *
 *   Plik:     robb3.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie bardzo podobne do wzorcowego, ale zapomina    *
 *             o tym, ze wystawanie prostokatnego ograniczenia lodki     *
 *             poza plansze nie jest warunkiem koniecznym wyplyniecia    *
 *             lodki poza plansze.                                       *
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
bool zabr[3 * MAX_N][2 * MAX_N]; /* pola zabronione */

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

queue<pair<int, int> > kol;
int odl[3 * MAX_N][2 * MAX_N];

int x[] = {1, -1, 0, 0};
int y[] = {0, 0, 1, -1};

vector<int> pocz[MAX_N]; /* poczatki odpowiednikow lodzi, ktore wyznaczaja
                            pola zabronione */
int pkt[3 * MAX_N];

void zabronione()
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      if (lodz[i][j] == 'X')
        pocz[i].push_back(j + n - (maxy - miny));
    reverse(pocz[i].begin(), pocz[i].end());
  }
  for (int j = 0; j < 2 * n; j++)
  {
    memset(pkt, 0, 3 * n * sizeof(int));
    for (int i = 0; i < n; i++)
    {
      while (!pocz[i].empty() && pocz[i].back() < j - (maxy - miny))
        pocz[i].pop_back();
      int dlug = pocz[i].size();
      while (dlug >= 2 && pocz[i][dlug - 1] <= j && pocz[i][dlug - 2] <= j
          && odc[j - pocz[i][dlug - 2]] > odc[j - pocz[i][dlug - 1]])
      {
        pocz[i].pop_back();
        dlug--;
      }
      if (!pocz[i].empty() && pocz[i].back() <= j)
      {
        pkt[i + n - odc[j - pocz[i].back()]]++;
        pkt[i + n + odc[j - pocz[i].back()] + 1]--;
      }
    }
    int licznik = 0;
    for (int i = 0; i < 3 * n; i++)
    {
      licznik += pkt[i];
      zabr[i][j] = (licznik > 0);
    }
  }
}

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
      if (a <= n - (maxx - sr + 1) || a >= 2 * n + (maxx - sr))
        return odl[p.first][p.second] + 1;
      if (b <= n - (maxy - miny + 1) || b >= 2 * n)
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
  reverse(odc.begin(), odc.end());
  zabronione();
  int wynik = bfs(n + sr, n + miny);
  if (wynik < 0)
    puts("NIE");
  else
    printf("%d\n", wynik);
  return 0;
}
