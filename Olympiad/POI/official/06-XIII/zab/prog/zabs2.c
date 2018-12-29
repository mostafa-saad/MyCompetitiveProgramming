/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ZAB (¯aby)                                     *
 *   Plik:                zabs2.c                                        *
 *   Autor:               Jakub Pawlewicz                                *
 *   Opis:                Faza szukania odleg³o¶ci: Przegl±danie         *
 *                        wszystkich elektrod.                           *
 *                        Faza szukania szeroko¶ci: Find-Union           *
 *                        z sortowaniem kube³kowym.                      *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

#define INF 0x7FFFFFFF

static inline int max(int a, int b) { return a > b ? a : b; }

struct point {
  int x, y;
};

static inline int sqr(int x)
{
  return x * x;
}

static inline int dist(struct point a, struct point b)
{
  return sqr(a.x - b.x) + sqr(a.y - b.y);
}

#define MAX_WIDTH 1024
#define MAX_HEIGHT 1000
#define VEC_SIZE (MAX_WIDTH * (MAX_HEIGHT + 2))

static inline int point2int(struct point p)
{
  return (p.y + 1) * MAX_WIDTH + p.x + 1;
}

struct point size;
int n;
struct point electrodes[VEC_SIZE];

int dist_vec[VEC_SIZE];

void read(struct point *p)
{
  scanf("%d%d", &p->x, &p->y);
}

void read1(struct point *p)
{
  read(p);
  p->x--;
  p->y--;
}

int dist_to_electrodes(struct point p)
{
  int ret = INF;
  int i;
  for (i = 0; i < n; i++) {
    int d = dist(p, electrodes[i]);
    if (d < ret)
      ret = d;
  }
  return ret;
}

void compute_dist_vec()
{
  struct point p;
  for (p.y = -1; p.y <= size.y; p.y++)
    for (p.x = -1; p.x <= size.x; p.x++) {
      int idx = point2int(p);
      dist_vec[idx] = p.x < 0 || p.x == size.x || p.y < 0 || p.y == size.y
          ? -1 : dist_to_electrodes(p);
    }
}

int set[VEC_SIZE];

void set_init()
{
  struct point p;
  for (p.y = 0; p.y < size.y; p.y++)
    for (p.x = 0; p.x < size.x; p.x++) {
      int idx = point2int(p);
      set[idx] = idx;
    }
}

int set_find(int idx)
{
  int root = idx;
  while (set[root] != root)
    root = set[root];
  while (idx != root) {
    int next = set[idx];
    set[idx] = root;
    idx = next;
  }
  return root;
}

void set_union(int idx1, int idx2)
{
  set[set_find(idx2)] = set_find(idx1);
}

int bucket[2 * MAX_HEIGHT * MAX_HEIGHT + 1];
int next[VEC_SIZE];
#define NIL (-1)

static inline void try_union(int idx, int nidx)
{
  if (dist_vec[idx] <= dist_vec[nidx])
    set_union(idx, nidx);
}

int compute_width(int s, int e)
{
  if (s == e)
    return dist_vec[s];
  set_init();
  int max_dist = sqr(size.x) + sqr(size.y);
  int i;
  for (i = 0; i <= max_dist; i++)
    bucket[i] = NIL;
  struct point p;
  for (p.y = 0; p.y < size.y; p.y++)
    for (p.x = 0; p.x < size.x; p.x++) {
      int idx = point2int(p);
      int d = dist_vec[idx];
      next[idx] = bucket[d];
      bucket[d] = idx;
    }
  for (i = max_dist; ; i--) {
    int idx = bucket[i];
    if (idx == NIL)
      continue;
    do {
      try_union(idx, idx + 1);
      try_union(idx, idx + MAX_WIDTH);
      try_union(idx, idx - 1);
      try_union(idx, idx - MAX_WIDTH);
      idx = next[idx];
    } while(idx != NIL);
    if (set_find(s) == set_find(e))
      return i;
  }
}

int main()
{
  read(&size);
  struct point s, e;
  read1(&s);
  read1(&e);
  scanf("%d", &n);
  int i;
  for (i = 0; i < n; i++)
    read1(&electrodes[i]);
  compute_dist_vec();
  printf("%d\n", compute_width(point2int(s), point2int(e)));
  return 0;
}
