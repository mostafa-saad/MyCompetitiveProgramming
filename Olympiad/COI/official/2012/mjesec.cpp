#include <algorithm>
#include <cstdio>
#include <vector>

using namespace std;

#define MAX 10000

typedef pair<int, bool> par;

int n;
int x[MAX], y[MAX];
int len[MAX];
bool left_corner[MAX];
int left_corners;
int L, R;
int sum;
int max_dist;

void ask(int k) {
  printf("hodaj %d\n", k);
  fflush(stdout);
  scanf("%d%d", &L, &R);
}

void solve_direction() {
  ask(sum);
  if (L != left_corners) {
    for (int i = 0; i < n - i - 1; ++i) {
      swap(x[i], x[n - i - 1]);
      swap(y[i], y[n - i - 1]);
      swap(len[i], len[n - i - 1]);
      swap(left_corner[i], left_corner[n - i - 1]);
    }
    for (int i = 0; i < n; ++i) left_corner[i] = !left_corner[i];
    int l = len[0];
    for (int i = 0; i < n; ++i) len[i] = len[i + 1];
    len[n - 1] = l;
  }
}

par goto_first_corner() {
  int cnt = 0;
  int lo = 1, hi = max_dist;
  while (lo != hi) {
    int mid = (lo + hi) / 2;
    ask(mid);
    if (L || R) hi = mid;
    else lo = mid + 1;
    ask(sum - mid);
  }
  ask(lo);
  return par(lo, !R);
}

int find_diff(int a, int b) {
  int ret = 0;
  while (len[a] == len[b]) {
    ret += len[a];
    a = (a + 1) % n;
    b = (b + 1) % n;
    if (left_corner[a] != left_corner[b]) {
      return ret;
    }
  }
  ret += min(len[a], len[b]);
  return ret;
}

bool test(int a, int k) {
  int l = 0, r = 0;
  while (k >= len[a]) {
    k -= len[a];
    a = (a + 1) % n;
    if (left_corner[a]) ++l; else ++r;
  }
  return l == L && r == R;
}

int main(void) {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &x[i], &y[i]);
  }
  
  for (int i = 0; i < n; ++i) {
    int j = i == 0 ? n - 1 : i - 1;
    int k = i + 1 == n ? 0 : i + 1;
    
    int dx1 = x[j] - x[i];
    int dy1 = y[j] - y[i];
    int dx2 = x[k] - x[i];
    int dy2 = y[k] - y[i];
    
    long long cross = (long long) dx1 * dy2 - (long long) dx2 * dy1;
    left_corner[i] = cross < 0;
    left_corners += left_corner[i];

    len[i] = abs(dx2) + abs(dy2);
    sum += len[i];
    max_dist = max(max_dist, len[i]);
  }
  
  solve_direction();
  par p = goto_first_corner();

  vector<int> candidates;
  for (int i = 0; i < n; ++i) {
    if (left_corner[i] == p.second) {
      candidates.push_back(i);
    }
  }
  
  while (candidates.size() > 1) {
    int a = rand() % candidates.size(), b = a;
    while (a == b) {
      b = rand() % candidates.size();
    }
    
    int k = find_diff(candidates[a], candidates[b]);
    ask(k);

    vector<int> new_candidates;
    for (vector<int>::iterator it = candidates.begin(); it != candidates.end(); ++it) {
      if (test(*it, k)) {
        new_candidates.push_back(*it);
      };
    }
    ask(sum - k);
    candidates = new_candidates;
  }
  
  int a = candidates[0];
  printf("kraj %d %d\n", x[a], y[a]);
  fflush(stdout);
  
  return 0;
}
