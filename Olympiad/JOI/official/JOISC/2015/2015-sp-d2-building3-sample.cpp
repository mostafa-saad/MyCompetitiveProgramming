#include <cstdio>
#include <cstring>

using namespace std;

typedef long long Int;

template<typename T> void chmax(T& a, T b) { if (a < b) a = b; }
int in() { int x; scanf("%d", &x); return x; }

const int MAXN = 1 << 20;
int N, B[MAXN], occur[MAXN];

int main() {
  N = in();
  for (int i = 0; i < N - 1; ++i) {
    B[i] = in();
  }

  Int pattern2_res = 0;
  bool pattern1 = false, impossible = false;
  int pattern1_val, pattern1_pos, running_max = 0;
  memset(occur, 0, sizeof(occur));
  occur[0] = 1;
  for (int i = 0; i < N - 1; ++i) {
    if (!occur[B[i] - 1]) {
      if ((B[i] >= 2 && !occur[B[i] - 2]) || (pattern1 && pattern1_val != B[i] - 1)) {
        impossible = true;
      }
      if (!pattern1) {
        pattern1 = true;
        pattern1_val = B[i] - 1;
        pattern1_pos = i;
      }
    }
    occur[B[i]] = 1;
    pattern2_res += running_max + 1;
    chmax(running_max, B[i]);
  }
  pattern2_res += running_max + 1;
  pattern2_res -= N - 1;

  if (impossible) {
    puts("0");
    return 0;
  }
  if (pattern1) {
    int prev_pos = pattern1_val == 1 ? -1 : 0;
    for (int i = 0; i < N - 1; ++i) {
      if (B[i] == pattern1_val - 1) {
        prev_pos = i;
        break;
      }
    }
    printf("%d\n", pattern1_pos - prev_pos);
    return 0;
  }

  printf("%lld\n", pattern2_res);
  return 0;
}
