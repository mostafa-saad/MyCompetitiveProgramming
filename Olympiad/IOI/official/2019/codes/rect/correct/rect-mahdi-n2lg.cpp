//IOI 2019
//Rect - Version 1 - First Approach
//Current Version: 24 May 2019
//Mahdi Safarnejad Boroujeni

#define forn(i, n) for (int i = 0; i < int(n); i++)
#define forkn(i, k, n) for(int i=(k); i<(n); i++)

#include "rect.h"

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>
using namespace std;

typedef pair<int, int> pir;

const int maxn = 10000 + 110;
int n, m;

int fnwk[maxn];
vector<pir> fnwk_history;

void fnwk_update(int index, int val, bool silent=false) {
	if (!silent)
		fnwk_history.push_back(pir(index, val));
	while (index < maxn) {
		fnwk[index] += val;
		index += index & (-index);
	}
}

int fnwk_sum(int index) {
	int result = 0;
	while (index) {
		result += fnwk[index];
		index -= index & (-index);
	}
	return result;
}

void reset_fnwk() {
	forn(i, fnwk_history.size())
		fnwk_update(fnwk_history[i].first, -fnwk_history[i].second, true);
	fnwk_history.resize(0);
}

struct tpl {
	int r, c, rc2;
	tpl(int _r, int _c, int _rc2): r(_r), c(_c), rc2(_rc2) {}
	bool operator < (const tpl &b) const {
		if (r!=b.r) return r<b.r;
		if (c!=b.c) return c<b.c;
		return rc2<b.rc2;
	}
};
map<tpl, int> horizontal, vertical;

void addh(int i, int j, int j2) {
	if (j-j2 <= 1) return;
	int val = 1;
	tpl above(i-1, j, j2);
	if (horizontal.find(above)!=horizontal.end())
		val += horizontal[above];
	horizontal[tpl(i, j, j2)] = val;
}

void addv(int i, int j, int i2) {
	if (i-i2 <= 1) return;
	int val = 1;
	tpl left(i, j-1, i2);
	if (vertical.find(left)!=vertical.end())
		val += vertical[left];
	vertical[tpl(i, j, i2)] = val;
}

long long count_rectangles(vector<vector<int> > a) {
	n = a.size();
	m = a[0].size();
	forn(i, n) {
		vector<int> stack;
		forn(j, m) {
			int last_element = INT_MIN;
			while (!stack.empty() && a[i][j] > a[i][stack.back()]) {
				if (a[i][stack.back()] > last_element)
					addh(i, j, stack.back());
				last_element = a[i][stack.back()];
				stack.pop_back();
			}
			if (!stack.empty())
				if (a[i][stack.back()] > last_element)
					addh(i, j, stack.back());
			stack.push_back(j);
		}
	}
	forn(j, m) {
		vector<int> stack;
		forn(i, n) {
			int last_element = INT_MIN;
			while (!stack.empty() && a[i][j] > a[stack.back()][j]) {
				if (a[stack.back()][j] > last_element)
					addv(i, j, stack.back());
				last_element = a[stack.back()][j];
				stack.pop_back();
			}
			if (!stack.empty())
				if (a[stack.back()][j] > last_element)
					addv(i, j, stack.back());
			stack.push_back(i);
		}
	}
	int sum = 0;
	forkn(i,2,n) forkn(j,2,m) {
		vector<pir> vec_hor, vec_ver;
		for (map<tpl, int>::iterator it_hor = horizontal.upper_bound(tpl(i-1,j,-1)); it_hor!=horizontal.end() && (it_hor->first).r==i-1 && (it_hor->first).c==j; it_hor++)
			vec_hor.push_back(pir(j-1-(it_hor->first).rc2, it_hor->second));
		for (map<tpl, int>::iterator it_ver = vertical.upper_bound(tpl(i,j-1,-1)); it_ver!=vertical.end() && (it_ver->first).r==i && (it_ver->first).c==j-1; it_ver++)
			vec_ver.push_back(pir(it_ver->second, i-1-(it_ver->first).rc2));
		if (vec_hor.empty() || vec_ver.empty()) continue;
		sort(vec_ver.begin(), vec_ver.end());
		int cur=int(vec_ver.size()) -1;
		forn(k, vec_hor.size()) {
			while (cur>=0 && vec_hor[k].first <= vec_ver[cur].first)
				fnwk_update(vec_ver[cur--].second, 1);
			sum += fnwk_sum(vec_hor[k].second);
		}
		reset_fnwk();
	}
	return sum;
}

// int main() {
//     cin>>n>>m;
//     vector<vector<int> > a(n);
//     forn(i, n) {
//     	a[i].resize(m);
//     	forn(j, m) cin>>a[i][j];
//     }
//     cout<<count_rect(n, m, a)<<endl;
//     return 0;
// }

