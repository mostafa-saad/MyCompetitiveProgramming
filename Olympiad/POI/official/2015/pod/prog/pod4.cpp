/******************************************************************************
 *                                                                            *
 *                    XXII Olimpiada Informatyczna                            *
 *                                                                            *
 *   Zadanie:              Podzial naszyjnika                                 *
 *   Autor programu:       Jakub Radoszewski                                  *
 *   Zlozonosc czasowa:    O(n log n)                                         *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *                                                                            *
 *****************************************************************************/

#include <cstdio>
#include <utility>
#include <algorithm>
using namespace std;

const int MAX_N = 1000000;
const int INFTY = 100000000;
const pair<int, int> EMPTY = make_pair(1, 0);

int n, k;
int r[MAX_N];

/***************************************************/
/************ Drzewo przedzialowe ******************/
/***************************************************/

const int MAX_NODES = 4 * MAX_N;
int w[MAX_NODES], f[MAX_NODES];
int nodes;
const int root = 1;
int depth;

void build(int n) {
  nodes = 1;
  depth = 0;
  while (nodes <= n) {
    nodes *= 2;
    ++depth;
  }
}

inline int leaf(int j) {
  return nodes + j;
}

inline int parent(int v) {
  return v / 2;
}

inline int left(int v) {
  return 2 * v;
}

inline int right(int v) {
  return 2 * v + 1;
}

inline int a(int v, int d) {
  return (v - (1 << d)) << (depth - d);
}

inline int b(int v, int d) {
  return a(v, d) + (1 << (depth - d)) - 1;
}

inline void update(int v, int d) {
  if (w[v]) f[v] = b(v, d) - a(v, d) + 1;
  else if (v >= nodes) f[v] = 0;
  else f[v] = f[left(v)] + f[right(v)]; 
}

// przedzial [i, n - 1]
void insert(int i, int j, int val) {
  int v1 = leaf(i), v2 = leaf(j);
  int d = depth;
  w[v1] += val;
  if (v2 != v1) w[v2] += val;
  update(v1, d); update(v2, d);
  while (v1 != root) {
    if (v1 / 2 != v2 / 2) {
      if (v1 == left(parent(v1))) {
        int u = right(parent(v1));
        w[u] += val;
        update(u, d);
      }
      if (v2 == right(parent(v2))) {
        int u = left(parent(v2));
        w[u] += val;
        update(u, d);
      }
    }
    v1 = parent(v1); v2 = parent(v2);
    --d;
    update(v1, d); update(v2, d);
  }
}

// liczba pozycji dozwolonych
int query1() {
  return f[root];
}

int initial_sumw(int j) {
  int v = leaf(j);
  int sumw = w[v];
  while (v != root) {
    v = parent(v);
    sumw += w[v];
  }
  return sumw;
}

// dozwolony poprzednik
int query2_pred(int j) {
  int v = leaf(j);
  int d = depth;
  int sumw = initial_sumw(j);
  if (!sumw) return j;
  int node = -1;
  while (v != root) {
    sumw -= w[v];
    if (v == right(parent(v))) {
      int v1 = left(parent(v));
      if (sumw == 0 && f[v1] < b(v1, d) - a(v1, d) + 1) {
        node = v1;
        break;
      }
    }
    v = parent(v);
    --d;
  }
  if (node == -1) return -1;

  v = node;
  while (v < nodes) { // dopoki v nie jest lisciem
    int v1 = right(v);
    ++d;
    if (f[v1] < b(v1, d) - a(v1, d) + 1) v = v1;
    else v = left(v);
  }
  return v - nodes;
}

// dozwolony nastepnik
int query2_succ(int j) {
  if (j >= n) return -1;
  int v = leaf(j);
  int d = depth;
  int sumw = initial_sumw(j);
  if (!sumw) return j;
  int node = -1;
  while (v != root) {
    sumw -= w[v];
    if (v == left(parent(v))) {
      int v1 = right(parent(v));
      if (sumw == 0 && f[v1] < b(v1, d) - a(v1, d) + 1) {
        node = v1;
        break;
      }
    }
    v = parent(v);
    --d;
  }
  if (node == -1) return -1;

  v = node;
  while (v < nodes) { // dopoki v nie jest lisciem
    int v1 = left(v);
    ++d;
    if (f[v1] < b(v1, d) - a(v1, d) + 1) v = v1;
    else v = right(v);
  }
  return v - nodes;
}


/***************************************************/

int next[MAX_N];
pair<int, int> interval[MAX_N + 1];

int next_coral[MAX_N + 1], last_coral[MAX_N + 1];

void wyznacz_tablice() {
  for (int c = 1; c <= k; ++c)
    next_coral[c] = last_coral[c] = INFTY;
  for (int i = n - 1; i >= 0; --i) {
    next[i] = next_coral[r[i]];
    next_coral[r[i]] = i;
    if (last_coral[r[i]] == INFTY)
      last_coral[r[i]] = i;
  }
}

void poczatkowe_zabronione() {
  insert(n - 1, n - 1, +1);
  for (int c = 1; c <= k; ++c)
    if (next_coral[c] == last_coral[c]) { // n_c == 1
      interval[c] = EMPTY;
    } else {
      interval[c] = make_pair(next_coral[c], last_coral[c] - 1);
      insert(interval[c].first, interval[c].second, +1);
    }
}

void iteracja() {
  long long wyn1 = 0;
  int wyn2 = n;
  for (int i = 0; i < n - 1; ++i) {
    // obliczamy wyniki
    wyn1 += n - i - query1();
    int j = i + n/2 - 1;
    if (j >= n) j = n - 1;
    int opcja = query2_pred(j);
    if (opcja != -1 && opcja >= i) wyn2 = min(wyn2, max(opcja - i + 1, n - opcja + i - 1));
    opcja = query2_succ(j);
    if (opcja != -1 && opcja < n ) wyn2 = min(wyn2, max(opcja - i + 1, n - opcja + i - 1));

    // przesuwamy sie z pozycji i na pozycje i+1
    int c = r[i];
    if (interval[c] != EMPTY) {
      insert(interval[c].first, interval[c].second, -1);
      if (next[i] < INFTY) {
        interval[c] = make_pair(next[i], n - 1);
        insert(interval[c].first, interval[c].second, +1);
      } else {
        interval[c] = EMPTY;
      }
    }
  }
  printf("%lld %d\n", wyn1, wyn2 - (n - wyn2));
}

int main() {
  scanf("%d%d", &n, &k);
  for (int i = 0; i < n; ++i)
    scanf("%d", r + i);
  wyznacz_tablice();
  build(n);
  poczatkowe_zabronione();
  iteracja();
  return 0;
}
