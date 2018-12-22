#include <iostream>
#include <vector>
using namespace std;

#define x first
#define y second

typedef pair<int, int> pii;
typedef long long ll;

const int MAXN = 100100;

int n, q, arr[MAXN];

int gcd(int a, int b) {
  while (b) a %= b, swap(a, b);
  return a;
}

struct Tournament {
  struct Node {
    vector<pii> l, r;
    ll cnt;

    // pii u vectoru oznacava
    // - first  - duljina prefiksa/sufiksa
    // - second - gcd tog prefiksa/sufiksa
    // uvijek je l[0] = r[0] = {0, 0}

    Node() : cnt(0) {}

    Node(int val) {
      l = r = {{0, 0}, {1, val}};
      cnt = (val != 1) ? 1 : 0;
    }

    static void expand(vector<pii> &ret, const vector<pii> &add) {
      int sz_init = ret.back().x;
      for (auto it : add) {
        int sz = sz_init + it.x;
        if (it.y % ret.back().y == 0) ret.back().x = sz;
        else ret.push_back({sz, gcd(it.y, ret.back().y)});
      }
    }

    friend Node operator+(const Node &a, const Node &b) {
      if (a.l.empty()) return b;
      if (b.l.empty()) return a;

      Node ret;
      ret.l = a.l;
      ret.r = b.r;
      expand(ret.l, b.l);
      expand(ret.r, a.r);
      ret.cnt = a.cnt + b.cnt;
      int rt = (int)b.l.size() - 1;
      for (int lt = 1; lt < (int)a.r.size(); ++lt) {
        while (rt > 0 && gcd(a.r[lt].y, b.l[rt].y) == 1)
          --rt;
        ret.cnt += (ll)(a.r[lt].x - a.r[lt - 1].x) * b.l[rt].x;
      }
      return ret;
    }
  };

  static const int off = 1 << 17;
  Node data[2 * off];
  int from, to;

  void update(int pos, int val) {
    pos += off;
    data[pos] = Node(val);
    for (pos /= 2; pos > 0; pos /= 2)
      data[pos] = data[2 * pos] + data[2 * pos + 1];
  }

  Node query(int nd, int lo, int hi) {
    if (lo >= to || hi <= from) return Node();
    if (lo >= from && hi <= to) return data[nd];
    int mid = (lo + hi) / 2;
    return query(2 * nd, lo, mid) + query(2 * nd + 1, mid, hi);
  }

  ll query(int l, int r) {
    from = l, to = r;
    return query(1, 0, off).cnt;
  }

  void build() {
    for (int i = 0; i < n; ++i)
      data[i + off] = Node(arr[i]);
    for (int i = off - 1; i > 0; --i)
      data[i] = data[2 * i] + data[2 * i + 1];
  }
} T;

int main() {
  cin >> n >> q;
  for (int i = 0; i < n; ++i)
    cin >> arr[i];

  T.build();

  for (int i = 0; i < q; ++i) {
    int cmd, a, b;
    cin >> cmd >> a >> b;
    if (cmd == 1) T.update(a - 1, b);
    else cout << T.query(a-1, b) << endl;
  }
  return 0;
}
