/* Verifying solution for the task SIM (Similarity)
 * Author: Jakub Radoszewski
 * Date: June 2011
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string pattern, text;
int n, m;
vector<int> t[256];

int main()
{
  ios_base::sync_with_stdio(0);
  cin >> pattern >> text;
  n = text.size();
  m = pattern.size();

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
  cout << similarity << endl;
  return 0;
}
