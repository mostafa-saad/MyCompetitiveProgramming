#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int w, h, n;
pi a[1005];

vector<pi> seg;

lint sqsum(int x){
	return (1ll * x * (2 * x + 1) * (x + 1)) / 6;
}

lint lsum(int x){
	return (1ll * x * (x+1)) / 2;
}

lint solve(int s, int e){
	if(s == e){
		int len = seg[s].second - seg[s].first + 1;
		int sent = min(len, h);
		lint ret = 0;
		ret += 1ll * (len + 1) * (h+1) * (sent - 1);
		ret += sqsum(sent) - sqsum(1);
		ret -= (len + h + 2) * (lsum(sent) - lsum(1));
		return ret;
	}
	vector<int> p;
	for(int i=0; i<n; i++){
		if(seg[s].first <= a[i].first && a[i].first <= seg[e].second){
			p.push_back(a[i].second);
		}
	}
	p.push_back(0);
	p.push_back(h+1);
	sort(p.begin(), p.end());
	p.resize(unique(p.begin(), p.end()) - p.begin());
	lint ret = 0;
	for(int i=0; i+1<p.size(); i++){
		int len1 = seg[s].second - seg[s].first + 1;
		int len2 = seg[e].second - seg[e].first + 1;
		int dist = p[i+1] - p[i] - 1;
		int base = dist - (seg[e].first - seg[s].second - 1);
		if(base <= 0) continue;
		if(len1 > len2) swap(len1, len2);
		int st = 2, ed = min(len1, base);
		if(st <= ed){
			ret -= 1ll * (base + 1) * (ed - st + 1);
			ret += 1ll * (base + 2) * (lsum(ed) - lsum(st-1));
			ret -= sqsum(ed) - sqsum(st-1);
		}
		st = len1 + 1, ed = min(len2, base);
		if(st <= ed){
			ret += 1ll * len1 * (base + 1) * (ed - st + 1);
			ret -= 1ll * len1 * (lsum(ed) - lsum(st - 1));
		}
		st = len2 + 1; ed = min(len1 + len2, base);
		if(st <= ed){
			ret += 1ll * (base + 1) * (len1 + len2 + 1) * (ed - st + 1);
			ret -= 1ll * (base + 1 + len1 + len2 + 1) * (lsum(ed) - lsum(st-1));
			ret += sqsum(ed) - sqsum(st-1);
		}
	}
	return ret;
}

struct sweep{
	int pos, s, e, x;
};
vector<sweep> swp;

struct segtree{
	int tree[33000], tree2[33000];
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree2[p] += v;
			if(tree2[p] == 0){
				if(ps == pe) tree[p] = 0;
				else tree[p] = tree[2*p] + tree[2*p+1];
			}
			else{
				tree[p] = pe - ps + 1;
			}
			return;
		}
		int pm = (ps + pe) / 2;
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		if(tree2[p] == 0) tree[p] = tree[2*p] + tree[2*p+1];
	}
}segt;

lint solve(int x){
	swp.clear();
	lint ret = 1ll * (w + 1 - x) * (h + 1 - x);
	for(int i=0; i<n; i++){
		int sx = a[i].first - x + 1;
		int ex = a[i].first;
		int sy = a[i].second - x + 1;
		int ey = a[i].second;
		sx = max(sx, 1);
		sy = max(sy, 1);
		ex = min(ex, w+1-x);
		ey = min(ey, h+1-x);
		if(sx <= ex && sy <= ey){
			swp.push_back({sx, sy, ey, 1});
			swp.push_back({ex+1, sy, ey, -1});
		}
	}
	sort(swp.begin(), swp.end(), [&](const sweep &a, const sweep &b){
		return pi(a.pos, -a.x) < pi(b.pos, -b.x);
	});
	for(int i=0; i<swp.size(); ){
		int e = i;
		while(e < swp.size() && swp[i].pos == swp[e].pos){
			segt.add(swp[e].s, swp[e].e, 1, h+1-x, 1, swp[e].x);
			e++;
		}
		if(e < swp.size()) ret -= 1ll * segt.tree[1] * (swp[e].pos - swp[i].pos);
		i = e;
	}
	return ret;
}

int main(){
	cin >> w >> h >> n;
	for(int i=0; i<n; i++){
		cin >> a[i].first >> a[i].second;
	}
	if(n > 200){
		lint ret = 0;
		for(int i=2; i<=min(w, h); i++){
			lint k = solve(i);
			if(k == 0) break;
			ret += k;
		}
		cout << ret;
		return 0;
	}
	sort(a, a+n);
	if(a[0].first > 1) seg.push_back(pi(1, a[0].first-1));
	if(a[n-1].first < w) seg.push_back(pi(a[n-1].first + 1, w));
	for(int i=0; i<n; i++){
		seg.push_back(pi(a[i].first, a[i].first));
		if(a[i+1].first - a[i].first >= 2){
			seg.push_back(pi(a[i].first + 1, a[i+1].first - 1));
		}
	}
	sort(seg.begin(), seg.end());
	seg.resize(unique(seg.begin(), seg.end()) - seg.begin());
	lint ret = 0;
	for(int i=0; i<seg.size(); i++){
		for(int j=i; j<seg.size(); j++){
			ret += solve(i, j);
		}
	}
	cout << ret;
}


