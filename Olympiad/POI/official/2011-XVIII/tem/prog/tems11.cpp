/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Temperatura                                      *
 *   Autor:             Tomasz Kociumaka                                 *
 *   Zlozonosc czasowa: O(n * (MAXX - MINX))                             *
 *   Opis:              Rozwiazanie powolne                              *
 *                                                                       *
 *************************************************************************/

#include <cstdio>
#include <algorithm>

using namespace std;

const int MAX_N=1000001;

int x[MAX_N];
int y[MAX_N];
int najdl[MAX_N];

int main() {
    int n;
    scanf("%d", &n);
	for (int i = 0; i < n; ++i) {
		scanf("%d%d", &x[i], &y[i]);
	}
	int wynik = 1;
	for (int j = n-1; j >= 0; --j) {
		int i = j+1;
		while (i < n && y[i] >= x[j]) {
			if (x[j] <= x[i]) {
				i = najdl[i]+1;
				break;
			} else {
				++i;
			}
		}
		najdl[j] = i-1;
		wynik = max(wynik, i-j);
	}
    printf("%d\n", wynik);
}

