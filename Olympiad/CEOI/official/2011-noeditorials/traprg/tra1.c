/* Model solution of task TRA/jlac012
 * Author: Mateusz Baranowski
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 300001

typedef struct {
  int first, second;
} pair_t;

typedef struct elem {
  int x;
  struct elem * nx;
} elem_t;

void push(elem_t ** el, int x) {
  elem_t *tmp = malloc(sizeof(elem_t));
  tmp->nx = *el;
  tmp->x = x;
  *el = tmp;
}

int pop(elem_t **el) {
  int result;
  elem_t *tmp;
  if (*el == NULL) return -1;
  tmp = (*el)->nx;
  result= (*el)->x;
  free(*el);
  *el = tmp;
  return result;
}

int max(int a, int b) { return (a < b)? b : a; }
int min(int a, int b) { return (a < b)? a : b; }
pair_t make_pair(int a, int b) {
  pair_t result;
  result.first = a;
  result.second = b;
  return result;
}

int n, m, A, B;
int i, l, j, k;
int west_size, east_size;
int tmp1, tmp2;
int scc_size; /* number of strongly connected components */
int west[MAXN], east[MAXN]; /* junctions on respective river banks */
elem_t *edges[MAXN]; /* streets in road network */
elem_t *edges_rev[MAXN]; /* edges in reversed network */
elem_t *scc[MAXN]; /* vertices in strongly connected component */
int visited[MAXN]; /* was a junction visited */
int order[MAXN]; /* dfs post-order of junctions */
int scc_inv[MAXN]; /* the scc for given junction */
int scc_edges[MAXN]; /* number of edges starting from scc */
pair_t interval[MAXN]; /* intervals of junctions reachable from junction */
pair_t *tab1;

void merge_sort(int l, int r) {
  int m = l + (r - l + 1)/2;
  pair_t tab[r - l];
  int a, b, c;
  if (r == l + 1) return;
  merge_sort(l, m);
  merge_sort(m, r);
  a = l;  b = m;  c = 0;
  while (a < m || b < r) {
    if (a < m && (b == r || tab1[a].first < tab1[b].first))
      tab[c++] = tab1[a++];
    else
      tab[c++] = tab1[b++];
  }
  for (i = 0; i < r-l; ++i) tab1[i + l] = tab[i];
}

void reorder(int v) {
  elem_t *it = edges[v];
  visited[v] = 1;
  while (it != NULL) {
    if (!visited[it->x]) reorder(it->x);
    it = it->nx;
  }
  order[l++] = v;
}

void mark_scc(int v) {
  elem_t *it = edges_rev[v];
  visited[v] = 0;
  push(scc + scc_size, v);
  scc_inv[v] = scc_size;
  while (it != NULL) {
    if (visited[it->x]) mark_scc(it->x);
    it = it->nx;
  }
}

void calculate_strongly_connected_components() {
  elem_t *it;
  for (i = 0; i < n; ++i) visited[i] = 0;
  l = 0; scc_size = 0;
  for (i = 0; i < n; ++i) if (!visited[i]) reorder(i);
  for (i = n-1; i >= 0; --i) if (visited[order[i]]) {
    mark_scc(order[i]);
    ++scc_size;
  }
  for (i = 0; i < scc_size; ++i) scc_edges[i] = 0;
  for (i = 0; i < n; ++i) {
    it = edges[i];
    while (it != NULL) {
      if (scc_inv[it->x] != scc_inv[i]) ++scc_edges[scc_inv[i]];
      it = it->nx;
    }
  }
}

void add_interval (pair_t * a, pair_t b) {
  if (b.first == -1) return;
  if (a->first == -1) { *a = b; return; }
  a->first = min(a->first, b.first);
  a->second = max(a->second, b.second);
}

void calculate_reachable_intervals() {
  elem_t *it, *q = NULL;
  for (i = 0; i < n; ++i) visited[i] = 0;
  for (i = 0; i < scc_size; ++i) interval[i] = make_pair(-1, -1);
  for (j = 0; j < east_size; ++j) {
    l = scc_inv[east[j]];
    add_interval (interval + l, make_pair(j, j));
  }
  for (l = 0; l < scc_size; ++l) if (scc_edges[l] == 0) { visited[l] = 1; push(&q, l); }
  while (q != NULL) {
    k = pop(&q);
    for (it = scc[k]; it != NULL; it = it->nx) {
      i = it->x;
      while (edges_rev[i] != NULL) {
        l = scc_inv[pop(edges_rev + i)];
        add_interval(interval + l, interval[k]);
        if (--scc_edges[l] == 0) {
          visited[l] = 1;
          push(&q, l);
        }
      }
    }
  }
}

void mark_reachable_industrial() {
  for (i = 0; i < n; ++i) visited[i] = 0;
  l = 0;
  for (j = 0; j < west_size; ++j) if (!visited[west[j]]) reorder(west[j]);
  for (i = 0; i < n; ++i) order[i] = 0;
  order[0] = visited[east[0]];
  for (j = 1; j < east_size; ++j)
    order[j] = order[j-1] + visited[east[j]];
}

void read_input() {
  pair_t west_tmp[MAXN], east_tmp[MAXN];
  west_size = 0; east_size = 0;
  scanf ("%d %d %d %d", &n, &m, &A, &B);
  for (i = 0; i < n; ++i) {
    edges[i] = NULL;
    edges_rev[i] = NULL;
    scc[i] = NULL;
    scanf ("%d %d", &tmp1, &tmp2);
    if (tmp1 == 0) west_tmp[west_size++] = make_pair(tmp2, i);
    else if (tmp1 == A) east_tmp[east_size++] = make_pair(tmp2, i);
  }
  /* sort junctions according to increasing second coordinates */
  tab1 = west_tmp;
  merge_sort(0, west_size);
  for (j = 0; j < west_size; ++j) west[j] = west_tmp[j].second;
  tab1 = east_tmp;
  merge_sort(0, east_size);
  for (j = 0; j < east_size; ++j) { east[j] = east_tmp[j].second;
  }
  while (m-->0) {
    scanf("%d %d %d", &tmp1, &tmp2, &i);
    --tmp1; --tmp2;
    push(edges + tmp1, tmp2);
    push(edges_rev + tmp2, tmp1);
    if (i == 2) {
      push(edges + tmp2, tmp1);
      push(edges_rev + tmp1, tmp2);
    }
  }
}

void write_output() {
  l = west_size;
  for (--l; l >= 0; --l) {
    tmp1 = interval[scc_inv[west[l]]].first;
    tmp2 = interval[scc_inv[west[l]]].second;
    if (tmp1 == -1) printf("0\n");
    else if (tmp1 == 0) printf("%d\n", order[tmp2]);
    else printf("%d\n", order[tmp2] - order[tmp1-1]);
  }
}

int main() {
  read_input();
  calculate_strongly_connected_components();
  calculate_reachable_intervals();
  mark_reachable_industrial();
  write_output();
  return 0;
}
