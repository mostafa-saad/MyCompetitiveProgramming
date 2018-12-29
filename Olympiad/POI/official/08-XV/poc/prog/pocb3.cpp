/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Pociagi (POC)                                             *
 *   Plik:     pocb3.cpp                                                 *
 *   Autor:    Piotr Stanczyk                                            *
 *   Opis:     Rozwiazanie niepoprawne.                                  *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

#define REP(x,n) for(int x=0;x<(n);++x)
typedef long long LL;
const int MAXPOC = 1000; // Max. liczba pociagow
const int MAXDL = 100;    // Max. dlugosc pociagu
const LL PRIME = 7057594037927903LL;

char pociagi[MAXPOC][MAXDL+1];
long long hash[MAXPOC];
long long off[MAXPOC];
map<LL, int> zbS;
int wynik[MAXPOC];
int poc, dl, op;

inline void Hash(int poc, int poz, int v) {
  hash[poc] = hash[poc] + off[poz]*(LL)v;
  if (hash[poc] < 0)
    hash[poc] += 256LL*PRIME;
  hash[poc] %= PRIME;
}

void Dodaj(long long h, int v) {
  if (zbS.find(h) == zbS.end()) {
    zbS[h] = 0;
  }
  zbS[h] += v;
}

int main() {
  scanf("%d %d %d\n", &poc, &dl, &op);
  REP(x, poc)
    scanf("%s\n", pociagi[x]);
  off[0] = 1;
  REP(x, dl-1) off[x+1] = (off[x] * 257LL) % PRIME;
  REP(x, poc) REP(y, dl) Hash(x, y, pociagi[x][y]);
  REP(x, poc) Dodaj(hash[x], 1);
  REP(x, poc) wynik[x] = zbS[hash[x]];
  int p1, p2, o1, o2;
  REP(z, op) {
    scanf("%d %d %d %d", &p1, &o1, &p2, &o2);
    p1--;
    o1--;
    p2--;
    o2--;
    Dodaj(hash[p1], -1);
    Dodaj(hash[p2], -1);
    swap(pociagi[p1][o1], pociagi[p2][o2]);
    Hash(p1, o1, (int)pociagi[p1][o1] - (int)pociagi[p2][o2]);
    Hash(p2, o2, (int)pociagi[p2][o2] - (int)pociagi[p1][o1]);
    Dodaj(hash[p1], 1);
    Dodaj(hash[p2], 1);
    wynik[p1] = max(wynik[p1], zbS[hash[p1]]);
    wynik[p2] = max(wynik[p2], zbS[hash[p2]]);
  }
  REP(x, poc) printf("%d\n", wynik[x]);
  return 0;
}
