/* Task Sequence
 * Author: Jakub Radoszewski
 * Date: 15.04.2007
 * Description: O(n^2) weak implementation of greedy solution */

#include <cstdio>
#include <algorithm>
using namespace std;

#define MAX_N 1000000
#define INFTY 1000000001

int n, a[MAX_N + 2];

int main()
{
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  a[0] = a[n + 1] = INFTY; /* to simplify the further code */
  long long res = 0LL;
  while (n > 1)
  {
    for (int i = 1; i <= n; i++)
      if (a[i] <= a[i - 1] && a[i] <= a[i + 1])
      {
        res += min(a[i - 1], a[i + 1]);
        for (int j = i + 1; j <= n + 1; j++)
          a[j - 1] = a[j];
        n--;
        break;
      }
  }
  printf("%lld\n", res);
  return 0;
}
