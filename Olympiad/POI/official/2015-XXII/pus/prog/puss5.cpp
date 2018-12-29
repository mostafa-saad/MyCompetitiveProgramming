/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Pustynia                                           *
 *   Autor programu:       Bartosz Tarnawski                                  *
 *   Zlozonosc czasowa:    O(nk)                                              *
 *   Opis:                 Rozwiazanie wolne                                  *
 *                                                                            *
 *****************************************************************************/


#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

const int K = 1000 * 1000 * 1000;
const int N = 100 * 1000;
const int M = 200 * 1000;
const int V = N;

int deg_in[V], d[V], ini[V];
vector< pair<int, int> > g[V];

int n, w, m;

void failure() {
  printf("NIE\n");
  exit(0);
}

void process_graph() {
  vector<int> sources;
  for(int i = 0; i < n; i++) {
    d[i] = K;
    for(auto e : g[i]) {
      deg_in[e.first]++;
    }
  }
  int cnt = 0;
  for(int i = 0; i < n; i++) {
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
  if(cnt != n) {
    failure();
  }
  printf("TAK\n");
  for(int i = 0; i < n; i++) {
    printf("%d ", d[i]);
  }
  printf("\n");
};

void add_edge(int x, int y, int w = 0) {
  g[x].push_back({y, w});
}

void add_edges(vector<int> v, vector<int> w) {
  for(int u: v) {
    for(int t: w) {
      add_edge(u, t, 1);
    }
  }
}

int main() {
  scanf("%d%d%d", &n, &w, &m);
  for(int i = 0; i < w; i++) {
    int p, de;
    scanf("%d%d", &p, &de);
    ini[p - 1] = de;
  }
  for(int i = 0; i < m; i++) {
    int l, r, k;
    scanf("%d%d%d", &l, &r, &k);
    l--, r--;
    int last = l - 1;
    vector<int> v1, v2;
    for(int j = 0; j < k; j++) {
      int x;
      scanf("%d", &x);
      x--;
      v1.push_back(x);
      for(int k = last + 1; k <= x - 1; k++) {
        v2.push_back(k);
      }
      last = x;
    }
    for(int k = last + 1; k <= r; k++) {
      v2.push_back(k);
    }
    add_edges(v1, v2);
  }
  process_graph();
  return 0;
};
