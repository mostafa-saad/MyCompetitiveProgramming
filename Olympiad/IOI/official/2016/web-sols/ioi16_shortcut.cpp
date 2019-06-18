#include "shortcut.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
 
struct Fucking_locality{
	lint arg1, arg2;
	lint first;
	int second;
	bool operator<(const Fucking_locality &fuck)const{
		return make_pair(first, second) < make_pair(fuck.first, fuck.second);
	}
};
 
int n, c;
lint a[1000005], b[1000005];
Fucking_locality v[1000005], w[1000005];
 
bool trial(lint x){
	lint ps = -1e18, pe = 1e18, ms = -1e18, me = 1e18;
	lint mx = -1e18, mxp = -1, smx = -1e18;
	lint mn = 1e18, mnp = -1, smn = 1e18;
	int p = 0;
	for(int i=0; i<n; i++){
		while(p < n && w[p].first + x < v[i].first){
			lint cmx = w[p].arg1;
			lint cmn = w[p].arg2;
			if(mx < cmx){
				smx = mx;
				mx = cmx;
				mxp = w[p].second;
			}
			else if(smx < cmx) smx = cmx;
			if(mn > cmn){
				smn = mn;
				mn = cmn;
				mnp = w[p].second;
			}
			else if(smn > cmn) smn = cmn;
			p++;
		}
		lint q1 = (v[i].second != mxp ? mx : smx);
		lint q2 = (v[i].second != mnp ? mn : smn);
		lint ca = v[i].arg1;
		lint cb = v[i].arg2;
		ps = max(ps, q1 - x + c + cb + ca);
		pe = min(pe, q2 + x - c + cb - ca);
		ms = max(ms, q1 - x + c - cb + ca);
		me = min(me, q2 + x - c - cb - ca);
	}
	p = 0;
	for(int i=0; i<n; i++){
		lint s = max(ps - b[i], b[i] - me);
		lint e = min(pe - b[i], b[i] - ms);
		while(p < n && s > b[p]) p++;
		while(p > 0 && s <= b[p-1]) p--;
		while(p < n && b[p] <= e) return true;
	}
	return false;
}
 
long long find_shortcut(int n, std::vector<int> l, std::vector<int> d, int c)
{
	::n = n;
	::c = c;
	for(int i=0; i<n; i++){
		a[i] = d[i];
		if(i >= 1) b[i] = b[i-1] + l[i-1];
	}
	for(int i=0; i<n; i++){
		v[i] = (Fucking_locality){a[i], b[i], a[i] + b[i], i};
		w[i] = (Fucking_locality){a[i] + b[i], -a[i] + b[i], -a[i] + b[i], i};
	}
	sort(v, v+n);
	sort(w, w+n);
	lint s = 0, e = 2e15;
	while(s != e){
		lint m = (s+e)/2;
		if(trial(m)) e = m;
		else s = m+1;
	}
	return s;
}
 