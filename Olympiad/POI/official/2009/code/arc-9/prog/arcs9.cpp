/*************************************************************************
 *                                                                       *
 *                     XVI Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Architekci (ARC)                                          *
 *   Plik:     arc95.java                                                *
 *   Autor:    Marcin Pilipczuk                                          *
 *   Opis:     Alternatywne rozwiazanie wzorcowe z dodanym niepotrzebnym *
 *             drzewem licznikowym; czas: O(n log n); pamiec: O(k)       *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <list>
#include <queue>
#include <deque>
#include <cctype>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <numeric>
#include <cmath>
using namespace std;

typedef vector <int > VI;
typedef vector < VI > VVI;
typedef long long LL;
typedef vector < LL > VLL;
typedef vector < double > VD;
typedef vector < string > VS;
typedef pair<int,int> PII;
typedef vector <PII> VPII;
typedef istringstream ISS;

#define ALL(x) x.begin(),x.end()
#define REP(i,n) for (int i=0; i<(n); ++i)
#define FOR(var,pocz,koniec) for (int var=(pocz); var<=(koniec); ++var)
#define FORD(var,pocz,koniec) for (int var=(pocz); var>=(koniec); --var)
#define FOREACH(it, X) for(__typeof((X).begin()) it = (X).begin(); it != (X).end(); ++it)
#define PB push_back
#define PF push_front
#define MP(a,b) make_pair(a,b)
#define ST first
#define ND second
#define SIZE(x) (int)x.size()

#include "carclib.h"

const int K = (1 << 20);
const int MAG = 2 * K;
int dr[4 * K];
int q[K];
int pq, kq;
bool pusta = true;
int k;

void dodaj(int x){
  int a = 1;
  while (a < MAG){
    a <<= 1;
    if (dr[a] >= x) a++;
  }
  if (a >= MAG + k) return;
  dr[a] = x;
  int b = a + 1;
  while (dr[b] > 0)
    dr[b++] = 0;
  --b;
  while (a > 1 && b > 1){
    a >>= 1; b >>= 1;
    FOR(i, a, b) dr[i] = min(dr[i << 1], dr[(i << 1) + 1]);
  }
}

int wyszukaj_max(int a, int b){
  int oa = a;
  int ma = max(dr[a], dr[b]);
  while ((a >> 1) < (b >> 1)){
    if (!(a & 1))
      ma = max(ma, dr[a+1]);
    if (b & 1)
      ma = max(ma, dr[b-1]);
    a >>= 1; b >>= 1;
  }
  a = oa;
  if (dr[a] == ma) return a;
  while(1){
    if (!(a & 1))
      if (dr[a+1] >= ma){
        a++; break;
      }
    a >>= 1;
  }
  while (a < MAG){
    a <<= 1;
    if (dr[a] < ma)
      a++;
  }
  return a;
}

int main(){
  k = inicjuj();
  int x;
  while ((x = wczytaj()) > 0){
    if (!pusta && pq == kq){
      int y = q[pq++];
      if (pq == k) pq = 0;
      dodaj(y);
    }
    q[kq++] = x;
    if (kq == k) kq = 0;
    pusta = false;
  }
  int poz = MAG;
  while (dr[poz] > 0) poz++;
  pusta = true;
  while (pusta || pq != kq){
    dr[poz++] = q[pq++];
    if (pq == k) pq = 0;
    pusta = false;
  }
  int a = MAG, b = poz - 1;
  while (a > 1 && b > 1){
    a >>= 1; b >>= 1;
    FOR(i, a, b)
      dr[i] = max(dr[i << 1], dr[(i << 1) + 1]);
  }
  int st = MAG, konc = poz - 1;
  while(k--){
    poz = wyszukaj_max(st, konc - k);
    wypisz(dr[poz]);
    st = poz + 1;
  }
  return 0;
}
