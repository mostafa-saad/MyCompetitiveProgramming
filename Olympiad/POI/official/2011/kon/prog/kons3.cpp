/*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kons3.cpp                                                  *}
{*   Autor:   Bartosz Górski                                             *}
{*   Opis:    Rozwiązanie nieefektywne czasowo                           *}
{*            Złożoność: O(n ^ 3)                                        *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************/

#include<cstdio>
#include<assert.h>

#define MAX_N 5000

int n, k, a;
char edgeColour[MAX_N][MAX_N], vertexColour[MAX_N];

void init(int n) {
	for(int i = 0; i < n; ++i) {
		vertexColour[i] = '?';
		for(int j = 0; j < n; ++j)
			edgeColour[i][j] = 'B';
		edgeColour[i][i] = '?';
	}
}

void readGraph() {
	assert(scanf("%d", &n) == 1);
	init(n);
	for(int i = 0; i < n; ++i) {
		assert(scanf("%d", &k) == 1);
		for(int j = 0; j < k; ++j) {
			assert(scanf("%d", &a) == 1);
			edgeColour[i][a - 1] = 'R';
		}
	}
}

char oppositeColour(char colour) {
	if(colour == 'R')
		return 'B';
	return 'R';
}

bool go(int v, char colour) {
	if(vertexColour[v] != '?')
		return vertexColour[v] == colour;
	vertexColour[v] = colour;
	bool res = true;
	for(int i = 0; i < n && res; ++i)
		if(i != v && (vertexColour[v] == '?' || 
				edgeColour[v][i] == oppositeColour(vertexColour[v])))
			res &= go(i, edgeColour[v][i]);
	return res;
}

bool check(int a, int b, int c) {
	if(edgeColour[a][b] == edgeColour[a][c] && edgeColour[a][b] != edgeColour[b][c])
		return go(a, edgeColour[a][b]);
	return true;
}

int solve() {
	for(int a = 0; a < n; ++a)
		for(int b = a + 1; b < n; ++b)
			for(int c = b + 1; c < n; ++c)
				if(!check(a, b, c) || !check(b, a, c) || !check(c, a, b))
					return 0;
	int res = 1;
	for(int i = 0; i < n; ++i)
		if(vertexColour[i] == '?')
			++res;
	if(res > n)
		--res;
	return res;
}

int main()
{
	readGraph();
	printf("%d\n", solve());
	return 0;
}

