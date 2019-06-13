#include <cstdio>
#include <vector>

using namespace std;

template<typename T> void chmax(T& a, T b) { if (a < b) a = b; }
int in() { int x; scanf("%d", &x); return x; }

const int MAXN = 2048;

struct ev {
  int t, id, go;
  ev(int t, int id, int go) : t(t), id(id), go(go) { }
};
bool operator < (const ev& e, const ev& f) {
  return e.t < f.t;
}

int P[MAXN][MAXN], nxt[MAXN], prv[MAXN];
void add_profit(int u, int v, int p) { P[u][v] = P[v][u] = p + P[u][v]; }

int dp[MAXN][MAXN][2];

int main() {
  int N = in();
  int M = in();
  int K = in();

  vector<ev> E;
  for (int i = 0; i < N; ++i) {
    int s = in();
    int t = in();
    E.emplace_back(s, i, 1);
    E.emplace_back(t, i, 0);
  }
  sort(E.begin(), E.end());

  int res = E[0].t + (M - E.back().t);

  memset(P, 0, sizeof(P));
  memset(nxt, ~0, sizeof(nxt));
  memset(prv, ~0, sizeof(prv));
  for (int i = 0; i + 1 < 2 * N; ++i) {
    if (E[i].go && E[i + 1].go) {
      add_profit(E[i].id, E[i].id, E[i + 1].t - E[i].t);
    } else if (E[i].go) {
      add_profit(E[i].id, E[i + 1].id, E[i + 1].t - E[i].t);
      if (E[i].id != E[i + 1].id) {
        prv[nxt[E[i + 1].id] = E[i].id] = E[i + 1].id;
      }
    } else if (E[i + 1].go) {
      res += E[i + 1].t - E[i].t;
    } else {
      add_profit(E[i + 1].id, E[i + 1].id, E[i + 1].t - E[i].t);
    }
  }

  vector<int> ord;
  for (int i = 0; i < N; ++i) {
    if (~prv[i]) {
      continue;
    }
    for (int u = i; ~u; u = nxt[u]) {
      ord.push_back(u);
    }
  }

  memset(dp, ~0, sizeof(dp));
  dp[1][1][1] = P[ord[0]][ord[0]];
  dp[1][0][0] = 0;
  for (int i = 1; i < N; ++i) {
    for (int j = 0; j <= i; ++j) {
      for (int k = 0; k < 2; ++k) {
        if (dp[i][j][k] >= 0) {
          chmax(dp[i + 1][j + 1][1], dp[i][j][k] + P[ord[i]][ord[i]] + k * P[ord[i - 1]][ord[i]]);
          chmax(dp[i + 1][j + 0][0], dp[i][j][k]);
        }
      }
    }
  }

  printf("%d\n", res + max(dp[N][K][0], dp[N][K][1]));

  return 0;
}
