#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

const int MAXN = 1 << 20;

int n;
int a[MAXN];
int q;
int l[MAXN], r[MAXN], sol[MAXN];
int blokSize;

int fl[MAXN];

int ans[MAXN];
int T[MAXN];

void build (int x, int l, int r) {
  if (l == r) {
    T[x] = l;
    return;
  }

  int mid = (l+r)/2;
  build(x*2, l, mid);
  build(x*2+1, mid+1, r);
  if (a[T[x*2]] > a[T[x*2+1]]) T[x] = T[x*2];
  else T[x] = T[x*2+1];
}

int query (int x, int l, int r, int L, int R) {
  if (R < l || L > r) return -1;
  if (l >= L && r <= R) return T[x];
  int mid = (l+r)/2;
  int p0 = query(x*2, l, mid, L, R);
  int p1 = query(x*2+1, mid+1, r, L, R);
  if (p0 == -1) return p1;
  if (p1 == -1) return p0;
  if (a[p0] > a[p1]) return p0;
  else return p1;
}

void solve_ans () {
  build(1, 0, n-1);
  for (int i = 0; i < n; ++i) 
    ans[i] = query(1, 0, n-1, i, fl[i] - 1) - i + 1;
}


vector <int> go[MAXN];

int mv[MAXN];
int nextt[MAXN];
int nxt[MAXN];

vector <int> queries[MAXN];

int nbest[MAXN];
int solve_small (int l, int r) {
  int ret = 0;
  int nbest = -1;
  for (int i = r; i >= l; --i) {
    if (nbest == -1 || a[nbest] < a[i]) nbest = i;
    if (fl[i] > r) ret = max(ret, nbest - i + 1);
    else ret = max(ret, ans[i]);
  }

  return ret;
}

int solve_large (int l, int r) {
  if (l > r) return 0;
  int ret = 0;
  int best = -1;
  vector <int> maks;
  for (int i = l; i < l + blokSize; ++i) {
    if (best == -1 || a[i] >= a[best]) best = i;
    maks.push_back(best);
  }

  int pos = l + blokSize;
  int have = 0;
  int took = 0;

  for (int i = l + blokSize - 1; i >= l; --i) {
    while (pos > l && (int)go[pos].size() + have <= took) {
      have += go[pos].size();
      --pos;
    }

    if (maks[i - l] == i && r >= i){
      if (go[pos].size() == 0) continue;
      int npos = go[pos].size() - 1 - (took - have);
//      if (pos != l + blokSize) npos = go[pos].size() - 1;
      if (go[pos].size() > 0 && fl[go[pos][npos]] > i) ret = max(ret, i - go[pos][npos] + 1);
    }

    took += mv[i];
  }


  return ret;
}

void solve () {
  stack <int> S;
  stack <int> Ss;

  int idx = 0;

  for (int i = n-1; i >= 0; --i) {
    while (!S.empty() && a[S.top()] < a[i]) S.pop();
    while (!Ss.empty() && a[Ss.top()] >= a[i]) Ss.pop();

    if (S.empty()) nxt[i] = n;
    else nxt[i] = S.top();

    if (Ss.empty()) fl[i] = n;
    else fl[i] = Ss.top();

    S.push(i);
    Ss.push(i);
  }

  solve_ans();

  for (int i = 0; i <= n; i += blokSize) {
    int best = 0;
    memset(mv, 0, sizeof mv);

    for (int j = 0; j <= n + blokSize; ++j) go[j].clear();
    for (int j = 0; j < n; ++j) queries[j].clear();

    for (int j = 0; j < q; ++j) {
      int s = (r[j] + 1)/blokSize;
      s *= blokSize;
      --s;
      if (s+1 != i) continue; 
      queries[l[j]].push_back(j);
      //[|ij]
      sol[j] = max(sol[j], solve_small(max(s + 1, l[j]), r[j]));
    }

    int nbest = -1;
    int most = 1 << 30;
    for (int j = 1; j <= i; ++j) {
      int pos = i - j;
      if (nbest == -1 || a[nbest] < a[pos]) nbest = pos;
      nextt[pos] = nxt[nbest];

      //[ij|]
      if (pos + ans[pos] > i){
	best = max(best, nbest - pos + 1);
	if (fl[pos]-1 < i + blokSize) {
	  if (nextt[pos] <= fl[pos]-1) {
	    go[fl[pos]-1].push_back(pos);
	    mv[nextt[pos]]++;
	  }
	} else if (nextt[pos] < i + blokSize) {
	  go[i + blokSize].push_back(pos);
	  mv[nextt[pos]]++;
	}
      } else best = max(best, ans[pos]);

      for (auto qIdx: queries[pos]) {
	sol[qIdx] = max(sol[qIdx], best);

	//[i|j]
	sol[qIdx] = max(sol[qIdx], solve_large(i, r[qIdx]));
      }
    }
  }
}

int main (void) {
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
  scanf("%d", &q);
  for (int i = 0; i < q; ++i) scanf("%d%d", &l[i], &r[i]);
  for (int i = 0; i < q; ++i) --l[i], --r[i];

  blokSize = sqrt(n);
  solve();

  reverse(a, a+n);
  for (int i = 0; i < q; ++i) {
    swap(l[i], r[i]);
    l[i] = n - l[i] - 1;
    r[i] = n - r[i] - 1;
  }

  solve();
  for (int i = 0; i < q; ++i) printf("%d\n", sol[i]);

  return 0;
}
