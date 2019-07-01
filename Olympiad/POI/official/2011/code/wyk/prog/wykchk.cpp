/*************************************************************************
 *                                                                       *
 *                    XVIII Olimpiada Informatyczna                      *
 *                                                                       *
 *   Zadanie:           Wykres                                           *
 *   Autor:             Filip Wolski                                     *
 *   Opis:              Program sprawdzajacy wyjscia                     *
 *                                                                       *
 *************************************************************************/

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

#define PREC 1e-6
#define MXN 1000000

using namespace std;

typedef long double LD;

struct wsp_t {
	LD x, y;
};

int n, m, k;
wsp_t wsp[MXN];
LD dist, rep_dist;

void check(bool ok, const char* msg) {
	if (!ok) {
		printf("WRONG\n%s\n", msg);
		exit(0);
	}
}

int main(int argc, char **argv) {
	FILE *inp = fopen(argv[1], "r");
	FILE *out = fopen(argv[2], "r");
	FILE *cor = fopen(argv[3], "r");
	fscanf(inp, "%d%d", &n, &m);
	for (int i = 0; i < n; ++i) {
		fscanf(inp, "%Lf%Lf", &wsp[i].x, &wsp[i].y);
	}
	fscanf(cor, "%Lf", &dist);
	fscanf(out, "%Lf", &rep_dist);
	check(fabsl(dist-rep_dist) <= PREC, "Nieprawidlowa wartosc r");
	fscanf(out, "%d", &k);
	check(1 <= k && k <= m, "Nieprawidlowa ilosc punktow przyblizonego wykresu w rozwiazaniu");
	int covered = 0;
	for (int i = 0; i < k; ++i) {
		LD x, y;
		fscanf(out, "%Lf%Lf", &x, &y);
		while (covered < n && (x-wsp[covered].x)*(x-wsp[covered].x) + (y-wsp[covered].y)*(y-wsp[covered].y) < (dist + PREC) * (dist + PREC)) {
			++covered;
		}
	}
	check(covered == n, "Stopien podobienstwa wypisanego wykresu jest nieprawidlowy");
	printf("OK\n");
	return 0;
}
