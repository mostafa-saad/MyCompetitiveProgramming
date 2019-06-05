#include "collapse.h"
#include <utility>
#include <algorithm>
#include <set>
#include <iostream>
#include <memory>

template<typename T> using vector = std::vector<T>;
template<typename T> using set = std::set<T>;
template<typename T, typename S> using pair = std::pair<T, S>;
using std::make_pair;
using Paths = vector<pair<int, int>>;

const int Bucket = 1000;

class UnionFind {
private:
	vector<int> parent;
	vector<int> rank;
	bool need_change;
	vector<int> change;
public:
	UnionFind(int n, bool need_change_ = false) : parent(n), rank(n, 0), need_change(need_change_) {
		for(int i = 0; i < n; i++) parent[i] = i;
	}
	int findParent(int x) {
		if(parent[x] == x) return x;
		return parent[x] = findParent(parent[x]);
	}
	bool unionGroup(int x, int y) {
		int xp = findParent(x);
		int yp = findParent(y);
		if(xp == yp) {
			return false;
		}
		else {
			if(need_change) {
				change.push_back(xp);
				change.push_back(yp);
			}
			if(rank[xp] > rank[yp]) {
				parent[yp] = xp;
			}
			else if(rank[xp] < rank[yp]) {
				parent[xp] = yp;
			}
			else {
				parent[yp] = xp;
				rank[xp]++;
			}
			return true;
		}
	}
	void reset() {
		for(auto i : change) {
			parent[i] = i;
			rank[i] = 0;
		}
		change.clear();
	}
};

vector<pair<int, int>> solve(
	int n,
	Paths fixed,
	vector<pair<int, pair<int, std::shared_ptr<Paths>>>> query
) {
	auto comp_second = [](const pair<int, int>& a, const pair<int, int>& b){ return a.second < b.second; };
	auto comp_first_only = [](const pair<int, pair<int, std::shared_ptr<Paths>>>& a, const pair<int, pair<int, std::shared_ptr<Paths>>>& b){ return a.first < b.first; };
	sort(fixed.begin(), fixed.end(), comp_second);
	sort(query.begin(), query.end(), comp_first_only);
	vector<pair<int, int>> ret;
	UnionFind large(n), tmp(n, true);
	int now = 0;
	int count = 0;
	for(auto i : query) {
		while(now < (int)fixed.size() && fixed[now].second <= i.first) {
			if(large.unionGroup(fixed[now].first, fixed[now].second)) count++;
			now++;
		}
		int c = count;
		for(auto j : *i.second.second)
			if(j.second <= i.first && tmp.unionGroup(large.findParent(j.first), large.findParent(j.second))) c++;
		ret.push_back(make_pair(i.second.first, i.first + 1 - c));
		tmp.reset();
	}
	return ret;
}

pair<int, int> minMaxPair(int a, int b) {
	return make_pair(std::min(a, b), std::max(a, b));
}

pair<int, int> revPath(int n, pair<int, int> p) {
	return make_pair(n - 1 - p.second, n - 1 - p.first);
}

vector<int> simulateCollapse(
	int N,
	vector<int> T,
	vector<int> X,
	vector<int> Y,
	vector<int> W,
	vector<int> P
) {
	vector<pair<pair<int, int>, int>> q;
	for(int i = 0; i < (int)W.size(); i++) {
		q.push_back(make_pair(make_pair(W[i], P[i]), i));
	}
	sort(q.begin(), q.end());
	vector<int> ans(q.size(), 0);
	set<pair<int, int>> path;
	int now = 0;
	for(int s = 0; s < (int)T.size(); s += Bucket) {
		int e = std::min(s + Bucket, (int)T.size());
		
		set<pair<int, int>> change;
		for(int i = s; i < e; i++) change.insert(minMaxPair(X[i], Y[i]));
		
		auto fixed_ = path;
		set<pair<int, int>> np;
		for(auto i : change) if(fixed_.find(i) != fixed_.end()) {
			fixed_.erase(i);
			np.insert(i);
		}
		
		Paths fixed1, fixed2;
		for(auto i : fixed_) {
			fixed1.push_back(i);
			fixed2.push_back(revPath(N, i));
		}
		
		vector<pair<int, pair<int, std::shared_ptr<Paths>>>> query1, query2;
		for(int i = s; i < e; i++) {
			if(T[i] == 0) {
				path.insert(minMaxPair(X[i], Y[i]));
				np.insert(minMaxPair(X[i], Y[i]));
			}
			else {
				path.erase(minMaxPair(X[i], Y[i]));
				np.erase(minMaxPair(X[i], Y[i]));
			}
			std::shared_ptr<Paths> p1(new Paths), p2(new Paths);
			for(auto j : np) {
				p1->push_back(j);
				p2->push_back(revPath(N, j));
			}
			while(now < (int)q.size() && q[now].first.first == i) {
				query1.push_back(make_pair(q[now].first.second, make_pair(q[now].second, p1)));
				query2.push_back(make_pair(N - 2 - q[now].first.second, make_pair(q[now].second, p2)));
				now++;
			}
		}
		
		for(auto i : solve(N, fixed1, query1)) ans[i.first] += i.second;
		for(auto i : solve(N, fixed2, query2)) ans[i.first] += i.second;
	}
	return ans;
}

