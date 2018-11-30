/* Task Sequence
 * Author: Jakub Radoszewski
 * Date: 15.04.2007
 * Description: O(n^2) implementation of greedy solution,
 *              well behaving on random input data */

#include <cstdio>
#include <algorithm>
#include <list>
using namespace std;

#define MAX_N 1000000
#define INFTY 1000000001

int n, a[MAX_N + 2];
list<int> l;

int main()
{
  scanf("%d", &n);
  for (int i = 1; i <= n; i++)
    scanf("%d", &a[i]);
  a[0] = a[n + 1] = INFTY; /* to simplify the further code */
  for (int i = 0; i <= n + 1; i++)
    l.push_back(a[i]);
  long long res = 0LL;
  while (n > 1)
  {
    list<int>::iterator it = l.begin();
    int last = *it;
    it++;
    /* Each execution of this loop decreases n by one */
    while (1)
    {
      int change = last;
      it++; change = min(change, *it);
      it--;
      if (change < *it)
      {
        last = *it;
        it++;
      }
      else
      {
        res += change;
        l.erase(it);
        n--;
        break;
      }
    }
  }
  printf("%lld\n", res);
  return 0;
}
