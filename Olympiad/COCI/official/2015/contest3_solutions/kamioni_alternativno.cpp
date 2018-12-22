#include <map>
#include <cstdio>
#include <algorithm>

using namespace std;
typedef long long llint;

const int MAGIC = 200;
const int MAXN = 100005;
const int MAXM = 100005;
const llint inf = 1000000000000000LL;

#define FOR(i, a, b) for(int i = (a); i < (b); ++i)
#define REP(i, n) FOR(i, 0, n)

struct Evt {
  llint x, y, ny;
  int id;

  Evt(llint x, llint y, llint ny, int id) :
    x(x), y(y), ny(ny), id(id) {}

  friend bool operator<(const Evt &a, const Evt &b) {
    if (a.x == b.x) 
      return a.y < b.y;
    else
      return a.x < b.x;
  }
};

int N, M, K, a, b;
vector< int > pos[MAXN];
vector< Evt > v, w;

vector< pair< int, int > > qs[MAXM];
int qid[MAXN];
int sol[MAXM];

void calc(int id, vector< Evt > &v) {
  llint y = -inf;
  for (Evt &e : v) {
    if (e.id == id && e.y == e.ny) 
      y = e.y;
    else if (e.id != id) 
      if (e.y < y && e.ny > y && e.y != e.ny) 
        ++sol[qid[e.id]];
  }
}

void solve_big(int id) {
  REP(i, N) qid[i] = M;
  for (auto query : qs[id])
    qid[query.first] = query.second;
  calc(id, v);
}

void add(int i, vector< Evt > &v, int type) {
  llint t = 0;
  llint x = pos[i][0];
  FOR(j, 1, (int)pos[i].size()) {
    llint delta = pos[i][j] - x;
    if (type == 0)
      v.push_back(Evt(t - x, t + x, t + x + abs(delta) + delta, i));
    else
      v.push_back(Evt(t + x, t - x, t - x + abs(delta) - delta, i));
    t += abs(delta);
    x += delta;
  }
  if (type == 0)
    v.push_back(Evt(t - x, inf, inf, i));
  else
    v.push_back(Evt(t + x, inf, inf, i));
}

void solve_small(int a, int b, int cqid, int type) {
  w.clear();
  add(a, w, type);
  add(b, w, type);
  inplace_merge(w.begin(), w.begin() + pos[a].size(), w.end());
  qid[a] = qid[b] = cqid;
  calc(a, w);
}

void solve(int type) {
  v.clear();
  REP(i, N) add(i, v, type);
  sort(v.begin(), v.end());
  REP(i, N) {
    if (pos[i].size() < MAGIC)
      for (auto query : qs[i]) 
        solve_small(i, query.first, query.second, type);
    else
      solve_big(i);
  }
}

map< pair< int, int >, int > ids;
int fake[MAXM];

int main(void)
{
  scanf("%d%d", &N, &M);

  REP(i, N) {
    scanf("%d", &K);

    REP(j, K) {
      int x;
      scanf("%d", &x);
      pos[i].push_back(x);
    }
  }

  REP(i, M) {
    scanf("%d%d", &a, &b); --a; --b;

    if (ids.count({a, b})) {
      sol[i] = -1;
      fake[i] = ids[make_pair(a, b)];
      continue;
    }

    ids[make_pair(a, b)] = ids[make_pair(b, a)] = i;

    if (pos[a].size() < pos[b].size())
      swap(a, b);
    
    qs[a].push_back({b, i});
  }

  solve(0);
  solve(1);

  REP(i, M) {
    if (sol[i] == -1)
      printf("%d\n", sol[fake[i]]);
    else
      printf("%d\n", sol[i]);
  }

  return 0;
}
