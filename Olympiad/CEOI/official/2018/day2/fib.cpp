/*
 * Kamil Debowski
 * O(n log(n)), the intended solution.
 * Finds all changes of intervals offline and then builds a segment tree over them.
 * No BST.
 */

#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9 + 1000; // must be bigger than max(A[i]) + log(n)
const int mod = 1e9 + 7;

set<pair<int,int>> intervals; // pairs of indices (A, B) such that A,A+2,A+4,...,B are all 1's
vector<vector<pair<int,int>>> events;
int current_time;

void add_if_not_empty(int a, int b) {
	assert((b - a) % 2 == 0);
	if(a <= b) {
		assert(0 <= a && b < INF);
		events[current_time].push_back({a, b});
		intervals.insert({a, b});
	}
}

void erase(set<pair<int,int>> :: iterator it) {
	events[current_time].push_back({it -> first, it -> second});
	intervals.erase(it);
}

void add_outside(const int x) {
	auto R = intervals.upper_bound({x, INF});
	if(x + 1 == R -> first) { // just before the interval R
		// the whole interval is compressed to R->second+1
		const int new_value = R -> second + 1;
		erase(R);
		add_outside(new_value);
		return;
	}
	auto L = prev(R);
	if(L -> second + 1 == x) { // just after the interval L
		// erase the last element of L
		add_if_not_empty(L -> first, L -> second - 2);
		erase(L);
		add_outside(x + 1);
		return;
	}
	pair<int,int> new_interval{x, x};
	if(x + 2 == R -> first) {
		new_interval.second = R -> second;
		erase(R);
	}
	if(L -> second + 2 == x) {
		new_interval.first = L -> first;
		erase(L);
	}
	add_if_not_empty(new_interval.first, new_interval.second);
}

void add_possibly_inside(const int x) {
	auto it = intervals.upper_bound({x, INF});
	it--;
	if(!(it -> first <= x && x <= it -> second)) {
		add_outside(x);
		return;
	}
	// now we know that 'x' is inside the interval
	assert(0 <= it -> first && it -> second < INF);
	if(it -> first % 2 != x % 2) {
		/*
		 *   ...0001010101010100...
		 * +            1
		 * = ...0001010100000010...
		 */
		add_if_not_empty(it -> first, x - 1);
		const int new_value = it -> second + 1;
		erase(it);
		add_outside(new_value);
		return;
	}
	/*
	 *   ...0001010101010100...
	 * +           1
	 * = ...0100101011010100...
	 * = ...0100101000000010...
	 */
	const vector<int> new_values{it -> first - 2, it -> second + 1};
	add_if_not_empty(it -> first + 1, x - 1);
	erase(it);
	for(int a : new_values) {
		if(a == -2) continue; // Fib[-2] = 0
		if(a == -1) a = 0; // Fib[-1] = Fib[0]
		add_outside(a);
	}
}

struct M {
	#define REP(i) for(int i = 0; i < 2; ++i)
	int m[2][2]; // m[A][B] = m[rightmost bit can be not-changed][leftmost bit...]
	int * operator [] (int i) { return m[i]; }
	const int * operator [] (int i) const { return m[i]; }
	M() { REP(i) REP(j) m[i][j] = 0; }
	M operator * (const M & b) const {
		M r;
		REP(i) REP(j) REP(k)
			r[i][k] = (r[i][k] + (long long) m[i][j] * b[j][k]) % mod;
		return r;
	}
	#undef REP
};

struct S {
	bool exists = false;
	M m;
	int low, high;
	void init(pair<int,int> p) {
		low = p.first, high = p.second;
		int size = (high - low) / 2 + 1;
		m[0][0] = 1;
		m[0][1] = 0;
		m[1][0] = size - 1;
		m[1][1] = 1;
	}
	void merge(const S & A, const S & B) {
		exists = A.exists || B.exists;
		if(!A.exists) {
			*this = B;
			return;
		}
		if(!B.exists) {
			*this = A;
			return;
		}
		low = A.low;
		high = B.high;
		const int dist = B.low - A.high;
		//~ assert(dist >= 3);
		M mid;
		if(dist % 2 == 0) {
			mid[0][0] = 1;
			mid[1][0] = 1;
		}
		mid[0][1] = mid[1][1] = max(0, (dist - 1) / 2);
		mid[1][1] = (mid[1][1] + 1) % mod;
		m = (B.m * mid) * A.m;
	}
};

int main() {
	int n;
	scanf("%d", &n);
	events.resize(n);
	intervals.insert({-4, -4});
	intervals.insert({INF, INF}); // to simplify the implementation
	for(current_time = 0; current_time < n; ++current_time) {
		int ai;
		scanf("%d", &ai);
		--ai;
		add_possibly_inside(ai);
	}
	
	vector<pair<int,int>> all;
	for(const vector<pair<int,int>> & vec : events)
		for(const pair<int,int> & p : vec)
			all.push_back(p);
	sort(all.begin(), all.end());
	all.resize(unique(all.begin(),all.end()) - all.begin());
	
	int pot = 1;
	while(pot < (int) all.size()) pot *= 2;
	vector<S> tr(2 * pot);
	for(int i = 0; i < (int) all.size(); ++i)
		tr[pot+i].init(all[i]);
	S START;
	START.init({-1, -1});
	START.exists = true;
	for(current_time = 0; current_time < n; ++current_time) {
		for(pair<int,int> p : events[current_time]) {
			int i = lower_bound(all.begin(), all.end(), p) - all.begin();
			tr[pot+i].exists = !tr[pot+i].exists;
			for(int x = (pot + i) / 2; x >= 1; x /= 2)
				tr[x].merge(tr[2*x], tr[2*x+1]);
		}
		S total;
		total.merge(START, tr[1]);
		printf("%d\n", total.m[1][1]);
	}
}
