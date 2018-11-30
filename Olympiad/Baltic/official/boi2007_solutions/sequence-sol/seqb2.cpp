/* Task Sequence
 * Author: Jakub Radoszewski
 * Date: 15.04.2007
 * Description: O(n) incorrect greedy solution. */

#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

#define MAX_N 1000000
#define INFTY 1000000001

int n, a[MAX_N + 2];
vector<int> stack;

int main()
{
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  a[0] = a[n + 1] = INFTY; /* to simplify the further code */
  long long res = 0LL;
  stack.push_back(a[0]);
  for (int i = 1; i <= n + 1; i++)
  {
    while (a[i] >= stack.back())
    {
      /* the error: reduces not with the smaller element, but with the
       * leftmost one */
      int change = stack[(int)stack.size() - 2];
      if (change == INFTY) /* in case of only one sequence element remaining */
        break;
      res += change;
      stack.pop_back();
    }
    stack.push_back(a[i]);
  }
  printf("%lld\n", res);
  return 0;
}
