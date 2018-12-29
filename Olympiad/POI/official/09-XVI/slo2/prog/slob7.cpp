/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Slowa (SLO)                                               *
 *   Plik:     slob7.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie wykladnicze z KMP                             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

#define MAX_N 100000
#define MAX_M 4000000

int k;
int n[MAX_N];
string fib[MAX_N];
string wzorzec;
int p[MAX_M]; /* funkcja prefiksowa */

/* KMP z funkcja prefiksowa */

/* Funkcja prefiksowa dla slowa a. */
void compute(const string &a, int n)
{
  p[0] = 0;
  int j = 0;
  for (int i = 1; i <= n - 1; i++)
  {
    while (j && a[j] != a[i])
      j = p[j - 1];
    if (a[j] == a[i])
      j++;
    p[i] = j;
  }
}

/* KMP - zwraca prawde, jezeli jest wystapienie a w b. */
inline bool kmp(const string &a, const string &b)
{
  int n = (int)a.size(), m = (int)b.size();
  if (n > m)
    return false;
  int j = 0;
  for (int i = 0; i < m; i++)
  {
    while (j && a[j] != b[i])
      j = p[j - 1];
    if (a[j] == b[i])
      j++;
    if (j == n)
      return true;
  }
  return false;
}



int main()
{
  int ile;
  scanf("%d", &ile);
  while (ile--)
  {
    scanf("%d", &k);
    int mx = 0;
    for (int i = 0; i < k; i++)
    {
      scanf("%d", n + i);
      mx = max(mx, n[i]);
    }

    fib[0] = string("0");
    fib[1] = string("1");
    for (int i = 2; i <= mx; i++)
      fib[i] = fib[i - 1] + fib[i - 2];
    wzorzec.clear();
    for (int i = 0; i < k; i++)
      wzorzec += fib[n[i]];

    compute(wzorzec, (int)wzorzec.size());

    int wynik = 0;
    bool NIE = false;
    while (!kmp(wzorzec, fib[wynik]))
    {
      wynik++;
      if (fib[wynik].empty())
        fib[wynik] = fib[wynik - 1] + fib[wynik - 2];

      /* zbyt mala stala */
      if ((int)fib[wynik].size() > 4 * (int)wzorzec.size())
      {
        puts("NIE");
        NIE = true;
        break;
      }
    }
    if (!NIE)
      puts("TAK");
  }
  return 0;
}
