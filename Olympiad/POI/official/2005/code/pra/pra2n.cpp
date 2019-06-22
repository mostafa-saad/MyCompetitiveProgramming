/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PRA (Prawoskrêtny wielb³ad)                    *
 *   Plik:                pra2n.cpp                                      *
 *   Autor:               Karol Cwalina                                  *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                        Rozwiazanie asymptotycznie szybsze od          *
 *                        autorskiego: O(n^2). Silnie wykorzystuje       *
 *                        ograniczenie na wielkosc wspolrzednych.        *
 *                        Sortowanie wektorow przez zliczanie w oparciu  *
 *                        o wczesniej policzone katy; Nieoszczedna, tzn. *
 *                        nie odrzuca nieprzydatnych punktow z sortowania*
 *                                                                       *
 *************************************************************************/

#include <iostream>
#include <cstdlib>

using namespace std;

inline int MAX(int a, int b)
{
  return (a > b ? a : b);
}                               // w wersji O(n^3) to jest makro -

                    // - tutaj w linii 165. to by nie wyszlo, bo dwukrotnie wykonalibysmy a++
inline int SGN(long long a)
{
  return (a == 0 ? 0 : (a < 0 ? -1 : 1));
}

#define VEC(a,b) (pun[(b)]-pun[(a)])

const int MaxN = 1000, Size = 19, Zakres = 1 << Size, Inf = 1234567890;
const long long Duza = 20000ll * 1000000ll; //20*10^9, wystarczy, zeby Duza > (4*MaxWspolrzedna)^2, gdzie MaxWspolrzedna = 16000

struct Pkt {
  long long x, y;

  Pkt(long long xx = 0, long long yy = 0):x(xx), y(yy) {
  }

  Pkt operator-(const Pkt & b) const {
    return Pkt(x - b.x, y - b.y);
  }

  bool operator<=(const Pkt & b) const {
    return (x * b.y - y * b.x <= 0);
  }

  //A < B <=> wektor A lezy na lewo od B (zaczepione w (0,0)); = <=> wektory sa rownolegle
  void wczytaj(void) {
    cin >> x >> y;
  }

  long long kat(void);          //kat to rosnaca funkcja kata skierowanego utworzonego pomiedzy polprosta OY a wketorem (x,y)
};

long long Pkt::kat(void)
{
  if (x >= 0)
    return (y >
            0 ? (Duza * x) / (x + y) : 2 * Duza - (Duza * x) / (x - y));
  else
    return (y <
            0 ? 2 * Duza + (Duza * x) / (x + y) : 4 * Duza -
            (Duza * x) / (x - y));
}

struct Oaza {
  int sas[MaxN];                //lista sasiadow, tzn. tych oaz z ktorych mozna przyjsc do tej Oazy i tych, do ktorych z niej mozna sie wybrac
  int ile_pop, ile_nast;        //ilu sasiadow poprzedza Oaze w porzadku zegarowym, a ilu jest po niej

Oaza(int ip = 0, int in = 0):ile_pop(ip), ile_nast(in) {
}};

Pkt pun[MaxN];
Oaza *oaz = new Oaza[MaxN];

int *ile[MaxN];                 //ile - tablica wartosci ile[a,b] (patrz opracowanie)
int n, odp = 1;                 //n - liczba oaz, odp - odpowiedz

struct Para {                   //obiekty sortowane przez zliczanie
  long long kat;                //kat odpowiadajacy obiektowi, wzgledem niego sortujemy
  int poz, kto;                 //poz - na liscie ktorej z oaz w oaz[?].sas znajduje sie oaza reprezentowana przez kto
};

inline int cmpPkt(const void *e1, const void *e2)
{
/* Porownuje w "porzadku zegarowym" wzgledem pun[1] (1-szej oazy, do ktorej mamy dojsc), traktujac punkty jak wektory zaczepione w (0,0) */
  Pkt *p1 = (Pkt *) e1, *p2 = (Pkt *) e2;
  long long k1 = (4 * Duza + p1->kat() - pun[1].kat()) % (4 * Duza),  //dzieki temu kat jest liczba z przedzialu [0,4*Duza)
      k2 = (4 * Duza + p2->kat() - pun[1].kat()) % (4 * Duza);
  return SGN(k1 - k2);          //mozna by zrezygnowac z sgn gdyby nie to, ze funkcja porownujaca musi zwracac int
}

//Pomocnicze struktury uzywane w sortowaniu przez zliczanie
int *silet = new int[Zakres];   //silet - w tej tablicy zliczamy liczbe wystapien danego obiektu
int sile;                       //sile - liczba obiektow do posortowania przez zliczanie
Para *sor1 = new Para[MaxN * MaxN], *sor2 = new Para[MaxN * MaxN];  //tablice do trzymania sortowanych obiektow

void dodajDoSort(int ss, Pkt wzgledem, int co[], int ile)
{
/* Dodaje oazy z tablicy co do danych ktore zostana posortowane przez zliczanie
   ss - srodek sortowania, tzn. nr punktu w ktorym tymczasowo zaczepiamy srodek ukladu wspolrzednych */
  long long kz;                 //kz - kat zwrocony przez wektor wzgeldem ktorego sortujemy, tzn. odpowiadajaacy 12-ej w "porzadku zegarowym"
  kz = wzgledem.kat();
  for (int i = 0; i < ile; ++i) {
    sor1[sile].kat = (4 * Duza + VEC(ss, co[i]).kat() - kz) % (4 * Duza);
    sor1[sile].kto = co[i];
    sor1[sile++].poz = ss;
  }
}

void Sort(void)
{
  /* Sortuje przez zliczanie (w dwoch fazach), a nastepnie rozrzuca wyniki do odpowiednich tablic oaz[].sas --- robi to korzystajac z pol poz i kto sortowanych obiektow */
  static int ktory_raz = 0;
  ++ktory_raz;

  // I faza
  for (int i = 0; i < Zakres; ++i)
    silet[i] = 0;
  for (int i = 0; i < sile; ++i)
    ++silet[sor1[i].kat & (Zakres - 1)];
  --silet[0];
  for (int i = 1; i < Zakres; ++i)
    silet[i] += silet[i - 1];
  for (int i = sile - 1; i >= 0; --i)
    sor2[silet[sor1[i].kat & (Zakres - 1)]--] = sor1[i];

  // II faza
  for (int i = 0; i < Zakres; ++i)
    silet[i] = 0;
  for (int i = 0; i < sile; ++i)
    ++silet[sor2[i].kat >> Size];
  --silet[0];
  for (int i = 1; i < Zakres; ++i)
    silet[i] += silet[i - 1];
  for (int i = sile - 1; i >= 0; --i)
    sor1[silet[sor2[i].kat >> Size]--] = sor2[i];

  //rozrzucamy
  if (ktory_raz == 1) {         //1. sortowanie, czyli oazy poprzedzajace
    for (int b = 1; b < n; ++b)
      oaz[b].ile_pop = 0;
    for (int i = 0; i < sile; ++i)
      oaz[sor1[i].poz].sas[oaz[sor1[i].poz].ile_pop++] = sor1[i].kto;
  }
  else {                        //2. sortowanie, czyli nastepne oazy
    for (int b = 1; b < n; ++b)
      oaz[b].ile_nast = 0;
    for (int i = 0; i < sile; ++i)
      oaz[sor1[i].poz].sas[oaz[sor1[i].poz].ile_pop +
                           oaz[sor1[i].poz].ile_nast++] = sor1[i].kto;
  }
}

void SortujListy(void)
{
/* Buduje listy oaz[].sas i sortuje je w porzadku zegarowym (kazda z czesci: oazy poprzedzajace i nastepne osobno);
 * porzadek sortowan jest taki, by dla a < ile_pop i ile_pop <= c1 < c2 < ile_pop+ile_nast zachodzilo: w_prawo (a,b,c1) => w_prawo(a,b,c2) */
  sile = 0;
  for (int b = 1; b < n; ++b) {
    oaz[b].ile_pop = 0;
    for (int a = 0; a < b; ++a)
      oaz[b].sas[oaz[b].ile_pop++] = a;
    dodajDoSort(b, VEC(b, 0), oaz[b].sas, oaz[b].ile_pop);
  }
  Sort();

  sile = 0;
  for (int b = 1; b < n; ++b) {
    oaz[b].ile_nast = 0;
    for (int c = b + 1; c < n; ++c)
      oaz[b].sas[oaz[b].ile_pop + oaz[b].ile_nast++] = c;
    dodajDoSort(b, VEC(0, b), oaz[b].sas + oaz[b].ile_pop,
                oaz[b].ile_nast);
  }
  Sort();
}

void Sortuj(void)
{
/* Wykonuje dwa sortowania: wszystkich oaz oraz list sasiadow kazdej z oaz w "porzadku zegarowym" */
  for (int i = n - 1; i >= 0; --i)
    pun[i] = pun[i] - pun[0];

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
