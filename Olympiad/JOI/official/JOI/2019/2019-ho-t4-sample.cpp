#include <cmath>
#include <cstdio>
#include <vector>

using std::abs;
using std::min;
using std::vector;

int N;
vector<int> X, Y;

int main() {
  scanf("%d", &N);
  X.resize(2 * N);
  Y.resize(2 * N);
  for (int i = 0; i < 2 * N; ++i) {
    scanf("%d%d", &X[i], &Y[i]);
  }

  long long ans = 0;
  vector<vector<int>> count(N + 1, vector<int>(3, 0));
  for (int i = 0; i < 2 * N; ++i) {
    int x = X[i], y = Y[i];
    if (x < 1) {
      ans += (1 - x);
      x = 1;
    }
    if (x > N) {
      ans += (x - N);
      x = N;
    }
    if (y < 1) {
      ans += (1 - y);
      y = 1;
    }
    if (y > 2) {
      ans += (y - 2);
      y = 2;
    }
    ++count[x][y];
  }
  vector<int> surplus(3, 0);
  for (int x = 1; x <= N; ++x) {
    for (int y = 1; y <= 2; ++y) {
      surplus[y] += (count[x][y] - 1);
    }
    for (int y = 1; y <= 2; ++y) {
      if (surplus[y] > 0 && 0 > surplus[3 - y]) {
        const int t = min(surplus[y], -surplus[3 - y]);
        ans += t;
        surplus[y] -= t;
        surplus[3 - y] += t;
      }
    }
    for (int y = 1; y <= 2; ++y) {
      ans += abs(surplus[y]);
    }
  }
  printf("%lld\n", ans);
  return 0;
}
