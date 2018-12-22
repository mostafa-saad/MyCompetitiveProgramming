// Autor: Ante Derek

#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cassert>
#include <algorithm>

#define TRACE(x) cerr << #x << " = " << x << endl
#define _ << " _ " << 

using namespace std;

map<string, int> index;
vector<vector<int>> parents;

int process(const string &k, const vector<string> &p) {
  int m = index.size();
  if (index.count(k))
    return 0;
  vector<int> pp;
  for (auto x : p) {
    if (index.count(x) == 0)
      return 0;
    pp.push_back(index[x]);
  }
  sort(pp.begin(), pp.end());
  vector<int> seen(m, 0);
  for (int i=(int)pp.size()-1; i>=0; i--) {
    int y = pp[i];
    if (seen[y])
      continue ;
    for (auto z : parents[y]) {
      if (seen[z])
        return 0;
      seen[z] = 1;
    }
  }
  index[k] = m;
  for (auto y : pp)
    seen[y] = 1;
  parents.push_back(vector<int>());
  for (int i=0; i<m; i++)
    if (seen[i])
      parents[m].push_back(i);
  return 1;
}

int main() {
  int n;
  cin >> n;
  for (int i=0; i<n; i++) {
    string k;
    vector<string> p;
    string temp;
    cin >> k >> temp;
    assert(temp == ":");
    cin >> temp;
    while (temp != ";") {
      p.push_back(temp);
      cin >> temp;
    }
    if (process(k, p))
      cout << "ok" << endl;
    else
      cout << "greska" << endl;
  }
  return 0;
}
