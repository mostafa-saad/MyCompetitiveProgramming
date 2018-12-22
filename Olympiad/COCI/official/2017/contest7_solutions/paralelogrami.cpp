#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <queue>

#define x first
#define y second
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR (i, 0, n)
#define _ << " _ " <<
#define TRACE(x) cerr << #x << " = " << x << endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
//#define debug
//#define TRACE(x)

using namespace std;
using point = pair<int, int>;

typedef long long llint;

const int MAX = 10;
const int INF = 1e9;
const int MAXN = 410;

struct state {
  int x[3], y[3];
};

struct command {
  int a, b, c;
};

int x[3], y[3];

vector<int> get_state(state s) {
  vector<int> ret;
  ret = {s.x[0], s.y[0], s.x[1], s.y[1], s.x[2], s.y[2]};
  return ret;
}

queue<state> q;
map<vector<int>, pair<state, int>> from;
const state EMPTY = state();
vector<command> com;

state bfs() {
  state start;
  start.x[0] = x[0]; start.y[0] = y[0];
  start.x[1] = x[1]; start.y[1] = y[1];
  start.x[2] = x[2]; start.y[2] = y[2];
  q.push(start);
  from[get_state(start)] = {EMPTY, -1};
  while (!q.empty()) {
    state s = q.front();
    q.pop();

    
    if (max(s.x[0], max(s.x[1], s.x[2])) < -MAX) continue;
    if (max(s.y[0], max(s.y[1], s.y[2])) < -MAX) continue;
	
    if (min(s.x[0], min(s.x[1], s.x[2])) >= MAX/2 &&
	min(s.y[0], min(s.y[1], s.y[2])) >= MAX/2) {
      state ret = s;
      
      while (true) {
	auto v = get_state(s);
	int j = from[v].second;
	if (j == -1) break;
	com.push_back({(j + 1) % 3, (j + 2) % 3, j});
	s = from[v].first;
      }
      
      return ret;
    }

    REP(j, 3) {
      state ns = s;
      ns.x[j] = (s.x[0] + s.x[1] + s.x[2]) - 2 * s.x[j];
      ns.y[j] = (s.y[0] + s.y[1] + s.y[2]) - 2 * s.y[j];
      if (from.find(get_state(ns)) == from.end()) {
	from[get_state(ns)] = {s, j};
	q.push(ns);
      }
    }
  }

  return EMPTY;
}

int X[MAXN], Y[MAXN], id[MAXN], n;

llint ccw(point a, point b, point c) {
  return (llint)a.x * (b.y - c.y) + (llint)b.x * (c.y - a.y) + (llint)c.x * (a.y - b.y);
}

int main(void) {
  bool found_ok = false, found_neg = false;
  scanf("%d",&n);
  REP(i, n) {
    scanf("%d %d",&X[i],&Y[i]);
    id[i] = i;
    if (X[i] < 0 || Y[i] < 0) found_neg = true;
  }

  if (!found_neg) {
    printf("0\n");
    return 0;
  }
  
  FOR(i, 2, n) 
    if (ccw({X[0], Y[0]}, {X[1], Y[1]}, {X[i], Y[i]}) != 0) {
      swap(id[2], id[i]);
      swap(X[2], X[i]);
      swap(Y[2], Y[i]);
      found_ok = true;
      break;
    }

  if (!found_ok) {
    printf("-1\n");
    return 0;
  }

  x[0] = X[0]; y[0] = Y[0];
  x[1] = X[1]; y[1] = Y[1];
  x[2] = X[2]; y[2] = Y[2];
  
  state s = bfs();
  reverse(com.begin(), com.end());
  
  FOR(i, 3, n) {
    if (X[i] >= 0 && Y[i] >= 0) continue;
    if (ccw({s.x[0], s.y[0]}, {s.x[1], s.y[1]}, {X[i], Y[i]}) != 0)
      com.push_back({0, 1, i});
    else
      com.push_back({0, 2, i});
  }

  printf("%d\n",(int)com.size());
  REP(i, (int)com.size())
    printf("%d %d %d\n",id[com[i].a]+1,id[com[i].b]+1,id[com[i].c]+1);
  
  return 0;
}
