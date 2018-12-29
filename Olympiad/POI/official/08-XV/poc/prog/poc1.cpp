/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Pociagi (POC)                                             *
 *   Plik:     poc1.cpp                                                  *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Alternatywna implementacja rozwiazania wzorcowego.        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <map>
#include <vector>
using namespace std;

#define MAX_N 1000
#define MAX_L 100
#define MAX_M 100000
/* maksymalna liczba zbiorow */
#define MAX_ZB (2 * MAX_M + MAX_N)

/* 15-cyfrowa liczba pierwsza */
#define HASZ 956985070659067LL

/* Operacje na zbiorze */
#define DODAJ 1
#define USUN -1


struct zbior
{
  int czas;
  int zbior;
};
vector<zbior> poc[MAX_N];

struct licznosc
{
  int czas;
  int ile;
};
vector<licznosc> zb[MAX_ZB];

int n, l, m;
char pociagi[MAX_N][MAX_L + 1];
long long hasz[MAX_N];
int map_hasz[MAX_N];
long long potegi[MAX_L]; /* potegi 26 modulo HASZ */
map<long long, int> mapa; /* mapa z haszy w male liczby */
int numer; /* wartosc najwiekszego numeru hasza */

/* Odczyt danych */
void odczyt()
{
  scanf("%d%d%d", &n, &l, &m);
  for (int i = 0; i < n; i++)
    scanf("%s", pociagi[i]);
}

/* Oblicza map_hasz[i] na podstawie hasz[i]. */
void ustaw_map_hasz(int p)
{
  if (mapa.find(hasz[p]) == mapa.end())
    map_hasz[p] = mapa[hasz[p]] = numer++;
  else
    map_hasz[p] = mapa[hasz[p]];
}

/* Modyfikuje zbior, dodajac lub usuwajac z niego element. */
void zmien_zbior(int zbior, int krok, int oper)
{
  if (!zb[zbior].empty() && zb[zbior].back().czas == krok)
    zb[zbior].back().ile += oper;
  else
  {
    licznosc li;
    li.czas = krok;
    li.ile = (zb[zbior].empty() ? 0 : zb[zbior].back().ile) + oper;
    zb[zbior].push_back(li);
  }
}

/* Oblicza poczatkowe hasze pociagow. */
void licz_hasze()
{
  zbior z;
  
  numer = 0;
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < l; j++)
      hasz[i] = (26LL * hasz[i] + (pociagi[i][j] - 'a')) % HASZ;
    ustaw_map_hasz(i);

    /* Wypelniamy tablice poc */
    z.czas = 0;
    z.zbior = map_hasz[i];
    poc[i].push_back(z);

    /* Wypelniamy tablice zb */
    zmien_zbior(map_hasz[i], 0, DODAJ);
  }
  
  potegi[l - 1] = 1LL;
  for (int i = l - 2; i >= 0; i--)
    potegi[i] = (26LL * potegi[i + 1]) % HASZ;
}

/* Ustawia w w-tym wagonie p-tego pociagu
 * w krok-tym kroku wagon o kolorze wag. */
void ustaw(int p, int w, char wag, int krok)
{
  zbior z;
  
  hasz[p] += (long long)(wag - pociagi[p][w]) * potegi[w];
  hasz[p] = (hasz[p] % HASZ + HASZ) % HASZ;
  pociagi[p][w] = wag;
  ustaw_map_hasz(p);
  
  z.czas = krok;
  z.zbior = map_hasz[p];
  poc[p].push_back(z);
}

/* Symulacja przestawiania wagonow. */
void symulacja()
{
  int p1, w1, p2, w2;
  for (int krok = 1; krok <= m; krok++)
  {
    scanf("%d%d%d%d", &p1, &w1, &p2, &w2);
    p1--; w1--; p2--; w2--;
    char wag1 = pociagi[p1][w1], wag2 = pociagi[p2][w2];
    zmien_zbior(map_hasz[p1], krok, USUN);
    if (p1 != p2)
      zmien_zbior(map_hasz[p2], krok, USUN);
    ustaw(p1, w1, wag2, krok);
    ustaw(p2, w2, wag1, krok);
    zmien_zbior(map_hasz[p1], krok, DODAJ);
    if (p1 != p2)
      zmien_zbior(map_hasz[p2], krok, DODAJ);
  }
}

#define KORZEN 1

struct wierzch
{
  int l, r;
  int mx;
};
vector<wierzch> drzewa[MAX_ZB];

/* Budowanie drzew przedzialowych dla zbiorow. */
void buduj_drzewa()
{
  for (int i = 0; i < numer; i++)
  {
    int wlk = 1;
    while (wlk < (int)zb[i].size())
      wlk *= 2;
    drzewa[i].resize(wlk * 2);
    
    /* Liscie faktyczne */
    for (int j = wlk; j < wlk + (int)zb[i].size(); j++)
    {
      drzewa[i][j].l = drzewa[i][j].r = zb[i][j - wlk].czas;
      drzewa[i][j].mx = zb[i][j - wlk].ile;
    }
    /* Liscie sztuczne, nic niewnoszace */
    for (int j = wlk + (int)zb[i].size(); j < 2 * wlk; j++)
    {
      drzewa[i][j].l = m;
      drzewa[i][j].r = m;
      drzewa[i][j].mx = 1;
    }

    /* Wezly wewnetrzne */
    for (int j = wlk - 1; j > 0; j--)
    {
      drzewa[i][j].l = drzewa[i][2 * j].l;
      drzewa[i][j].r = drzewa[i][2 * j + 1].r;
      drzewa[i][j].mx = max(drzewa[i][2 * j].mx, drzewa[i][2 * j + 1].mx);
    }
  }
}

/* Zapytanie o maksimum z wartosci w przedziale [a,b]
 * w drzewie przedzialowym drzewa[zbior]; jestesmy aktualnie w wezle
 * v. */
int zapyt(int zbior, int a, int b, int v)
{
  if (drzewa[zbior][v].l >= a && drzewa[zbior][v].r <= b)
    return drzewa[zbior][v].mx;
  int w = 0;
  if (2 * v < (int)drzewa[zbior].size() && drzewa[zbior][2 * v].r >= a)
    w = max(w, zapyt(zbior, a, b, 2 * v));
  if (2 * v + 1 < (int)drzewa[zbior].size() && drzewa[zbior][2 * v + 1].l <= b)
    w = max(w, zapyt(zbior, a, b, 2 * v + 1));
  return w;
}

/* Liczenie wynikow dla wszystkich pociagow. */
void policz_wyniki()
{
  zbior z;
  z.czas = m + 1; z.zbior = -1;
  for (int i = 0; i < n; i++)
  {
    poc[i].push_back(z); /* straznik */
    int wyn = 1;
    for (int j = 0; j < (int)poc[i].size() - 1; j++)
      wyn = max(wyn, zapyt(poc[i][j].zbior, poc[i][j].czas,
                           poc[i][j + 1].czas - 1, KORZEN));
    printf("%d\n", wyn);
  }
}

int main()
{
  odczyt();
  licz_hasze();
  symulacja();
  buduj_drzewa();
  policz_wyniki();
  return 0;
}
