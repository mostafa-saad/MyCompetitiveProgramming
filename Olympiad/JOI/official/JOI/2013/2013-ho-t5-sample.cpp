#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cctype>
#include <cmath>
#include <cassert>
using namespace std;

#define all(c) (c).begin(), (c).end()
#define iter(c) __typeof((c).begin())
#define cpresent(c, e) (find(all(c), (e)) != (c).end())
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define tr(c, i) for (iter(c) i = (c).begin(); i != (c).end(); ++i)
#define pb(e) push_back(e)
#define mp(a, b) make_pair(a, b)

typedef long long ll;

int segt_max[1000010], segt_dif[1000010];

int segt_add(int a, int b, int v, int k, int l, int r) {
  if (r <= a || b <= l) return segt_max[k];
  if (a <= l && r <= b) {
    segt_dif[k] += v;
    return segt_max[k] += v;
  }
  else {
    return segt_max[k] = segt_dif[k] + max(
        segt_add(a, b, v, k * 2 + 1, l, (l + r) / 2),
        segt_add(a, b, v, k * 2 + 2, (l + r) / 2, r));
  }
}

ll merge_count(vector<int> &a) {
  int n = a.size();
  if (n <= 1) return 0;
  vector<int> b(a.begin(), a.begin() + n / 2);
  vector<int> c(a.begin() + n / 2, a.end());
  ll res = 0;
  res += merge_count(b);
  res += merge_count(c);
  for (int ai = 0, bi = 0, ci = 0; ai < n; ++ai) {
    if (ci == (int)c.size() || (bi < (int)b.size() && b[bi] <= c[ci])) {
      a[ai] = b[bi++];
    } else {
      a[ai] = c[ci++];
      res += n / 2 - bi;
    }
  }
  return res;
}

int N, A[1000010];
int Yu[1000010];

vector<int> Ux, Uy, L;
bool usd[1000010];

pair<int, int> get_u_range(int i) {
  return mp(upper_bound(all(Uy), A[i]) - Uy.begin(),
            upper_bound(all(Ux), i) - Ux.begin());
}

ll solve() {
  vector<int> a(A, A + N);
  ll org = merge_count(a), ans = org + 1;
  rep (i, N - 1) {
    if (a[i] == a[i + 1]) {
      --ans;
      break;
    }
  }

  for (int i = 0; i < N; ++i) {
    if (Ux.empty() || A[Ux.back()] < A[i]) {
      usd[i] = true;
      Ux.pb(i);
      Uy.pb(A[i]);
    }
  }
  for (int i = N - 1; i >= 0; --i) {
    if ((L.empty() || A[L.back()] > A[i]) && !usd[i]) {
      L.pb(i);
      usd[i] = true;
    }
  }
  reverse(all(L));

  vector<int> Mx, My;
  rep (i, N) if (!usd[i]) Mx.pb(i);
  {
    vector<pair<int, int> > tmp;
    rep (i, Mx.size()) tmp.pb(mp(A[Mx[i]], Mx[i]));
    sort(all(tmp));
    rep (i, tmp.size()) My.pb(tmp[i].second);
  }
  int Un = Ux.size(), Ln = L.size(), Mn = Mx.size();

  memset(segt_max, 0, sizeof(segt_max));
  memset(segt_dif, 0, sizeof(segt_dif));

  int mxi = 0, myi = 0;
  rep (li, Ln) {
    int l = L[li];

    for (; mxi < Mn && Mx[mxi] < l; ++mxi) {  // In
      pair<int, int> ur = get_u_range(Mx[mxi]);
      segt_add(ur.first, ur.second, +1, 0, 0, Un);
      if (ur.first - 1 >= 0 && A[Ux[ur.first - 1]] == A[Mx[mxi]]) --ur.first;
      segt_add(ur.first, ur.second, +1, 0, 0, Un);
    }
    for (; myi < Mn && A[My[myi]] < A[l]; ++myi) {  // Out
      pair<int, int> ur = get_u_range(My[myi]);
      segt_add(ur.first, ur.second, -1, 0, 0, Un);
      if (ur.first - 1 >= 0 && A[Ux[ur.first - 1]] == A[My[myi]]) --ur.first;
      segt_add(ur.first, ur.second, -1, 0, 0, Un);
    }
    for (int k = 0; myi + k < Mn && A[My[myi + k]] == A[l]; ++k) {  // Border
      pair<int, int> ur = get_u_range(My[myi + k]);
      if (ur.first - 1 >= 0 && A[Ux[ur.first - 1]] == A[My[myi]]) --ur.first;
      segt_add(ur.first, ur.second, -1, 0, 0, Un);
    }

    pair<int, int> ur = get_u_range(l);
    if (ur.first < ur.second) {
      int tmp = segt_max[0];
      ans = min(ans, org - tmp - 1);
    }
    for (; myi < Mn && A[My[myi]] == A[l]; ++myi) {  // Out
      pair<int, int> ur = get_u_range(My[myi]);
      segt_add(ur.first, ur.second, -1, 0, 0, Un);
    }
  }

  return ans;
}

int main() {
  scanf("%d", &N);
  rep (i, N) scanf("%d", &A[i]);

  vector<int> nums(A, A + N);
  sort(all(nums));
  nums.erase(unique(all(nums)), nums.end());
  rep (i, N) A[i] = lower_bound(all(nums), A[i]) - nums.begin();

  printf("%lld\n", solve());
  return 0;
}
