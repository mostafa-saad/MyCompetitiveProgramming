/* Verifying solution for the task SIM (Similarity)
 * Author: Jakub Radoszewski
 * Date: June 2011
 */

#include <cstdio>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

#define MAX 2000000

char pattern[MAX + 2], text[MAX + 2];
int n, m;
vector<int> t[256];

int main()
{
  scanf("%s", pattern);
  scanf("%s", text);

  n = strlen(text);
  m = strlen(pattern);

  for (int i = 0; i < n; i++)
    t[(int)text[i]].push_back(i);

  long long similarity = 0;
  for (int i = 0; i < m; i++)
  {
    int ch = pattern[i];
    int matches = t[ch].size();
    matches -= lower_bound(t[ch].begin(), t[ch].end(), i) - t[ch].begin();
    matches -= t[ch].end() - upper_bound(t[ch].begin(), t[ch].end(), n - (m - i));
    similarity += max(matches, matches);
  }
  printf("%lld\n", similarity);
  return 0;
}
