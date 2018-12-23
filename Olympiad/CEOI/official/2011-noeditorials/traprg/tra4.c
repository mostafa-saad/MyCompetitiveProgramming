/* Alternative solution of TRA/jlac012
 * Searching for lowest and highest reachable eastern junction
 * Author: Mateusz Baranowski
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 300003

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

size_t j;
int n, m, A, B;
int i, l, k;
int west_size, east_size;
int tmp1, tmp2;
int west[MAXN], east[MAXN]; /* junctions on respective river banks */
elem_t *edges[MAXN]; /* streets in road network */
elem_t *edges_rev[MAXN]; /* edges in reversed network */
int visited[MAXN]; /* was a junction visited */
int visited2[MAXN]; /* whether a juntion was visited */
int eastern[MAXN]; /* the number of eastern bank junction for node */
pair_t interval[MAXN]; /* intervals of junctions reachable from junction */
pair_t *tab1;

void merge_sort(int l, int r) {
  int m = l + (r - l + 1)/2;
  pair_t tab[r - l + 2];
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

/* check which junctions are reachable from nodes through current_edges */
void visit(int size, int * nodes, elem_t ** current_edges) {
  elem_t *it, *q = NULL;
  for (i = 0; i < n; ++i) visited[i] = 0;
  for (i = 0; i < size; ++i) {
    visited[nodes[i]] = 1;
    push(&q, nodes[i]);
  }
  while (q != NULL) {
    i = pop(&q);
    for (it = current_edges[i]; it != NULL; it = it->nx) {
      l = it->x;
      if (!visited[l]) { visited[l] = 1; push(&q, l); }
    }
  }
}

/* mark reachable eastern junctions */
void mark_reachable_east() {
  visit(west_size, west, edges);
  for (i = 0; i < n; ++i) eastern[i] = -1;
  l = 0;
  for (j = 0; j < east_size; ++j)
    if (visited[east[j]]) eastern[east[j]] = l++;
}

void read_input() {
  pair_t west_tmp[MAXN], east_tmp[MAXN];
  west_size = 0; east_size = 0;
  scanf ("%d %d %d %d", &n, &m, &A, &B);
  for (i = 0; i < n; ++i) {
    edges[i] = NULL;
    edges_rev[i] = NULL;
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
  for (j = 0; j < east_size; ++j) east[j] = east_tmp[j].second;
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

/* find northernmost (when k==0 southernmost) eastern junction reachable from v */
int visit_and_find(int v, int p) {
  elem_t *q = NULL, *it;
  push(&q, v);
  visited2[v] = 1;
  while (q != NULL) {
    i = pop(&q);
    if ((k == 1 && eastern[i] > p) || (k == 0 && eastern[i] < p && eastern[i] != -1))
      p = eastern[i];
    for (it = edges[i]; it != NULL; it = it->nx) {
      l = it->x;
      if (!visited2[l]) { visited2[l] = 1; push(&q, l); }
    }
  }
  return p;
}

void calculate_output() {
  int l = west_size;
  /* calculate southernmost reachable eastern bank junction */
  tmp1 = MAXN;
  k = 0;
  for (i = 0; i < n; ++i) visited2[i] = 0;
  for (--l; l >= 0; --l) if (visited[west[l]]) {
    tmp1 = visit_and_find(west[l], tmp1);
    interval[l].first = tmp1;
  }
  /* calculate northernmost reachable eastern bank junction */
  tmp1 = -1;
  k = 1;
  for (i = 0; i < n; ++i) visited2[i] = 0;
  for (j = 0; j < west_size; ++j) if (visited[west[j]]) {
    tmp1 = visit_and_find(west[j], tmp1);
    interval[j].second = tmp1;
  }
}

void write_output() {
  l = west_size;
  for (--l; l >= 0; --l)
    if (visited[west[l]])
      printf("%d\n", interval[l].second - interval[l].first + 1);
    else
      printf("0\n");
}

int main() {
  read_input();
  mark_reachable_east();
  visit(east_size, east, edges_rev);
  calculate_output();
  write_output();
  return 0;
}
