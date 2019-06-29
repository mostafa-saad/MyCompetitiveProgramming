/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Pociagi (POC)                                             *
 *   Plik:     pocs2.cpp                                                 *
 *   Autor:    Piotr Stanczyk                                            *
 *   Opis:     Rozwiazanie wolne.                                        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

#define REP(x,n) for(int x=0;x<(n);++x)

const int MAXPOC = 1000; // Max. liczba pociagow
const int MAXDL = 100;    // Max. dlugosc pociagu

char pociagi[MAXPOC][MAXDL+1];
int maxbl[MAXPOC];
int poc, dl, op;

void Odswierz(int nr) {
  int r = 0;
  REP(x, poc) if (strcmp(pociagi[nr], pociagi[x]) == 0) r++;
  REP(x, poc) if (strcmp(pociagi[nr], pociagi[x]) == 0) maxbl[x] = max(maxbl[x], r);
}

int main() {
  scanf("%d %d %d\n", &poc, &dl, &op);
  REP(x, poc) {
    scanf("%s\n", pociagi[x]);
    maxbl[x] = 0;
  }
  REP(x, poc) REP(y, poc) if (strcmp(pociagi[x], pociagi[y]) == 0) maxbl[x]++;
  int p1, p2, o1, o2;
  REP(z, op) {
    scanf("%d %d %d %d", &p1, &o1, &p2, &o2);
    swap(pociagi[p1-1][o1-1], pociagi[p2-1][o2-1]);
    Odswierz(p1-1);
    Odswierz(p2-1);
  }
  REP(x, poc) printf("%d\n", maxbl[x]);
  return 0;
}
