#include <cstdio>
#include <cstdlib>
#include <set>
#include <functional>
#include <algorithm>

using namespace std;

typedef long long Int;

const int MAXN = 500050;
const Int INFLL = 1001001001001001001LL;

template<typename T> void chmin(T& a, T b) { if (a > b) a = b; }
template<typename T> void chmax(T& a, T b) { if (a < b) a = b; }
int in() { int x; scanf("%d", &x); return x; }
Int lin() { Int x; scanf("%lld", &x); return x; }

struct CHT {
  typedef pair<Int, Int> line;
  struct comp {
    bool operator() (const line& a, const line& b) {
      return a.first != b.first ? a.first > b.first : a.second < b.second;
    }
  };
  set<line, comp> lines;

  CHT() {
    lines.emplace(INFLL, INFLL);
    lines.emplace(0, INFLL + 1);
  }

  template<typename T> T prev(T it) { --it; return it; }
  template<typename T> T next(T it) { ++it; return it; }

  bool compare(Int a, Int b, Int c, Int d) {  // ab >= cd?
    bool neg1 = (a < 0) ^ (b < 0), neg2 = (c < 0) ^ (d < 0);
    if (neg1 ^ neg2) return neg2;
    if (neg1 && neg2) return compare(abs(c), abs(d), abs(a), abs(b));
    if (a < 0) return compare(-a, -b, -c, -d);
    if (b == 0 || d == 0) return d == 0;
    if (a / d != c / b) return a / d > c / b;
    if (c % b == 0 || a % d == 0) return c % b == 0;
    return compare(b, a % d, d, c % b);
  }

  bool check(line l1, line l2, line l3) {
    return compare(l2.first - l1.first, l3.second - l2.second, l2.second - l1.second, l3.first - l2.first);
  }

  void add(Int a, Int b) {
    line l(a, b);
    auto it = lines.insert(l).first;
    if (check(*prev(it), *it, *next(it))) {
      lines.erase(it);
      return;
    }

    for (--it; it != lines.begin() && check(*prev(it), *it, l); --it) { }
    lines.erase(++it, lines.find(l));

    if (next(lines.find(l)) == lines.end()) {
      return;
    }

    for (it = next(lines.find(l)); next(it) != lines.end() && check(l, *it, *next(it)); ++it) { }
    lines.erase(next(lines.find(l)), it);
  }

  Int value(const line& l, Int x) {
    return l.second >= INFLL ? INFLL : l.first * x + l.second;
  }

  Int query(Int x) {
    lines.erase(lines.begin());
    auto it = lines.begin();
    Int res = value(*it++, x);
    while (it != lines.end()) {
      Int v = value(*it, x);
      if (res > v) {
        res = v;
        lines.erase(lines.begin());
        it = next(lines.begin());
      } else {
        break;
      }
    }
    lines.emplace(INFLL, INFLL);
    return res;
  }
};

Int X, T, W, S[MAXN], dp[MAXN], C[MAXN];
int N, M;

Int off(Int s) {
  return s % T;
}

struct passenger {
  int d, c;
  Int cnt;
} P[MAXN];

int main() {
  X = lin();
  N = in();
  M = in();
  W = lin();
  T = lin();
  for (int i = 0; i < N; ++i) {
    S[i] = lin();
  }
  S[N++] = X;
  for (int i = 1; i <= M; ++i) {
    P[i].d = in();
    P[i].c = in();
    P[i].cnt = X / T + (P[i].d < X % T ? 1 : 0);
  }

  sort(P + 1, P + M + 1, [] (const passenger& a, const passenger& b) {
    return a.d > b.d;
  });
  sort(S, S + N, [] (const Int a, const Int b) {
    return off(a) < off(b);
  });

  C[0] = 0;
  for (int i = 1; i <= M; ++i) {
    C[i] = C[i - 1] + P[i].c;
  }

  CHT cht;
  int last = N;
  Int empty = 0;
  P[0].d = T + 1;
  for (int i = 1; i <= M; ++i) {
    Int min1 = min(empty, (i == 1 ? INFLL : cht.query(i - 1) + C[i - 1]));
    empty = min1 + W * P[i].cnt;
    for (int j = last - 1; j >= 0 && off(S[j]) >= P[i].d; --j) {
      Int b = min1;
      cht.add(W * (S[j] / T), b - W * (S[j] / T) * (i - 1) - C[i - 1]);
      last = j;
    }
  }

  printf("%lld\n", min(empty, cht.query(M) + C[M]) + W * (X / T + (X % T ? 1 : 0)));

  return 0;
}
