/*
 * CEOI'04
 * Journey - solution
 * Author: Tomek Czajka
 * time: O(n) (after reading input)
*/

#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

struct Edge {
  int x; /* destination */
  int w; /* distance */
  Edge() {}
  Edge(int x,int w):x(x),w(w) {}
};

/* cities are numbered 0..(n-1) in the program */
int n;
/* edges[x] - edges from city x */
vector<vector<Edge> > edges;
/* starting city */
int start;
/* wantToVisit[x] - do we want to visit city x */
/* should be vector<bool>, but we don't want bit compression */
/* wantToVisit[start] = true */
vector<char> wantToVisit;


/* read input data */
void read() {
  scanf("%d%d", &n, &start);
  --start;
  edges.assign(n, vector<Edge>());
  for(int i=0; i<n-1; ++i) {
    int a,b,d;
    scanf("%d%d%d", &a, &b, &d);
    --a; --b;
    edges[a].push_back(Edge(b,d));
    edges[b].push_back(Edge(a,d));
  }
  wantToVisit.assign(n, false);
  wantToVisit[start] = true;
  int visitHowMany;
  scanf("%d", &visitHowMany);
  for(int i=0; i<visitHowMany; ++i) {
    int x;
    scanf("%d", &x);
    --x;
    wantToVisit[x] = true;
  }
}

/* calculate answers for the subtree rooted at x
 * results:
 * any - do we need to visit this subtree at all
 * cost = cost of a tour starting at x (root), visiting all cities we
 *    have to visit and returning to x
 * costNoReturn = same, but without the need of returning to x
*/
void calc(int x, int parent, bool &any, int &cost, int &costNoReturn) {
  any = wantToVisit[x];
  cost = 0;
  int save = 0; // how much can we save if we don't need to return
  vector<Edge> &v = edges[x];
  for(vector<Edge>::iterator it = v.begin(); it!=v.end(); ++it) {
    if(it->x != parent) { // don't go back to parent
      bool any2;
      int cost2, costNoReturn2;
      calc(it->x, x, any2, cost2, costNoReturn2);
      if(any2) {
        any = true;
        cost += 2 * it->w + cost2;
        save = max(save, it->w + (cost2 - costNoReturn2) );
      }
    }
  }
  costNoReturn = cost - save;
}

/* main computation */
int calculate() {
  bool any;
  int cost, costNoReturn;
  calc(start, -1, any, cost, costNoReturn);
  return costNoReturn;
}

int main() {
  read();
  int result = calculate();
  printf("%d\n", result);
}
