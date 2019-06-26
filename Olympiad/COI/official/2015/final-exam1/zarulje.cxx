#include <algorithm>
#include <cassert>
#include <cstring>
#include <iostream>
#include <stack>

using namespace std;

typedef long long llint;

const int MAXN = 1000100;
const int mod = 1e9 + 7;

int mul(int a, int b) {
  return llint(a)*b % mod;
}

int powmod(int a, int b) {
  if (b == 0) return 1;
  if (b&1) return mul(a, powmod(a, b-1));
  return powmod(mul(a, a), b/2);
}

int f[MAXN], invf[MAXN];
int a[MAXN], ans[MAXN];
int fl[MAXN], fr[MAXN];
vector<pair<int, int>> e[MAXN];

void add(int &a, int b, int d, int &ways) {
  ways = mul(ways, mul(f[a], mul(f[b], invf[a+b])));
  a += d;
  ways = mul(ways, mul(invf[a], mul(invf[b], f[a+b])));
}

int main(void) {
  int n, k;
  scanf("%d %d", &n, &k);
  for (int i = 0; i < n; ++i)
    scanf("%d", &a[i]);
  
  f[0] = invf[0] = 1;
  for (int i = 1; i <= n; ++i) {
    f[i] = mul(f[i-1], i);
    invf[i] = powmod(f[i], mod-2);
  }

  stack<int> S;
  for (int i = n-1; i >= 0; --i) {
    while (!S.empty() && S.top() > a[i]) {
      fr[S.top()]--;
      e[i].push_back({S.top(), +1});
      S.pop();
    }
    e[i].push_back({a[i], -1});
    fr[a[i]]++;
    S.push(a[i]);
  }
  while (!S.empty()) S.pop();

  int ways = 1;
  for (int i = 0; i < n; ++i) {
    for (auto &p: e[i])
      add(fr[p.first], fl[p.first], p.second, ways);    
    ans[i] = ways;

    while (!S.empty() && S.top() > a[i]) {
      add(fl[S.top()], fr[S.top()], -1, ways);
      S.pop();
    }
    add(fl[a[i]], fr[a[i]], +1, ways);
    S.push(a[i]);
  }
  
  for (int i = 0; i < k; ++i) {
    int p;
    scanf("%d", &p); --p;
    printf("%d\n", ans[p]);
  }
  return 0;
}
