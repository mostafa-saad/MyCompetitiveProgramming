/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Robinson (ROB)                                            *
 *   Plik:     rob1.c                                                    *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie o zlozonosci czasowej O(n^2), ktore najpierw  *
 *             sprytnie znajduje wszystkie pola zabronione, a potem      *
 *             wykonuje jedno przeszukiwanie grafu wszerz.               *
 *                                                                       *
 *************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_N 2000

char lodz[MAX_N][MAX_N + 1];
int n;
int odc[MAX_N]; /* odcinki skladajace sie na lodke */
int odcsize;

int minx, miny, maxx, maxy;
int sr; /* srodek lodki */
char zabr[3 * MAX_N][2 * MAX_N]; /* pola zabronione */

int min(int a, int b)
{
  if (a < b)
    return a;
  else
    return b;
}

int max(int a, int b)
{
  if (a < b)
    return b;
  else
    return a;
}

/* Sprawdzanie poprawnosci ulozenia lodki */
int lodka()
{
  int i, j;
  minx = n; miny = n; maxx = -1; maxy=-1;
  odcsize = 0;
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
      if (lodz[i][j] == 'r')
      {
        minx = min(minx, i);
        maxx = max(maxx, i);
        miny = min(miny, j);
        maxy = max(maxy, j);
      }
  sr = (maxx + minx) / 2;
  for (j = miny; j <= maxy; j++)
  {
    int i1 = 0, i2 = 0; /* ile kawalkow pod osia symetrii, a ile nad */
    for (i = minx; i <= maxx; i++)
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
      return 0;
    odc[odcsize++] = i1;
  }
  return 1;
}

struct pair
{
  short int first, second;
};

struct pair make_pair(int a, int b)
{
  struct pair p;
  p.first = (short int)a; 
  p.second = (short int)b;
  return p;
}

struct pair kol[6 * MAX_N * MAX_N];
int head, tail;

int odl[3 * MAX_N][2 * MAX_N];

int x[] = {1, -1, 0, 0};
int y[] = {0, 0, 1, -1};

int pocz[MAX_N][2 * MAX_N]; /* poczatki odpowiednikow lodzi, ktore wyznaczaja
                            pola zabronione */
int poczlen[MAX_N];
int pkt[3 * MAX_N];

void reverse(int i)
{
  int a = 0, b = poczlen[i] - 1;
  while (a < b)
  {
    int c = pocz[i][a];
    pocz[i][a] = pocz[i][b];
    pocz[i][b] = c;
    a++; b--;
  }
}

void zabronione()
{
  int i, j;
  for (i = 0; i < n; i++)
  {
    poczlen[i] = 0;
    for (j = 0; j < n; j++)
      if (lodz[i][j] == 'X')
        pocz[i][poczlen[i]++] = j + n - (maxy - miny);
    reverse(i);
  }
  for (j = 0; j < 2 * n; j++)
  {
    int licznik;
    memset(pkt, 0, 3 * n * sizeof(int));
    for (i = 0; i < n; i++)
    {
      while (poczlen[i] && pocz[i][poczlen[i]-1] < j - (maxy - miny))
        poczlen[i]--;
      while (poczlen[i] >= 2 && pocz[i][poczlen[i] - 1] <= j &&
          pocz[i][poczlen[i] - 2] <= j
          && odc[j - pocz[i][poczlen[i] - 2]] > odc[j - pocz[i][poczlen[i] - 1]])
        poczlen[i]--;
      if (poczlen[i] && pocz[i][poczlen[i] - 1] <= j)
      {
        pkt[i + n - odc[j - pocz[i][poczlen[i] - 1]]]++;
        pkt[i + n + odc[j - pocz[i][poczlen[i] - 1]] + 1]--;
      }
    }
    licznik = 0;
    for (i = 0; i < 3 * n; i++)
    {
      licznik += pkt[i];
      zabr[i][j] = (licznik > 0);
    }
  }
}

struct pair przedzial[2 * MAX_N + 1];

/* Funkcja zwraca przykladowy pusty przedzial (obustronnie domkniety). */
inline struct pair pusty()
{
  return make_pair(1, 0);
}

/* Dla kazdego b liczy, w jakim przedziale musi sie znajdowac a,
 * zeby lodka o poczatku w polu (a,b) byla wewnatrz planszy. */
void licz_przedzialy()
{
  /* lodka przed plansza */
  int p = n - odcsize;
  int i, j, k, mx;
  for (i = 0; i <= p; i++)
    przedzial[i] = pusty();
  
  /* lodka nad/pod plansza */
  mx = odc[0];
  for (i = 1; i < odcsize; i++)
    if (odc[i] > mx)
      mx = odc[i];
  for (i = p + 1; i < 2 * n; i++)
    przedzial[i] = make_pair(n - mx, 2 * n - 1 + mx);

  /* lodka dochodzi do planszy */
  j = 0;
  while (j < odcsize - 1 && odc[j] <= odc[j + 1])
  {
    p++;
    przedzial[p] = make_pair(n - odc[j], 2 * n - 1 + odc[j]);
    j++;
  }

  /* lodka odchodzi od planszy */
  k = 2 * n - 1;
  j = odcsize - 1;
  while (j > 0 && odc[j] <= odc[j - 1])
  {
    przedzial[k] = make_pair(n - odc[j], 2 * n - 1 + odc[j]);
    j--;
    k--;
  }

  /* lodka za plansza */
  przedzial[2 * n] = pusty();
}

inline int wyplynela(int a, int b)
{
  return a < przedzial[b].first || a > przedzial[b].second;
}

/* BFS zaczynajacy od punktu (x0,y0). */
int bfs(int x0, int y0)
{
  int i, j, a, b;
  for (i = 0; i < 3 * n; i++)
    for (j = 0; j < 2 * n; j++)
      odl[i][j] = -1;
  odl[x0][y0] = 0;
  kol[0] = make_pair(x0, y0);
  head = 0; tail = 1;

  while (head != tail)
  {
    struct pair p = kol[head];
    head++;
    for (i = 0; i < 4; i++)
    {
      a = p.first + x[i]; b = p.second + y[i];
      /* Wyszlismy poza plansze - sukces */
      if (wyplynela(a, b))
        return odl[p.first][p.second] + 1;
      if (odl[a][b] == -1 && !zabr[a][b])
      {
        odl[a][b] = odl[p.first][p.second] + 1;
        kol[tail++] = make_pair(a, b);
      }
    }
  }
  return -1;
}

void odwroc()
{
  int a = 0, b = odcsize - 1;
  while (a < b)
  {
    int c = odc[a];
    odc[a] = odc[b];
    odc[b] = c;
    a++; b--;
  }
}

int main()
{
  int i, j, wynik;
  scanf("%d", &n);
  for (i = 0; i < n; i++)
    scanf("%s", lodz[i]);
  if (!lodka()) /* czy lodka zorienowana poziomo */
  {
    /* Odbij wszystko wzgledem osi y=x */
    for (i = 0; i < n; i++)
      for (j = 0; j < i; j++)
      {
        char c = lodz[i][j];
        lodz[i][j] = lodz[j][i];
        lodz[j][i] = c;
      }
    lodka(); /* no to lodka zorientowana pionowo */
  }
  odwroc();
  zabronione();
  licz_przedzialy();
  wynik = bfs(n + sr, n + miny);
  if (wynik < 0)
    puts("NIE");
  else
    printf("%d\n", wynik);
  return 0;
}
