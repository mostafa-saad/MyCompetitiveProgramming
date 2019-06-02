/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Slowa (SLO)                                               *
 *   Plik:     slo2.cpp                                                  *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie alternatywne. Spacer po grafie podslow dla    *
 *             F_{infty}. Zlozonosc czasowa i pamieciowa O(n).           *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX_K 100000

/* Fib_0=b, Fib_1=a, Fib_i=Fib_{i-1}Fib{i-2}
 * (definicja inna niz w tresci zadania, ale jakos tak bardziej standardowa) */

/* Niech r bedzie rozmiarem wektora slowo.
 * Wowczas pozostala czesc grafu podslow slowa Fibonacciego sklada sie kolejno
 * ze slow Fibonacciego o indeksach:
 *
 * slowo[r-1].first, slowo[r-1].first+1, ..., slowo[r-1].second, ...
 * slowo[0].first, slowo[0].first+1, ..., slowo[0].second,
 * pocz, pocz+1, pocz+2, ...
 *
 * Przy tym zachodzi zawsze:
 * slowo[i].second <= slowo[i-1].first-3
 * slowo[0].second <= pocz-3
 *
 * Skoki w grafie podslow (tzn. krawedzie o dlugosci >1) wystepuja poczawszy
 * od slow slowo[0].second, pocz, pocz+1, ... (poza pewnymi wyjatkami, kiedy
 * np. ktores z tych slow to "b" lub "a", to skoki moga byc minimalnie
 * wczesniejsze).
 */
vector<pair<long long, long long> > slowo;
long long pocz;




inline void pierwszy(int n)
{
  if (!n)
    /* Fib_0=b, przypadek rozpatrywany osobno */
    pocz = 1;
  else
    pocz = n - 1;
}


bool NIE;

inline void kolejny(int n)
{
  if (slowo.empty())
  {
    /* Zadne slowo nie jest aktualnie rozkrojone. */
    if (n < pocz)
    {
      /* Przypadek 1. Rozkrawamy slowo. */
      if (!n)
      {
        /* przypadek szczegolny */
        if (pocz == 2)
        {
          /* Bez tego nie dziala dla fib2c.in. */
          slowo.push_back(make_pair(1, 1));
          pocz += 2;
        } else
        {
          NIE = true;
          return;
        }
      } else
      {
        /* n>0 */
        slowo.push_back(make_pair(n - 1, pocz - 2));
        pocz++;
      }
    } else if (n == pocz)
    {
      /* Przypadek 2. Zwykly przeskok */
      pocz++;
    } else
    {
      /* n > pocz */

      /* przypadki szczegolne */
      if (n == 2 && pocz == 1)
      {
        /* Bez tego nie dziala dla fib3c.in. */
        slowo.push_back(make_pair(1, 1));
        pocz += 3;
      } else if (n == 1 && pocz == 0)
      {
        /* Bez tego nie dziala dla fib4c.in. */
        slowo.push_back(make_pair(0, 0));
        pocz += 3;
      } else
      {
        /* Przypadek 3. Wycinamy duzo slow, korzystajac z potencjalnie wielu
         * skokow. */
        if ((n - pocz) % 2)
        {
          /* Bez tego nie dziala w czasie dla fib9d.in, fib10a.in i fib10b.in. */
          slowo.push_back(make_pair(n - 3, n - 2));
          pocz = n + 1;
        } else
        {
          /* (n - pocz) % 2 == 0
           * Bez tego nie dziala w czasie dla fib7b.in, fib8b.in i fib10d.in. */
          pocz = n + 1;
        }
      }
    }
  } else
  {
    /* !slowo.empty(), tzn. jakies slowo jest aktualnie rozkrojone. */
    if (n < slowo.back().first)
    {
      if (!n)
      {
        /* przypadek szczegolny */
        if ((int)slowo.size() == 1 && slowo.back() == make_pair(2LL, 2LL))
        {
          /* Bez tego nie dziala dla fib5c.in. */
          slowo.pop_back();
          slowo.push_back(make_pair(1, 1));
          pocz++;
        } else
        {
          NIE = true;
          return;
        }
      } else
      {
        /* Przypadek 1. Rozkrawamy slowo. */
        int poz = slowo.back().first;
        slowo.back().first++;
        if (slowo.back().first > slowo.back().second)
          slowo.pop_back();
        slowo.push_back(make_pair(n - 1, poz - 2));
      }
    } else if (n == slowo.back().first)
    {
      /* Przypadek 2. Zwykly przeskok */
      slowo.back().first++;
      if (slowo.back().first > slowo.back().second)
        slowo.pop_back();
    } else
    {
      /* Przypadek 3. n > slowo.back().first, bedzie sie dzialo. */
      if (n == 1)
      {
        /* przypadek szczegolny */
        if ((int)slowo.size() == 1 && slowo.back() == make_pair(0LL, 1LL))
        {
          /* Bez tego nie dziala dla fib7c.in. */
          slowo.pop_back();
          slowo.push_back(make_pair(0, 0));
          pocz++;
        } else
        {
          /* Bez tego nie dziala dla fib10c.in. */
          NIE = true;
          return;
        }
      } else if (slowo.back().second > slowo.back().first)
      {
        /* przedzial zlozony z wiecej niz 1 slowa */
        if (n == slowo.back().first + 1)
        {
          if (n == 2)
          {
            /* przypadek szczegolny */
            if ((int)slowo.size() != 1 || slowo.back().second != 2)
            {
              /* Bez tego nie dziala dla fib2d.in. */
              NIE = true;
              return;
            } else
            {
              /* Bez tego nie dziala dla fib8c.in. */
              slowo.pop_back();
              slowo.push_back(make_pair(1, 1));
              pocz++;
            }
          } else
          {
            int poz = slowo.back().first;
            slowo.back().first += 2;
            if (slowo.back().first > slowo.back().second)
              slowo.pop_back();
            slowo.push_back(make_pair(poz - 2, poz - 1));
          }
        } else if (slowo.back().first + 1 == slowo.back().second && (int)slowo.size() == 1)
        {
          /* przedzial dlugosci 2, jedyny na wektorze slowo */
          int poz = slowo.back().first + 2;
          slowo.pop_back();
          if (n == poz)
          {
            pocz++;
          } else if (n == poz + 1)
          {
            pocz++;
            slowo.push_back(make_pair(poz - 2, pocz - 2));
            pocz++;
          } else
          {
            NIE = true;
            return;
          }
        } else
        {
          NIE = true;
          return;
        }
      } else
      {
        /* przedzial dlugosci 1, mamy wiekszego Fiba */
        if (n >= slowo.back().first + 2 || n == 2)
        {
          /* za duzy Fib sie nie znajdzie */
          NIE = true;
          return;
          /* Bez warunku n==2 nie dziala na tescie fib3d.in. */
        }
        slowo.pop_back();
        /* n = slowo.back().first + 1 */
        if (slowo.empty())
        {
          /* Bez tego nie dziala dla fib9c.in. */
          int poz = pocz;
          pocz++;
          slowo.push_back(make_pair(n - 3, poz - 2));
        } else
        {
          /* !slowo.empty() */
          int poz = slowo.back().first;
          slowo.back().first++;
          if (slowo.back().first > slowo.back().second)
            slowo.pop_back();
          slowo.push_back(make_pair(n - 3, poz - 2));
        }
      }
    }
  }
}




int main()
{
  int ile;
  scanf("%d", &ile);
  while (ile--)
  {
    slowo.clear();
    int k, n; /* dane */
    scanf("%d", &k);

    /* Pierwszy Fib rozpatrywany osobno. */
    scanf("%d", &n);
    pierwszy(n);
    if (k == 1 && n == 0)
    {
      /* Wyjatek */
      puts("TAK");
      continue;
    }
    
    /* Kolejne Fiby. */
    NIE = false;
    for (int i = 2; i <= k; i++)
    {
      scanf("%d", &n);
      if (!NIE)
        kolejny(n);
    }
    if (NIE)
      puts("NIE");
    else
      puts("TAK");
  }
  return 0;
}
