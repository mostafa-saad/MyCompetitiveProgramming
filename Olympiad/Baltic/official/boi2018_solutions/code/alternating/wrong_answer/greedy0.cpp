#include <bits/stdc++.h>

using namespace std;

struct arc {
  int a, b, i;
};

int main() {
  int n, m;
  cin >> n >> m;
  vector<arc> arcs(m);
  for (int i = 0; i < m; ++i) {
    int a,b;
    cin >> a >> b;
    arcs[i] = {a, b, i};
  }

  sort(arcs.begin(), arcs.end(), [](arc& a, arc& b){
    return pair<int,int>(a.a, a.b) < pair<int,int>(b.a, b.b);
  });

  vector<int> ans(m);
  vector<pair<int,int>> end = {{0, 0}, {0, 0}};
  vector<vector<pair<int,int>>> part(2);
  for (int i = 0; i < m; ++i) { 
    int a = arcs[i].a, b = arcs[i].b;
    int c = end[0] < end[1] ? 0 : 1;
    end[c].second = b;
    ans[arcs[i].i] = c;
    if (b < a) {
      part[c].emplace_back(1, b);
      part[c].emplace_back(a, n);
      end[c].first = 1;
    } else {
      part[c].emplace_back(a, b);
    }
  }

  bool lose = 0;
  for (auto& i:part) {
    sort(i.begin(), i.end());
    int l = 0;
    for (auto& j:i) {
      lose |= l+1 < j.first;
      l = j.second;
    }
    lose |= l != n;
  }

  if (lose) cout << "impossible";
  else {
    for (int i:ans)
      cout << i;
  }
  cout << endl;
}
