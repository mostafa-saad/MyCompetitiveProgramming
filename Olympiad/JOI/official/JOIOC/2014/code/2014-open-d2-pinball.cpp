#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

#define rep(i,n) for(int i = 0; i < (n); i++)
#define mp make_pair
#define pb push_back
#define all(x) (x).begin(), (x).end()
#define pr(x) cout << #x << " = " << x << endl

typedef long long llint;
typedef vector<int> vint;
typedef vector<llint> vllint;

const llint INFLL = 1001001001001001001ll;

int in() {
	int a;
	scanf("%d", &a);
	return a;
}

int M, N;
vint coords;

int c2i(int x) {
	vint::iterator iter = lower_bound(all(coords), x);
	if (*iter == x) {
		return iter - coords.begin();
	}
	
	cerr << "Fatal error: compression failed." << endl;
	exit(-1);
	return -1;
}

struct Device {
	int a, b, c;
	llint d;
	void compress() {
		a = c2i(a);
		b = c2i(b);
		c = c2i(c);
	}
} dev[100010];

struct RMQ {
	int n;
	vllint data;
	
	RMQ(int n)
		: n(n), data(n * 2) {
		rep(i, n * 2) data[i] = INFLL;
	}
	
	llint query(int a, int b, int k, int l, int r) {
		if (b <= l || r <= a) return INFLL;
		if (a <= l && r <= b) return data[k];
		return min(query(a, b, k * 2 + 1, l, (l + r) / 2), query(a, b, k * 2 + 2, (l + r) / 2, r));
	}
	
	void update(int i, llint x) {
		i += n - 1;
		data[i] = x;
		while (i > 0) {
			i = (i - 1) / 2;
			data[i] = min(data[i * 2 + 1], data[i * 2 + 2]);
		}
	}
	
	llint value(int i) {
		return data[i + n - 1];
	}
	
	bool chmin(int i, llint x) {
		if (x < value(i)) {
			update(i, x);
			return true;
		}
		else {
			return false;
		}
	}
};

int main() {
	M = in();
	N = in();
	rep(i,M) {
		dev[i].a = in() - 1;
		dev[i].b = in();
		dev[i].c = in() - 1;
		dev[i].d = in();
		
		coords.pb(dev[i].a);
		coords.pb(dev[i].b);
		coords.pb(dev[i].c);
	};
	
	coords.pb(0);
	coords.pb(N);
	sort(all(coords));
	coords.erase(unique(all(coords)), coords.end());
	N = coords.size();
	rep(i,M) dev[i].compress();
	
	int n = 1;
	while(n < N) n *= 2;
	RMQ lq(n), rq(n);
	
	llint ans = INFLL;
	
	rep(i,M) {
		llint costl = (dev[i].a == 0 ? 0 : lq.query(dev[i].a, dev[i].b, 0, 0, n)) + dev[i].d;
		llint costr = (dev[i].b == N - 1 ? 0 : rq.query(dev[i].a, dev[i].b, 0, 0, n)) + dev[i].d;
		
		lq.chmin(dev[i].c, costl);
		rq.chmin(dev[i].c, costr);
		
		llint cost = costl + costr - dev[i].d;
		if (cost < ans) ans = cost;
	}
	
	cout << (ans == INFLL ? -1 : ans) << endl;
	return 0;
}
