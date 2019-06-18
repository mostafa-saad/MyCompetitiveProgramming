#include "molecules.h"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;

int n;
pi elem[200005];

vector<int> find_subset(int l, int u, vector<int> w) {
	n = w.size();
	for(int i=0; i<n; i++) elem[i] = pi(w[i], i);
	sort(elem, elem + n);
	lint e = 0, sum = 0;
	for(int i=0; i<n; i++){
		while(e < n && sum < l){
			sum += elem[e++].first;
		}
		if(sum >= l && sum <= u){
			vector<int> r;
			for(int j=i; j<e; j++) r.push_back(elem[j].second);
			sort(r.begin(), r.end());
			return r;
		}
		sum -= elem[i].first;
	}
	return vector<int>();
}