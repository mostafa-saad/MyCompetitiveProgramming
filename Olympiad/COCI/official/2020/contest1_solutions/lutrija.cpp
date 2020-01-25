#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef double lf;
typedef long double Lf;
typedef pair <int,int> pii;
typedef pair <ll, ll> pll;

#define TRACE(x) cerr << #x << "  " << x << endl
#define FOR(i, a, b) for (int i = (a); i < int(b); i++)
#define REP(i, n) FOR(i, 0, n)
#define all(x) (x).begin(), (x).end()
#define _ << " " <<

#define fi first
#define sec second
#define mp make_pair
#define pb push_back

const int MAXN = 10;

int bio[MAXN];

bool prosti(ll x) {
  if (x < 2) return 0;
  for (ll i = 2; i * i <= x; i++) {
    if (x % i == 0) return 0;
  }
  return 1;
}

ll a, b;

vector <ll> v;
vector <ll> rj, tmp;

void dfs(int cvor) {
  bio[cvor] = 1;
  tmp.pb(v[cvor]);
  if (v[cvor] == b) {
    if (rj.empty() || rj.size() > tmp.size()) rj = tmp;
    tmp.pop_back();
    return;
  }
  REP(i, (int)v.size()) {
    if (!bio[i] && prosti(max(v[i] - v[cvor], v[cvor] - v[i]))) {
      dfs(i);
      bio[i] = 0;
    }
  }
  tmp.pop_back();
}

int main() {
  cin >> a >> b;
  for (ll i = a - 2; i <= a + 2; i++) if (prosti(i)) v.pb(i);
  for (ll i = b - 2; i <= b + 2; i++) if (prosti(i)) v.pb(i);
  v.pb(2);

  sort(all(v));
  v.erase(unique(all(v)), v.end());

  REP(i, (int)v.size()) {
    if (v[i] == a) {
      bio[i] = 1;
      dfs(i);
    }
  }

  if (rj.empty()) puts("-1");
  else {
    printf("%d\n",(int)rj.size());
    for (auto t : rj) printf("%lld ", t);
    puts("");
  }
  return 0;
}
