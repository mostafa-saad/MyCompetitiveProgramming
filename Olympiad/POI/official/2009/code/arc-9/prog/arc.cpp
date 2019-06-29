/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Architekci (ARC)                                          *
 *   Plik:     arc.cpp                                                   *
 *   Autor:    Bartosz Gorski                                            *
 *   Opis:     Rozwiazanie wzorcowe                                      *
 *             czas: O(n); pamiec: O(k)                                  *
 *                                                                       *
 *************************************************************************/

#include <list>
#include "carclib.h"
#define MAXK 1000000
using namespace std;

int k;
list<int> best;
list<list<int>::iterator> q;

void print_best() {
  list<int>::iterator it = best.begin();
  while (it != best.end())
    wypisz(*it++);
}

int main () {
  k = inicjuj();
  for (int i = 0; i < k; i++) best.push_back(-i);
  int cur;
  cur = wczytaj();
  while (cur) {
    if (cur > best.back()) q.push_back((--best.end()));
    if (! q.empty()) {
      best.push_back(cur);
      list<int>::iterator it = q.front();
      list<int>::iterator pr = it;
      list<int>::iterator ne = it;
      ne++; pr--;
      if (it != best.begin() && *pr < *ne) q.front()--; else q.pop_front();
      best.erase(it);
    }
    cur = wczytaj();
  }
  print_best();
  return 0;
}
