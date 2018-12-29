/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Atrakcje turystyczne                                       *}
{*   Plik:    atrb4.cpp                                                  *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Rozwiazanie wzorcowe O(k*(m+n)*log(n) + k^2*2^k), w za     *}
{*            duzej pamieci, ale dostajace dodatnie punkty (zapisane     *}
{*            poprawnie dla k <= 19                                      *}
{*                                                                       *}
{*************************************************************************/
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

typedef pair<int,int> PII;
#define MP make_pair
#define FOR(v,p,k) for(int v=p;v<=k;++v)
#define REP(i,n) for(int i=0;i<(n);++i)
#define VAR(v,i) __typeof(i) v=(i)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define ST first
#define ND second
const int INF = 1000000001;
const int MaxK=19;
const int MaxN=20000;

int sol[(1<<MaxK)+1][MaxK+2];
struct Kraw {int v, l;};
vector<vector<Kraw> > gr;
int odl[MaxK+3][MaxK+3];
int ogr[MaxK+3];
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
  int dist[n];
  bool vis[n];
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

int Rozwiaz() {
  int zak = (1<<(k-1)) - 1;
  REP(x,(1<<(k-1))) FOR(y,0,k) sol[x][y] = INF;
  FOR(x,1,k-1) if (!ogr[x])
    sol[1<<(x-1)][x] = odl[0][x];
  FOR(x,1,zak) {
    FOR(y,1,k-1) if (!(x & (1<<(y-1))) && (ogr[y] | x) == x)
      FOR(z,1,k-1) if (x & (1<<(z-1)))
        sol[x | (1<<(y-1))][y] = min(sol[x | (1<<(y-1))][y], odl[z][y] + sol[x][z]);
  }
  int res = INF;
  FOR(x,1,k-1) res = min(res, sol[zak][x]+odl[x][k]);
  return res;
}

int main() {
  WczytajDane();
  LiczOdl();
  printf("%d\n", Rozwiaz());
  return 0;
}
