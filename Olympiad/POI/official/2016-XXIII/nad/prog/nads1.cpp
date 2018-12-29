/******************************************************************************
 *                                                                            *
 *                    XXIII Olimpiada Informatyczna                           *
 *                                                                            *
 *   Zadanie:              Nadajniki                                          *
 *   Autor programu:       Kamil Debowski                                     *
 *   Zlozonosc czasowa:    O(3^n * poly(n))                                   *
 *   Opis:                 Rozwiazanie wolne                                  *
 *****************************************************************************/

#include<bits/stdc++.h>
using namespace std;

const int nax = 1e6 + 5;
vector<int> w[nax];
int n, result = nax;
int t[nax];
int used;

void change(int a, int c) {
	used += c;
	t[a] += c;
	for(int i = 0; i < (int) w[a].size(); ++i)
		t[w[a][i]] += c;
}

void rec(int a) {
	if(a == n + 1) {
		for(int x = 1; x <= n; ++x)
			for(int i = 0; i < (int) w[x].size(); ++i)
				if(t[x] + t[w[x][i]] <= 1)
					return;
		result = min(result, used);
		return;
	}
	rec(a+1);
	change(a,1);
	rec(a+1);
	change(a,1);
	rec(a+1);
	change(a,-2);
}

int main() {
	scanf("%d", &n);
	assert(n <= 20);
	for(int i = 0; i < n - 1; ++i) {
		int a, b;
		scanf("%d%d", &a, &b);
		w[a].push_back(b);
		w[b].push_back(a);
	}
	rec(1);
	printf("%d\n", result);
	return 0;
}
