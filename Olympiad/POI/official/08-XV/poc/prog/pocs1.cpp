/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Pociagi (POC)                                             *
 *   Plik:     pocs1.cpp                                                 *
 *   Autor:    Piotr Stanczyk                                            *
 *   Opis:     Rozwiazanie wolne.                                        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <string>
#include <algorithm>
#define REP(x,n) for(int x=0;x<(n);++x)

using namespace std;

#define WYLICZ REP(x, poc) {int v = 0; REP(y, poc) if (strcmp(pociagi[x], pociagi[y]) == 0) v++; maxbl[x] = max(v, maxbl[x]);}

int main() {
  int poc, dl, op;
  scanf("%d %d %d\n", &poc, &dl, &op);
  char pociagi[poc][dl+1];
  int maxbl[poc];
  REP(x, poc) {
    scanf("%s\n", pociagi[x]);
    maxbl[x] = 0;
  }
  WYLICZ;
  int p1, p2, o1, o2;
  REP(z, op) {
    scanf("%d %d %d %d", &p1, &o1, &p2, &o2);
    swap(pociagi[p1-1][o1-1], pociagi[p2-1][o2-1]);
    WYLICZ;
  }
  REP(x, poc) printf("%d\n", maxbl[x]);
  return 0;
}
