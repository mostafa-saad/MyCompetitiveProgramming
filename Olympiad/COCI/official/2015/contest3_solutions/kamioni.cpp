#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <map>

using namespace std;

#define LOG(x) cerr << #x << " = " << (x) << "\n"

typedef long long llint;
typedef pair<int,int> pii;
const int MAXN = 300100;

enum { LEFT = -1, ABDUCTED, RIGHT };

struct event {
  int truck_id;
  int x, direction;
  llint time;
};

struct query {
  int truck_id, was_left, query_id;
};

struct truck {
  int k;
  int x, direction;
  llint time;
  vector<query> queries;
};

truck trucks[MAXN];
int ans[MAXN];

void apply_event(const event &e) {
  trucks[e.truck_id].x = e.x;
  trucks[e.truck_id].direction = e.direction;
  trucks[e.truck_id].time = e.time;
}

int check_is_left(const truck &a, const truck &b, 
    llint prev_time, int prev_direction) {
  if (b.direction == ABDUCTED && prev_time >= b.time)
    return ABDUCTED;
  int b_pos, a_pos;
  if (b.direction == ABDUCTED) {
    b_pos = b.x;
    a_pos = (a.time - b.time) *(-prev_direction) + a.x;
  } else {
    a_pos = a.x;
    b_pos = (a.time - b.time) * b.direction + b.x;
  }
  assert(b_pos != a_pos);
  if (b_pos < a_pos)
    return LEFT;
  return RIGHT;
}

void solve_query(const truck &t, query &q, 
    llint prev_time, int prev_direction) {
  int is_left = check_is_left(t, trucks[q.truck_id], 
      prev_time, prev_direction);
  ans[q.query_id] += (q.was_left * is_left == -1);
  q.was_left = is_left;
}

bool cmp(const event &a, const event &b) {
  if (a.time != b.time)
    return a.time < b.time;
  return a.direction > b.direction;
}

int main() {
  int n, m;
  vector<event> events;
  map<pii,vector<int>> same_queries;

  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    int x;
    llint sum_time = 0;
    scanf("%d%d", &trucks[i].k, &x);

    for (int j = 0; j < trucks[i].k-1; ++j) {
      int new_x; scanf("%d", &new_x);
      event e = { i, x, x < new_x ? RIGHT : LEFT, sum_time };
      if (j == 0) {
        apply_event(e);
      } else {
        events.push_back(e);
      }
      sum_time += abs(x - new_x);
      x = new_x;
    }
    event e = { i, x, ABDUCTED, sum_time };
    events.push_back(e);
  }

  for (int i = 0; i < m; ++i) {
    int a, b;
    scanf("%d%d", &a, &b);
    --a; --b;
    if (a > b)
      swap(a, b);
    same_queries[{a, b}].push_back(i);
    if ((int)same_queries[{a, b}].size() > 1)
      continue;
    if (trucks[a].k > trucks[b].k)
      swap(a, b);
    trucks[a].queries.push_back(
        {b, trucks[b].x < trucks[a].x ? LEFT : RIGHT, i});
  }

  sort(events.begin(), events.end(), cmp);
  for (const event &e : events) {
    llint prev_time = trucks[e.truck_id].time;
    int prev_direction = trucks[e.truck_id].direction;
    apply_event(e);
    for (query &q : trucks[e.truck_id].queries)
      solve_query(trucks[e.truck_id], q, prev_time, prev_direction);
  }

  for (auto queries : same_queries) {
    int res = ans[queries.second[0]];
    for (int t : queries.second)
      ans[t] = res;
  }

  for (int i = 0; i < m; ++i)
    printf("%d\n", ans[i]);
  return 0;
}
