/*************************************************************************}
{*                                                                       *}
{*                              XIV OI                                   *}
{*                                                                       *}
{*   Zadanie: Atrakcje turystyczne                                       *}
{*   Plik:    atrs2.cpp                                                  *}
{*   Autor:   Piotr Stanczyk                                             *}
{*   Opis:    Rozwiazanie wzorcowe O(k*(m+n^2) + k^2*2^k)                *}
{*            (implementacja rozwiazania wzorcowego z generatorem        *}
{*            wszystkich podzbiorow w czasie O(n logn) i przy uzyciu     *}
{             algorytmu Dijkstry z uzyciem prostej listy).               *}
{*                                                                       *}
{*************************************************************************/
#include <algorithm>
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

inline int Bity(int b) {
  int r=0;
  while(b) {
    r++;
    b &= (b-1);
  }
  return r;
}

void GenZbNlogN() {
  REP(x, 1<<k) zb[x] = x+1 + (Bity(x+1) << MaxK);
  sort(zb, zb + (1<<k));
  REP(x,1<<k) zb[x] &= (1<<MaxK)-1;
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

void LiczOdln2() {
  int dist[n+1];
  bool vis[n+1];
  FOR(x,0,k+1) {
    REP(y,n+1) dist[y] = INF, vis[y] = 0;
    dist[x==k+1 ? n-1 : x] = 0;
    REP(y,n) {
      int best = 0;
      while(vis[best]) best++;
      REP(z,n) if (!vis[z] && dist[z] < dist[best]) best=z;
      vis[best] = 1;
      FKR(it, gr, best+1)
        dist[wie[it]-1] = min(dist[wie[it]-1], dist[best] + bf[it]);
    }
    FOR(y,0,k+1)  odl[x][y] = dist[y==k+1 ? n-1 : y];
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
  LiczOdln2();
  if (!k)
  {
    printf("%d\n", odl[0][1]);
    return 0;
  }
  GenZbNlogN();
  InicjujBufor();
  printf("%d\n", Rozwiaz());
  return 0;
}
