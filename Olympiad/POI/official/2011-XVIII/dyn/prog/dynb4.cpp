/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Dynamit                                          *
 *   Autor:             Bartosz Gorski                                   *
 *   Zlozonosc czasowa: O(n * lg(n))                                     *
 *   Opis:              Rozwiazanie bledne                               *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <vector>
#include <algorithm>
#include <assert.h>
#include <queue>
using namespace std;

#define MAX_N 300000
#define INF 1000000000

int n, m, a, b, c, p1[MAX_N], p2[MAX_N], deg[MAX_N], deg1[MAX_N];
bool d[MAX_N];
char vis[MAX_N];
vector<int> gra[MAX_N];
queue<int> que;

bool check(int t) {
	int a = 0, b, k = 0;
	for(int i = 0; i < n; ++i) {
		deg[i] = deg1[i];
		vis[i] = '?';
		if(deg[i] == 1) {
			vis[i] = 'v';
			que.push(i);
			p1[i] = -INF;
			if(d[i])
				p2[i] = 0;
			else
				p2[i] = -INF;
		}
	}
	while(!que.empty()) {
		a = que.front();
		que.pop();
		if((int) gra[a].size() > 1) {
			p1[a] = p2[a] = -INF;
			for(int i = 0; i < (int) gra[a].size(); ++i) {
				b = gra[a][i];
				if(vis[b] == 'p') {
					p1[a] = max(p1[a], p1[b] - 1);
					p2[a] = max(p2[a], p2[b] + 1);
				}
			}
			if(d[a])
				p2[a] = max(p2[a], 0);
			if(p1[a] >= p2[a])
				p2[a] = -INF;
			if(p2[a] == t) {
				++k;
				p1[a] = t;
				p2[a] = -INF;
			}
		}
		for(int i = 0; i < (int) gra[a].size(); ++i) {
			b = gra[a][i];
			--deg[b];
			if(vis[b] == '?' && deg[b] <= 1) {
				que.push(b);
				vis[b] = true;
			}
		}
		vis[a] = 'p';
	}
	if(p2[a] >= 0)
		++k;
	return (k <= m);
}

int main() {
	assert(scanf("%d%d", &n, &m) == 2);
	for(int i = 0; i < n; ++i) {
		assert(scanf("%d", &a) == 1);
		d[i] = a;
	}
	for(int i = 0; i < n - 1; ++i) {
		assert(scanf("%d%d", &a, &b) == 2);
		--a; --b;
		gra[a].push_back(b);
		gra[b].push_back(a);
		++deg1[a];
		++deg1[b];
	}
	a = 0;
	b = n;
	while(a < b) {
		c = (a + b) / 2;
		if(check(c))
			b = c;
		else
			a = c + 1;
	}
	printf("%d\n", a);
	return 0;
}

