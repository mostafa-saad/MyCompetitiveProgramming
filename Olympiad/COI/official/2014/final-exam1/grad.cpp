#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <string>

#define MAXN 100010
#define LOG_MAXN 18

using namespace std;

double const oo = 1e15;

struct Point {
  double x, y;
};

double Dist(Point const& a, Point const& b) {
  double dx = a.x - b.x;
  double dy = a.y - b.y;
  return sqrt(dx*dx + dy*dy);
}

struct Node;
struct Edge;

struct Jump {
  Edge* edge;
  double cost[2][2];
};

struct Edge {
  int depth;
  Node* node[2];
  Jump jumps[LOG_MAXN];

  Edge() {
    depth = 0;
    node[0] = node[1] = NULL;
    for (int p = 0; p < LOG_MAXN; ++p) {
      jumps[p].edge = NULL;
      for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
          jumps[p].cost[i][j] = oo;
        }
      }
    }
  }
};

struct Node {
  Point point;
  Edge edge[2];
};

Node A[MAXN + 1];

void AssignNodes(Edge* edge, Node* a, Node* b) {
  edge->node[0] = a;
  edge->node[1] = b;
}

void AssignParent(Edge* child, Edge* parent) {
  child->depth = parent->depth + 1;
  child->jumps[0].edge = parent;
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      child->jumps[0].cost[i][j] = Dist(child->node[i]->point,
                                        parent->node[j]->point);
    }
  }
  for (int p = 1; (1 << p) <= child->depth; ++p) {
    Edge const* midway = child->jumps[p - 1].edge;
    child->jumps[p].edge = midway->jumps[p - 1].edge;
    for (int i = 0; i < 2; ++i) {
      for (int j = 0; j < 2; ++j) {
        double* cost_ij = &child->jumps[p].cost[i][j];
        *cost_ij = oo;
        for (int k = 0; k < 2; ++k) {
          double const cost_ik = child->jumps[p - 1].cost[i][k];
          double const cost_kj = midway->jumps[p - 1].cost[k][j];
          *cost_ij = min(*cost_ij, cost_ik + cost_kj);
        }
      }
    }
  }
}

void Climb(Edge** a, double cost[2], int p) {
  double new_cost[2] = { oo, oo };
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      new_cost[j] = min(new_cost[j], cost[i] + (*a)->jumps[p].cost[i][j]);
    }
  }
  *a = (*a)->jumps[p].edge;
  assert(*a != NULL);
  cost[0] = new_cost[0];
  cost[1] = new_cost[1];
}

double Solve(Edge* a, Edge* b) {
  if (a->depth > b->depth) {
    swap(a, b);
  }
  double a_cost[2] = {0, Dist(a->node[0]->point, a->node[1]->point)};
  double b_cost[2] = {0, Dist(b->node[0]->point, b->node[1]->point)};

  for (int p = LOG_MAXN - 1; p >= 0; --p) {
    if (b->depth - (1<<p) >= a->depth) {
      Climb(&b, b_cost, p);
    }
  }

  for (int p = LOG_MAXN - 1; p >= 0; --p) {
    if (a->jumps[p].edge != b->jumps[p].edge) {
      Climb(&a, a_cost, p);
      Climb(&b, b_cost, p);
    }
  }

  double ret = oo;
  if (a->node[0] == b->node[0]) {
    ret = a_cost[0] + b_cost[0];
  }
  if (a != b) {
    Climb(&a, a_cost, 0);
    Climb(&b, b_cost, 0);
  }

  assert(a == b);
  ret = min(ret, a_cost[0] + b_cost[0]);
  ret = min(ret, a_cost[1] + b_cost[1]);
  return ret;
}
int main() {
  A[0].point.x = oo;
  A[0].point.y = oo;
  scanf("%lf%lf", &A[1].point.x, &A[1].point.y);

  A[1].edge[0].depth = 0;
  AssignNodes(&A[1].edge[0], &A[1], &A[0]);
  scanf("%lf%lf", &A[2].point.x, &A[2].point.y);

  AssignNodes(&A[2].edge[0], &A[2], &A[1]);
  AssignParent(&A[2].edge[0], &A[1].edge[0]);
  int n = 2;

  int Q;
  scanf("%d", &Q);
  for (int q = 0; q < Q; ++q) {
    static char op[8];
    scanf("%s", op);
    if (op[0] == 'd') {
      int a, b;
      int c = ++n;
      scanf("%lf%lf%d%d", &A[c].point.x, &A[c].point.y, &a, &b);
      if (a > b) {
        swap(a, b);
      }
      Edge* ca = &A[c].edge[0];
      AssignNodes(ca, &A[c], &A[a]);
      Edge* cb = &A[c].edge[1];
      AssignNodes(cb, &A[c], &A[b]);
      Edge* ba = (A[b].edge[0].node[1] == &A[a]) 
          ? &A[b].edge[0]
          : &A[b].edge[1];
      assert(ba->node[0] == &A[b]);
      assert(ba->node[1] == &A[a]);
      AssignParent(ca, ba);
      AssignParent(cb, ba);
    } else {
      int a, b;
      scanf("%d%d", &a, &b);
      printf("%lf\n", Solve(&A[a].edge[0], &A[b].edge[0]));
    }
  }
  return 0;
}
