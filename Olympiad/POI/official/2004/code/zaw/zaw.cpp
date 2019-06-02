/*************************************************************************
 *                                                                       *
 *                    XI Olimpiada Informatyczna                         *
 *                                                                       *
 *   Rozwi±zanie zadania: Zawody                                         *
 *   Plik:                zaw.cpp                                        *
 *   Autor:               Tomasz Czajka                                  *
 *************************************************************************/

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

const int INF = 2000000000;

// kolejka priorytetowa
class Kolejka {
  public:
  // klucze 0..n-1, poczatkowa wartosc v
  Kolejka(int n,int v):rozmiar(n),heap(n+1),inHeap(n) {
    for(int i=0;i<n;++i) {
      heap[i+1].x = i;
      heap[i+1].v = v;
      inHeap[i] = i+1;
    }
  }
  bool empty() const { return rozmiar==0; }
  void extractMin(int &x,int &v) {
    x = heap[1].x;
    v = heap[1].v;
    xchg(1,rozmiar);
    inHeap[x]=0;
    --rozmiar;
    if(rozmiar>0) downheap(1);
  }
  bool containsKey(int x) const { return inHeap[x]!=0; }
  int value(int x) const { return heap[inHeap[x]].v; }
  void decreaseKey(int x,int v) {
    int poz = inHeap[x];
    heap[poz].v = v;
    upheap(poz);
  }

  private:
  struct Elem { int x,v; };
  int rozmiar;
  vector<Elem> heap;
  vector<int> inHeap; // 0 = brak
  
  bool cmp(int a,int b) const { return heap[a].v<heap[b].v; }
  void xchg(int a,int b) {
    swap(heap[a],heap[b]);
    inHeap[heap[a].x]=a;
    inHeap[heap[b].x]=b;
  }
  void upheap(int poz) {
    while(poz>1 && cmp(poz,poz>>1)) {
      xchg(poz,poz>>1);
      poz>>=1;
    }
  }
  void downheap(int poz) {
    for(;;) {
      poz<<=1;
      if(poz+1<=rozmiar && cmp(poz+1,poz)) ++poz;
      if(poz>rozmiar || !cmp(poz,poz>>1)) break;
      xchg(poz,poz>>1);
    }
  }
};


struct Krawedz {
  int x; // kierunek
  int w; // waga
  Krawedz(int x,int w):x(x),w(w) {}
};

typedef vector<Krawedz> VK;

struct Graf {
  int v; 
  vector<VK> e;
};

const int WW = 0; // wierzcholek wejsciowy w G
const int SS = 0; // start w G'
const int MM = 1; // meta w G'

void wczytaj(Graf &g) {
  int ne;
  cin >> g.v >> ne;
  g.e.assign(g.v,VK());
  for(int i=0;i<ne;++i) {
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    --a; --b;
    g.e[a].push_back(Krawedz(b,c));
    g.e[b].push_back(Krawedz(a,d));
  }
}

// oblicza odleglosci w d[] i pierwsze wierzcholki na sciezkach w p[]
// INF - nie da sie dojechac
void dijkstra(const Graf &g,int start,vector<int>&d,vector<int>&p) {
  d.assign(g.v,INF);
  p.assign(g.v,-1);
  Kolejka kol(g.v,INF);
  kol.decreaseKey(start,0);
  while(!kol.empty()) {
    int x,v;
    kol.extractMin(x,v);
    if(v==INF) break;
    d[x] = v;
    const VK &vk = g.e[x];
    for(VK::const_iterator it=vk.begin();it!=vk.end();++it) {
      int y = it->x;
      if(kol.containsKey(y) && v + it->w < kol.value(y)) {
        p[y] = x==start ? y : p[x]; 
        kol.decreaseKey(y, v + it->w);
      }
    }
  }
}

// v' = v+1
void zbudujG1(const Graf &g,const vector<int> &d, const vector<int> &p,
              Graf &g1) {
  g1.v = g.v + 1;
  g1.e.assign(g1.v,VK());
  for(int u=0;u<g.v;++u) if(d[u]!=INF) {
    const VK &vk=g.e[u];
    for(VK::const_iterator it=vk.begin();it!=vk.end();++it) {
      int v = it->x;
      int w = it->w;
      // d[v]!=INF, bo d[u]!=INF i jest krawedz u->v w G
      // mamy krawedz u->v o wadze w
      if(u==WW) {
        if(v!=p[v]) g1.e[SS].push_back(Krawedz(v+1,w));
      }
      else if(v==WW) {
        if(u==p[u]) g1.e[u+1].push_back(Krawedz(MM,w));
        else g1.e[SS].push_back(Krawedz(MM,d[u]+w));
      }
      else {
        if(p[u]==p[v]) g1.e[u+1].push_back(Krawedz(v+1,w));
        else g1.e[SS].push_back(Krawedz(v+1,d[u]+w));
      }
    }
  }
}

int main() {
  Graf g,g1;
  vector<int> d,p;
  wczytaj(g);
  dijkstra(g,WW,d,p);
  zbudujG1(g,d,p,g1);
  dijkstra(g1,SS,d,p);
  int wynik = d[MM];
  if(wynik==INF) cout << "NIE DA SIE!!!\n";
  else cout << wynik << "\n";
}
