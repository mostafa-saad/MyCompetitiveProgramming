/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Najdzielniejszy dzielnik (NAJ)                            *
 *   Plik:     najs4.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             Rozklada kazda z liczb a_i brutalnie.                     *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <cstdlib>
using namespace std;

vector<long long> prime;

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
  int n;
  scanf("%d", &n);
  while (n--)
  {
    long long a;
    scanf("%lld", &a);
    int gora = int(floor(sqrt(double(a))));
    int i = 2;
    while (i <= gora)
    {
      if (a % i == 0)
      {
        while (a % i == 0)
        {
          prime.push_back(i);
          a /= i;
        }
        gora = int(floor(sqrt(double(a))));
      }
      i++;
    }
    if (a > 1LL)
      prime.push_back(a);
  }

  sort(prime.begin(), prime.end());

  int k = 1, c = 0;
  int i = 0;
  while (i < (int)prime.size())
  {
    int i0 = i;
    while (i0 < (int)prime.size() && prime[i0] == prime[i])
      i0++;
    if (i0 - i > k)
    {
      k = i0 - i;
      c = 1;
    } else if (i0 - i == k)
    {
      c++;
    }
    i = i0;
  }
  printf("%d\n", k);
  wypisz(c);
  return 0;
}
