/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Pociagi (POC)                                             *
 *   Plik:     pocb2.cpp                                                 *
 *   Autor:    Piotr Stanczyk, Jakub Radoszewski                         *
 *   Opis:     Rozwiazanie niepoprawne (haszujace) z bledem.             *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include <map>

using namespace std;

typedef long long LL;

#define FOR(x,b,e) for(int x=b;x<=(e);++x)
#define FORD(x,b,e) for(int x=b;x>=(e);--x)
#define REP(x,n) for(int x=0;x<(n);++x)
#define ND second

const int MAXPOC = 1000; // Max. liczba pociagow
const int MAXDL = 128;    // Max. dlugosc pociagu, musi byc potega dwojki
const int BMAXDL = 7;    // Liczba poziomow
const int MAXOP = 100000; // Max. liczba operacji
const int STRMAX = 2*MAXPOC*MAXDL+4*MAXOP; // Max. wielkosc struktur danych do wyliczania max. liczby podobnych pociagow
const LL PRIME = 7057594037927903LL;

char pociagi[MAXPOC][MAXDL+1];
long long hash[MAXPOC];
long long off[MAXDL];

inline void Hash(int poc, int poz, int v) {
  hash[poc] = hash[poc] + off[poz]*(LL)v;
  if (hash[poc] < 0)
    hash[poc] += 256LL*PRIME;
  hash[poc] %= PRIME;
}

struct operacja {
  int nast;
  int waga;
  int id;
};

operacja op[STRMAX];
int lHead[STRMAX];
int wynik[MAXPOC];
int idList[MAXPOC];
int opU = 0;

int ListLen(int l) {
  int res = 0;
  for(; l != -1; res++) l = op[l].nast;
  return res;
}

struct vert {
  int suma; // Suma wartosci z poddrzewa
  bool pocz;
  int poc;  // Identyfikator pociagu
};

vert drzewo[2*STRMAX];

int Rzad(int v) {
  int res = 0;
  for(; v > 1; res++) v >>= 1;
  return res;
}

// Funkcja wyznacza dla kazdego pociagu o postaci identyfikowanej przez l
// najwieksza liczbe pociagow wygladajacych tak samo
void wyliczWynik(int l) {
  int len = ListLen(lHead[l]);
  int start = 1<<Rzad(len);
  int pos = len + start - 1;
  for(int p = lHead[l]; p != -1; p = op[p].nast, pos--) {
    drzewo[pos].poc = op[p].id;
    drzewo[pos].suma = op[p].waga;
    drzewo[pos].pocz = (op[p].waga == 1);
  }
  FOR(x, start + 1, start + len - 1) drzewo[x].suma += drzewo[x-1].suma;
  while(pos) {
    drzewo[pos].suma = max(drzewo[2*pos].suma, drzewo[2*pos+1].suma);
    pos--;
  }
  FOR(x, start, start + len - 1) {
    if (drzewo[x].pocz) {
      idList[drzewo[x].poc] = x;
    } else {
      int lewy = idList[drzewo[x].poc];
      int prawy = x;
      int res = 0;
      while(lewy < prawy) {
        if ((lewy & 1) == 1) res = max(res, drzewo[lewy++].suma);
        if ((prawy & 1) == 0) res = max(res, drzewo[prawy--].suma);
        lewy >>= 1;
        prawy >>= 1;
      }
      if (lewy == prawy)
        res = max(res, drzewo[lewy].suma);
      wynik[drzewo[x].poc] = max(wynik[drzewo[x].poc], res);
    }
  }
}

map<LL, int> reNumber;
map<LL, int>::iterator reIt;
int reNum = 0;
void dodajElement(LL zb, int waga, int id) {
  if ((reIt = reNumber.find(zb)) == reNumber.end()) {
    reNumber[zb] = reNum;
    zb = reNum++;
  } else
    zb = reIt->ND;
  if (lHead[zb] == -1) {
    lHead[zb] = opU;
    op[lHead[zb]].nast = -1;
  } else {
    op[opU].nast = lHead[zb];
    lHead[zb] = opU;
  }
  op[opU].waga = waga;
  op[opU++].id = id;
}

int main() {
  int poc, dl, op;
  REP(x, STRMAX) lHead[x] = -1;
  REP(x, MAXPOC) wynik[x] = 0;
  scanf("%d %d %d\n", &poc, &dl, &op);
  REP(x, poc) {
    scanf("%s\n", pociagi[x]);
  }
  off[0] = 1;
  REP(x, dl-1) off[x+1] = (off[x] * 257LL) % PRIME;
  REP(x, poc) REP(y, dl) Hash(x, y, pociagi[x][y]);
  REP(x, poc)  dodajElement(hash[x], 1, x);
  int p1, p2, o1, o2;
  REP(z, op) {
    scanf("%d %d %d %d", &p1, &o1, &p2, &o2);
    p1--;
    o1--;
    p2--;
    o2--;
    dodajElement(hash[p1], -1, p1);
    if (p1 != p2)
      dodajElement(hash[p2], -1, p2);
    swap(pociagi[p1][o1], pociagi[p2][o2]);
    Hash(p1, o1, (int)pociagi[p1][o1] - (int)pociagi[p2][o2]);
    Hash(p2, o2, (int)pociagi[p2][o2] - (int)pociagi[p1][o1]);
    if (p1 != p2)
      dodajElement(hash[p1], 1, p1);
    dodajElement(hash[p2], 1, p2);
  }
  REP(x, poc) dodajElement(hash[x], -1, x);
  REP(x, STRMAX) if (lHead[x] != -1)
    wyliczWynik(x);
  REP(x, poc) printf("%d\n", wynik[x]);
  return 0;
}
