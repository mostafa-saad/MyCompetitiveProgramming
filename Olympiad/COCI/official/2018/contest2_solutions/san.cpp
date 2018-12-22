#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 42;

int n;
int h[MAXN], g[MAXN];
ll k;

vector<int> hs;
vector<ll> L[MAXN], R[MAXN];

void rec_left(int pos, int last, ll sum) {
  if (pos == n/2) {
    int idx = lower_bound(hs.begin(), hs.end(), last) - hs.begin();
    L[idx].push_back(sum);
    return;
  }
  rec_left(pos+1, last, sum);
  if (h[pos] >= last) {
    rec_left(pos+1, h[pos], sum + g[pos]);
  }
}

void rec_right(int pos, int first, int last, ll sum) {
  if (pos == n) {
    int idx = lower_bound(hs.begin(), hs.end(), first) - hs.begin();
    R[idx].push_back(sum);
    return;
  }
  rec_right(pos+1, first, last, sum);
  if (h[pos] >= last) {
    int nfirst = (first == 0) ? h[pos] : first;
    rec_right(pos+1, nfirst, h[pos], sum + g[pos]);
  }
}

int main(void) {
  scanf("%d%lld", &n, &k);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &h[i], &g[i]);
    hs.push_back(h[i]);
  }
  hs.push_back(0);
  sort(hs.begin(), hs.end());
  
  rec_left(0, 0, 0);
  rec_right(n/2, 0, 0, 0);

  ll ans = 0;

  for (int i = 0; i < (int)hs.size(); ++i) {
    sort(R[i].begin(), R[i].end());
  }
  
  for (int i = 0; i < (int)hs.size(); ++i) {
    for (auto it : L[i]) {
      ans += R[0].end() - lower_bound(R[0].begin(), R[0].end(), k - it);
      for (int j = i; j < (int)hs.size(); ++j) {
        ans += R[j].end() - lower_bound(R[j].begin(), R[j].end(), k - it);
      }
    }
  }

  printf("%lld\n", ans);

  return 0;
}

