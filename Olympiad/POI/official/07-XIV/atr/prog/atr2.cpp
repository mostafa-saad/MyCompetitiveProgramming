/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Atrakcje turystyczne                                       *}
{*   Plik:    atr2.cpp                                                   *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Rozwiazanie wzorcowe O(k*(m+n)*log(n) + k^2*2^k), przy     *}
{*            uzyciu algorytmu Dijkstry z uzyciem set jako kolejki       *}
{*                                                                       *}
{*************************************************************************/
#include <algorithm>
#include <set>
#include <queue>
#include <cstdio>

using namespace std;

typedef pair<int,int> PII;
#define MP make_pair
#define FOR(v,p,k) for(int v=p;v<=k;++v)
#define FORD(v,p,k) for(int v=p;v>=k;--v)
#define REP(i,n) for(int i=0;i<(n);++i)
#define VAR(v,i) __typeof(i) v=(i)
#define FOREACH(i,c) for(VAR(i,(c).begin());i!=(c).end();++i)
#define ST first
#define ND second
const int INF = 1000000001;
const int MaxK=20;
const int MaxN=20000;
const int MaxM=1000000;
const int TabSize=2000001; // Max(2*MaxM+1, 2^MaxK)
const int BufS=351200;

int sol[BufS][MaxK]; // 370000 =~ 2*(MaxK po (MaxK/2))
int kol[BufS];
int kolhead;
int bf[TabSize];
int zb[TabSize];
short int wie[TabSize]; // Dla krawedzi - numer wierzcholka do ktorego prowadzi
int kra[MaxN+1]; // Dla wierzcholka - numer pierwszej krawedzi
int ks = 0; // Liczba uzywanych krawedzi
int ilezb[MaxK+2];
int odl[MaxK+3][MaxK+3];
int ogr[MaxK+3];
int n, m, k;

#define FKR(x,g,q) for(int x=kra[q];x!=-1;x=zb[x])

void Dodaj(int p, int k, int l) {
  wie[++ks]=k;
  bf[ks]=l;
  zb[ks] = kra[p];
  kra[p]=ks;
}

void CalcZb(int v, int k, int bity) {
  ilezb[bity]++;
  if (k>0) {
    CalcZb(v<<1, k-1, bity);
    CalcZb((v<<1)+1, k-1, bity+1);
  }
}

void GenZb(int v, int k, int bity) {
  zb[--ilezb[bity]] = v;
  if (k>0) {
    GenZb((v<<1)+1, k-1, bity+1);
    GenZb(v<<1, k-1, bity);
  }
}

void GenZbN() {
  FOR(x, 1, k+1) ilezb[x] = 0;
  ilezb[1] = 1;
  CalcZb(1, k-1, 1);
  FOR(x, 1, k) ilezb[x+1] += ilezb[x];
  zb[--ilezb[1]] = 1<<k;
  GenZb(1, k-1, 1);
}

void InicjujBufor() {
  kolhead = 0;
  REP(x, BufS) kol[x] = x+1;
  REP(x, (1<<k)+1) bf[x] = -1;
}

inline void DajBufor(int nr) {
  if (bf[nr] == -1) {
    bf[nr] = kolhead;
    REP(x, MaxK) sol[kolhead][x] = INF;
    kolhead = kol[kolhead];
  }
}

inline void ZwolnijBufor(int nr) {
  if (bf[nr] != -1) {
    kol[bf[nr]] = kolhead;
    kolhead = bf[nr];
  }
}

void WczytajDane() {
  REP(x,MaxN+1) kra[x] = -1;
  int pk, kk, wa, g;
  scanf("%d %d %d", &n, &m, &k);
  REP(x,m) {
    scanf("%d %d %d", &pk, &kk, &wa);
    Dodaj(pk, kk, wa);
    Dodaj(kk, pk, wa);
  }
  REP(x, k+2) ogr[x] = 0;
  scanf("%d", &g);
  REP(x, g) {
    scanf("%d %d", &pk, &kk);
    ogr[kk-1] |= (1<<(pk-2));
  }
}

void LiczOdlDijkstraSet() {
  int dist[n+1];
  bool vis[n+1];
  FOR(x,0,k+1) {
    REP(y,n+1) dist[y] = INF, vis[y] = 0;
    dist[x==k+1 ? n : x+1] = 0;
    set<PII> q;
    q.insert(MP(0, x==k+1 ? n : x+1));
    while(!q.empty()) {
      PII el = *(q.begin());
      q.erase(q.begin());
      if (!vis[el.ND]) {
        vis[el.ND] = 1;
        FKR(it, gr, el.ND) if (dist[wie[it]] > dist[el.ND] + bf[it]) {
          q.erase(MP(dist[wie[it]], wie[it]));
          dist[wie[it]] = dist[el.ND] + bf[it];
          q.insert(MP(dist[wie[it]], wie[it]));
        }
      }
    }
    FOR(y,0,k+1) odl[x][y] = dist[y==k+1 ? n : y+1];
  }
}

int Rozwiaz() {
  int zak = (1<<k) - 1;
  REP(x,k) if (!ogr[x+1]) {
    DajBufor(1<<x);
    sol[bf[1<<x]][x] = odl[0][x+1];
  }
  REP(it,zak) {
    int x = zb[it];
    if (bf[x]!=-1) {
      REP(y,k) if (!(x & (1<<y)) && (ogr[y+1] | x) == x) {
        REP(z,k) if (x & (1<<z)) {
          DajBufor(x | (1<<y));
          sol[bf[x | (1<<y)]][y] = min(sol[bf[x | (1<<y)]][y], odl[z+1][y+1] + sol[bf[x]][z]);
        }
      }
      if (x != zak)
        ZwolnijBufor(x);
    }
  }
  int res = INF;
  REP(x,k) res = min(res, sol[bf[zak]][x]+odl[x+1][k+1]);
  return res;
}

int main() {
  WczytajDane();
  LiczOdlDijkstraSet();
  if (!k)
  {
    printf("%d\n", odl[0][1]);
    return 0;
  }
  GenZbN();
  InicjujBufor();
  printf("%d\n", Rozwiaz());
  return 0;
}
