#include <cstdio>
#include <queue>
#include <vector>

using namespace std;

const int INF = 1001001001;

int in() { int x; scanf("%d", &x); return x; }

const int MAX = 2048;

char F[MAX][MAX];
int U[MAX][MAX], R[MAX][MAX], D[MAX][MAX], L[MAX][MAX], A[MAX][MAX];

int main() {
  const int H = in();
  const int W = in();
  for (int i = 0; i < H; ++i) {
    scanf("%s", F[i]);
    for (int j = 0; j < W; ++j) {
      A[i][j] = INF;
    }
  }

  const int sr = in() - 1;
  const int sc = in() - 1;
  const int gr = in() - 1;
  const int gc = in() - 1;

  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
      if (F[i][j] == '#') {
        U[i][j] = i;
        L[i][j] = j;
      } else {
        U[i][j] = U[i - 1][j];
        L[i][j] = L[i][j - 1];
      }
    }
  }

  for (int i = H - 1; i >= 0; --i) {
    for (int j = W - 1; j >= 0; --j) {
      if (F[i][j] == '#') {
        D[i][j] = i;
        R[i][j] = j;
      } else {
        D[i][j] = D[i + 1][j];
        R[i][j] = R[i][j + 1];
      }
    }
  }

  struct state {
    int r, c, s;
    state(int r, int c, int s) : r(r), c(c), s(s) { }
    bool operator < (const state& o) const {
      return s > o.s;
    }
  };
  priority_queue<state> Q;

  Q.emplace(sr, sc, 0);
  while (!Q.empty()) {
    const state s = Q.top(); Q.pop();
    if (s.r == gr && s.c == gc) {
      printf("%d\n", s.s);
      return 0;
    }

    const auto update = [&] (const int rr, const int cc, const int ss) {
      if ((s.r == rr && s.c == cc) || F[rr][cc] == '#') return;
      if (ss < A[rr][cc]) {
        A[rr][cc] = ss;
        Q.emplace(rr, cc, ss);
      }
    };

    update(U[s.r][s.c] + 1, s.c, s.s + 1);
    update(D[s.r][s.c] - 1, s.c, s.s + 1);
    update(s.r, L[s.r][s.c] + 1, s.s + 1);
    update(s.r, R[s.r][s.c] - 1, s.s + 1);

    const static int dr[] = {1, 0, -1, 0}, dc[] = {0, 1, 0, -1};
    for (int d = 0; d < 4; ++d) {
      update(s.r + dr[d], s.c + dc[d], s.s + 2);
    }
  }

  puts("-1");
  return 0;
}
