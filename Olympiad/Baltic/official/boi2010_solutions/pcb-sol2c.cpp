// BOI 2010, day 1
// Task: PCB
// Solution: Swedish team leaders

// Efficient solution that reduces the problem to finding the longest
// decreasing subsequence and then solves the latter in O(N log N)
// using C++ standard containers

#include <fstream>
#include <set>
#include <vector>
using namespace std;

#define rep(i, n) for (int i = 0; i < (int)(n); ++i)

int main() {
	ifstream cin("pcb.in");
	ofstream cout("pcb.out");
	int a, b, N;
	cin >> N;

	vector< pair<int, int> > V;
	rep(i, N) {
		cin >> a >> b;
		V.push_back( make_pair(a, b) );
	}
	sort( V.begin(), V.end() );

	set<int, greater<int> > S;
	rep(i, N) {
		int x = V[i].second;
		typeof(S.begin()) it = S.upper_bound(x);
		if ( it != S.end() ) S.erase( it );
		S.insert(x);
	}
	cout << S.size() << endl;

	return 0;
};
