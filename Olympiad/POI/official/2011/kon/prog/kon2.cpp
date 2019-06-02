/*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kon.cpp                                                    *}
{*   Autor:   Jakub Wojtaszczyk                                          *}
{*   Opis:    Rozwiązanie wzorcowe                                       *}
{*            Złożoność: O(n ^ 2)                                        *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************/

#include <cstdio>
#include <algorithm>
#include <assert.h>

using namespace std;

#define REP(i,n) for (int i=0; i<n; i++)
#define MAXN 5020

char edges[MAXN][MAXN];
char clr[MAXN];
int N, k, l, A, B;

int colour (int i, char c) {
	if (clr[i] != 2) return (clr[i] == c);
	clr[i] = c;
	REP (j, N) if (i != j && edges[i][j] != c && !colour(j, 1-c)) return 0;
	return 1;
} // Pokoloruj wierz. i na kol. c, przemaluj sasiadow, zwroc czy sukces.

int chee (int m, char c) {
	int x = m / N; int y = m % N;
	if (x == y) return 1;
	if (edges[x][y] != c) return 1;
	if (clr[x] + clr[y] != 4) return 1;
	return 0;
} // Czy skipowac krawedz?

int solvet (int x, int y, int z) {
	if (edges[x][y] == edges[y][z]) return solvet (y, x, z);
	if (edges[x][z] == edges[y][z]) return solvet (z, x, y);
//printf("Found triangle %d %d %d, colouring %d in %d\n", x, y, z, x, edges[x][y]);
	return colour (x, edges[x][y]);
} // Rozwiaz polichromatyczny trojkat

int solve (int m0, int m1) {
	int x0 = m0 / N; int y0 = m0 % N; int x1 = m1 / N; int y1 = m1 % N;
//printf("Solving %d-%d, %d-%d\n", x0, y0, x1, y1);
//printf("Current colours: "); REP(i, N) printf("%d ", clr[i]); printf("\n");
	if (x0 == x1) return solvet(x0,y0,y1);
	if (x0 == y1) return solvet(x0,y0,x1);
	if (y0 == x1) return solvet(x0,y0,y1);
	if (y0 == y1) return solvet(x0,y0,x1);
	if (edges[x0][x1] == edges[x0][y0]) return solvet(x0,x1,y1);
	return solvet(x0,y0,x1);
} // Rozwiaz dwie polichromatyczne krawedzie

int main() {
	assert(scanf("%d", &N) == 1);
	REP (i, N) REP (j, N) edges[i][j] = 0;
	REP (i, N) {
		assert(scanf("%d", &k) == 1);
		REP (j, k) {
			assert(scanf("%d", &l) == 1);
			edges[i][l-1] = edges[l-1][i] = 1;
		}
	}
	REP (i, N) clr[i] = 2;
	A = B = 0;
	while (A < N*N && B < N*N) {
		while (A < N*N && chee(A,0)) A++;
		while (B < N*N && chee(B,1)) B++;
		if (A < N*N && B < N*N) if (!solve(A,B)) {printf("0\n"); return 0;}
	}
	int nres = 1;
	REP (i, N) if (clr[i] == 2) nres += 1;
	if(nres > N)
		--nres;
	printf("%d\n", nres);
//REP (i, N) {REP (j, N) printf("%d", edges[i][j]); printf("\n");}
//REP (i, N) {printf("%d ", clr[i]);} printf("\n");
	return 0;
}

