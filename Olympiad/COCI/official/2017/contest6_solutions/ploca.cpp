#include <cstdio>
#include <cstring>
#include <cassert>
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

#define num first
#define val second
#define FOR(i, a, b) for (int i = (a); i < (b); ++i)
#define REP(i, n) FOR (i, 0, n)
#define _ << " _ " <<
#define TRACE(x) cerr << #x << " = " << x << endl
#define debug(...) fprintf(stderr, __VA_ARGS__)
//#define debug
//#define TRACE(x)

using namespace std;
using llint = long long;
using vec = vector<int>;
using pii = pair<int, int>;

const int MAX = 1000000;
const int MAXK = 10010;
const int MAXC = 305;
const int MAXD = 6500;
const int MAXM = 55;
const int MAXLEN = 23;
const int INF = 1e9;

struct edge {
  int div, v, w;
};

struct line {
  llint k, l;
};

vector<pii> happy;
vec primes, s;
int dist[MAXC][MAXLEN], divs[MAXC], f[MAXK], K, hap[MAX + 10], price[MAX + 10];
vector<edge> edg[MAXC];

inline int get(int i) { return (i > K) ? 0 : f[i]; }

inline void add_edge(int a, int div, int b, int w) {
  edg[a].push_back({div, b, w});
  if (b == 0 && a != 0) 
    dist[a][1] = min(dist[a][1], w);
}

inline int index(int x) {
  return (int)(lower_bound(s.begin(), s.end(), x) - s.begin());
}

int compress(int n) {
  vec e;
  for (int p : primes) {
    if (p * p > n) break;
    if (n % p > 0) continue;
    int ec = 0;
    while (n % p == 0) {
      n /= p;
      ++ec;
    }
    e.push_back(ec);
  }
  if (n > 1)
    e.push_back(1);
  
  sort(e.begin(), e.end());
  reverse(e.begin(), e.end());
  
  int ret = 1;
  for (int i = 0; i < (int)e.size(); ++i)
    for (int j = 0; j < e[i]; ++j)
      ret *= primes[i];
  return ret;
}

int divisors(int n) {
  int ret = 0;
  for (int m = 1; m * m <= n; ++m)
    if (n % m == 0) {
      ++ret;
      if (m * m != n)
	++ret;
    }
  return ret;
}

bool isprime(int p) {
  for (int q = 2; q * q <= p; ++q)
    if (p % q == 0)
      return false;
  return true;
}

void gen(llint m, int i, int prv) {
  s.push_back((int)m);

  for (int x = 1; x <= prv; ++x) {
    m *= primes[i];
    if (m > MAX) break;
    gen(m, i + 1, x);
  }
}

//llint best[MAXC][MAXC][MAXM][MAXM];
llint bl[MAXD][MAXM][MAXLEN];
llint bl2[MAXD][MAXM][MAXLEN];
int idx[MAXC][MAXC];
vector<int> lens;

int sz;
line st[MAXM * MAXLEN];

double getx(line l1, line l2) {
  return (l2.l - l1.l) / (double)(l1.k - l2.k);
}

void insert(line l) {
  while (sz >= 1 && st[sz - 1].k == l.k) {
    if (st[sz - 1].l > l.l)
      --sz;
    else
      return;
  }

  while (sz >= 2 && getx(st[sz - 1], l) < getx(st[sz - 1], st[sz - 2]))
    --sz;

  st[sz++] = l;
}

void preprocess_fast() {
  int tot = 0;
  REP(x, (int)s.size()) 
    REP(y, (int)s.size()) {
      if ((llint)s[x] * s[y] > MAX) continue;
      idx[x][y] = tot++;
  }

  REP(x, (int)s.size()) {
    REP(y, (int)s.size()) {
      if ((llint)s[x] * s[y] > MAX) continue;
      for (int i = 0; i < (int)happy.size(); ++i) {
	  REP(len, MAXLEN) bl[idx[x][y]][i][len] = INF;
	  REP(len1, MAXLEN) {
	    REP(len2, MAXLEN - len1) {
	      if (dist[x][len1] != INF && dist[y][len2] != INF) {
		llint tmp = 0;
		tmp += dist[x][len1];
		tmp += dist[y][len2];
		tmp += (llint)(-len1 - len2) * happy[i].val;
		bl[idx[x][y]][i][len1 + len2] =
		  min(bl[idx[x][y]][i][len1 + len2], tmp);
	      }
	    }
	    bl2[idx[x][y]][i][0] = bl[idx[x][y]][i][0];
	    FOR(len, 1, MAXLEN)
	      bl2[idx[x][y]][i][len] =
	      min(bl2[idx[x][y]][i][len - 1], bl[idx[x][y]][i][len]);
	  }
      }
    }
  }
}

llint solve_fast2(int a, int b) {
  llint sol = 0;
  sz = 0;
  int ptr = 0;
  
  for (int j = 0; j < (int)happy.size(); ++j) {
    int c = happy[j].num;
    if (a % c != 0 || c % b != 0) continue;
    int x = index(compress(a / c));
    int y = index(compress(c / b));

    insert({happy[j].val, bl2[idx[x][y]][j][MAXLEN - 1]});
  }

  for (int i = 0; i < (int)lens.size(); ++i) {
    llint ret = INF;
    if (lens[i] < MAXLEN) {
      ret = dist[index(compress(a / b))][lens[i]];
      for (int j = 0; j < (int)happy.size(); ++j) {
	int c = happy[j].num;
	if (a % c != 0 || c % b != 0) continue;
	int x = index(compress(a / c));
	int y = index(compress(c / b));
	ret = min(ret, bl2[idx[x][y]][j][lens[i]] + (llint)lens[i] * happy[j].val);
      }
    } else {
      for (; ptr + 1 < sz && getx(st[ptr], st[ptr + 1]) < lens[i]; ++ptr);
      if (sz > 0) 
      	ret = min(ret, st[ptr].k * (llint)lens[i] + st[ptr].l);
    }
    if (ret == INF) ret = -1;
    sol += (a % b != 0) ? -1 : ret;
  }
  return sol;
}

bool cmp2(pii a, pii b) { return a.second > b.second; }

void init() {
  int M, L;
  scanf("%d",&K);
  FOR(i, 1, K + 1) scanf("%d",&f[i]);
  scanf("%d",&L);
  lens.resize(L);
  REP(i, L) scanf("%d",&lens[i]);
  sort(lens.begin(), lens.end());
  
  scanf("%d",&M);
  REP(i, M) {
    int x, cost;
    scanf("%d %d",&x,&cost);
    happy.push_back({x, cost});
    hap[x] = 1;
    price[x] = cost;
  }
  sort(happy.begin(), happy.end(), cmp2);
}

int main(void) {
  REP(a, MAXC) REP(len, MAXLEN) dist[a][len] = INF;
  dist[0][0] = 0;
  init();

  for (int p = 2; p * p <= MAX; ++p)
    if (isprime(p))
      primes.push_back(p);

  gen(1, 0, MAX);
  sort(s.begin(), s.end());
  
  REP(i, (int)s.size()) 
    divs[i] = divisors(s[i]);

  // TRACE((int)s.size());
  // TRACE((int)primes.size());

  for (int i = 0; i < (int)s.size(); ++i) {
    int a = s[i];
    for (int x = 1; x * x <= a; ++x)
      if (a % x == 0) {
	int j = index(compress(x));
	int k = index(compress(a / x));
	add_edge(i, x, j, get(divs[k]));
	if (x * x != a) 
	  add_edge(i, a / x, k, get(divs[j]));
      }
  }

  for (int len = 2; len < MAXLEN; ++len) 
    for (int x = 0; x < MAXC; ++x) 
      for (auto y : edg[x])
	if (y.v != x)
	  dist[x][len] = min(dist[x][len], dist[y.v][len - 1] + y.w);
  
  preprocess_fast();
  
  int q, A, B;
  scanf("%d",&q);
  
  REP(it, q) {
    scanf("%d %d",&A,&B);
    printf("%lld\n",solve_fast2(A,B));
  }
  
  return 0;
}
