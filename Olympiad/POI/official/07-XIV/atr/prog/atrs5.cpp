/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Atrakcje turystyczne                                       *}
{*   Plik:    atrs5.cpp                                                  *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Rozwiazanie alternatywne O(k*n^2 + k^2*p), gdzie p - liczba*}
{*            poprawnych permutacji, z obcinaniem szukania permutacji.   *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <queue>
#include <vector>
using namespace std;
typedef long long LL;
typedef pair<int,int> PII;
#define MP make_pair
#define FOR(v,p,k) for(int v=p;v<=k;++v)
#define FORD(v,p,k) for(int v=p;v>=k;--v)
#define REP(i,n) for(int i=0;i<(n);++i)
#define VAR(v,i) __typeof(i) v=(i)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define PB push_back
#define ST first
#define ND second
#define SIZE(x) (int)x.size()
#define ALL(c) c.begin(),c.end()
const int INF = 1000000001;
const int MaxK=20;
const int MaxN=20000;

struct Kraw {int v, l;};
vector<vector<Kraw> > gr;
int odl[MaxK+2][MaxK+2];
int ogr[MaxK+2];
int n, m, k;

void WczytajDane() {
  int pk, kk, g;
  scanf("%d %d %d", &n, &m, &k);
  k++;
  gr.resize(n);
  Kraw kr;
  REP(x,m) {
    scanf("%d %d %d", &pk, &kr.v, &kr.l);
    pk--; kr.v--;
    gr[pk].push_back(kr);
    swap(kr.v, pk);
    gr[pk].push_back(kr);
  }
  REP(x, k+1) ogr[x] = 0;
  scanf("%d", &g);
  REP(x, g) {
    scanf("%d %d", &pk, &kk);
    ogr[kk-1] |= (1<<(pk-2));
  }
}


void LiczOdl() {
  int dist[n+1];
  bool vis[n+1];
  FOR(x,0,k) {
    REP(y,n) dist[y] = INF, vis[y] = 0;
    dist[x==k ? n-1 : x] = 0;
    priority_queue<PII> queue;
    queue.push(MP(0, x==k ? n-1 : x));
    while(!queue.empty()) {
      PII el = queue.top();
      queue.pop();
      if (!vis[el.ND]) {
        vis[el.ND] = 1;
        FOREACH(it, gr[el.ND]) if (dist[it->v] > dist[el.ND] + it->l) {
          dist[it->v] = dist[el.ND] + it->l;
          queue.push(MP(-dist[it->v], it->v));
        }
      }
    }
    FOR(y,0,k) odl[x][y] = dist[y==k ? n-1 : y];
  }
}

int elGorne[MaxK+2];
int bestDist;

void GenPerm(int lastEl, int len, int zbior, int elS, int kroki) {
  if (kroki == 0) {
    bestDist = min(bestDist, len + odl[lastEl][k]);
  } else
  {
    if (lastEl != 0)
      FOR(x,1,k-1) if ((zbior | ogr[x]) == zbior && (ogr[x] & (1<<(lastEl-1))))
        elGorne[elS++] = x;
    REP(x,elS) {
      int t = elGorne[x];
      elGorne[x] = elGorne[elS-1];
      GenPerm(t, len+odl[lastEl][t], zbior | (1<<(t-1)), elS-1, kroki-1);
      elGorne[elS-1] = elGorne[x];
      elGorne[x] = t;
    }
  }
}


int Rozwiaz() {
  bestDist = INF;
  int len = 0;
  FOR(x,1,k-1) if (ogr[x] == 0) elGorne[len++] = x;
  GenPerm(0, 0, 0, len, k-1);
  return bestDist;
}

int main() {
  WczytajDane();
  LiczOdl();
  if (!k)
  {
    printf("%d\n", odl[0][1]);
    return 0;
  }
  printf("%d\n", Rozwiaz());
  return 0;
}
