/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Slowa (SLO)                                               *
 *   Plik:     slob11.cpp                                                *
 *   Autor:    Jakub Radoszewski                                         *
 *   Opis:     Rozwiazanie bledne. Skraca poki sie da, jezeli otrzyma    *
 *             krotkie slowo w wyniku, to wypisuje TAK.                  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
using namespace std;

#define MAX_N 100000

int ile, n;
int k[MAX_N];

bool ok()
{
  vector<int> stos;
  int l = 0;
  for (int i = 0; i < n; i++)
  {
    stos.push_back(k[i]);
    l++;
    if (l >= 2 && stos[l - 2] == stos[l - 1] + 1)
    {
      stos[l - 2]++;
      stos.pop_back();
      l--;
    }
  }
#define STALA 1
  return (l > STALA) ? false : true;
}

int main()
{
  scanf("%d", &ile);
  while (ile--)
  {
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
      scanf("%d", k + i);
    if (ok())
      puts("TAK");
    else
      puts("NIE");
  }
  return 0;
}
