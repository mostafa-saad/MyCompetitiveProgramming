#include <algorithm>
#include <climits>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

const int MIN_V = -5000000;
const int RANGE_V = 10000001;

void countingSort(vector<int>& v) {
  vector<int> f(RANGE_V);
  for (int i = 0; i < (int) v.size(); ++i) {
    ++f[v[i] - MIN_V];
  }
  for (int i = 0, j = 0; i < RANGE_V; ++i) {
    while (f[i]--) {
      v[j++] = MIN_V + i;
    }
  }
}

int solve(vector<int>& v, int n, int k) {
  countingSort(v);
  k = n - k;
  
  deque<pair<int, int> > q;
  int ans = INT_MAX;
  
  for (int i = 1; i < n; ++i) {
    if (!q.empty() && q.front().second - 1 <= i - k) {
      q.pop_front();
    }
    int d = v[i] - v[i - 1];
    while (!q.empty() && q.back().first >= d) {
      q.pop_back();
    }
    q.push_back(make_pair(d, i));
    
    if (i >= k - 1) {
      int M = v[i] - v[i - k + 1];
      int m = q.front().first;
      ans = min(ans, M + m);
    }
  }
  
  return ans;
}

int main(void) {
  ios::sync_with_stdio(false);
  
  int n, k;
  cin >> n >> k;
  vector<int> v(n);
  for (int i = 0; i < n; ++i) {
    cin >> v[i];
  }
  cout << solve(v, n, k) << "\n";
  
  return 0;
}
