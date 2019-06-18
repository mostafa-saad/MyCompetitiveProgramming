#include "messy.h"
#include <bits/stdc++.h>
using namespace std;

int n, occ[128];

void solve(int s, int e){
	if(s == e) return;
	string str;
	for(int j=0; j<n; j++){
		str.push_back('0');
	}
	for(int j=s; j<=e; j++){
		str[j] = '1';
	}
	int m = (s+e)/2;
	for(int j=m+1; j<=e; j++){
		str[j] = '0';
		add_element(str);
		str[j] = '1';
	}
	solve(s, m);
	solve(m+1, e);
}

void solve2(int s, int e, vector<int> c){
	if(s == e){ 
		occ[c[0]] = s;
		return;
	}
	int m = (s+e)/2;
	string str;
	for(int i=0; i<n; i++){
		str.push_back('0');
	}
	for(auto &i : c){
		str[i] = '1';
	}
	vector<int> l, h;
	for(auto &j : c){
		str[j] = '0';
		if(check_element(str)) h.push_back(j);
		else l.push_back(j);
		str[j] = '1';
	}
	solve2(s, m, l);
	solve2(m+1, e, h);
}

vector<int> restore_permutation(int _n, int w, int r) {
	n = _n;
	solve(0, n-1);
	compile_set();
	vector<int> v;
	for(int i=0; i<n; i++) v.push_back(i);
	solve2(0, n-1, v);
	vector<int> dap;
	for(int i=0; i<n; i++) dap.push_back(occ[i]);
	return dap;
}