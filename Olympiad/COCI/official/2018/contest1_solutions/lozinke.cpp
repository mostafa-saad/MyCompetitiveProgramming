#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <string>
#include <vector>
#include <queue>

using namespace std;

#define TRACE(x) cerr << #x << " " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); ++i)
#define REP(i, n) FOR(i, 0, n)
#define _ << " " <<

#define fst first
#define snd second

typedef long long llint;
typedef pair<int, int> pii;

const int MAXN = 2e4 + 10;

int n;

string l[MAXN];

unordered_set<string> s;
unordered_map<string, int> cnt;

int main(void) {
  cin >> n;
  for (int i = 0; i < n; ++i) {
    cin >> l[i];
    s.clear();

    for (int j = 0; j < (int) l[i].size(); ++j) {
      string curr;
      for (int k = j; k < (int) l[i].size(); ++k) {
        curr.push_back(l[i][k]);
        s.insert(curr);
      }
    }

    for (auto &x : s)
      cnt[x]++;
  }

  int sol = 0;
  for (auto &x : l)
    sol += cnt[x];

  cout << sol - n << endl;

  return 0;
}

