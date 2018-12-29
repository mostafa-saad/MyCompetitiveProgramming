/*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kon.cpp                                                    *}
{*   Autor:   Jakub Wojtaszczyk                                          *}
{*   Opis:    Rozwiązanie alternatywne                                   *}
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
char colourc;
int k, l, N;

int colour (int i, int c) {
	if (clr[i] == 1-c) return 0;
	clr[i] = c;
	return 1;
}

int go() {
	assert(scanf("%d", &N) == 1);
	REP (i, N) REP (j, N) edges[i][j] = 0;
	REP (i, N) {
		assert(scanf("%d", &k) == 1);
		REP (j, k) {
			assert(scanf("%d", &l) == 1);
			edges[i][l-1] = edges[l-1][i] = 1;
		}
	}
//REP (i, N) {REP (j, N) printf("%d", edges[i][j]); printf("\n");}
	colourc = 0;
	REP (k, N) {
//printf("Na wejsciu do %d kolorowanie (%d)", k, colourc); REP (i, k) printf("%d", clr[i]); printf("\n");
		clr[k] = 2;
		int dcnt = 0;
		REP (j, k) {
			if (clr[j] != 2 && clr[j] != edges[j][k] && !colour(k, edges[j][k])) return 0;
			if (clr[j] == 2 && colourc != edges[j][k]) dcnt += 1;
		}
		if (dcnt > 1 && !colour(k, 1-colourc)) return 0; // Dwie czerw. kraw. do nieb. kliki
		if (clr[k] == colourc && dcnt == 1) REP (j, k) if (clr[j] == 2) colour(j, edges[j][k]);
		if (clr[k] == 1-colourc) REP (j, k) if (edges[j][k] == colourc) colour(j, colourc);
		if (clr[k] == 2 && dcnt == 1) {
			REP (j, k) if (clr[j] == 2 && edges[j][k] == colourc && !colour(j, colourc)) return 0;
			colourc = 1 - colourc;
		} // Jedna krawedz czerwona w niebieskiej klice staje sie mala czerwona klika
	}
	int res = 1;
	REP (i, N) if (clr[i] == 2) res += 1;
	if(res > N)
		--res;
	return res;
}

int main() {
	printf("%d\n", go());
	return 0;
}

