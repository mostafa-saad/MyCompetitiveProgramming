#include <cstdio>
#include <set>
#include <vector>

using namespace std;

const int MAXN = 1100;
const int MAXM = 100100;

struct rect {
  int id, c, x1, y1, x2, y2;
  rect() {}
  rect(int _id, int _c, int _x1, int _y1, int _x2, int _y2) {
    id = _id, c = _c, x1 = _x1, y1 = _y1, x2 = _x2, y2 = _y2;
  }
};

struct cmp {
  bool operator () (const rect &A, const rect &B) {
    return A.id > B.id;
  }
};

int N, K, M, S;
enum {SAVE, LOAD, PAINT};
int command[MAXM];

int save[MAXM];
int load[MAXM];
rect paint[MAXM];

vector< rect > beg[MAXN];
vector< rect > end[MAXN];

int odd = 1;
inline int f(int x) { return (x & 1) ? odd : !odd; }

struct node {
  set< rect, cmp > R[2];
  node() {}
};

struct tree {
  node A[2 * MAXN];
  tree() {}

  rect r;
  int a, b;

  void doit(int x, int lo, int hi, int add) {
    if (lo > b || hi < a) return;
    
    if (a <= lo && hi <= b) {
      if (add) {
        A[x].R[f(a)].insert(r);
      } else
        A[x].R[f(a ^ (r.x2 - r.x1 + 1))].erase(r);
      return;
    }
    
    doit(2 * x, lo, (lo + hi) / 2, add);
    doit(2 * x + 1, (lo + hi) / 2 + 1, hi, add);
  }

  void insert(rect _r) {
    r = _r; a = r.y1; b = r.y2;
    doit(1, 0, 1 << 10, 1);
  }

  void remove(rect _r) {
    r = _r; a = r.y1; b = r.y2;
    doit(1, 0, 1 << 10, 0);
  }

  int query(int x, int lo, int hi) {
    int ret = -1;
    if (lo > a || hi < a) return ret;

    if (!A[x].R[f(a)].empty())
      ret = max(ret, A[x].R[f(a)].begin()->id);
    
    if (lo == hi) return ret;
    ret = max(ret, query(2 * x, lo, (lo + hi) / 2));
    ret = max(ret, query(2 * x + 1, (lo + hi) / 2 + 1, hi));
    return ret;
  }

  int query(int x) {
    a = x;
    int ret = query(1, 0, 1 << 10);
    return (ret == -1) ? 1 : paint[ret].c;
  }
} T;

int main(void) 
{
  scanf("%d %d %d", &N, &K, &M);

  for (int i = 0; i < M; ++i) {
    char buff[10]; scanf("%s", buff);
    char c = buff[0];

    switch (c) {
      case 'S': 
        command[i] = SAVE;
        save[i] = ++S;
        break;
      case 'L':
        int x; scanf("%d", &x);
        command[i] = LOAD;
        load[i] = x;
        break;
      case 'P':
        int c, x1, y1, x2, y2;
        scanf("%d %d %d %d %d", &c, &x1, &y1, &x2, &y2);
        command[i] = PAINT;
        paint[i] = rect(i, c, x1, y1, x2, y2);
    }
  }

  for (int i = M - 1; i >= 0; --i) {
    switch (command[i]) {
      case SAVE: 
        break;
      case LOAD:
        int x; x = load[i];
        while (save[i] != x) --i;
        break;
      case PAINT:
        beg[paint[i].x1].push_back(paint[i]);
        end[paint[i].x2 + 1].push_back(paint[i]);
    }
  }

  for (int row = 0; row < N; ++row, odd ^= 1) {
    for (int i = 0; i < end[row].size(); ++i)
      T.remove(end[row][i]);
    for (int i = 0; i < beg[row].size(); ++i)
      T.insert(beg[row][i]);
    for (int col = 0; col < N; ++col)
      printf("%d ", T.query(col));
    printf("\n");
  }

  return 0;
}
