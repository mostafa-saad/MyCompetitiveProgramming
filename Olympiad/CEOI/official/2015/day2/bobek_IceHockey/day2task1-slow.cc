/* Written by Filip Hlasek 2015 */
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstring>

#define FOR(i,a,b) for(int i=(a);i<=(b);i++)
#define FORD(i,a,b) for(int i=(a);i>=(b);i--)
#define REP(i,b) for(int i=0;i<(b);i++)

using namespace std;

#define MAXN 44
long long C[MAXN];
int N;
long long M;

int main(int argc, char *argv[]) {
  scanf("%d%lld", &N, &M);
  REP(i, N) scanf("%lld", C + i);
  long long ans = 0;
  for (long long mask = 0; mask < (1LL << N); ++mask) {
    long long sum = 0;
    REP(i, N) if (mask & (1LL << i)) if ((sum += C[i]) > M) break;
    ans += (sum <= M);
  }
  printf("%lld\n", ans);
  return 0;
}
