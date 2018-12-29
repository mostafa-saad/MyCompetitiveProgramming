/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zabs5.cpp                                                 *
 *   Autor:    Bartosz Gorski                                            *
 *   Opis:     Rozwiazanie powolne.                                      *
 *             Rozwiazanie podobne do zabs41.cpp, lecz zoptymalizowane   *
 *             do zlozonosci czasowej O(n^2).                            *
 *                                                                       *
 *************************************************************************/  

#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<assert.h>
using namespace std;

#define MAX_N 1000000

int n, k, is, f[MAX_N], fr[MAX_N], sta[MAX_N], whe[MAX_N], nr[MAX_N], d[MAX_N];
char vis[MAX_N];
long long m, p[MAX_N];
vector<vector<int> > cyc;

void getCycle(int a) {
	vector<int> tmp;
	tmp.clear();
	for(int j = is - 1; sta[j] != a; --j)
		tmp.push_back(sta[j]);
	tmp.push_back(a);
	reverse(tmp.begin(), tmp.end());
	for(int j = 0; j < (int)tmp.size(); ++j) {
		whe[tmp[j]] = j; 
		nr[tmp[j]] = cyc.size();
	}
	cyc.push_back(tmp);
}

void dfsVisit1(int a) {
	if(vis[a] == '?') {
		vis[a] = 'v';
		if(vis[f[a]] == 'v')
			getCycle(f[a]);
		if(vis[f[a]] == '?') {
			sta[is++] = f[a];
			return;
		}
	}
	vis[a] = 'p';
	--is;
}

void dfs1() {
	for(int i = 0; i < n; ++i) {
		vis[i] = '?';
		whe[i] = nr[i] = -1;
	}
	for(int i = 0; i < n; ++i) {
		if(vis[i] == '?') {
			is = 1;
			sta[0] = i;
			while(is > 0)
				dfsVisit1(sta[is - 1]);
		}
	}
}

void dfsVisit2(int a) {
	if(d[a] == -1) {
		int b = f[a];
		if(d[b] == -1) {
			sta[is++] = b;
			return;
		}
		d[a] = d[b] + 1;
		nr[a] = nr[b];
		whe[a] = whe[b];
		if(m >= d[a])
			fr[a] = cyc[nr[a]][(m + whe[b] - d[a]) % (int)cyc[nr[a]].size()];
		else
			for(int j = 0; j < m; ++j)
				fr[a] = f[fr[a]];
	}
	--is;
}

void dfs2() {
	for(int i = 0; i < n; ++i)
		d[i] = -1;
	for(int i = 0; i < (int)cyc.size(); ++i) {
		int len = cyc[i].size(), m1 = m % len;
		for(int j = 0; j < len; ++j) {
			int a = cyc[i][j];
			d[a] = 0;
			fr[a] = cyc[i][(whe[a] + m1) % len];
		}
	}
	for(int i = 0; i < n; ++i) {
		if(d[i] == -1) {
			sta[0] = i;
			is = 1;
			while(is > 0)
				dfsVisit2(sta[is - 1]);
		}
	}
}

int main()
{
	assert(scanf("%d%d%lld", &n, &k, &m) == 3);
	for(int i = 0; i < n; ++i)
		assert(scanf("%lld", &p[i]) == 1);
	int a = 0, b = k;
	for(int i = 0; i < n; ++i) {
		while((b + 1) < n && (p[b + 1] - p[i]) < (p[i] - p[a])) {
			++b;
			++a;
		}
		f[i] = ((p[b] - p[i]) <= (p[i] - p[a]) ? a : b);
		fr[i] = i;
	}
	dfs1();
	dfs2();
	for(int i = 0; i < n; ++i)
		printf("%d%c", fr[i] + 1, (i + 1 < n ? ' ' : '\n'));
	return 0;
}
