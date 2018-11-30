// Adam Karczmarz

#include <bits/stdc++.h>

#define SZ(AA) int((AA).size())

using namespace std;

const int MAXN = 6000, MAXK = 1000000;
vector<int> ve[MAXN + 10];
int N, M, K, S, h[MAXN + 10], cnt[MAXK + 10];
bool res[MAXN + 10], us[MAXK + 10];

void add(int v, int delta, int x) {
  if (v > N) {
    return;
  }
  int y = h[v] + delta;
  if (y <= MAXK) {
    cnt[y] += x;
  }
  for (int w : ve[v]) {
    add(w, delta, x);
  }
}

// use cycle
void case1(int v) {
  if (v > N) {
    int y = K - h[v];
    if (y > 0) {
      for (int d = 1; d * d <= y; ++d) {
        if (y % d == 0 && (cnt[d] > 0 || cnt[y / d] > 0)) {
          res[v] = true;
        }
      }
    }
    return;
  }
  add(v, S + 1 - h[v], 1);
  for (int w : ve[v]) {
    case1(w);
  }
  add(v, S + 1 - h[v], -1);
}

vector<int> anc;

// use single directory symlink
void case2(int v) {
  if (v > N) {
    for (int a : anc) {
      int y = K - (h[v] - h[a]) - (S + 1);
      if (y >= 0 && us[y]) {
        res[v] = true;
      }
    }
    return;
  }
  anc.push_back(v);
  for (int w : ve[v]) {
    case2(w);
  }
  anc.pop_back();
}

// do not use symlinks at all
void case3() {
  for (int i = N + 1; i <= N + M; ++i) {
    if (h[i] == K) {
      res[i] = true;
    }
  }
}

// use file symlink
void case4() {
  for (int i = 0; i <= N; ++i) {
    if (h[i] + S == K) {
      for (int j = N + 1; j <= N + M; ++j) {
        res[j] = true;
      }
      return;
    }
  }
}

int main(void) {
  scanf("%d%d%d%d", &N, &M, &K, &S);
  h[0] = 1; us[1] = true;
  for (int i = 1; i <= N + M; ++i) {
    int p; scanf("%d%d", &p, &h[i]);
    ve[p].push_back(i);
    h[i] += h[p] + (i <= N ? 1 : 0);
    if (i <= N) {
      us[h[i]] = true;
    }
  }
  case1(0);
  case2(0);
  case3();
  //case4();
  for (int i = N + 1; i <= N + M; ++i) {
    puts(res[i] ? "YES" : "NO");
  }
  return 0;
}

