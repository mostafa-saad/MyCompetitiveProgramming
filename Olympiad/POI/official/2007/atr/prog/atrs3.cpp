/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Atrakcje turystyczne                                       *}
{*   Plik:    atrs3.cpp                                                  *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Rozwiazanie alternatywne O(k*n^2 + k*k!), generuje         *}
{*            wszystkie mozliwe permutacje zbiorow.                      *}
{*                                                                       *}
{*************************************************************************/
#include <cstdio>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
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
#include <queue>
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
        FOREACH(it, gr[el.ND]) if (dist[it->v] > dist[el.ND] + it->l) 
{
          dist[it->v] = dist[el.ND] + it->l;
          queue.push(MP(-dist[it->v], it->v));
        }
      }
    }
    FOR(y,0,k) odl[x][y] = dist[y==k ? n-1 : y];
  }
}

int sol = INF;
int V[MaxK];
void PermOk(){
  int c = 0;
  bool niezg = 0;
  REP(x,k-1) {
    if ((ogr[V[x]] | c) != c)
      niezg = 1;
    c |= (1 << (V[x]-1));
  }
  if (!niezg) {
    int act = odl[0][V[0]] + odl[V[k-2]][k];
    REP(x,k-2) act += odl[V[x]][V[x+1]];
    sol = min(sol, act);
  }
}

void PermMinTrSas(int s) {
  int x,k,i=0;
  vector<int> c(s, 1);
  vector<bool> pr(s, 1);
  c[s-1] = 0;
  PermOk();
  while(i < s-1) {
    i=x=0;
    while(c[i] == s-i) {
      pr[i]=!pr[i];
      if(pr[i]) x++;
      c[i++]=1;
    }
    if(i < s-1) {
      k = pr[i] ? c[i]+x : s-i-c[i]+x;
      swap(V[k-1], V[k]);
      PermOk();
      c[i]++;
    }
  }
}


int Rozwiaz() {
  REP(x,k-1) V[x] = x+1;
  PermMinTrSas(k-1);
  return sol;
}

int main() {
  WczytajDane();
  LiczOdl();
  if (k == 1)
  {
    printf("%d\n", odl[0][1]);
    return 0;
  }
  printf("%d\n", Rozwiaz());
  return 0;
}
