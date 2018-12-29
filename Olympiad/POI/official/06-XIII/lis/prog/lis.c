/*************************************************************************
 *                                                                       *
 *                   XIII Olimpiada Informatyczna                        *
 *                                                                       *
 *   Rozwi±zanie zadania: LIS (Listonosz)                                *
 *   Plik:                lis.c                                          *
 *   Autor:               Jakub Pawlewicz                                *
 *   Opis:                Program wzorcowy.                              *
 *                                                                       *
 *************************************************************************/

#include <stdio.h>

#define MAX_N  50000
#define MAX_M  200000
#define MAX_T  10000

int n;
int m;

struct node {
  int count;
  int memidx;
};

struct edge {
  int a, b;
};

struct seqnode {
  int seqid;
  int next;
};

union {
  struct node beg[MAX_N];
  struct node end[MAX_N];
  struct {
    int incount[MAX_N];
    int outcount[MAX_N];
  };
} node;

struct {
  int node[MAX_M];
  union {
    struct edge edge[MAX_M];
    struct seqnode seqnode[MAX_M];
  };
} mem;

struct seq {
  int seqid;
  int beg_node;
  int memidx;
} seq[MAX_T];

int seqcount = 0;

int residx;
int res[MAX_M + 1];

int stack[MAX_M + 1];
int stack_idx = 0;

int begidx[MAX_N];

static inline void read_arr_edge()
{
  int i;
  for (i = 0; i < m; i++) {
    int a, b;
    scanf("%d%d", &a, &b);
    mem.edge[i] = (struct edge) {a - 1, b - 1};
  }
}

static inline int check_euler_condition()
{
  int i;
  for (i = 0; i < n; i++)
    node.incount[i] = 0;
  for (i = 0; i < n; i++)
    node.outcount[i] = 0;
  for (i = 0; i < m; i++) {
    struct edge *e = &mem.edge[i];
    node.incount[e->b]++;
    node.outcount[e->a]++;
  }
  for (i = 0; i < n; i++)
    if (node.incount[i] != node.outcount[i])
      return 0;
  return 1;
}

static inline void create_street_end()
{
  int i;
  for (i = 0; i < n; i++)
    node.end[i].count = 0;
  for (i = 0; i < m; i++)
    node.end[mem.edge[i].b].count++;
  int memidx = 0;
  for (i = 0; i < n; i++) {
    struct node *endptr = &node.end[i];
    endptr->memidx = memidx;
    memidx += endptr->count;
  }
  for (i = 0; i < n; i++)
    node.end[i].count = 0;
  for (i = 0; i < m; i++) {
    struct edge *e = &mem.edge[i];
    struct node *endptr = &node.end[e->b];
    mem.node[endptr->memidx + endptr->count++] = e->a;
  }
}

static inline void create_street_beg()
{
  int i;
  for (i = 0; i < n; i++)
    node.beg[i].count = 0;
  for (i = 0; i < m; i++)
    node.beg[mem.edge[i].a].count++;
  int memidx = 0;
  for (i = 0; i < n; i++) {
    struct node *begptr = &node.beg[i];
    begptr->memidx = memidx;
    memidx += begptr->count;
  }
  for (i = 0; i < n; i++)
    node.beg[i].count = 0;
  for (i = 0; i < m; i++) {
    struct edge *e = &mem.edge[i];
    struct node *begptr = &node.beg[e->a];
    mem.node[begptr->memidx + begptr->count++] = e->b;
  }
}

static inline void rearrange_arr_edge_by_end()
{
  int i;
  int edge_count = 0;
  for (i = 0; i < n; i++) {
    struct node *endptr = &node.end[i];
    int j;
    for (j = 0; j < endptr->count; j++) {
      int *memnode = mem.node + endptr->memidx;
      mem.edge[edge_count++] = (struct edge) {memnode[j], i};
    }
  }
}

static inline void sort_arr_edge_by_end()
{
  create_street_end();
  rearrange_arr_edge_by_end();
}

static inline void init_streets_seq()
{
  int i;
  for (i = 0; i < m; i++)
    mem.seqnode[i].seqid = -1;
}

static inline int read_streets_and_check_euler_condition()
{
  scanf("%d%d", &n, &m);
  read_arr_edge();
  if (!check_euler_condition())
    return 0;
  sort_arr_edge_by_end();
  create_street_beg();
  init_streets_seq();
  return 1;
}

static inline int node_search(int l, int r, int v)
{
  if (v == mem.node[r])
    return r;
  while (l < r) {
    int m = (l + r) >> 1;
    int vm = mem.node[m];
    if (v == vm)
      return m;
    if (v < vm)
      r = m;
    else
      l = m + 1;
  }
  if (v == mem.node[l])
    return l;
  return -1;
}

static inline int find_edge(int a, int b)
{
  struct node *begptr = &node.beg[a];
  int memidx = begptr->memidx;
  return node_search(memidx, memidx + begptr->count - 1, b);
}

static inline void create_seqnode(int seqid, int memidx)
{
  mem.seqnode[memidx] = (struct seqnode) {seqid, -1};
}

static inline int create_new_seq(int beg_node, int memidx)
{
  int seqid = seqcount++;
  seq[seqid] = (struct seq) {seqid, beg_node, memidx};
  create_seqnode(seqid, memidx);
  return seqid;
}

static inline int find_seqid(int leafseqid)
{
  int seqid = leafseqid;
  for (;;) {
    int nextseqid = seq[seqid].seqid;
    if (nextseqid == seqid)
      break;
    seqid = nextseqid;
  }
  return seqid;
}

static inline void union_seqid(int leafseqid, int seqid)
{
  for (;;) {
    int nextseqid = seq[leafseqid].seqid;
    if (nextseqid == seqid)
      break;
    seq[leafseqid].seqid = seqid;
    leafseqid = nextseqid;
  }
}

static inline int find_and_union_seqid(int leafseqid)
{
  int seqid = find_seqid(leafseqid);
  union_seqid(leafseqid, seqid);
  return seqid;
}

static inline int try_read_and_process_seq()
{
  int k;
  int a, b;
  scanf("%d%d%d", &k, &a, &b);
  a--;
  b--;
  k -= 2;

  int seqid;
  
  int memidx = find_edge(a, b);
  if (memidx < 0)
    return 0;
  
  struct seqnode *seqnodeptr = &mem.seqnode[memidx];
  if (seqnodeptr->seqid < 0)
    seqid = create_new_seq(a, memidx);
  else
    seqid = find_and_union_seqid(seqnodeptr->seqid);
  
  for (; k; k--) {
    a = b;
    scanf("%d", &b);
    b--;
    if (seqnodeptr->next >= 0) {
      memidx = seqnodeptr->next;
      // overlapping seqs cannot split
      if (b != mem.node[memidx])
        return 0;
      seqnodeptr = &mem.seqnode[memidx];
    } else {
      memidx = find_edge(a, b);
      if (memidx < 0)
        return 0;
      seqnodeptr->next = memidx;
      seqnodeptr = &mem.seqnode[memidx];
      if (seqnodeptr->seqid < 0) {
        create_seqnode(seqid, memidx);
      } else {
        int prevseqid =
          find_and_union_seqid(seqnodeptr->seqid);
         // seq cannot cycle
        if (prevseqid == seqid)
          return 0;
         // seq must overlap another seq from beginnig
        if (seq[prevseqid].memidx != memidx)
          return 0;
        seq[prevseqid].seqid = seqid;
      }
    }
  }
  
  return 1;
}

static inline int try_read_and_process_seqs()
{
  int t;
  scanf("%d", &t);
  for (; t; t--)
    if (!try_read_and_process_seq())
      return 0;
  return 1;
}

static inline void stack_push(int a)
{
  stack[stack_idx++] = a;
}

static inline int stack_pop()
{
  for (;;) {
    res[--residx] = stack[--stack_idx];
    if (res[residx] >= n)
      res[residx] -= n;
    if (!stack_idx)
      return -1;
    int ret = stack[stack_idx - 1];
    if (ret < n)
      return ret;
  }
}

static inline int move_through_seq(int seqid)
{
  int memidx = seq[seqid].memidx;
  int last;
  for (;;) {
    last = mem.node[memidx];
    memidx = mem.seqnode[memidx].next;
    if (memidx < 0)
      break;
    stack_push(n + last);
  }
  return last;
}

static inline int try_move(int a)
{
  struct node *begptr = &node.beg[a];
  
  while (begidx[a] < begptr->count) {
    int memidx = begptr->memidx + begidx[a];
    begidx[a]++;
    if (mem.seqnode[memidx].seqid < 0) {
      return mem.node[memidx];
    } else {
      struct seqnode *seqnodeptr = &mem.seqnode[memidx];
      int seqid = find_and_union_seqid(seqnodeptr->seqid);
      if (seq[seqid].memidx == memidx)
        return move_through_seq(seqid);
    }
  }
  
  return -1;
}

static inline int try_find_euler_cycle()
{
  int i;
  residx = m + 1;
  for (i = 0; i < n; i++)
    begidx[i] = 0;
  stack_push(0);
  int a = 0;

  for (;;) {
    a = try_move(a);
    if (a < 0) {
      a = stack_pop();
      if (a < 0)
        break;
    } else
      stack_push(a);
  }
  
  return !residx && !res[m];
}

static inline void print_res()
{
  int i;
  for (i = 0; i <= m; i++)
    printf("%d\n", res[i] + 1);
}

int main()
{
  int found = 0;
  if (read_streets_and_check_euler_condition()) {
    if (try_read_and_process_seqs()) {
      if (try_find_euler_cycle())
        found = 1;
    }
  }
  
  if (found) {
    printf("TAK\n");
    print_res();
  } else
    printf("NIE\n");
  
  return 0;
}
