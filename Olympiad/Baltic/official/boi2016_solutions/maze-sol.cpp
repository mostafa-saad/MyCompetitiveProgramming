// note: slow and uses lots of memory for big cases

#include <iostream>
#include <array>
#include <map>
#include <algorithm>
#include <cassert>
#include <tuple>
#include <cassert>
#include <sstream>

using namespace std;

constexpr int maxM = 13;
constexpr int maxN = 20;
int n, m, k;

struct Conf {
	Conf() : leaves(0), compCount(0), started(false) {
		fill(deg.begin(), deg.begin() + m, -1);
	}
	
	int leaves;
	int compCount;
	bool started;
	array<char, maxM> deg;
	array<short, maxM / 2 + 1> comps;
	
	int compContaining(int j) {
		for(int i = 0; i < compCount; ++i) {
			if(comps[i] & (1 << j)) return i;
		}
		return -1;
	}
	
	bool chooseEmpty(int j) {
		if(deg[j] == 0 || deg[j] == 1) {
			++leaves;
		}
		deg[j] = -1;
		
		for(int i = 0; i < compCount; ++i) {
			short& comp = comps[i];
			if(comp & (1 << j)) {
				if(comp == (1 << j) && compCount != 1) {
					return false;
				}
				comp &= ~(1 << j);
			}
		}
		
		normalize();
		return true;
	}
	bool chooseFill(int j) {
		if(!compCount && started) return false;
		
		if(deg[j] == -1) {
			comps[compCount++] = 1 << j;
		}
		
		started = true;
		if(deg[j] == 0) {
			++leaves;
		}
		deg[j] = deg[j] == -1 ? 0 : 1;
		if(j && deg[j - 1] != -1) {
			++deg[j - 1];
			++deg[j];
		}
		
		if(j) {
			int lComp = compContaining(j - 1);
			if(lComp != -1) {
				int jComp = compContaining(j);
				if(lComp != jComp) {
					comps[jComp] |= comps[lComp];
					swap(comps[lComp], comps[compCount - 1]);
					--compCount;
				} else {
					return false;
				}
			}
		}
		
		normalize();
		return true;
	}
	void normalize() {
		sort(comps.begin(), comps.begin() + compCount, greater<int>());
		while(compCount && comps[compCount - 1] == 0) {
			--compCount;
		}
	}
};
bool operator<(const Conf& a, const Conf& b) {
	if(a.started != b.started) return (int)a.started < (int)b.started;
	if(a.leaves != b.leaves) return a.leaves < b.leaves;
	if(a.compCount != b.compCount) return a.compCount < b.compCount;
	for(int i = 0; i < m; ++i) {
		if(a.deg[i] != b.deg[i]) return a.deg[i] < b.deg[i];
	}
	for(int i = 0; i < a.compCount; ++i) {
		if(a.comps[i] != b.comps[i]) return a.comps[i] < b.comps[i];
	}
	return false;
}
bool operator==(const Conf& a, const Conf& b) {
	if(a.started != b.started) return false;
	if(a.leaves != b.leaves) return false;
	if(a.compCount != b.compCount) return false;
	for(int i = 0; i < m; ++i) {
		if(a.deg[i] != b.deg[i]) return false;
	}
	for(int i = 0; i < a.compCount; ++i) {
		if(a.comps[i] != b.comps[i]) return false;
	}
	return true;
}

struct Res {
	Res() : cells(-1), res() { }
	Res(bool fill, int p, const Res& prev) : cells(prev.cells + (int)fill), res(prev.res) {
		if(fill) {
			res[p >> 6] |= (uint64_t)1 << (p & 63);
		}
	}
	
	int cells;
	array<uint64_t, ((maxN * maxM + 63) >> 6)> res;
};
bool operator<(const Res& a, const Res& b) {
	return a.cells > b.cells;
}

int main(int argc, char* argv[]) {
	vector<pair<Conf, Res>> M;
	size_t reserve = 0;
	if(argc >= 2) {
		size_t sz;
		stringstream ss(argv[1]);
		ss >> sz;
		sz *= 1024;
		sz *= 1024;
		sz /= sizeof(pair<Conf, Res>);
		reserve = sz;
	}
	
	int t;
	cin >> t;
	while(t) {
		--t;
		cin >> n >> m >> k;
		bool transpose = false;
		if(m > n) {
			swap(n, m);
			transpose = true;
		}
		++k;
		assert(m <= maxM);
		assert(n <= maxN);
		
		M.clear();
		M.reserve(reserve);
		Res initRes;
		initRes.cells = 0;
		M.emplace_back(Conf(), initRes);
		
		int p = 0;
		for(int i = 0; i < n; ++i) {
			for(int j = 0; j < m; ++j) {
				int sz = M.size();
				int writei = 0;
				for(int readi = 0; readi < sz; ++readi) {
					const Conf& baseConf = M[readi].first;
					const Res& baseRes = M[readi].second;
					{
						Conf conf = baseConf;
						if(conf.chooseEmpty(j) && conf.leaves <= k) {
							if(writei < readi) {
								M[writei++] = make_pair(conf, Res(false, p, baseRes));
							} else {
								M.emplace_back(conf, Res(false, p, baseRes));
							}
						}
					}
					{
						Conf conf = baseConf;
						if(conf.chooseFill(j) && conf.leaves <= k) {
							if(writei < readi) {
								M[writei++] = make_pair(conf, Res(true, p, baseRes));
							} else {
								M.emplace_back(conf, Res(true, p, baseRes));
							}
						}
					}
				}
				while((int)M.size() != sz && writei < sz) {
					M[writei++] = move(M.back());
					M.pop_back();
				}
				if((int)M.size() == sz) M.resize(writei);
				sort(M.begin(), M.end());
				M.erase(unique(M.begin(), M.end(), [](const pair<Conf, Res>& a, const pair<Conf, Res>& b) { return a.first == b.first; }), M.end());
				++p;
			}
		}
		
		int best = -1;
		const Res* bestres = nullptr;
		int bestLeafCount = 0;
		for(const pair<Conf, Res>& end : M) {
			Conf conf = end.first;
			bool ok = true;
			for(int j = 0; j < m; ++j) {
				ok = ok && conf.chooseEmpty(j);
			}
			if(!ok) continue;
			if(conf.leaves <= k) {
				const Res& res = end.second;
				if(res.cells > best) {
					best = res.cells;
					bestres = &res;
					bestLeafCount = conf.leaves;
				}
			}
		}
		
		assert(best != -1);
		const Res& res = *bestres;
		vector<vector<char>> X(n);
		p = 0;
		for(int i = 0; i < n; ++i) {
			X[i].resize(m);
			for(int j = 0; j < m; ++j) {
				X[i][j] = ((res.res[p >> 6] >> (p & 63)) & 1) ? '.' : '#';
				++p;
			}
		}
		
		int leavesFound = 0;
		for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(X[i][j] == '#') continue;
			int cnt = 0;
			auto neigh = [&](int i2, int j2) {
				if(i2 == -1 || j2 == -1 || i2 == n || j2 == m) return;
				if(X[i2][j2] != '#') ++cnt;
			};
			neigh(i + 1, j);
			neigh(i - 1, j);
			neigh(i, j + 1);
			neigh(i, j - 1);
			if(cnt <= 1) {
				X[i][j] = leavesFound ? 'o' : 'x';
				++leavesFound;
			}
		}
		}
		assert(leavesFound == bestLeafCount);
		for(int i = 0; i < n; ++i) {
		for(int j = 0; j < m; ++j) {
			if(X[i][j] == '.' && leavesFound != k) {
				++leavesFound;
				X[i][j] = 'o';
			}
		}
		}
		if(leavesFound != k) {
			cout << "QAQ\n\n";
		} else {
			//cerr << "Difficulty: " << 2 * (best - 1) << '\n';
			if(transpose) {
				for(int j = 0; j < m; ++j) {
					for(int i = 0; i < n; ++i) {
						cout << X[i][j];
					}
					cout << '\n';
				}
				cout << '\n';
			} else {
				for(int i = 0; i < n; ++i) {
					for(int j = 0; j < m; ++j) {
						cout << X[i][j];
					}
					cout << '\n';
				}
				cout << '\n';
			}
		}
	}
	
	return 0;
}
