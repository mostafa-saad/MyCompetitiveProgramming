/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Najdzielniejszy dzielnik (NAJ)                            *
 *   Plik:     najb4.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie bledne.                                       *
 *             Wypisuje zawsze poprawne k, a w drugiej linii 1.          *
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
int k = 0;

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





/* Wyznaczamy krotnosc p w ramach N i ewentualnie aktualizujemy k. */
void aktualizuj(ll p)
{
  int kr = 0;
  for (int i = 0; i < n; i++)
    while (a[i] % p == 0)
    {
      a[i] /= p;
      kr++;
    }

  if (kr > k)
    k = kr;
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
      aktualizuj(a[i]);

  printf("%d\n1\n", k);
  return 0;
}
