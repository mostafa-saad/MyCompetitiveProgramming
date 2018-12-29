/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PRA (Prawoskrêtny wielb³ad)                    *
 *   Plik:                pra1n.cpp                                      *
 *   Autor:               Karol Cwalina                                  *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                        Z³o¿onosæ czasowa: O(n^2*logn)                 *
 *                        Porownywanie wektorow poprzez liczenie sinusa  *
 *                        kata miedzy nimi. Nieoszczedna, tzn. nie       *
 *                        odrzuca nieprzydatnych punktow z sortowania    *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <cstdlib>

using namespace std;

inline int MAX(int a, int b)
{
  return (a > b ? a : b);
}                               // w wersji O(n^3) to jest makro -

                    // - tutaj w linii 115. to by nie wyszlo, bo dwukrotnie wykonalibysmy a++
inline int SGN(long long a)
{
  return (a == 0 ? 0 : (a < 0 ? -1 : 1));
}

#define VEC(a,b) (pun[(b)]-pun[(a)])

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
    if (x * ks.x + y * ks.y >= 0)
      return 0;
    else
      return 2;
  }
  if ((*this) <= ks)
    return 3;
  else
    return 1;
}

struct Oaza {
  int sas[MaxN];                //lista sasiadow, tzn. tych oaz z ktorych mozna przyjsc do tej Oazy i tych, do ktorych z niej mozna sie wybrac
  int ile_pop, ile_nast;        //ilu sasiadow poprzedza Oaze w porzadku zegarowym, a ilu jest po niej

Oaza(int ip = 0, int in = 0):ile_pop(ip), ile_nast(in) {
}};

Pkt pun[MaxN];                  //pun - tablica punktow reprezentujacych oazy
Oaza *oaz = new Oaza[MaxN];     //oaz - tablica oaz

int ss;                         //ss - srodek sortowania, tzn. nr punktu w ktorym zaczepiamy srodek ukladu wspolrzednych w SortujListy
Pkt kz;                         //kz - kat zwrocony przez wektor wzgeldem ktorego sortujemy, tzn. odpowiadajaacy 12-ej w "porzadku zegarowym"

int *ile[MaxN];                 //ile - tablica wartosci ile[a,b] (patrz opracowanie)
int n, odp = 1;                 //n - liczba oaz, odp - odpowiedz

inline int cmpPkt(const void *e1, const void *e2)
{
/* Porownuje w "porzadku zegarowym" wzgledem wektora kz, traktujac punkty jako wektory zaczepione w (0,0) */
  Pkt *p1 = (Pkt *) e1, *p2 = (Pkt *) e2;
  int s1 = p1->strefa(kz), s2 = p2->strefa(kz);

  if (s1 != s2)
    return s1 - s2;
  else
    return SGN((*p1) * (*p2));  //mozna by zrezygnowac z sgn gdyby nie to, ze funkcja porownujaca musi zwracac int
}

inline int cmpSL(const void *e1, const void *e2)
{
/* Porownuje w "porzadku zegarowym" wzgledem wektora kz i przy umieszczeniu poczatku wspolrzednych w ss */
  int o1 = *((int *) e1), o2 = *((int *) e2);
  Pkt p1 = VEC(ss, o1), p2 = VEC(ss, o2);
  return cmpPkt(&p1, &p2);
}

void SortujListy(void)
{
/* Buduje listy oaz[].sas i sortuje je w porzadku zegarowym (kazda z czesci: oazy poprzedzajace i nastepne osobno);
 * porzadek sortowan jest taki, by dla a < ile_pop i ile_pop <= c1 < c2 < ile_pop+ile_nast zachodzilo: w_prawo (a,b,c1) => w_prawo(a,b,c2) */
  for (int b = 1; b < n; ++b) {
    for (int a = 0; a < b; ++a)
      oaz[b].sas[oaz[b].ile_pop++] = a;
    for (int c = b + 1; c < n; ++c)
      oaz[b].sas[oaz[b].ile_pop + oaz[b].ile_nast++] = c;

    ss = b;
    kz = VEC(b, 0);
    qsort(oaz[b].sas, oaz[b].ile_pop, sizeof(int), cmpSL);

    kz = VEC(0, b);
    qsort(oaz[b].sas + oaz[b].ile_pop, oaz[b].ile_nast, sizeof(int),
          cmpSL);
  }
}

void Sortuj(void)
{
/* Wykonuje dwa sortowania: wszystkich oaz oraz list sasiadow kazdej z oaz w "porzadku zegarowym" */
  for (int i = n - 1; i >= 0; --i)
    pun[i] = pun[i] - pun[0];
  kz = pun[1];

  qsort(pun + 2, n - 2, sizeof(Pkt), cmpPkt);
  SortujListy();
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
  for (int b = 1; b < n; ++b) {
    int a = 0, c = oaz[b].ile_pop, max = -Inf;
    while (c < oaz[b].ile_pop + oaz[b].ile_nast) {
      while ((a < oaz[b].ile_pop)
             && w_prawo(oaz[b].sas[a], b, oaz[b].sas[c]))
        max = MAX(max, ile[oaz[b].sas[a++]][b]);
      odp = MAX(odp, ile[b][oaz[b].sas[c]] =
                MAX(ile[b][oaz[b].sas[c]], 1 + max));
      ++c;
    }
  }
}

int main(void)
{
  cin >> n;
  for (int i = 0; i < n; ++i)
    pun[i].wczytaj();

  for (int i = 0; i < n; ++i) {
    ile[i] = new int[n];        //tworzenie tablicy dopiero teraz wynika z tego, ze DJGPP wkompilowuje tablice w kod, co powoduje powsawanie kodu wielkosc paru MB; g++ jest pozbawione tej wady
    for (int j = 0; j < n; ++j)
      ile[i][j] = -Inf;
  }

  Sortuj();
  Licz();
  cout << odp << endl;

  return 0;
}
