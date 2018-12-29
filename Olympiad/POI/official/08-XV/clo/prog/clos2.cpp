/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clos2.cpp                                                 *
 *   Autor:    Adam Iwanicki                                             *
 *   Opis:     Rozwiazanie nieoptymalne. Stara sie w pesymistycznie      *
 *             wykladniczym czasie sprawdzic dla kazdej krawedzi (ktorej *
 *             konce nie maja jeszcze przypisanej krawedzi) sprawdzic do *
 *             ktorego z sasiadujacych dwoch wierzcholkow ja przypisac   *
 *             tak aby przyporzadkowanie bylo mozliwe. Krawedz jest      *
 *             wybierana losowo.                                         *
 *                                                                       *
 *************************************************************************/
#include <cstdio>
#include <cassert>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;

const int MAXN = 100000;
const int MAXM = 200000;
struct Edge {
  int a,b;
  bool isUsed;
};

Edge edges[MAXM];

vector<int> adj[MAXN];

int odwiedzone[MAXN];
int clo[MAXN];

vector<int> adjNum;
int ile = 0;
int round = 0;

void przejdz(int start) {
  ++ile;
  odwiedzone[start] = round;
  int rozm = adj[start].size();
  vector<int> &v = adj[start];
  for (int i=0; i<rozm; ++i) {
    const Edge &e = edges[v[i]];
    if (!e.isUsed) {
      int other = e.a == start ? e.b : e.a;
      if (odwiedzone[other] < round) {
        przejdz(other);
      }
      adjNum.push_back(v[i]);
    }
  }
}

void przypisz(int start) {
  int rozm = adj[start].size();
  vector<int> &v = adj[start];
  for (int i=0; i<rozm; ++i) {
    Edge &e = edges[v[i]];
    if (!e.isUsed) {
      e.isUsed = true;
      int other = e.a == start ? e.b : e.a;
      clo[other] = start;
      przypisz(other);
    }
  }
}

bool probuj(int start) {
  adjNum.clear();
  ++round;
  ile = 0;
  przejdz(start);
  if (0 == adjNum.size()) {
    return 0;
  }
  // try with random_shuffle
  int num = rand() % adjNum.size();
  Edge &e = edges[adjNum[num]];
  e.isUsed = true;

  int a = e.a;
  int b = e.b;
  if (rand() & 1) {
    swap(a, b);
  }

  clo[a] = b;

  int pozostalo = ile;
  adjNum.clear();
  ile = 0;
  ++round;
  przejdz(a);
  if (ile == pozostalo) { // pozostaly graf jest spojny
    przypisz(a);
    return true;
  } else {
    if (probuj(b)) { // dalo sie teraz przypisujemy
      przypisz(a);
      return true;
    } else { // probujemy w druga strone
      clo[a] = -1;
      clo[b] = a;
      if (probuj(a)) {
        przypisz(b);
        return true;
      }
      clo[b] = -1;
      e.isUsed = false;
      return false;
    }
  }
}

int main()
{
  int n,m;
  scanf("%d %d", &n, &m);
  for (int i=0; i<n; ++i) {
    odwiedzone[i] = round;
  }

  for (int i=0; i<m; ++i) {
    int a, b;
    scanf("%d %d", &a, &b);
    --a; --b;
    edges[i].a = a;
    edges[i].b = b;
    edges[i].isUsed = false;

    adj[a].push_back(i);
    adj[b].push_back(i);
  }
  bool isPossibe = true;
  for (int i=0; i<n; ++i) {
    if (0 == odwiedzone[i]) {
      if (!probuj(i)) {
        isPossibe = false;
        break;
      }
    }
  }
  if (isPossibe) {
    printf("TAK\n");
    for (int i=0; i<n; ++i) {
      printf("%d\n", clo[i] + 1);
    }
  } else {
    printf("NIE\n");
  }
}
