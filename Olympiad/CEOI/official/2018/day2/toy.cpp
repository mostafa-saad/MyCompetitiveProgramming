#include <bits/stdc++.h>
using namespace std;

vector<unordered_set<int>> results;

vector<int> Divisors(int n) {
  vector<int> result;
  for (int i = 1; i*i <= n; i++)
    if (n % i == 0) {
      result.push_back(i);
      if (i*i < n) result.push_back(n / i);
    }
  sort(result.begin(), result.end());
  return result;
}

int main() {
  int n;
  cin >> n;

  vector<int> divisors = Divisors(n);
  for (int x : divisors) {
    assert(x > 0);
    results.push_back(unordered_set<int>(1000));
  }

  results[0].insert(0);

  vector<int> to_add;
  int last = divisors.size()-1;

  for (int i = 0; i < (int)divisors.size(); i++) {
    int x = divisors[i];
    for (int j = i+1; j < (int)divisors.size(); j++) {
      int y = divisors[j];
      if (y % x != 0) continue;
      int add = y / x - 1;
      to_add.clear();
      for (int r : results[i]) to_add.push_back(r + add);
      results[j].insert(to_add.begin(), to_add.end());
    }
    if (i != last) results[i].clear();
  }

  vector<int> final_result = vector<int>(results[last].begin(), results[last].end());
  sort(final_result.begin(), final_result.end());

  cout << final_result.size() << "\n";
  for (int r : final_result)
    cout << r << " ";
  cout << "\n";

  return 0;
}
