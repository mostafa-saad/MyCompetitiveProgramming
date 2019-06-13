#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cassert>
#include <vector>
#include <map>

using namespace std;

#define rep(i,x) for(int i = 0; i < x; i++)
typedef pair<int, int> pint;
typedef vector<pint> vpint;

bool ri_le(long long a, long long b) {
	// rt(a) <= b?
	assert(a >= 0);
	if (b < 0) return false;
	return b * b >= a;
}

bool ri_lt(long long a, long long b) {
	// rt(a) < b?
	assert(a >= 0);
	if (b <= 0) return false;
	return b * b > a;
}

bool rrr_lt(long long a, long long b, long long c) {
	// rt(a) + rt(b) < rt(c)?
	assert(a >= 0 && b >= 0 && c >= 0);
	return ri_lt(4 * a * b, c - a - b);
}

bool iri_le(long long a, long long b, long long c) {
	// a + rt(b) <= c?
	assert(b >= 0);
	return ri_le(b, c - a);
}

int sqsum(int a, int b) {
	return a * a + b * b;
}

int main() {
	int N, W, H;
	cin >> N >> W >> H;
	vpint S(N);
	
	rep(i, N) {
		cin >> S[i].first >> S[i].second;
	}
	
	int ans = 0;
	rep(a, N) rep(b, N) rep(c, N) rep(d, N) {
		if (a == b || b == c || c == d || d == a || a == c || b == d) continue;
		// A: center=a, rad=b
		// B: center=c, rad=d
		// A is in B
		int r1 = sqsum(S[a].first - S[b].first, S[a].second - S[b].second);
		int r2 = sqsum(S[c].first - S[d].first, S[c].second - S[d].second);
		int dist = sqsum(S[a].first - S[c].first, S[a].second - S[c].second);
		
		if (rrr_lt(r1, dist, r2)) {
			if (ri_le(r2, S[c].first) && iri_le(S[c].first, r2, W) && ri_le(r2, S[c].second) && iri_le(S[c].second, r2, H)) {
				ans++;
			}
		}
	}
	
	cout << ans << endl;
	
	return 0;
}
