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

int ok[MAXN], cnt;
int last[ABC];
int bio[MAXN];

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
    kada[p[i+1]] = i+1;
  }

  REP(i, n + 1) {
    if (i) s[--p[i]] = '*';
    REP(j, q) {
      if (bio[j]) continue;
      REP(k, ABC) last[k] = -1;
      bool ok = 1;
      FOR(k, a[j], b[j] + 1) {
        if (s[k] == '*') continue;
        if (last[s[k] - 'a'] != -1) { 
          ok = 0;
          break;
        } else {
          last[s[k] - 'a'] = 1;
        }
      }
      bio[j] = ok;
      cnt += ok;
    }
    if (cnt == q) {
      printf("%d\n",i);
      return 0;
    }
  }
  return 0;
}

