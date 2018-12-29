/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PRA (Prawoskrêtny wielb³ad)                    *
 *   Plik:                pra3n.cpp                                      *
 *   Autor:               Karol Cwalina                                  *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                        Z³o¿onosæ czasowa: O(n^3)                      *
 *                        Zero optymalizacji                             *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <cstdlib>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define VEC(a,b) (pun[(b)]-pun[(a)])

inline int SGN(long long a)
{
  return (a == 0 ? 0 : (a < 0 ? -1 : 1));
}

using namespace std;

const int MaxN = 1000, Inf = 1234567890;

struct Pkt {
  long long x, y;

  Pkt(long long xx = 0, long long yy = 0):x(xx), y(yy) {
  }

  Pkt operator-(const Pkt & b) const {
    return Pkt(x - b.x, y - b.y);
  }

  long long operator*(const Pkt & b) const {
    return x * b.y - y * b.x;
  }

  //iloczyn wektorowy; A*B < 0 <=> wektor A lezy na lewo od B (zaczepione w (0,0)); =0 <=> wektory sa rownolegle
  bool operator<(const Pkt & b) const {
    return (x * b.y - y * b.x < 0);
  }

  //A < B <=> wektor A lezy na lewo od B (zaczepione w (0,0))
  bool operator<=(const Pkt & b) const {
    return (x * b.y - y * b.x <= 0);
  }

  //A < B <=> wektor A lezy na lewo od B (zaczepione w (0,0)); = <=> wektory sa rownolegle
  bool operator||(const Pkt & b) const {
    return (x * b.y - y * b.x == 0);
  }

  //rownoleglosc
  void wczytaj(void) {
    cin >> x >> y;
  }
  int strefa(const Pkt & ks) const; //mowi, w ktorej "strefie" wzgledem wektora ks lezy punkt: na polprostej (0,0),ks -> 0; na prawo od tej polprostej -> 1; na polprostej (0,0),(-ks) -> 2; na lewo od polprostej (0,0),ks -> 3
};

int Pkt::strefa(const Pkt & ks) const
{
  if ((*this) || ks) {
    if (x * ks.x + y * ks.y > 0)
      return 0;
    else
      return 2;
  }
  if ((*this) < ks)
    return 3;
  else
    return 1;
}

Pkt pun[MaxN];                  //pun - tablica punktow reprezentujacych oazy
int *ile[MaxN];                 //ile - tablica wartosci ile[a,b] (patrz opracowanie)
int n, odp = 1;                 //n - liczba oaz, odp - odpowiedz

inline int cmpPkt(const void *e1, const void *e2)
{
/* Porownuje w "porzadku zegarowym" wzgledem wektora pun[1], traktujac punkty jako wektory zaczepione w (0,0) */
  Pkt *p1 = (Pkt *) e1, *p2 = (Pkt *) e2;
  int s1 = p1->strefa(pun[1]), s2 = p2->strefa(pun[1]);

  if (s1 != s2)
    return s1 - s2;
  else
    return SGN((*p1) * (*p2));  //mozna by zrezygnowac z sgn gdyby nie to, ze funkcja porownujaca musi zwracac int
}

void Sortuj(void)
{
/* Wykonuje sortowanie oaz w "porzadku zegarowym" */
  for (int i = n - 1; i >= 0; --i)
    pun[i] = pun[i] - pun[0];
  qsort(pun + 2, n - 2, sizeof(Pkt), cmpPkt);
}

inline bool w_prawo(int a, int b, int c)
{
/* Sprawdza, czy zakret pun[a],pun[b],pun[c] jest zakretem w prawo */
  return (VEC(a, b) <= VEC(b, c)) && (VEC(a, b) <= VEC(a, 0)) && (VEC(b, c) <= VEC(b, 0));  // dwa ostatnie warunki odpowiadaja za to, ze nie przecinamy naszej trasy
}

void Licz(void)
{
/* Wylicza liczby ile[a,b] */
  ile[0][1] = 1;
  for (int c = 1; c < n; ++c) {
    for (int b = 1; b < c; ++b) {
      for (int a = 0; a < b; ++a)
        if (w_prawo(a, b, c))
          ile[b][c] = MAX(ile[b][c], 1 + ile[a][b]);
      odp = MAX(odp, ile[b][c]);
    }
  }
}

int main(void)
{
  cin >> n;
  for (int i = 0; i < n; ++i)
    pun[i].wczytaj();

  for (int i = 0; i < n; ++i) {
    ile[i] = new int[n];
    for (int j = 0; j < n; ++j)
      ile[i][j] = -Inf;
  }

  Sortuj();
  Licz();
  cout << odp << endl;

  return 0;
}
