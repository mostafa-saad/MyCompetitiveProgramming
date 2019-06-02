/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Slowa (SLO)                                               *
 *   Plik:     slob6.cpp                                                 *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie wzorcowe zmienione w ten sposob, ze operacja  *
 *             Zmniejsz stara sie zbytnio zmniejszyc wszystkie elementy. *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX_N 100000

int ile, n;
int k[MAX_N + 1];

bool ewidentnie_zly()
{
  /* Sufiks (k, 1, 1) dla k nieparzystego. */
  if (n >= 3 && k[n - 3] % 2 == 1 && k[n - 2] == 1 && k[n - 1] == 1)
    return true;
  /* Podslowo (k, 0) dla k!=1 i k!=3 */
  for (int i = 1; i < n; i++)
    if (k[i] == 0)
    {
      if (k[i - 1] != 1 && k[i - 1] != 3)
        return true;
    }
  return false;
}

/* Jezeli k[0]==x, to zmienia k[0] na a. */
void na_poczatku(int x, int a)
{
  if (k[0] == x)
    k[0] = a;
}

/* Jezeli ostatnia liczba w k to x, to zamiast niej wstawia a, lub nic,
 * jezeli a==-1. */
void na_koncu(int x, int a)
{
  if (k[n - 1] == x)
  {
    k[n - 1] = a;
    if (a == -1)
      n--;
  }
}

int k1[MAX_N], n1;

/* Zamienia wszystkie wystapienia (x, 0) na (a, b) lub a, gdy b==-1.
 * Zalozenie: x!=0. */
void wszystkie(int x, int a, int b)
{
  k[n] = -1;
  n1 = 0;
  for (int i = 0; i < n; i++)
  {
    if (k[i] != x || k[i + 1] != 0)
    {
      k1[n1++] = k[i];
      continue;
    }
    k1[n1++] = a;
    if (b != -1)
      k1[n1++] = b;
    i++;
  }

  /* Przepisywanie do pomocniczej tablicy. */
  for (int i = 0; i < n1; i++)
    k[i] = k1[i];
  n = n1;
}

void zmniejsz(int o_ile)
{
  for (int i = 0; i < n; i++)
    k[i] -= o_ile;
}

int main()
{
  scanf("%d", &ile);
  while (ile--)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%d", k + i);

    bool ok = true;
    while (n > 1)
    {
      if (ewidentnie_zly())
      {
        ok = false;
        break;
      }
      na_poczatku(0, 2);
      na_koncu(3, 2);
      na_koncu(1, -1);
      wszystkie(1, 2, -1);
      wszystkie(3, 2, 2);
//      zmniejsz(1);
      zmniejsz(max(*min_element(k, k + n) - 1, 1));
    }
    puts(ok ? "TAK" : "NIE");
  }
  return 0;
}
