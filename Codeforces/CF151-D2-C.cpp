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

// for 40: {2, 2, 2}, for 15 = {3, 5}
vector<ll> factorization(ll n) {
  vector<ll> first_primes;

  if (n == 1)
    return first_primes;

  for (ll d = 1, i = 2; i * i <= n && first_primes.size() <= 3; i += d, d = 2) {
      while (n % i == 0)
        first_primes.push_back(i), n /= i;
  }

  if (n > 1)
    first_primes.push_back(n);

  return first_primes;
}

int main() {
#ifndef ONLINE_JUDGE
  freopen("zin.txt", "rt", stdin);
#endif

  ll n;
  cin >> n;

  vector<ll> first_primes = factorization(n);

  if (first_primes.size() <= 1)
    cout << "1\n0\n";
  else if (first_primes.size() == 2)
    cout << "2\n";
  else
    cout << "1\n" << first_primes[0] * first_primes[1] << "\n";

  return 0;
}
