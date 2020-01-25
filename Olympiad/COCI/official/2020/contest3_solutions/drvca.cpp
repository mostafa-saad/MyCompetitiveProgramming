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

const int MAXN = 100100;

int n, p[MAXN];

void print(vector <int> &a, multiset <int> &b) {
  printf("%d\n", (int)a.size());
  for (auto x : a) printf("%d ", x);
  puts("");
  printf("%d\n", (int)b.size());
  for (auto x : b) printf("%d ", x);
  puts("");
}

void check(int a, int b) {
  multiset <int> s, raz;
  int k = b - a;
  REP(i, n) s.insert(p[i]);
  s.erase(s.find(a));
  s.erase(s.find(b));

  vector <int> ans;
  ans.pb(a);
  ans.pb(b);

  int last = -1;
  for (auto x : s) {
    if (last != -1) raz.insert(x - last);
    last = x;
  }

  int tmp = b + k;
  do {
    if (*raz.begin() == *raz.rbegin()) {
      print(ans, s);
      exit(0);  
    }

    auto it = s.find(tmp);
    if (it == s.end()) break;
    auto l = it;
    auto r = it;
    if (it != s.begin()) {
      l--;
      raz.erase(raz.find(*it - *l));
    }
    r++;
    if (r != s.end()) {
      raz.erase(raz.find(*r - *it));
      if (it != s.begin()) raz.insert(*r - *l);
    }
    s.erase(it);
    ans.pb(tmp);
    tmp += k;
  } while ((int)ans.size() < n);
}

int main() {
  scanf("%d",&n);
  REP(i, n) scanf("%d",&p[i]);
  sort(p, p + n);

  if (n <= 4) {
    printf("%d\n",n / 2);
    REP(i, n / 2) printf("%d ",p[i]);
    puts("");
    printf("%d\n",n - n / 2);
    FOR(i, n / 2, n) printf("%d ",p[i]);
    puts("");
    return 0;
  }

  check(p[0], p[1]);
  check(p[0], p[2]);
  check(p[1], p[2]);

  puts("-1");

  return 0;
}

