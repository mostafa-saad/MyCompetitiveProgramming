/* Task Sequence
 * Author: Jakub Radoszewski
 * Date: 15.04.2007
 * Description: O(n^3) dynamic programming solution */

#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX_N 2000
#define INFTY 1000000000000000LL

int n, a[MAX_N];
long long tab[MAX_N][MAX_N]; /* for DP */

int main()
{
  scanf("%d", &n);
  for (int i = 0; i < n; i++)
    scanf("%d", &a[i]);
  /* tab[l][l] = 0 is automatic */
  for (int len = 2; len <= n; len++)
    for (int l = 0; l < n; l++)
    {
      int r = l + len - 1;
      if (r >= n) break;
      /* counting tab[i][j] */
      int mx = 0;
      for (int i = l; i <= r; i++)
        mx = max(mx, a[i]);
      tab[l][r] = INFTY;
      for (int i = l; i < r; i++)
        tab[l][r] = min(tab[l][r], tab[l][i] + tab[i+1][r] + mx);
    }
  printf("%lld\n", tab[0][n - 1]);
  return 0;
}
