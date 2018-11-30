#include <iostream>
#include <vector>
#include <algorithm>
#include <array>

using namespace std;
typedef long long int Z;

Z T, P;
Z xm, ym;
Z tx[5050];
Z ty[5050];
Z tr[5050];

Z par[5050];

Z find(Z x) {
	if(par[par[x]] != par[x]) {
		par[x] = find(par[x]);
	}
	return par[x];
}

void merge(Z a, Z b) {
	a = find(a);
	b = find(b);
	par[a] = b;
}

// Trees T, T + 1, T + 2, T + 3 are the bottom, right, top and left borders.
bool overlap(Z time, Z tree1, Z tree2) {
	if(tree1 >= T) {
		if(tree2 >= T) {
			return false;
		} else {
			if(tree1 == T    ) return ty[tree2] - tr[tree2] - time < time;
			if(tree1 == T + 1) return tx[tree2] + tr[tree2] + time > xm - time;
			if(tree1 == T + 2) return ty[tree2] + tr[tree2] + time > ym - time;
			if(tree1 == T + 3) return tx[tree2] - tr[tree2] - time < time;
			throw 5;
			return false;
		}
	} else {
		if(tree2 >= T) {
			return overlap(time, tree2, tree1);
		} else {
			Z dx = tx[tree1] - tx[tree2];
			Z dy = ty[tree1] - ty[tree2];
			Z dist2 = dx * dx + dy * dy;
			Z maxdist2 = tr[tree1] + tr[tree2] + 2 * time;
			maxdist2 *= maxdist2;
			return dist2 < maxdist2;
		}
	}
}

int main() {
	for(Z i = 0; i < 5050; ++i) par[i] = i;
	
	cin.sync_with_stdio(false);
	cin.tie(nullptr);
	
	cin >> T >> P;
	cin >> xm >> ym;
	
	for(Z t = 0; t < T; ++t) {
		cin >> tx[t] >> ty[t] >> tr[t];
	}
	
	// ((radius, corner), order)
	vector<pair<pair<Z, Z>, Z>> Q(P);
	for(Z p = 0; p < P; ++p) {
		cin >> Q[p].first.first >> Q[p].first.second;
		--Q[p].first.second;
		Q[p].second = p;
	}
	sort(Q.begin(), Q.end());
	
	// (time, (tree1, tree2))
	vector<pair<Z, pair<Z, Z>>> events;
	for(Z i = 0; i < T + 4; ++i) {
		for(Z j = i + 1; j < T + 4; ++j) {
			Z A = 0;
			Z B = xm + ym + 5;
			while(A != B) {
				Z M = (A + B) / 2;
				if(overlap(M, i, j)) {
					B = M;
				} else {
					A = M + 1;
				}
			}
			events.emplace_back(A, make_pair(i, j));
		}
	}
	sort(events.begin(), events.end());
	
	vector<array<bool, 4>> res(P);
	Z evi = 0;
	for(auto q : Q) {
		while(evi != (Z)events.size() && events[evi].first <= q.first.first) {
			merge(events[evi].second.first, events[evi].second.second);
			++evi;
		}
		Z c = q.first.second;
		array<bool, 4>& r = res[q.second];
		auto conn = [c](Z a, Z b) {
			return find(T + (c + a) % 4) == find(T + (c + b) % 4);
		};
		r[c] = true;
		if(!conn(0, 1) && !conn(0, 2) && !conn(0, 3)) r[(c + 1) % 4] = true;
		if(!conn(0, 2) && !conn(0, 3) && !conn(1, 2) && !conn(1, 3)) r[(c + 2) % 4] = true;
		if(!conn(3, 0) && !conn(3, 1) && !conn(3, 2)) r[(c + 3) % 4] = true;
	}
	for(array<bool, 4> r : res) {
		for(Z i = 0; i < 4; ++i) {
			if(r[i]) {
				cout << i + 1;
			}
		}
		cout << '\n';
	}
	
	return 0;
}
