/*************************************************************************
 *                                                                       *
 *                    XII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: SUM (Sumy Fibbonacciego)                       *
 *   Plik:                sums0.cpp                                      *
 *   Autor:               Marcin Michalski                               *
 *   Opis:                Rozwiazanie nieoptymalne                       *
 *                        zamiana na liczby w systemie dziesietnym       *
 *                        i z powrotem                                   *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cctype>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>
#include <vector>
#include <cstring>
using namespace std;
#define VAR(a,b) typeof(b) a=(b)
#define REP(i,n) for(int _n=n, i=0;i<_n;++i)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;++i)
#define FORD(i,a,b) for(int i=(a),_b=(b);i>=_b;--i)
#define FOREACH(it,c) for(VAR(it,(c).begin());it!=(c).end();++it)
#define ALL(f,w) ({ bool _ok=true; f _ok=_ok && (w); _ok; })
#define EXISTS(f,w) (!ALL(f,!(w)))
typedef long long LL;
const int INF = 1000000000;
typedef vector < int >VI;
template < class T > inline int size(const T & c)
{
  return c.size();
}

template < class T > inline vector < T > makeV(const T & x)
{
  return vector < T > (1, x);
}

template < class T > inline vector < T > makeV(const T & x, const T & y)
{
  vector < T > v(2);
  v[0] = x;
  v[1] = y;
  return v;
}

template < class T > inline vector < T > makeV(const T & x, const T & y,
                                               const T & z)
{
  vector < T > v(3);
  v[0] = x;
  v[1] = y;
  v[2] = z;
  return v;
}

template < class A, class B > inline bool contains(const A & a,
                                                   const B & b)
{
  return find(a.begin(), a.end(), b) != a.end();
}


class Natural {
  /* obowiazkowa czesc prywatna */
  static const int BASE = 100000000;
  static const int BASEDIGS = 8;
  int ndigs;
  int *digs;
  void init(int n, const int *d) {
    while (n > 0 && d[n - 1] == 0)
      --n;
    ndigs = n;
    digs = new int[n];
    for (int i = 0; i < n; ++i)
       digs[i] = d[i];
  } Natural(int n, const int *d) {
    init(n, d);
  }
  /* przesuwanie (dla dzielenia i pierwiastkowania) */
  Natural operator<<(int sh) const {  // sh >= 0
    int n = sh + ndigs;
    int d[n];
     REP(i, sh) d[i] = 0;
     REP(i, ndigs) d[i + sh] = digs[i];
     return Natural(n, d);
} public:
  /* konstruktory */
   Natural(int x = 0) {
    int d[2];
    d[0] = x % BASE;
    d[1] = x / BASE;
    init(2, d);
  }
  Natural(const Natural & a) {
    init(a.ndigs, a.digs);
  }
  Natural(const char *s) {
    int n = strlen(s);
    int nd = n / BASEDIGS + 1;
    int d[nd];
    REP(i, nd) {
      d[i] = 0;
      FORD(j, BASEDIGS - 1, 0) {
        int poz = i * BASEDIGS + j;
        if (poz < n)
          d[i] = 10 * d[i] + s[n - 1 - poz] - '0';
      }
    }
    init(nd, d);
  }
  /* destruktor */
  ~Natural() {
    delete[]digs;
  }
  /* przypisanie */
  Natural & operator=(const Natural & a) {
    delete[]digs;
    init(a.ndigs, a.digs);
    return *this;
  }
  /* dodawanie */
  Natural operator+(const Natural & a) const {
    int n = max(ndigs, a.ndigs) + 1;
    int d[n];
     REP(i, n) d[i] = 0;
     REP(i, n) {
      if (i < ndigs)
        d[i] += digs[i];
      if (i < a.ndigs)
        d[i] += a.digs[i];
      if (d[i] >= BASE) {
        d[i] -= BASE;
        ++d[i + 1];
    }} return Natural(n, d);
  }
  Natural & operator+=(const Natural & a) {
    return *this = *this + a;
  }
  /* odejmowanie */
  Natural operator-(const Natural & a) const {  // a <= *this
    int d[ndigs];
     REP(i, ndigs) d[i] = digs[i];
     REP(i, ndigs) {
      if (i < a.ndigs)
        d[i] -= a.digs[i];
      if (d[i] < 0) {
        d[i] += BASE;
        --d[i + 1];
    }} return Natural(ndigs, d);
  }
  Natural & operator-=(const Natural & a) {
    return *this = *this - a;
  }
  /* mno¿enie liczb */
  Natural operator*(const Natural & a) const {
    int n = ndigs + a.ndigs;
    int d[n];
     REP(i, n) d[i] = 0;
     REP(i, ndigs) {
      int p = 0;
       REP(j, a.ndigs) {
        long long v = (long long) (digs[i]) * a.digs[j];
        int v1 = v / BASE, v0 = v % BASE;
         d[i + j] += v0 + p;
         p = v1 + d[i + j] / BASE;
         d[i + j] %= BASE;
      } for (int j = i + a.ndigs; p > 0; ++j) {
        d[j] += p;
        p = d[j] / BASE;
        d[j] %= BASE;
      }
    }
    return Natural(n, d);
  }
  Natural & operator*=(const Natural & a) {
    return *this = *this * a;
  }
  /* dzielenie liczb */
  Natural operator/(const Natural & a) const {
    int n = max(ndigs - a.ndigs + 1, 0);
    int d[n];
    Natural prod;
     FORD(i, n - 1, 0) {
      int l = 0, r = BASE - 1;
      while (l < r) {
        int m = (l + r + 1) / 2;
        if (*this < prod + (a * m << i))
           r = m - 1;
        else
           l = m;
      } prod += a * l << i;
      d[i] = l;
    }
    return Natural(n, d);
  }
  Natural & operator/=(const Natural & a) {
    return *this = *this / a;
  }
  /* modulo */
  Natural operator%(const Natural & a) const {
    return *this - *this / a * a;
  } Natural & operator%=(const Natural & a) {
    return *this = *this % a;
  }
  /* pierwiastek */
  Natural sqrt() const {
    int n = (ndigs + 1) / 2;
    int d[n];
     REP(i, n) d[i] = 0;
    Natural sq;
     FORD(i, n - 1, 0) {
      Natural a(n, d);
      int l = 0, r = BASE - 1;
      while (l < r) {
        int m = (l + r + 1) / 2;
        if (*this < sq + (a * 2 * m << i) + (Natural(m) * m << 2 * i))
           r = m - 1;
        else
           l = m;
      } sq += (a * 2 * l << i) + (Natural(l) * l << 2 * i);
      d[i] = l;
    }
    return Natural(n, d);
  }
  /* mno¿enie przez inta */
  Natural operator*(int x) const {  // !!! 0 <= x <= BASE
    int n = ndigs + 1;
    int d[n];
    long long a = 0;
     REP(i, ndigs) {
      a += digs[i] * (long long) x;
      d[i] = a % BASE;
      a /= BASE;
    } d[ndigs] = a;
    return Natural(n, d);
  }
  Natural & operator*=(int x) {
    return *this = *this * x;
  }
  /* dzielenie przez inta */
  Natural operator/(int x) const {  // !!! 0 < x
    int d[ndigs];
    long long a = 0;
     FORD(i, ndigs - 1, 0) {
      a = BASE * a + digs[i];
      d[i] = a / x;
      a %= x;
    } return Natural(ndigs, d);
  }
  Natural & operator/=(int x) {
    return *this = *this / x;
  }
  /* modulo int */
  int operator%(int x) const {  // !!! 0 < x
    long long a = 0;
     FORD(i, ndigs - 1, 0) {
      a = BASE * a + digs[i];
      a %= x;
    } return a;
  }
  /* porównania (< potrzebne dla dzielenia i pierwiastka) */
  bool operator<(const Natural & a) const {
    if (ndigs < a.ndigs)
      return true;
    if (ndigs > a.ndigs)
      return false;
    FORD(i, ndigs - 1, 0) {
      if (digs[i] < a.digs[i])
        return true;
      if (digs[i] > a.digs[i])
        return false;
    } return false;
  }
  bool operator==(const Natural & a) const {
    if (ndigs != a.ndigs)
      return false;
    REP(i, ndigs) {
      if (digs[i] != a.digs[i])
        return false;
    } return true;
  }
  bool operator>(const Natural & a) const {
    return a < *this;
  } bool operator<=(const Natural & a) const {
    return !(a < *this);
  } bool operator>=(const Natural & a) const {
    return !(*this < a);
  } bool operator!=(const Natural & a) const {
    return !(*this == a);
  }
  /* wypisywanie */ void write() const {
    if (ndigs == 0)
      printf("0");
    else {
      printf("%d", digs[ndigs - 1]);
      FORD(i, ndigs - 2, 0) printf("%0*d", BASEDIGS, digs[i]);
  }} void write(char *buf) const {
    if (ndigs == 0)
      sprintf(buf, "0");
    else {
      int pos = 0;
       pos += sprintf(buf, "%d", digs[ndigs - 1]);
       FORD(i, ndigs - 2, 0) pos +=
          sprintf(buf + pos, "%0*d", BASEDIGS, digs[i]);
}}};

// KONIEC KLASY DUZYCH LICZB



Natural fib[1000100];
int slowo1[1000100];
int slowo2[1000100];
int wynik[1000100];
int n, m, dlugosc_wyniku;
Natural liczba1;
Natural liczba2;


int max(int x, int y)
{
  return (x > y ? x : y);
}

void czysc()
{
  for (int i = 0; i < 1000; i++)
    wynik[i] = 0;
}

void wczytaj()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++) {
    scanf("%d", &slowo1[i]);
  }
  scanf("%d", &m);
  for (int i = 0; i < m; i++) {
    scanf("%d", &slowo2[i]);
  }
  return;
}


void wypisz_wynik()
{
  printf("%d", dlugosc_wyniku);
  for (int i = 0; i < dlugosc_wyniku; i++)
    printf(" %d", wynik[i]);
  printf("\n");
  return;
}



int main()
{
  fib[0] = 1;
  fib[1] = 2;
  wczytaj();
  // wyznaczanie liczb Fibonacciego
  for (int i = 2; i < max(n, m) + 4; i++)
    fib[i] = fib[i - 1] + fib[i - 2];
  // zamiana na system dziesietny
  liczba1 = 0;
  for (int i = 0; i < n; i++)
    if (slowo1[i] == 1)
      liczba1 += fib[i];
  liczba2 = 0;
  for (int i = 0; i < m; i++)
    if (slowo2[i] == 1)
      liczba2 += fib[i];
  Natural suma = liczba1 + liczba2;
  // i spowrotem
  int wart = 0;
  while (fib[wart] <= suma) {
    wart++;
  }
  wart--;
  dlugosc_wyniku = wart;
  for (int i = dlugosc_wyniku; i >= 0; i--) {
    if (fib[i] <= suma) {
      suma -= fib[i];
      wynik[i] = 1;
    }
    else
      wynik[i] = 0;
  }
  dlugosc_wyniku++;
  wypisz_wynik();
  return 0;
}
