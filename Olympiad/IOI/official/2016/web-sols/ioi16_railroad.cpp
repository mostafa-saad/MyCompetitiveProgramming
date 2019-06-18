#include "railroad.h"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;

struct disj{
	int pa[400005];
	void init(int n){
		for(int i=0; i<=n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

struct edg{
	int s, e, x;
	bool operator<(const edg &e)const{
		return x < e.x;
	}
};

int dx[400005];

long long plan_roller_coaster(std::vector<int> s, std::vector<int> t) {
	vector<int> crd;
	int n = (int) s.size();
	for(int i=0; i<n; i++){
		crd.push_back(s[i]);
		crd.push_back(t[i]);
	}
	sort(crd.begin(), crd.end());
	crd.resize(unique(crd.begin(), crd.end()) - crd.begin());
	disj.init(crd.size());
	for(int i=0; i<n; i++){
		s[i] = lower_bound(crd.begin(), crd.end(), s[i]) - crd.begin();
		t[i] = lower_bound(crd.begin(), crd.end(), t[i]) - crd.begin();
		dx[s[i]]++;
		dx[t[i]]--;
		disj.uni(s[i], t[i]);
	}
	int cur = 1;
	lint ans = 0;
	vector<edg> v;
	for(int i=crd.size() - 1; i>=0; i--){
		cur += dx[i];
		if(cur < 0){
			ans += -1ll * cur * (crd[i] - crd[i-1]);
			dx[i-1] += cur;
			disj.uni(i-1, i);
			cur = 0;
		}
		if(cur > 0 && i) disj.uni(i, i-1);
		else if(cur == 0) v.push_back({i, i-1, crd[i] - crd[i-1]});
	}
	sort(v.begin(), v.end());
	for(auto &i : v){
		if(disj.uni(i.s, i.e)) ans += i.x;
	}
	return ans;
}

