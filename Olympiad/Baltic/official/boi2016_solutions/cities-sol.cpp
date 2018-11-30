#include <iostream>
#include <climits>
#include <queue>

using namespace std;
typedef long long int Z;

int n, k, m;
vector<int> imp;
vector<vector<pair<int, Z>>> G;
Z d[32][202020];
Z huge = LLONG_MAX / 3;
bool seen[202020];

int main() {
	cin.sync_with_stdio(false);
	
	cin >> n >> k >> m;
	imp.resize(k);
	for(int i = 0; i < k; ++i) {
		cin >> imp[i];
		--imp[i];
	}
	
	G.resize(n);
	for(int i = 0; i < m; ++i) {
		int a, b;
		Z c;
		cin >> a >> b >> c;
		--a;
		--b;
		G[a].emplace_back(b, c);
		G[b].emplace_back(a, c);
	}
	
	fill((Z*)d, (Z*)d + 32 * 202020, huge);
	
	for(int i = 0; i < k; ++i) {
		d[1 << i][imp[i]] = 0;
	}
	
	priority_queue<pair<Z, int>> Q;
	for(int c = 1; c < (1 << k); ++c) {
		for(int a = 0; a < c; ++a) {
			if((a | c) != c) continue;
			int b = c ^ a;
			if(b > a) continue;
			for(int v = 0; v < n; ++v) {
				d[c][v] = min(d[c][v], d[a][v] + d[b][v]);
			}
		}
		fill(seen, seen + n, false);
		for(int v = 0; v < n; ++v) {
			if(d[c][v] == huge) continue;
			Q.emplace(-d[c][v], v);
		}
		
		while(!Q.empty()) {
			Z cost = -Q.top().first;
			int v = Q.top().second;
			Q.pop();
			if(seen[v]) continue;
			seen[v] = true;
			for(auto edge : G[v]) {
				Z ec = cost + edge.second;
				if(ec < d[c][edge.first]) {
					d[c][edge.first] = ec;
					Q.emplace(-ec, edge.first);
				}
			}
		}
	}
	
	Z res = huge;
	for(int v = 0; v < n; ++v) {
		res = min(res, d[(1 << k) - 1][v]);
	}
	cout << res << '\n';
	
	return 0;
}
