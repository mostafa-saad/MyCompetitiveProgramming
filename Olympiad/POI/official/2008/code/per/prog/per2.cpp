/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Permutacja (PER)                                          *
 *   Plik:     per2.cpp                                                  *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie autorskie.                                    *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <utility>
#include <algorithm>
#include <cmath>
using namespace std;

#define MAX_N 300000

int n, m;
int t[MAX_N];
int mx; /* = *max_element(t, t + n) + 1 */
vector<int> p; /* liczby pierwsze z rozkladu m na czynniki */
int l; /* dlugosc tegoz */

void rozklad()
{
  int i = 2, m1 = m;
  while (i <= int(floor(sqrt(double(m)))))
  {
    if (m1 % i == 0)
    {
      while (m1 % i == 0)
        m1 /= i;
      p.push_back(i);
    }
    i++;
  }
  if (m1 > 1)
    p.push_back(m1);
  l = p.size();
}

/* Rozszerzony algorytm Euklidesa.
 * Dla a i b podaje (p,q,d) takie, ze ap+bq=d. */
void euclid(int a, int b, long long &p, long long &q, int &d)
{
  if (!b)
  {
    p = 1; q = 0;
    d = a;
  } else
  {
    long long p1, q1; int d1;
    euclid(b, a % b, p1, q1, d1);
    d = d1;
    p = q1;
    q = p1 - q1 * (a / b);
  }
}

/* Odwrotnosc v modulo m (musi byc NWD(v,m)=1). */
int odwrotnosc(int v)
{
  long long x, y; int z;
  euclid(v, m, x, y, z);
  return int(x % m + m) % m;
}

/* Szybkie potegowanie modulo: (x ^ u) modulo m. */
int potmod(int x, int u)
{
  int a = 1LL, b = x;
  while (u > 0)
    if (u % 2)
    {
      a = int(((long long)a * b) % m);
      u--;
    }
    else
    {
      b = int(((long long)b * b) % m);
      u /= 2;
    }
  return (int)a;
}

/* Drzewo przedzialowe wraz z jego rozmiarem */
int drz[1100000], ile;

inline void ustaw(int x, int delta)
{
  int v = x + ile;
  drz[v] += delta;
  while (v != 1)
  {
    v /= 2;
    drz[v] = drz[2 * v] + drz[2 * v + 1];
  }
}

inline int zapytanie(int x)
{
  if (x <= 0)
    return 0;
  int v = x + ile, wyn = 0;
  while (v != 1)
  {
    if (v % 2)
      wyn += drz[v - 1];
    v /= 2;
  }
  return wyn;
}

/* Reprezentacja wyniku */
class liczba
{
  vector<int> tab; /* wykladniki liczb pierwszych sposrod p[i],
                      dzielacych liczbe (moga byc ujemne!) */
  int val; /* reszta modulo m (z czynnikow wzglednie pierwszych z m) */
public:
  liczba()
  {
    val = 1;
    tab.resize(l, 0);
  }
  void operator*= (int x)
  {
    if (!x)
    {
      val = 0;
      return;
    }
    for (int i = 0; i < l; i++)
      while (x % p[i] == 0)
      {
        x /= p[i];
        tab[i]++;
      }
    val = int(((long long)(val) * x) % m);
  }
  void operator/= (int x)
  {
    if (x <= 1)
      return;
    for (int i = 0; i < l; i++)
      while (x % p[i] == 0)
      {
        x /= p[i];
        tab[i]--;
      }
    val = int(((long long)(val) * odwrotnosc(x)) % m);
  }
  int wartosc()
  {
    int wyn = val;
    for (int i = 0; i < l; i++)
      wyn = int(((long long)(wyn) * potmod(p[i], tab[i])) % m);
    return wyn;
  }
};

/* Glowna funkcja, ktora... liczy wynik */
void doit()
{
  int wynik = 1;
  liczba akt, pom;
  for (int i = 2; i <= n - 1; i++)
    akt *= i;
  for (int i = 0; i < mx; i++)
    for (int j = 2; j <= drz[i + ile]; j++)
      akt /= j;
  for (int i = 0; i < n - 1; i++)
  {
    pom = akt;
    pom *= zapytanie(t[i]);
    wynik = (wynik + pom.wartosc()) % m;
    akt *= drz[t[i] + ile];
    akt /= n - i - 1;
    ustaw(t[i], -1);
  }
  printf("%d\n", wynik);
}

int main()
{
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; i++)
    scanf("%d", t + i);
  rozklad();

  /* Konstrukcja drzewa przedzialowego */
  mx = *max_element(t, t + n) + 1;
  ile = 1;
  while (ile < mx)
    ile *= 2;
  for (int i = 0; i < n; i++)
    ustaw(t[i], 1);

  doit();
  return 0;
}
