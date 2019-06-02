/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PRA (Prawoskrêtny wielb³ad)                    *
 *   Plik:                prab3.cpp                                      *
 *   Autor:               Karol Cwalina                                  *
 *   Opis:                Rozwiazanie niepoprawne                        *
 *                        Zle zaimplementowana wersja                    *
 *                        rozwiazania wzorcowego: O(n^2*logn)            *
 *                        Zle zaimplementowana funkcja w_prawo()         *
 *                        + dopuszcza drogi 0-x-... (x > 1)              *
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <cstdlib>

using namespace std;

inline int MAX (int a, int b) { return (a > b ? a : b); } // w wersji O(n^3) to jest makro -
                    // - tutaj w linii 114. to by nie wyszlo, bo dwukrotnie wykonalibysmy a++
inline int SGN (long long a) {
  return (a == 0 ? 0 : (a < 0 ? -1 : 1));
}

#define VEC(a,b) (pun[(b)]-pun[(a)])

const int MaxN = 1000,
          Inf = 1234567890;
const long long Duza = 20000ll*1000000ll; //20*10^9, wystarczy, zeby Duza > (4*MaxWspolrzedna)^2, gdzie MaxWspolrzedna = 16000

struct Pkt {
  long long x, y;

  Pkt (long long xx = 0, long long yy = 0) : x(xx), y(yy) { }
  Pkt       operator-  (const Pkt &b) const { return Pkt(x-b.x, y-b.y); }
  bool      operator<= (const Pkt &b) const { return (x*b.y-y*b.x <= 0); }  //A < B <=> wektor A lezy na lewo od B (zaczepione w (0,0)); = <=> wektory sa rownolegle
  void wczytaj (void) { cin >> x >> y; }
  long long kat (void);  //kat to rosnaca funkcja kata skierowanego utworzonego pomiedzy polprosta OY a wketorem (x,y)
};

long long Pkt::kat (void) {
  if (x >= 0) return (y > 0 ? (Duza*x)/(x+y) : 2*Duza-(Duza*x)/(x-y));
  else return (y < 0 ? 2*Duza+(Duza*x)/(x+y) : 4*Duza-(Duza*x)/(x-y));
}

struct Oaza {
  int sas[MaxN];  //lista sasiadow, tzn. tych oaz z ktorych mozna przyjsc do tej Oazy i tych, do ktorych z niej mozna sie wybrac
  int ile_pop, ile_nast;  //ilu sasiadow poprzedza Oaze w porzadku zegarowym, a ilu jest po niej

  Oaza (int ip = 0, int in = 0) : ile_pop(ip), ile_nast(in) { }
};

Pkt pun[MaxN]; //pun - tablica punktow reprezentujacych oazy
Oaza *oaz = new Oaza[MaxN]; //oaz - tablica oaz

int* ile[MaxN]; //ile - tablica wartosci ile[a,b] (patrz opracowanie)
int n, odp = 1;  //n - liczba oaz, odp - odpowiedz

inline int cmpPkt (const void *e1, const void *e2) {
/* Porownuje w "porzadku zegarowym" wzgledem pun[1] (1-szej oazy, do ktorej mamy dojsc), traktujac punkty jak wektory zaczepione w (0,0) */
  Pkt *p1 = (Pkt*)e1, *p2 = (Pkt*)e2;
  long long k1 = (4*Duza + p1->kat() - pun[1].kat()) % (4*Duza), //dzieki temu kat jest liczba z przedzialu [0,4*Duza)
            k2 = (4*Duza + p2->kat() - pun[1].kat()) % (4*Duza);
  return SGN(k1-k2); //mozna by zrezygnowac z sgn gdyby nie to, ze funkcja porownujaca musi zwracac int
}

long long kat[MaxN]; //kat - stablicowane katy wykorzystywane w sortWzgledemPoKacie (stablicowanie pozwala uniknac wielokrotnego wyliczania wartosci i znaczaco przyspiesza --- patrz pra1.cpp)

inline int cmpWPK (const void *e1, const void *e2) {
/* Porownuje w "porzadku zegarowym", na podstawie katow stablicowanych w tablicy kat */
  int o1 = *((int *)e1), o2 = *((int *)e2);
  return SGN(kat[o1]-kat[o2]); //mozna by zrezygnowac z sgn gdyby nie to, ze funkcja porownujaca musi zwracac int
}

void sortWzgledemPoKacie (int ss, Pkt wzgledem, int co[], int ile) {
/* Sortuje przekazana tablice w "porzadku zegarowym" wzgledem wektora wzgledem, odpowiadajacemu 12-ej w tym porzadku
   ss - srodek sortowania, tzn. nr punktu w ktorym tymczasowo zaczepiamy srodek ukladu wspolrzednych */
  long long kz; //kz - kat zwrocony przez wektor wzgledem ktorego sortujemy
  kz = wzgledem.kat();
  for (int i = 0; i < ile; ++i)
    kat[co[i]] = (4*Duza+VEC(ss,co[i]).kat()-kz) % (4*Duza);  //dzieki temu kat jest liczba z przedzialu [0,4*Duza)
  qsort(co, ile, sizeof(int), cmpWPK);
}

void SortujListy (void) {
/* Buduje listy oaz[].sas i sortuje je w porzadku zegarowym (kazda z czesci: oazy poprzedzajace i nastepne osobno);
 * porzadek sortowan jest taki, by dla a < ile_pop i ile_pop <= c1 < c2 < ile_pop+ile_nast zachodzilo: w_prawo (a,b,c1) => w_prawo(a,b,c2) */
  for (int b = 1; b < n; ++b) {
    for (int a = 0; a < b; ++a) oaz[b].sas[oaz[b].ile_pop++] = a;
    for (int c = b+1; c < n; ++c) oaz[b].sas[oaz[b].ile_pop+oaz[b].ile_nast++] = c;

    sortWzgledemPoKacie(b, VEC(b,0), oaz[b].sas, oaz[b].ile_pop);
    sortWzgledemPoKacie(b, VEC(0,b), oaz[b].sas+oaz[b].ile_pop, oaz[b].ile_nast);
  }
}

void Sortuj (void) {
/* Wykonuje dwa sortowania: wszystkich oaz oraz list sasiadow kazdej z oaz w "porzadku zegarowym" */
  for (int i = n-1; i >= 0; --i) pun[i] = pun[i]-pun[0];

  qsort(pun+2, n-2, sizeof(Pkt), cmpPkt);
  SortujListy();
}

//ZLE !!!!
inline bool w_prawo (int a, int b, int c) {
  return (VEC(a,b) <= VEC(b,c)); //powinno byc (VEC(a,b) <= VEC(b,c)) && (VEC(a,b) <= VEC(a,0)) && (VEC(b,c) <= VEC(b,0))
}

void Licz (void) {
/* Wylicza liczby ile[a,b] */
  for (int b = 1; b < n; ++b) {
    int a = 0, c = oaz[b].ile_pop, max = -Inf;
    ile[0][b] = 1;
    while (c < oaz[b].ile_pop+oaz[b].ile_nast) {
      while ((a < oaz[b].ile_pop) && w_prawo(oaz[b].sas[a],b,oaz[b].sas[c]))
        max = MAX(max, ile[oaz[b].sas[a++]][b]);
      odp = MAX(odp, ile[b][oaz[b].sas[c]] = MAX(ile[b][oaz[b].sas[c]], 1+max));
      ++c;
    }
  }
}

int main (void) {
  cin >> n;
  for (int i = 0; i < n; ++i) pun[i].wczytaj();

  for (int i = 0; i < n; ++i) {
    ile[i] = new int[n]; //tworzenie tablicy dopiero teraz wynika z tego, ze DJGPP wkompilowuje tablice w kod, co powoduje powsawanie kodu wielkosc paru MB; g++ jest pozbawione tej wady
    for (int j = 0; j < n; ++j) ile[i][j] = -Inf;
  }

  Sortuj();
  Licz();
  cout << odp << endl;

  return 0;
}
