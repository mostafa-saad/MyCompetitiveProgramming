/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: PUN (Punkty)                                   *
 *   Plik:                pun1.cpp                                       *
 *   Autor:               Arkadiusz Paterek                              *
 *   Opis:                Rozwiazanie alternatywne                       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

#define REP(a,n) for(int a=0; a<(n); ++a)
#define FOR(a,b,c) for(int a=(b); a<=(c); ++a)
#define FORD(a,b,c) for(int a=(b); a>=(c); --a)

using namespace std;

////////////////////////

#define Liczba double

struct Para {
  Liczba x, y;
  Liczba & operator[] (int n) {
    return n ? y : x;
  }
  int typ() const {
    if (y == 0 && x == 0)
      return 6;
    if (y == 0 && x > 0)
      return 1;
    if (y > 0)
      return 2;
    if (y == 0 && x < 0)
      return 3;
    return 4;                   // y<0
  }
  Liczba diff(const Para & a) const {
    return x * a.y - y * a.x;
  }
  bool operator<(const Para & a) const {
    if (typ() < a.typ())
      return true;
    if (typ() > a.typ())
      return false;
    Liczba il_wek = diff(a);
    if (il_wek > 0)
       return true;
    if (il_wek < 0)
       return false;
     return x * x + y * y < a.x * a.x + a.y * a.y;
  }
  Liczba dlug() const {
    return x * x + y * y;
}};

////////////////////////


// wczytywanie punktow
int czyt(Para * pun)
{
  int K;
  scanf("%d", &K);
  REP(a, K) {
    int x, y;
    scanf("%d%d", &x, &y);
    pun[a].x = x;
    pun[a].y = y;
  }
  return K;
}

// przeksztalca "pun" tak, aby srodek ciezkosci byl w (0,0), moze przeskalowac
void wysrodkuj(Para * pun, int K)
{
  REP(xy, 2) {
    Liczba suma = 0;
    REP(a, K)
        suma += pun[a][xy];
    REP(a, K)
        pun[a][xy] = pun[a][xy] * K - suma;
  }
}

// sortuje "pun" po wspolrzednych katowych, ewentualnie po odleglosci od (0,0)
// punkt (0,0) wyladuje na koncu
void sortuj(Para * pun, int K)
{
//  fprintf(stderr, "start\n");
  sort(pun, pun + K);
//  fprintf(stderr, "stop\n");
}


// zwraca odleglosc od (0,0) do najdalszego punktu
Liczba licz_skale(const Para * pun, int K)
{
  Liczba m = 0;
  REP(a, K) {
    Liczba w = pun[a].dlug();
    if (m < w)
      m = w;
  }
  return m;
}

// czy ostatnia z liczb to (0,0)
bool czy_zero(const Para * pun, int K)
{
  return pun[K - 1].x == 0 && pun[K - 1].y == 0;
}

// tworzy tablice zawierajaca pare (odleglosc od srodka, kat do nastepnego punktu)
// na podstawie wysrodkowanych i posortowanych punktow, nie moze byc punktu (0,0)
void licz_roznice(const Para * pun, pair < Liczba, Liczba > *tab, int K)
{
  REP(a, K)
      tab[a] = make_pair(pun[a].dlug(), pun[(a + 1) % K].diff(pun[a]));
}

// tworzy tablice "p" dla "tab" wedlug KMP
void licz_p(const pair < Liczba, Liczba > *tab, int *p, int K)
{
  p[0] = 0;
  int k = 0;
  FOR(q, 1, 2 * K - 1) {
    while (k > 0 && tab[k] != tab[q])
      k = p[k - 1];
    if (tab[k] == tab[q])
      ++k;
    p[q] = k;
  }
}

// przeskalowuje punkty[0] i punkty[1] do przesk[0] i przesk[1] tak, 
// ze najdluzsze odcinki w obu beda mialy ta sama dlugosc
void przeskaluj(const pair < Liczba, Liczba > *tab, pair < Liczba,
                Liczba > *tab2, int K, Liczba skala)
{
  REP(a, K) {
    tab2[a].first = tab[a].first * skala;
    tab2[a].second = tab[a].second * skala;
  }
}

// wyszukiwanie KMP "text" we "wzorzec" wedlug "p"
bool wyszukaj(const pair < Liczba, Liczba > *wzorzec, int KD,
              const pair < Liczba, Liczba > *text, const int *p, int K)
{
  int q = 0;
  if (q == K)
    return true;
  REP(i, KD) {
    while (q > 0 && text[q] != wzorzec[i])
      q = p[q - 1];
    if (text[q] == wzorzec[i])
      ++q;                      //printf("+");}
    if (q == K)
      return true;
  }
//  printf("\n");
  return false;
}

void odbij(Para * pun, int K)
{
  REP(a, K)
      pun[a].y = Liczba(0) - pun[a].y;
}

static pair < Liczba, Liczba > wzorzec[50000], wzorzec_sk[50000];

static pair < Liczba, Liczba > text[25000];
static int p[25000];

bool szukaj(const pair < Liczba, Liczba > *wzor, int KD, const Para * pun,
            int K, const Liczba & skala)
{
  licz_roznice(pun, text, K);
  przeskaluj(text, text, K, skala);
  licz_p(text, p, K);
  return wyszukaj(wzor, KD, text, p, K);
}

static Para punkty[2][25000];

int main()
{
  static Liczba skala[2];
  int K = czyt(punkty[0]);
  wysrodkuj(punkty[0], K);
  sortuj(punkty[0], K);
  skala[0] = licz_skale(punkty[0], K);
  bool zero = czy_zero(punkty[0], K);
  int Kw = K - (zero ? 1 : 0);
  licz_roznice(punkty[0], wzorzec, Kw);
  REP(a, Kw) wzorzec[a + Kw] = wzorzec[a];
  int N;
  scanf("%d", &N);
  FOR(a, 1, N) {
    int K2 = czyt(punkty[1]);
    if (K2 == K) {
      wysrodkuj(punkty[1], K);
      sortuj(punkty[1], K);
      bool zero2 = czy_zero(punkty[1], K);
      if (zero2 == zero) {
        skala[1] = licz_skale(punkty[1], Kw);
        przeskaluj(wzorzec, wzorzec_sk, Kw * 2, skala[1]);

        if (szukaj(wzorzec_sk, 2 * Kw, punkty[1], Kw, skala[0])) {
          printf("TAK\n");
          continue;
        }

        odbij(punkty[1], Kw);
        sortuj(punkty[1], Kw);

        if (szukaj(wzorzec_sk, 2 * Kw, punkty[1], Kw, skala[0])) {
          printf("TAK\n");
          continue;
        }
      }
    }
    printf("NIE\n");
  }
}
