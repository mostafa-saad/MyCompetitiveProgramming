/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Najdzielniejszy dzielnik (NAJ)                            *
 *   Plik:     naj.cpp                                                   *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie wzorcowe.                                     *
 *             Uzywa testu Millera-Rabina z mnozeniem pseudopisemnym.    *
 *                                                                       *
 *************************************************************************/          
#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAX_N 600
typedef long long ll;

int los(int m)
{
  return (int)((double)m * (rand() / (RAND_MAX + 1.0)));
}

ll nwd(ll a, ll b)
{
  return !b ? a : nwd(b, a % b);
}


int n;
ll a[MAX_N];
int k = 0, c = 0;

/* Sito Eratostenesa w wersji logarytmicznej. */
vector<int> sito(int m = 1000000)
{
  int p[m + 1];
  for (int i = 2; i <= m; i++)
    p[i] = 1;
  for (int i = 2; i <= m; i++)
    if (p[i])
    {
      int j = 2 * i;  /* tu mozna by wpisac i*i, ale uwaga na rozmiar typu! */
      while (j <= m)
      {
        p[j] = 0;
        j += i;
      }
    }

  vector<int> pierwsze;
  for (int i = 2; i <= m; i++)
    if (p[i])
      pierwsze.push_back(i);
  return pierwsze;
}



/******* Test Millera-Rabina *******/

/* Oblicza (a*b) mod p za pomoca algorytmu mnozenia pisemnego. */
#define MLD 1000000000
ll mnoz(ll a, ll b, ll p)
{
  ll wyn = 0;
  ll a1 = a / MLD, a2 = a % MLD;
  ll b1 = b / MLD, b2 = b % MLD;
  wyn += a2 * b2;
  ll pom = a1 * b2 + a2 * b1;
  if (pom)
    for (int i = 1; i <= 9; i++)
    {
      pom = (pom * 2) % p;
      pom = (pom * 5) % p;
    }
  wyn += pom;
  pom = a1 * b1;
  if (pom)
    for (int i = 1; i <= 18; i++)
    {
      pom = (pom * 2) % p;
      pom = (pom * 5) % p;
    }
  wyn += pom;
  return wyn % p;
}

/* Oblicza (x^n) mod p za pomoca szybkiego potegowania binarnego. */
ll potmod(ll a, ll n, ll p)
{
  ll wyn = 1LL;
  while (n)
  {
    if (n % 2)
      wyn = mnoz(wyn, a, p);
    n /= 2;
    a = mnoz(a, a, p);
  }
  return wyn;
}

/* Czy a jest pseudopierwsza przy podstawie p? */
bool psp(ll a, ll p)
{
  ll q = p - 1;
  int ile = 0;
  while (q % 2 == 0LL)
  {
    ile++;
    q /= 2;
  }
  a = potmod(a, q, p);
  while (ile--)
  {
    ll b = mnoz(a, a, p);
    if (b == 1LL && a != 1LL && a != p - 1)
      return false;
    a = b;
  }
  if (a != 1LL)
    return false;
  return true;
}

/* Test pierwszosci Millera-Rabina */
bool Miller_Rabin(ll p)
{
#define PROBY 50
  for (int a = 2; a < PROBY; a++)
    if (!psp(a, p))
      return false;
  return true;
}







/* Wyznaczamy krotnosc p w ramach N i ewentualnie aktualizujemy k i c. */
void aktualizuj(ll p, bool na_pewno_pierwsza = true)
{
  int kr = 0;
  for (int i = 0; i < n; i++)
    while (a[i] % p == 0)
    {
      a[i] /= p;
      kr++;
    }

  int wklad = (na_pewno_pierwsza || Miller_Rabin(p)) ? 1 : 2;
  if (kr > k)
  {
    k = kr;
    c = wklad;
  } else if (kr == k)
  {
    c += wklad;
  }
}


/* Wypisywanie 2^c-1 - zawiera operacje na duzych liczbach. */
void wypisz(int c)
{
  /* 2^c */
  vector<int> wyn;
  wyn.push_back(1);
  while (c--)
  {
    int a = 0;
    for (int i = 0; i < (int)wyn.size(); i++)
    {
      wyn[i] = 2 * wyn[i] + a;
      a = 0;
      if (wyn[i] >= 10)
      {
        wyn[i] -= 10;
        a = 1;
      }
    }
    if (a)
      wyn.push_back(a);
  }

  /* 2^c-1 */
  wyn[0]--;
  int i = 0;
  while (wyn[i] < 0)
  {
    wyn[i] += 10;
    i++;
    wyn[i]--;
  }

  /* Wypisywanie. */
  for (int i = (int)wyn.size() - 1; i >= 0; i--)
    printf("%d", wyn[i]);
  puts("");
}

int main()
{
  /* Odczyt */
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%lld", a + i);

  /* Faza 1: dzielniki z sita */
  vector<int> pr(sito());
  for (int i = 0; i < (int)pr.size(); i++)
    aktualizuj(pr[i]);

  /* Faza 2: dzielniki z nwd */
  for (int i = 0; i < n; i++)
    for (int j = i + 1; j < n; j++)
    {
      ll d = nwd(a[i], a[j]);
      if ((d < a[i] || d < a[j]) && d > 1)
        aktualizuj(d);
    }

  /* Faza 3: Pierwiastki */
  for (int i = 0; i < n; i++)
    if (a[i] > 1)
    {
      int z = int(floor(sqrt(double(a[i]))));
      if ((ll)z * z == a[i])
        aktualizuj(z);
    }

  /* Faza 4: odroznienie pierwszych od zlozonych */
  for (int i = 0; i < n; i++)
    if (a[i] > 1)
      aktualizuj(a[i], false);

  printf("%d\n", k);
  wypisz(c);
  return 0;
}
