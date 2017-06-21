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

ll gcd(ll a, ll b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

vector<ll> generate_divisors(long long n = (ll) (1e12)) {
  vector<ll> v;
  ll i = 1;
  for (; i * i < n; ++i)
    if (n % i == 0)
      v.push_back(i), v.push_back(n / i);
  if (i * i == n)
    v.push_back(i);

  return v;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("zin.txt", "rt", stdin);
#endif

  ll a, b;
  cin >> a >> b;

  ll g = gcd(a, b);
  vector<ll> div = generate_divisors(g);
  sort(all(div));

  int q;
  cin >> q;

  lp(cc, q)
  {
    ll low, high;
    cin >> low >> high;

    auto it = lower_bound(all(div), high);

    if(it == div.end() || *it > high)
      it--;

    if(low <= *it && *it <= high)
      cout<<*it<<"\n";
    else
      cout<<-1<<"\n";
  }

  return 0;
}
