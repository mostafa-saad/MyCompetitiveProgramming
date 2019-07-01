/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Pustynia                                           *
 *   Autor programu:       Bartosz Tarnawski                                  *
 *   Zlozonosc czasowa:    O((n + k) log n)                                   *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/


#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int K = 1000 * 1000 * 1000;
const int N = 100 * 1000;
const int M = 200 * 1000;
const int SN = 128 * 1024;
const int V = 2 * SN + M;

int deg_in[V], d[V], ini[V];
vector< pair<int, int> > g[V];

int n, w, m;
int nm, bn, bm;

void failure() {
  printf("NIE\n");
  exit(0);
}

void process_graph() {
  vector<int> sources;
  for(int i = 0; i < nm; i++) {
    d[i] = K;
    for(auto e : g[i]) {
      deg_in[e.first]++;
    }
  }
  int cnt = 0;
  for(int i = 0; i < nm; i++) {
    if(deg_in[i] == 0) {
      sources.push_back(i);
      cnt++;
    }
  }
  while(!sources.empty()) {
    int s = sources.back();
    sources.pop_back();
    if(d[s] <= 0) {
      failure();
    } 
    if(ini[s]) {
      if(d[s] < ini[s]) {
        failure();
      }
      d[s] = ini[s];
    }
    for(auto e : g[s]) {
      int u = e.first;
      d[u] = min(d[u], d[s] - e.second);
      deg_in[u]--;
      if(deg_in[u] == 0) {
        sources.push_back(u);
        cnt++;
      }
    }
  }
  if(cnt != nm) {
    failure();
  }
  printf("TAK\n");
  for(int i = 0; i < n; i++) {
    printf("%d ", d[bn + i]);
  }
  printf("\n");
};

void add_edge(int x, int y, int w = 0) {
  g[x].push_back({y, w});
}

void add_verts() {
  int sn = 1;
  while(sn < n) sn *= 2;
  nm = 2 * sn + m;
  bn = sn, bm = 2 * sn;
  for(int i = 1; i < sn; i++) {
    add_edge(i, 2 * i);
    add_edge(i, 2 * i + 1);
  }
}

void add_edges(int v, int l, int r) {
  if(l > r) return;
  add_edge(v, l);
  if(l != r) {
    add_edge(v, r);
  }
  while((l / 2) != (r / 2)) {
    if(l % 2 == 0) add_edge(v, l + 1);
    if(r % 2 == 1) add_edge(v, r - 1);
    l /= 2, r /= 2;
  }
}

int main() {
  scanf("%d%d%d", &n, &w, &m);
  add_verts();
  for(int i = 0; i < w; i++) {
    int p, de;
    scanf("%d%d", &p, &de);
    ini[bn + p - 1] = de;
  }
  for(int i = 0; i < m; i++) {
    int l, r, k;
    scanf("%d%d%d", &l, &r, &k);
    l--, r--;
    int last = l - 1;
    for(int j = 0; j < k; j++) {
      int x;
      scanf("%d", &x);
      x--;
      add_edge(bn + x, bm + i, 1);
      add_edges(bm + i, bn + last + 1, bn + x - 1);
      last = x;
    }
    add_edges(bm + i, bn + last + 1, bn + r);
  }
  process_graph();
  return 0;
};
