/* Slower solution of TRA/jlac012
 * Brutal O(n^2) solution, for each west junction search the whole graph
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

int n, m, A, B, west_size;
int i, l;
int tmp1, tmp2;
elem_t *edges[MAXN];/* junctions in road network */
int eastern[MAXN]; /* equals 1 when junction lies on the east bank */
pair_t west[MAXN]; /* junctions on west riverbank */
size_t visited[MAXN];

void merge_sort(int l, int r) {
  int m = l + (r - l + 1)/2;
  pair_t tab[r - l];
  int a, b, c;
  if (r == l + 1) return;
  merge_sort(l, m);
  merge_sort(m, r);
  a = l;  b = m;  c = 0;
  while (a < m || b < r) {
    if (a < m && (b == r || west[a].first < west[b].first))
      tab[c++] = west[a++];
    else
      tab[c++] = west[b++];
  }
  for (i = 0; i < r-l; ++i) west[i + l] = tab[i];
}

void read_input() {
  west_size = 0;
  scanf ("%d %d %d %d", &n, &m, &A, &B);
  for (i = 1; i <= n; ++i) {
    scanf ("%d %d", &tmp1, &tmp2);
    eastern[i] = 0;
    edges[i] = NULL;
    if (tmp1 == 0) {
      west[west_size].first = tmp2;
      west[west_size++].second = i;
    } else if (tmp1 == A) eastern[i] = 1;
  }
  merge_sort(0, west_size);
  while (m-->0) {
    scanf ("%d %d %d", &tmp1, &tmp2, &i);
    push(edges + tmp1, tmp2);
    if (i == 2) push(edges + tmp2, tmp1);
  }
}

int reachable(int v) {
  int result = 0;
  elem_t *q = NULL, *tmp;
  push(&q, v);
  while (q != NULL) {
    i = pop(&q);
    result += eastern[i];
    for (tmp = edges[i]; tmp != NULL; tmp = tmp->nx) {
      l = tmp->x;
      if (visited[l] != west_size) { visited[l] = west_size; push(&q, l); }
    }
  }
  return result;
}

void generate_output() {
  for (i = 1; i <= n; ++i) visited[i] = 0;
  while (west_size > 0) {
    printf ("%d\n", reachable(west[west_size-1].second));
    --west_size;
  }
}

int main() {
  read_input();
  generate_output();
  return 0;
}
