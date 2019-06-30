/*************************************************************************
 *                                                                       *
 *                    XVII Olimpiada Informatyczna                       *
 *                                                                       *
 *   Zadanie:  Zabka (ZAB)                                               *
 *   Plik:     zab1.cpp                                                  *
 *   Autor:    Bartosz Gorski                                            *
 *   Opis:     Rozwiazanie weryfikujace.                                 *
 *             k-te kamienie wyznaczamy w czasie O(n).                   *
 *             Skakanie zabki symulujemy w czasie O(n).                  *
 *                                                                       *
 *************************************************************************/  

#include<cstdio>
#include<cstdlib>
#include<vector>
#include<algorithm>
#include<assert.h>
using namespace std;

#define MAX_N 1000000

int n, k, is, f[MAX_N], sta[MAX_N], whe[MAX_N], ie[MAX_N], nr[MAX_N];
char vis[MAX_N];
long long m, p[MAX_N];
vector<vector<int> > cyc;
vector<int> fr[MAX_N];

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

void dfsVisit2(int a, int len, int num, int ind) {
	for(int j = ie[a]; j < (int)fr[a].size(); ++j) {
		int b = fr[a][j];
		++ie[a];
		if(whe[b] != -1)
			continue;
		if(m > is)
			f[b] = cyc[num][(m + ind - is) % len];
		else
			f[b] = sta[is - m];
		sta[is++] = b;
		return;
	}
	--is;
}

void dfs2() {
	for(int i = 0; i < (int)cyc.size(); ++i) {
		int len = cyc[i].size(), m1 = m % len;
		for(int j = 0; j < len; ++j) {
			int a = cyc[i][j];
			f[a] = cyc[i][(whe[a] + m1) % len];
		}
	}
	for(int i = 0; i < n; ++i) {
		if(nr[i] != -1) {
			sta[0] = i;
			is = 1;
			while(is > 0)
				dfsVisit2(sta[is - 1], cyc[nr[i]].size(), nr[i], whe[i]);
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
		fr[f[i]].push_back(i);
	}
	dfs1();
	dfs2();
	for(int i = 0; i < n; ++i)
		printf("%d%c", f[i] + 1, (i + 1 < n ? ' ' : '\n'));
	return 0;
}
