/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Pociagi (POC)                                             *
 *   Plik:     poc0.cpp                                                  *
 *   Autor:    Piotr Stanczyk                                            *
 *   Opis:     Rozwiazanie wzorcowe.                                     *
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

const int MAXPOC = 1000; // Max. liczba pociagow
const int MAXDL = 128;    // Max. dlugosc pociagu, musi byc potega dwojki
const int BMAXDL = 7;    // Liczba poziomow
const int MAXOP = 100000; // Max. liczb operacji
const int STRMAX = 2*MAXPOC*MAXDL+4*MAXOP; // Max. wielkosc struktur danych do wyliczania max. liczby podobnych pociagow

// Struktura do reprezentacji dynamicznych tesktow - pozwala na zmiane dowolnych liter w czasie log^2(n)
// i porownywanie w czasie stalym
map<LL, int> pary[BMAXDL];
int IdU[BMAXDL];
map<LL, int>::iterator iter;
struct DynTxt {
  int heap[2*MAXDL+1];
  DynTxt() {
    FORD(x, 2*MAXDL, 0) heap[x] = 0;
  }
  void zmiana(int pos, char zn) {
    int poz = BMAXDL;
    heap[pos += MAXDL] = zn;
    while(pos >>= 1) {
      --poz;
      if ((iter = pary[poz].find((((LL)heap[pos<<1])<<32)+(LL)heap[(pos<<1)+1])) == pary[poz].end()) {
        heap[pos] = ++IdU[poz];
        pary[poz][(((LL)heap[pos<<1])<<32)+(LL)heap[(pos<<1)+1]] = IdU[poz];
      } else
        heap[pos] = iter->second;
    }
  }
  char litera(int pos) {
    return (char) heap[pos+MAXDL];
  }
};
DynTxt pociag[MAXPOC];

struct operacja {
  int nast;
  int waga;
  int id;
};

operacja op[STRMAX];
int lHead[STRMAX];
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
  for(; v > 0; res++) v >>= 1;
  return res;
}

// Funkcja wyznacza dla kazdego pociagu o postaci identyfikowanej przez l
// najwieksza liczbe pociagow wygladajacych tak samo
// w pociag[x].heap[0] umieszczany jest wynik
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
      pociag[drzewo[x].poc].heap[1] = x;
    } else {
      int lewy = pociag[drzewo[x].poc].heap[1];
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
      pociag[drzewo[x].poc].heap[0] = max(pociag[drzewo[x].poc].heap[0], res);
    }
  }
}

void dodajElement(int zb, int waga, int id) {
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
  REP(x, STRMAX) lHead[x] = -1;
  REP(x, BMAXDL) IdU[x] = 0;
  int poc, dl, op;
  scanf("%d %d %d\n", &poc, &dl, &op);
  char buf[dl+1];
  REP(x, poc) {
    scanf("%s\n", buf);
    REP(y, dl) pociag[x].zmiana(y, buf[y]);
    dodajElement(pociag[x].heap[1], 1, x);
  }
  int poc1, pos1, poc2, pos2, l1, l2;
  REP(x, op) {
    scanf("%d %d %d %d", &poc1, &pos1, &poc2, &pos2);
    poc1--;
    poc2--;
    pos1--;
    pos2--;
    l1 = pociag[poc2].litera(pos2);
    l2 = pociag[poc1].litera(pos1);
    dodajElement(pociag[poc1].heap[1], -1, poc1);
    if (poc1 != poc2)
      dodajElement(pociag[poc2].heap[1], -1, poc2);
    pociag[poc1].zmiana(pos1, l1);
    pociag[poc2].zmiana(pos2, l2);
    if (poc1 != poc2)
      dodajElement(pociag[poc1].heap[1], 1, poc1);
    dodajElement(pociag[poc2].heap[1], 1, poc2);
  }
  REP(x, poc) dodajElement(pociag[x].heap[1], -1, x);
  REP(x, STRMAX) if (lHead[x] != -1)
    wyliczWynik(x);
  REP(x, poc) printf("%d\n", pociag[x].heap[0]);
  return 0;
}
