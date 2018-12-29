/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Impreza                                          *
 *   Autor:             Bartosz Gorski                                   *
 *   Zlozonosc czasowa: O(n^2)                                           *
 *   Opis:              Rozwiazanie alternatywne                         *
 *                                                                       *
 *************************************************************************/


#include <cstdio>
#include <assert.h>
using namespace std;

#define MAX_N 3000

int n, m, a, b, k;
bool del[MAX_N], gra[MAX_N][MAX_N];

int main() {
	assert(scanf("%d%d", &n, &m) == 2);
	for(int i = 0; i < m; ++i) {
		assert(scanf("%d%d", &a, &b) == 2);
		--a; --b;
		gra[a][b] = gra[b][a] = true;
	}
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n && !del[i]; ++j)
			if(!del[j] && !gra[i][j])
				del[i] = del[j] = true;
	for(int i = 0; i < n && k < n / 3; ++i)
		if(!del[i]) {
			printf("%d ", i + 1);
			++k;
		}
	return 0;
}
