/*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kons1.cpp                                                  *}
{*   Autor:   Bartosz Górski                                             *}
{*   Opis:    Rozwiązanie nieefektywne czasowo                           *}
{*            Złożoność: O(n ^ 6 log n)                                  *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************/

#include<cstdio>
#include<algorithm>
#include<assert.h>
using namespace std;

#define MAX_N 5000

int n, k, a, is, nr[MAX_N];
bool e[MAX_N][MAX_N], sol[MAX_N + 1][MAX_N], vis[MAX_N], col[MAX_N];

bool go(int v, bool c, bool * vis, bool * col) {
	if(vis[v])
		return col[v] == c;
	vis[v] = true;
	col[v] = c;
	bool res = true;
	for(int i = 0; i < n && res; ++i)
		if(i != v && e[v][i] == !col[v])
				res &= go(i, e[v][i], vis, col);
	return res;
}

bool rek(int nv, int * ver, bool * vis, bool * col);

bool paint(int a, bool c, int nv, int * ver, bool * vis, bool * col) {
	bool nvis[n], ncol[n];
	for(int i = 0; i < n; ++i) {
		nvis[i] = vis[i];
		ncol[i] = col[i];
	}
	bool ok = go(a, c, nvis, ncol);
	if(!ok)
		return false;
	int nr[nv], in = 0;
	for(int i = 0; i < nv; ++i) {
		if(!nvis[ver[i]])
			nr[in++] = ver[i];
	}
	return rek(in, nr, nvis, ncol);
}

bool check(int a, int b, int c, int nv, int * ver, bool * vis, bool * col,
	bool & tri) {
	if(e[a][b] && e[a][c] && !e[b][c]) {
		tri = true;
		return paint(a, true, nv, ver, vis, col);
	}
	if(!e[a][b] && !e[a][c] && e[b][c]) {
		tri = true;
		return paint(a, false, nv, ver, vis, col);
	}
	return true;
}

bool lower(bool * ncol, int nr) {
	if(nr == -1)
		return false;
	for(int i = 0; i < n; ++i)
		if(sol[nr][i] != ncol[i])
			return ncol[i] < sol[nr][i];
	return false;
}

int bs(bool * ncol) {
	int l = -1, c, r = is - 1;
	while(l < r) {
		c = (l + r + 1) / 2;
		if(lower(ncol, c))
			r = c - 1;
		else
			l = c;
	}
	return l; 
}

bool equal(bool * ncol, int nr) {
	if(nr == -1)
		return false;
	for(int i = 0; i < n; ++i)
		if(sol[nr][i] != ncol[i])
			return false;
	return true;
}

void add(bool * ncol) {
	int poz = bs(ncol);
	if(equal(ncol, poz))
		return;
	++poz;
	for(int i = is; i > poz; --i)
		for(int j = 0; j < n; ++j)
			sol[i][j] = sol[i - 1][j];
	for(int i = 0; i < n; ++i)
		sol[poz][i] = ncol[i];
	++is;
}

bool rek(int nv, int * ver, bool * vis, bool * col) {
	if(n == 0)
		return true;
	if(n == 1) {
		col[ver[0]] = true;
		add(col);
		col[ver[0]] = false;
		add(col);
		return true;
	}
	bool ok = true, tri = false;
	for(int a = 0; a < nv && ok; ++a)
		for(int b = a + 1; b < nv && ok; ++b)
			for(int c = b + 1; c < nv && ok; ++c) {
				ok &= check(ver[a], ver[b], ver[c], nv, ver, vis, col, tri);
				ok &= check(ver[b], ver[a], ver[c], nv, ver, vis, col, tri);
				ok &= check(ver[c], ver[a], ver[b], nv, ver, vis, col, tri);
			}
	if(ok && !tri) {
		int in = 0, nr[nv];
		for(int a = 0; a < nv; ++a)
			if(!vis[ver[a]])
				nr[in++] = ver[a];
		bool k = e[nr[0]][nr[1]];
		for(int a = 0; a < in; ++a)
			col[nr[a]] = k;
		add(col);
		for(int a = 0; a < in; ++a) {
			col[nr[a]] = !col[nr[a]];
			add(col);
			col[nr[a]] = !col[nr[a]];
		}
	}
	return ok;
}

int main() {
	assert(scanf("%d", &n) == 1);
	for(int i = 0; i < n; ++i) {
		nr[i] = i;
		assert(scanf("%d", &k) == 1);
		for(int j = 0; j < k; ++j) {
			assert(scanf("%d", &a) == 1);
			e[i][a - 1] = true;
		}
	}
	rek(n, nr, vis, col);
	if(is > n)
		--is;
	printf("%d\n", is);
	return 0;
}

