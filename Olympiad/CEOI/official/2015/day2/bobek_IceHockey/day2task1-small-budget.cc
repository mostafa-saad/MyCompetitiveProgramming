/* Written by Filip Hlasek 2015 */
#include <cstdio>
using namespace std;

#define MAXN 40
#define MAXM 1000000

long long ways[MAXM + 1];

int main(int argc, char *argv[]) {
  int N;
  long long M;
  scanf("%d%lld", &N, &M);
  ways[0] = 1;
  for (int i = 0; i < N; ++i) {
    long long a;
    scanf("%lld", &a);
    for (long long b = M; b >= 0; --b) {
      if (b + a <= M) {
        ways[b + a] += ways[b];
      }
    }
  }
  long long ans = 0;
  for (long long b = 0; b <= M; ++b) {
    ans += ways[b];
  }
  printf("%lld\n", ans);
  return 0;
}
