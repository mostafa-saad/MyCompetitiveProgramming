/*************************************************************************
 *                                                                       *
 *                     XV  Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Clo (CLO)                                                 *
 *   Plik:     clos1.cpp                                                 *
 *   Autor:    Adam Iwanicki                                             *
 *   Opis:     Nieoptymalne rozwiazanie przyporzadkowujace wierzcholkom  *
 *             kraweidze przy pomocy skojarzenia metoda Hopcrofta-Karpa. *
 *             Zlozonosc O(m*sqrt(n))                                    *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cstdio>
#include <cstring>
#include <deque>
#include <utility>
#include <vector>

#define FOREACH(I,C)  for(__typeof((C).begin()) I=(C).begin(); I != (C).end(); ++I)
#define REP(i, x) for(int i=0;i<x;++i)

using namespace std;

typedef vector<int> VI;
struct Edge{
  int v; /*wierzcholek docelowy*/
};

struct Vertex{
  vector<Edge> kr;
  int t; /*dane pomocnicze*/
  int s; /*dane pomocnicze*/
  int le;
};

struct Graf{
  vector<Vertex> g;
  Graf(int n=0): g(n){}
  /*dodawanie krawedzi SKIEROWANEJ*/
  void AddEdge(int p,int k){Edge e; e.v=k; g[p].kr.push_back(e);}
  /*w polu t jest odleglosc (-1 jesli sie nie da dojsc) */
  /*w polu s jest numer ojca*/
  void Bfs(int v) {
    FOREACH(it, g) it->t=-1; g[v].t=0; g[v].s=-1;
    int kol[g.size()],p,k;
    kol[0]=v; p=k=0;
    while(p<=k) {
      v=kol[p++];
      FOREACH(it,g[v].kr) if (g[it->v].t==-1) {
        g[it->v].t=g[v].t+1; g[it->v].s=v;
        kol[++k]=it->v;
      }
    }
  }
  void Przenies(int v, Edge &e){
    int u=e.v;
    g[u].kr.push_back(e); g[u].kr.back().v=v;
    swap(g[v].kr.back(),e); g[v].kr.pop_back();
  }
  int UFend;
  bool UFDfs(int v){
    if (v==UFend) return true;
    g[v].s=1;
    FOREACH(it,g[v].kr){
      int u=it->v;
      if (g[u].t==1+g[v].t && !g[u].s && UFDfs(it->v)){
        Przenies(v,*it); return true;
      }
    }
    return false;
  }
  /*maksymalny przeplyw z v1 do v2 dla krawedzi jednostkowych*/
  /*UWAGA: graf ulega modyfikacji.*/
  int UnitFlow(int v1,int v2){
    int res=0; UFend=v2;
    while (1){
      Bfs(v1); if (g[v2].t==-1) break;
      FOREACH(it,g) it->s=0;
      FOREACH(it,g[v1].kr) if (UFDfs(it->v)) {res++; Przenies(v1, *it--);}
    }
    return res;
  }
  /*zwracany wektor mowi co z czym jest skojarzone, -1 jesli z niczym*/
  /*UWAGA: funkcja SILNIE modyfikuje graf*/
  VI Hopcroft(){
    int n=(int)g.size(); g.resize(n+2);
    REP(i,n) if (g[i].le) AddEdge(n,i); else AddEdge(i,n+1);
    VI res(n,-1); UnitFlow(n,n+1);
    REP(i,n) if (!g[i].le && g[i].kr[0].v!=n+1)
      res[ res[g[i].kr[0].v]=i ]=g[i].kr[0].v;
    return res;
  }
};

vector<pair<int,int> > edges;

int main(){
  int n,m;
  scanf("%d %d", &n, &m);

  Graf g(n+m);
  REP(i,n+m) {
    g.g[i].le = i<n;
  }
  REP(i,m) {
    int a,b;
    scanf("%d %d", &a, &b);
    g.AddEdge(a-1,n+i);
    g.AddEdge(b-1,n+i);
    edges.push_back(make_pair(a,b));
  }
  VI pom=g.Hopcroft();
  REP(i,n) {
    if( -1==pom[i] ) {
      printf("NIE\n");
      return 0;
    }
  }
  printf("TAK\n");
  REP(i,n) {
    printf("%d\n", edges[pom[i]-n].first == 1+i ? edges[pom[i]-n].second : edges[pom[i]-n].first );
  }
  return 0;
}
