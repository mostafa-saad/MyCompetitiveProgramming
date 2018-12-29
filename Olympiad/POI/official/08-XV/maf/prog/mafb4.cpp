/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Mafia (MAF)                                               *
 *   Plik:     mafb4.cpp                                                 *
 *   Autor:    Marian Marek Kedzierski                                   *
 *   Opis:     Heurystyka oparta o metodę Monte-Carlo: wykonywanych jest *
 *             10^7 / n prób strzałów w losowej kolejności i ze          *
 *             wszystkich tych prób brane jest minimum i maksimum ofiar. *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

#define TIME 10000000
#define MAXN 1000000

int s[MAXN];
int order[MAXN];
bool alive[MAXN];

int main () {
  int n;
  scanf("%d", &n);
  int a;
  for (int i=0; i<n; ++i) {
    scanf("%d", &a);
    s[i] = a-1;
  }

  int times = TIME / n;
  int killed;
  int minimum = n, maximum = 0;
  assert(times > 0);

  for (int t=0; t<times; ++t) {
    for (int i=0; i<n; ++i) {
      order[i] = i;
      alive[i] = true;
    }
    random_shuffle(order, order + n);

    killed = 0;
    for (int i=0; i<n; ++i)
      if (alive[order[i]]) {
        if (alive[s[order[i]]]) ++killed;
        alive[s[order[i]]] = false;
      }
    minimum = min (minimum, killed);
    maximum = max (maximum, killed);
  }

  printf("%d %d\n", minimum, maximum);

  return 0;
}
