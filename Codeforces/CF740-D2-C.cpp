#include <bits/stdc++.h>
using namespace std;

#define all(v)				((v).begin()), ((v).end())
#define sz(v)				((int)((v).size()))
#define clr(v, d)			memset(v, d, sizeof(v))
#define repi(i, j, n) 		for(int i=(j);i<(int)(n);++i)
#define repd(i, j, n) 		for(int i=(j);i>=(int)(n);--i)
#define repa(v)				repi(i, 0, sz(v)) repi(j, 0, sz(v[i]))
#define rep(i, v)			repi(i, 0, sz(v))
#define lp(i, cnt)			repi(i, 0, cnt)
#define lpi(i, s, cnt)		repi(i, s, cnt)
#define P(x)				cout<<#x<<" = { "<<x<<" }\n"
#define pb					push_back
#define MP					make_pair

typedef vector<int> vi;
typedef vector<double> vd;
typedef vector<vi> vvi;
typedef vector<vd> vvd;
typedef vector<string> vs;
typedef long long ll;
typedef long double ld;

int main() {
#ifndef ONLINE_JUDGE
  freopen("zin.txt", "rt", stdin);
#endif

  int n, m;
  cin >> n >> m;

  int minRange = 1e9;

  lp(i, m)
  {
    int s, e;
    cin >> s >> e;

    minRange = min(minRange, e - s + 1);
  }

  cout << minRange << "\n";

  string str = "";

  for (int i = 0; i < n; ++i, str = " ")
    cout << str << i % minRange;
  cout << "\n";

  return 0;
}
