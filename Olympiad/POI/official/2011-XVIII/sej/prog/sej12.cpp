/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Sejf                                             *
 *   Autor:             Jakub Radoszewski                                *
 *   Zlozonosc czasowa: O(sqrt(n)+k*log(n))                              *
 *   Opis:              Rozwiazanie wzorcowe                             *
 *                                                                       *
 *************************************************************************/


/* Rozwiazanie weryfikujace do zadania SEJ (Sejf)
 * Autor: Jakub Radoszewski
 * Data: 5.02.2011
 * Zlozonosc czasowa: O(sqrt(n)+k*log(n))
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <cmath>
using namespace std;

long long nwd(long long a,long long b)
{
  return !b ? a : nwd(b, a % b);
}


#define MX 250000

long long n;
int k;
long long t[MX];

vector<long long> dzielniki;
vector<bool> bylo;
vector<long long> pierwsze;

inline int znajdz(long long d)
{
  return lower_bound(dzielniki.begin(), dzielniki.end(), d) - dzielniki.begin();
}


int main()
{
  // Odczyt
  ios_base::sync_with_stdio(0);
  cin >> n >> k;
  for (int i = 0; i < k; i++)
  {
    cin >> t[i];
    t[i] = nwd(t[i], n);
  }

  // Dzielniki n
  int gora = int(floor(sqrtl((long double)(n))));
  for (int i = 1; i <= gora; i++)
    if (n % i == 0)
    {
      dzielniki.push_back((long long)i);
      dzielniki.push_back(n / i);
    }
  sort(dzielniki.begin(), dzielniki.end());
  dzielniki.erase(unique(dzielniki.begin(), dzielniki.end()), dzielniki.end());

  // Dzielniki pierwsze n
  long long n1 = n;
  for (int i = 2; i <= gora; i++)
    if (n1 % i == 0)
    {
      pierwsze.push_back((long long)i);
      while (n1 % i == 0)
        n1 /= i;
      gora = int(floor(sqrtl((long double)(n1))));
    }
  if (n1 > 1LL)
    pierwsze.push_back(n1);

  // Zaznaczanie dzielnikow dzielacych t[i]
  bylo.resize(dzielniki.size());
  for (int i = 0; i < k - 1; i++)
    bylo[znajdz(t[i])] = true;
  for (int i = (int)dzielniki.size() - 1; i >= 0; i--)
    if (bylo[i])
    {
      for (int j = 0; j < (int)pierwsze.size(); j++)
        if (dzielniki[i] % pierwsze[j] == 0LL)
          bylo[znajdz(dzielniki[i] / pierwsze[j])] = true;
    }

  // Obliczenie wyniku
  long long wynik = -1LL;
  for (int i = (int)dzielniki.size() - 1; i >= 0; i--)
    if (!bylo[i] && t[k - 1] % dzielniki[i] == 0)
      wynik = n / dzielniki[i];
  cout << wynik << endl;
  return 0;
}
