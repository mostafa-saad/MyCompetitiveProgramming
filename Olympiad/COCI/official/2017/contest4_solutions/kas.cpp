#include <algorithm>
#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 505;
const int MAXS = 100010; 
const int INF  = 1e9;

int n, sum, sol;
int c[MAXN], memo[MAXN][MAXS/2];

int rek(int pos, int diff) {

  if (diff > sum / 2) 
    return -INF;

  int& memo_ref = memo[pos][diff];

  if (memo_ref != -1)
    return memo_ref;

  if (pos == n)
    return memo_ref = (diff != 0) * (-INF);

  return memo_ref = max(rek(pos + 1, diff), 
                    max(rek(pos + 1, diff + c[pos]) + c[pos], 
                        rek(pos + 1, abs(diff - c[pos])) + max(0, c[pos] - diff)));

}

int main(void) {
 
  memset(memo, -1, sizeof memo);

  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &c[i]);
    sum += c[i];
  }

  sol = rek(0, 0);
  sol += sum - 2 * sol;

  printf("%d\n", sol);

  return 0;

}
