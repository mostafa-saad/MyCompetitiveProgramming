#include "circus.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, a[100005];
int d[100005], rg[100005], lg[100005];
set<int> s;
priority_queue<pi, vector<pi>, greater<pi> > pq;

vector<pi> vd, vp;

void init(int N, int M, int P[])
{
	n = N;
	for(int i=0; i<n; i++) a[i] = P[i];
	sort(a, a+n);
	a[n] = M;
	for(int i=0; i<=n; i++) s.insert(i);
	fill(d, d + n + 1, 1e9);
	fill(lg, lg + n + 1, -1e9);
	fill(rg, rg + n + 1, 1e9);
	d[n] = 0;
	pq.push(pi(d[n], n));
	auto enqueue = [&](int x, int dis){
		if(d[x] > dis){
			d[x] = dis;
			pq.push(pi(d[x], x));
		}
	};
	while(!pq.empty()){
		auto t = pq.top();
		pq.pop();
		if(s.find(t.second) == s.end()) continue;
		s.erase(t.second);
		// propagating part
		auto lb = s.lower_bound(t.second);
		if(lb != s.begin()){
			lb--;
			rg[*lb] = min(rg[*lb], rg[t.second]);
			enqueue(*lb, rg[*lb] - a[*lb]);
		}
		auto rb = s.upper_bound(t.second);
		if(rb != s.end()){
			lg[*rb] = max(lg[*rb], lg[t.second]);
			enqueue(*rb, a[*rb] - lg[*rb]);
		}
		// filling part
		int p = lower_bound(a, a+n+1, a[t.second] + d[t.second]) - a;
		lb = s.lower_bound(p);
		if(lb != s.end()){
			p = *lb;
			lg[p] = max(lg[p], a[t.second]);
			enqueue(p, a[p] - a[t.second]);
		}
		p = upper_bound(a, a+n+1, a[t.second] - d[t.second]) - a;
		rb = s.lower_bound(p);
		if(rb != s.begin()){
			p = *--rb;
			rg[p] = min(rg[p], a[t.second]);
			enqueue(p, a[t.second] - a[p]);
		}
	}
	for(int i=0; i<=n; i++){
		vd.push_back(pi(a[i] - d[i], a[i]));
		vp.push_back(pi(a[i] + d[i], a[i]));
	}
	sort(vd.begin(), vd.end());
	sort(vp.begin(), vp.end());
	for(int i=1; i<=n; i++){
		vp[i].second = max(vp[i].second, vp[i-1].second);
	}
	for(int i=n-1; i>=0; i--){
		vd[i].second = min(vd[i].second, vd[i+1].second);
	}
}

int minLength(int x)
{
	int ret = 2e9;
	auto p = lower_bound(vp.begin(), vp.end(), pi(x, 2e9));
	if(p != vp.begin()){
		p--;
		ret = min(ret, x - p->second);
	}
	p = lower_bound(vd.begin(), vd.end(), pi(x, -2e9));
	if(p != vd.end()){
		ret = min(ret, p->second - x);
	}
	return ret;
}


