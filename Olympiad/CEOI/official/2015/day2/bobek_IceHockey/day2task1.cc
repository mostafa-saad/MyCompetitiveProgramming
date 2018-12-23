/* Written by Filip Hlasek 2015 */
#include <cstdio>
#include <algorithm>
using namespace std;

#define MAXN 40
long long A[MAXN];

#define MAX (1 << ((MAXN + 1) / 2))
long long sums1[MAX], sums2[MAX];

void gen_subset_sums(long long A[], int N, long long sums[]) {
  for (int mask = 0; mask < (1 << N); ++mask) {
    long long sum = 0;
    for (int i = 0; i < N; ++i) if (mask & (1 << i)) sum += A[i];
    sums[mask] = sum;
  }
  sort(sums, sums + (1 << N));
}

int main(int argc, char *argv[]) {
  int N;
  long long M;
  scanf("%d%lld", &N, &M);
  for (int i = 0; i < N; ++i) scanf("%lld", A + i);

  int N1 = N / 2, N2 = N - N1;
  gen_subset_sums(A, N1, sums1);
  gen_subset_sums(A + N1, N2, sums2);

  long long ans = 0;
  int pos2 = (1 << N2);
  for (int pos1 = 0; pos1 < (1 << N1); ++pos1) {
    while (pos2 && sums1[pos1] + sums2[pos2 - 1] > M) pos2--;
    ans += pos2;
  }

  printf("%lld\n", ans);

  return 0;
}
