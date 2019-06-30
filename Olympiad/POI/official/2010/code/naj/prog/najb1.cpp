/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Najdzielniejszy dzielnik (NAJ)                            *
 *   Plik:     najb1.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie bledne.                                       *
 *             Wymnaza wszystko i brutalnie faktoryzuje.                 *
 *                                                                       *
 *************************************************************************/    

#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

#define MAX_N 600
typedef long long ll;

int n;
ll a[MAX_N];
int k = 0, c = 0;

int main()
{
  /* Odczyt */
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%lld", a + i);
  ll N = 1;
  for (int i = 0; i < n; i++)
    N *= a[i];
  
  /* Faktoryzacja O(sqrt(N)). */
  int z = int(floor(sqrt(double(N))));
  int i = 2;
  while (i <= z)
  {
    if (N % i == 0)
    {
      int kr = 0;
      while (N % i == 0)
      {
        N /= i;
        kr++;
      }
      z = int(floor(sqrt(double(N))));
      if (kr > k)
      {
        k = kr;
        c = 1;
      } else if (k == kr)
      {
        c++;
      }
    }
    i++;
  }
  if (N > 1 && k == 1)
    c++;

  /* Wypisywanie wyniku */
  printf("%d\n%lld\n", k, (1LL << c) - 1);
  return 0;
}
