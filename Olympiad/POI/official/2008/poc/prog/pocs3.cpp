/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Pociagi (POC)                                             *
 *   Plik:     pocs3.cpp                                                 *
 *   Autor:    Piotr Stanczyk                                            *
 *   Opis:     Rozwiazanie wolne.                                        *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <string>
#include <algorithm>

using namespace std;

#define REP(x,n) for(int x=0;x<(n);++x)
typedef long long LL;
const int MAXPOC = 1000; // Max. liczba pociagow
const int MAXDL = 100;    // Max. dlugosc pociagu
const LL PRIME = 7057594037927903LL;

char pociagi[MAXPOC][MAXDL+1];
int maxbl[MAXPOC];
long long hash[MAXPOC];
long long off[MAXDL];
int poc, dl, op;

void Odswierz(int nr) {
  int r = 0;
  REP(x, poc) if (hash[nr] == hash[x] && (strcmp(pociagi[x], pociagi[nr]) == 0)) r++;
  REP(x, poc) if (hash[nr] == hash[x] && (strcmp(pociagi[x], pociagi[nr]) == 0)) maxbl[x] = max(maxbl[x], r);
}

inline void Hash(int poc, int poz, int v) {
  hash[poc] = hash[poc] + off[poz]*(LL)v;
  if (hash[poc] < 0)
    hash[poc] += 256LL*PRIME;
  hash[poc] %= PRIME;
}

int main() {
  scanf("%d %d %d\n", &poc, &dl, &op);
  REP(x, poc) {
    scanf("%s\n", pociagi[x]);
    maxbl[x] = 0;
  }
  off[0] = 1;
  REP(x, dl-1) off[x+1] = (off[x] * 257LL) % PRIME;
  REP(x, poc) REP(y, dl) Hash(x, y, pociagi[x][y]);
  REP(x, poc) REP(y, poc) if (hash[x] == hash[y] && (strcmp(pociagi[x], pociagi[y]) == 0)) maxbl[x]++;
  int p1, p2, o1, o2;
  REP(z, op) {
    scanf("%d %d %d %d", &p1, &o1, &p2, &o2);
    p1--;
    o1--;
    p2--;
    o2--;
    swap(pociagi[p1][o1], pociagi[p2][o2]);
    Hash(p1, o1, (int)pociagi[p1][o1] - (int)pociagi[p2][o2]);
    Hash(p2, o2, (int)pociagi[p2][o2] - (int)pociagi[p1][o1]);
    Odswierz(p1);
    Odswierz(p2);
  }
  REP(x, poc) printf("%d\n", maxbl[x]);
  return 0;
}
