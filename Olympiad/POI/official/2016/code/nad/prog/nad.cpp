/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Nadajniki                                          *
 *   Autor programu:       Kamil Debowski                                     *
 *   Zlozonosc czasowa:    O(n * 27^2)                                        *
 *   Opis:                 Rozwiazanie wzorcowe                               *
 *****************************************************************************/

#include<bits/stdc++.h>
using namespace std;
const int inf = 42e6;

#define FOR(i) for(int i = 0; i < 3; ++i)
#define mini(a,b) a = min(a, b)

struct Matrix {
	// needNow - co potrzebuje najgorsza krawedz do dziecka
	// a - ile wstawiamy w ten wierzcholek
	// needUp - ile potrzebuje krawedz do (wyimaginowanego) rodzica
	int t[3][3][3];
	Matrix(int fill) {
		FOR(a)FOR(b)FOR(c) t[a][b][c] = fill;
	}
	Matrix operator * (Matrix m2) {
		Matrix res(inf);
		FOR(needNow1)FOR(a1)FOR(needUp1) {
			int x = t[needNow1][a1][needUp1];
			FOR(needNow2)FOR(a2)FOR(needUp2) {
				int y = m2.t[needNow2][a2][needUp2];
				int needNow = max(needNow1, needNow2);
				int a = min(2, a1 + a2);
				int needUp = max(0, max(needUp1-a2, needUp2-a1));
				mini(res.t[needNow][a][needUp], x + y);
			}
		}
		return res;
	}
};

const int nax = 1e6 + 5;
vector<int> w[nax];

Matrix dfs(int a, int par) {
	Matrix me(-4);
	bool nil = true;
	for(int i = 0; i < (int) w[a].size(); ++i) {
		int b = w[a][i];
		if(b != par) {
			if(nil) {
				me = dfs(b, a);
				nil = false;
			}
			else me = dfs(b, a) * me;
		}
	}
	if(nil) {
		me = Matrix(inf);
		me.t[0][0][2] = 0;
		return me;
	}
	Matrix res(inf);
	// here = number of tokens in vertex a
	FOR(here)FOR(needNow)FOR(a)FOR(needUp) if(here >= needNow) {
		int nNow = here ? 0 : needUp;
		int nUp = here ? 0 : (2 - a);
		mini(res.t[nNow][here][nUp], here + me.t[needNow][a][needUp]);
	}
	return res;
}

int main() {
	int n;
	scanf("%d", &n)?:0;
	for(int i = 0; i < n - 1; ++i) {
		int a, b;
		scanf("%d%d", &a, &b)?:0;
		w[a].push_back(b);
		w[b].push_back(a);
	}
	Matrix m = dfs(1, -1);
	int result = inf;
	FOR(b)FOR(c) mini(result, m.t[0][b][c]);
	printf("%d\n", result);
	return 0;
}
