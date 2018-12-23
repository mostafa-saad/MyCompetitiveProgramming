/* Written by Filip Hlasek 2015 */
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cmath>
using namespace std;

#define MAX_TIME 5 // seconds
#define ITERATION_STEPS 1000000
#define MAXN 40
long long A[MAXN];

int main(int argc, char *argv[]) {
  int N;
  long long M;
  scanf("%d%lld", &N, &M);
  for (int i = 0; i < N; ++i) scanf("%lld", A + i);

  long long positive_tries = 0, all_tries = 0;

  time_t start_time = time(NULL);
  while (time(NULL) - start_time < MAX_TIME) {
    for (int step = 0; step < ITERATION_STEPS; ++step) {
      long long sum = 0;
      for (int i = 0; i < N; ++i) if (rand() % 2) sum += A[i];
      positive_tries += (sum <= M);
      all_tries++;
    }
  }

  long double ratio = (long double)positive_tries / all_tries;
  long long ans = llround(ratio * (1LL << N));
  printf("%lld\n", ans);
  return 0;
}
