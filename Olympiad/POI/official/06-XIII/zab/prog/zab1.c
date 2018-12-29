/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: ZAB (¯aby)                                     *
 *   Plik:                zab1.c                                         *
 *   Autor:               Jakub Pawlewicz                                *
 *   Opis:                Faza szukania odleg³o¶ci: Algorytm wêdrowców   *
 *                        z u¿yciem kube³ków.                            *
 *                        Faza szukania szeroko¶ci: Find-Union           *
 *                        z sortowaniem kube³kowym.                      *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define INF 0x7FFFFFFF

static inline int max(int a, int b) { return a > b ? a : b; }

struct point {
  int x, y;
};

static inline struct point right(struct point p)
{
  return (struct point) {p.x + 1, p.y};
}

static inline struct point up(struct point p)
{
  return (struct point) {p.x, p.y + 1};
}

static inline struct point left(struct point p)
{
  return (struct point) {p.x - 1, p.y};
}

static inline struct point down(struct point p)
{
  return (struct point) {p.x, p.y - 1};
}

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

static inline int int2x(int idx)
{
  return idx % MAX_WIDTH - 1;
}

static inline int int2y(int idx)
{
  return idx / MAX_WIDTH - 1;
}

struct point size;
int n;
struct point electrodes[VEC_SIZE];

int dist_vec[VEC_SIZE];
struct point source[VEC_SIZE];

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

enum {
  PLANE,
  QUARTER,
  HALFLINE
};

enum {
  RIGHT,
  UP,
  LEFT,
  DOWN
};

#define DIRS 4

static inline int prev_dir(int d)
{
  return (d + 3) & 3;
}

static inline struct point move(struct point p, int dir)
{
  switch (dir) {
  case RIGHT:
    return right(p);
  case UP:
    return up(p);
  case LEFT:
    return left(p);
  default: /* DOWN */
    return down(p);
  }
}

static inline int good_direction(int e, struct point m, struct point n)
{
  switch (e) {
  case RIGHT:
    return n.x < m.x;
  case UP:
    return n.y < m.y;
  case LEFT:
    return m.x < n.x;
  default: /* DOWN */
    return m.y < n.y;
  }
}

struct walker {
  int type;
  int dir;
  struct point pos;
  struct point source;
};

struct walker_list {
  struct walker walker;
  struct walker_list *next;
};

struct walker_list * walker_bucket[2 * MAX_HEIGHT * MAX_HEIGHT + 1];
int walker_cur_bucket;
int walkers_count;

void add_walker(struct walker *walker, int d)
{
  struct walker_list *l =
    (struct walker_list *) malloc(sizeof(struct walker_list));
  l->walker = *walker;
  l->next = walker_bucket[d];
  walker_bucket[d] = l;
  walkers_count++;
}

struct walker delmin_walker()
{
  while (!walker_bucket[walker_cur_bucket])
    walker_cur_bucket++;
  struct walker_list *l = walker_bucket[walker_cur_bucket];
  struct walker walker = l->walker;
  walker_bucket[walker_cur_bucket] = l->next;
  free(l);
  walkers_count--;
  return walker;
}

static inline void move_plane_and_reduce_dist(struct walker walker)
{
  int idx = point2int(walker.pos);
  if (dist_vec[idx] > 0) {
    dist_vec[idx] = 1;
    source[idx] = walker.source;
    add_walker(&walker, 1);
  }
}

void try_move_plane(struct walker *walker)
{
  int d;
  for (d = 0; d < DIRS; d++)
    move_plane_and_reduce_dist((struct walker)
                               {QUARTER, d,
                                   move(walker->pos, d), walker->source});
}

int try_move_and_reduce_dist(struct walker walker, int destp_idx,
                             int walker_dist)
{
  if (walker_dist < dist_vec[destp_idx]) {
    dist_vec[destp_idx] = walker_dist;
    source[destp_idx] = walker.source;
    add_walker(&walker, walker_dist);
    return 1;
  } else
    return 0;
}

int try_forced_move(int e, struct walker walker, int destp_idx,
                    int walker_dist)
{
  if (good_direction(e, walker.source, source[destp_idx])) {
    add_walker(&walker, walker_dist);
    return 1;
  } else
    return 0;
}

void try_move_halfline(struct walker *walker)
{
  int e0 = walker->dir;
  struct walker w0 = {HALFLINE, e0, move(walker->pos, e0), walker->source};
  int idx0 = point2int(w0.pos);
  int d0 = dist(w0.pos, w0.source);
  if (!try_move_and_reduce_dist(w0, idx0, d0) && dist_vec[idx0] > 0)
    try_forced_move(e0, w0, idx0, d0);
}

void try_move_quarter(struct walker *walker)
{
  int w1_created = 1;
  int e1 = walker->dir;
  struct walker w1 = {QUARTER, e1, move(walker->pos, e1), walker->source};
  int idx1 = point2int(w1.pos);
  int d1 = dist(w1.pos, w1.source);
  if (dist_vec[idx1] < 0) {
    struct walker walker_new = *walker;
    walker_new.dir = prev_dir(e1);
    try_move_halfline(&walker_new);
    return;
  }
  if (!try_move_and_reduce_dist(w1, idx1, d1))
    if (!try_forced_move(e1, w1, idx1, d1))
      w1_created = 0;

  int e0 = prev_dir(e1);
  struct walker w0 = {w1_created ? HALFLINE : QUARTER, w1_created ? e0 : e1,
                      move(walker->pos, e0), walker->source};
  int idx0 = point2int(w0.pos);
  int d0 = dist(w0.pos, w0.source);
  if (!try_move_and_reduce_dist(w0, idx0, d0) && dist_vec[idx0] > 0)
    if (!try_forced_move(e0, w0, idx0, d0))
      if (!w1_created)
        try_forced_move(e1, w0, idx0, d0);
}

void try_move(struct walker *walker)
{
  switch (walker->type) {
  case PLANE:
    try_move_plane(walker);
    break;
  case QUARTER:
    try_move_quarter(walker);
    break;
  default: /* HALFLINE */
    try_move_halfline(walker);
  }
}

void compute_dist_vec()
{
  struct point p;
  for (p.y = -1; p.y <= size.y; p.y++)
    for (p.x = -1; p.x <= size.x; p.x++) {
      int idx = point2int(p);
      dist_vec[idx] =
        p.x < 0 || p.x == size.x || p.y < 0 || p.y == size.y ? -1 : INF;
    }

  int d ;
  for (d = 0; d <= sqr(size.x) + sqr(size.y); d++)
    walker_bucket[d] = 0;
  walker_cur_bucket = 0;
  
  walkers_count = 0;
  int i;
  for (i = 0; i < n; i++) {
    struct point p = electrodes[i];
    struct walker w = {PLANE, 0, p, p};
    add_walker(&w, 0);
    int idx = point2int(p);
    dist_vec[idx] = 0;
    source[idx] = p;
  }

  while (walkers_count) {
    struct walker w = delmin_walker();
    try_move(&w);
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
