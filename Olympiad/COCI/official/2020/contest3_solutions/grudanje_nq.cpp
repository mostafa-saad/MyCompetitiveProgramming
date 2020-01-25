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
const int ABC = 30;

int n, q;
string s;
int p[MAXN], kada[MAXN];
int a[MAXN], b[MAXN];

int pref[ABC][MAXN];

bool check(int x) {
  REP(j, ABC) {
    char z = s[0];
    if (kada[0] <= x) z = '*';
    pref[j][0] = (z - 'a' == j);
  }
  FOR(i, 1, n) {
    char z = s[i];
    if (kada[i] <= x) z = '*';
    REP(j, ABC) {
      pref[j][i] = pref[j][i - 1] + (j == z - 'a');
    }
  }

  REP(i, q) {
    REP(j, ABC) {
      int r = pref[j][b[i]];
      int l = 0;
      if (a[i]) l = pref[j][a[i] - 1];
      if (r - l > 1) return 0;
    }
  }
  return 1;
}

int main() {
  cin >> s;
  n = s.size();
  scanf("%d",&q);
  REP(i, q) {
    scanf("%d %d",&a[i],&b[i]);
    a[i]--; b[i]--;
  }
  REP(i, n) {
    scanf("%d",&p[i+1]);
    kada[--p[i+1]] = i+1;
  }

  REP(i, n + 1) {
    if (check(i)) {
      printf("%d\n",i);
      return 0;
    }
  }

  return 0;
}

