// Author:	Adrian Kuegel
// Date: 	January 16th, 2007
// Algorithm:	Dynamic Programming
// Complexity:	O(n^2)

#include <stdio.h>
#include <algorithm>
#include <assert.h>
#include <vector>
#include <map>
using namespace std;

#define INF 100000000
#define MAXN 1024

typedef vector<int> VI;
typedef pair<int,int> PII;
typedef vector<PII> VPII;

// simulates the sorting process and prints out the moves
// used specifies the numbers which keep their position
// p is the current permutation of the numbers
int simulate(char *used, VI &p) {
	int n = p.size();
	int cost = 0;
	VPII moves;

	for (int i=n-1; i>=0; i--) {
		if (used[i])
			continue;

		// find element i
		VI::iterator it = find(p.begin(),p.end(),i);
		assert(it != p.end());

		int from_pos = distance(p.begin(),it) + 1;
		p.erase(it);

		// find element i+1
		it = find(p.begin(),p.end(),i+1);

		// reinsert i before element i+1
		p.insert(it, i);

		int to_pos = distance(p.begin(),it) + 1;
		cost += from_pos + to_pos;
		moves.push_back(PII(from_pos,to_pos));
	}

	for (int i=0; i<n; i++)
		assert(p[i] == i);

	// print the result
	printf("%d\n",(int)moves.size());
	for (VPII::iterator it=moves.begin(); it!=moves.end(); ++it)
		printf("%d %d\n",it->first,it->second);
	return cost;
}

char used[MAXN+1];
int dp[MAXN+1][MAXN+1],prev[MAXN+1][MAXN+1];

void solve(VI &p) {
	int n = p.size();
	VI pos(n+1);

	p.push_back(n);
	for (int i=0; i<=n; i++)
		pos[p[i]] = i;
	for (int i=0; i<n; i++)
		dp[n][i] = INF;
	dp[n][n] = 0;

	for (int i=n-1; i>=0; --i) {
		int v = 1;

		// determine the current position v, assuming all bigger elements already moved
		// we can only make this assumption because we adjust the costs of not moving an
		// element accordingly (see below)
		for (int j=0; j<pos[i]; ++j)
			if (p[j]<i)
				++v;

		int v2 = 1;
		// move i before element i+1
		// h is the old index position where it moves to
		// v2 is the "real" position where it moves to
		for (int h=0; h<=n; h++) {
			if (p[h] < i)
				++v2;
			dp[i][h] = dp[i+1][h]+v+v2;
			prev[i][h] = h;
		}

		// try to let i at its current position
		// add specifies the additional costs for elements which are skipped
		int add = 0;
		for (int k=pos[i]+1; k<=n; k++) {
			int tcost = dp[i+1][k]+add;
			if (dp[i][pos[i]] > tcost) {
				dp[i][pos[i]] = tcost;
				prev[i][pos[i]] = k;
			}
			if (p[k]<i) {
				// there are i - p[k] elements which will be moved before it
				// since they are all bigger than p[k] they wouldn't be counted
				// when determining the current position
				add += (i-p[k]);
			}
		}
	}

	int mincost = INF,ind = -1;
	for (int i=0; i<=n; i++)
		if (dp[0][i] < mincost) {
			mincost = dp[0][i];
			ind = i;
		}
	assert(ind >= 0);

	// determine which numbers kept their position
	for (int i=0; i<n; ++i) {
		used[i] = (ind == pos[i])?1:0;
		ind = prev[i][ind];
	}
	assert(ind == n);

	used[n] = 1;
	int tcost = simulate(used,p);
	assert(tcost == mincost);
}

int main() {
	int n;
	map<int,int> byscore;

	freopen("sorting.in","r",stdin);
	freopen("sorting.out","w",stdout);
	scanf("%d",&n);
	assert(2 <= n && n <= 1000); // assert valid range for n

	for (int i=0; i<n; ++i) {
		int val;
		scanf("%d",&val);
		assert(val >= 0 && val <= 1000000); // assert valid range
		assert(byscore.find(val) == byscore.end()); // assert distinct scores
		byscore[val] = i;
	}

	int pos = 0; // position counter
	VI p(n); // desired final positions
	for (map<int,int>::reverse_iterator it=byscore.rbegin(); it!=byscore.rend(); ++it,++pos)
		p[it->second] = pos;
	solve(p);
	return 0;
}
