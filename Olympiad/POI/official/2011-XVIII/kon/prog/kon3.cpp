/*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kon3.cpp                                                   *}
{*   Autor:   Bartosz Górski                                             *}
{*   Opis:    Rozwiązanie alternatywne                                   *}
{*            Złożoność: O(n ^ 2)                                        *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************/

#include<cstdio>
#include<assert.h>

#define MAX_N 5000

int n, k, a, cliqueSize, edgeToClique, firstVertexInClique;
char edgeColour[MAX_N][MAX_N], vertexColour[MAX_N], cliqueColour;

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

bool extortVertexColour(int u) {
	edgeToClique = 0;
	firstVertexInClique = -1;
	for(int v = 0; v < u; ++v)
		if(vertexColour[v] == '?') {
			if(firstVertexInClique == -1)
				firstVertexInClique = v;
			if(edgeColour[u][v] != cliqueColour)
				++edgeToClique;
		}
		else
			if(edgeColour[u][v] != vertexColour[v]) {
				if(vertexColour[u] != '?' && vertexColour[u] != edgeColour[u][v])
					return true;
				vertexColour[u] = edgeColour[u][v];
			}
	return false;
}

char oppositeColour(char colour) {
	if(colour == 'R')
		return 'B';
	return 'R';
}

int solve() {
	cliqueColour = edgeColour[0][1];
	cliqueSize = 2;
	for(int u = 2; u < n; ++u) {
		if(extortVertexColour(u)) 
			return 0;
		if(vertexColour[u] == '?') {
			if(edgeToClique == 0 || cliqueSize < 2) {
				if(cliqueSize == 1)
					cliqueColour = edgeColour[firstVertexInClique][u];
				++cliqueSize;
				continue;
			}
			if(edgeToClique == 1) {
				for(int v = 0; v < u; ++v)
					if(vertexColour[v] == '?' && edgeColour[u][v] == cliqueColour)
						vertexColour[v] = cliqueColour;
				cliqueColour = oppositeColour(cliqueColour);
				cliqueSize = 2;
				continue;
			}
			if(edgeToClique >= 2)
				vertexColour[u] = oppositeColour(cliqueColour);
		}
		if(cliqueSize == 0)
			continue;
		if(cliqueSize == 1) {
			if(vertexColour[u] != edgeColour[u][firstVertexInClique]) {
				vertexColour[firstVertexInClique] = edgeColour[u][firstVertexInClique];
				--cliqueSize;
			}
			continue;
		}
		if(vertexColour[u] == cliqueColour) {
			if(edgeToClique > 1)
				return 0;
			if(edgeToClique == 1) {
				for(int v = 0; v < u; ++v)
					if(vertexColour[v] == '?') {
						if(vertexColour[u] == edgeColour[u][v])
							vertexColour[v] = cliqueColour;
						else
							vertexColour[v] = oppositeColour(cliqueColour);
					}
				cliqueColour = '?';
				cliqueSize = 0;
			}
		}
		else {
			for(int v = 0; v < u; ++v)
				if(vertexColour[v] == '?' && vertexColour[u] != edgeColour[u][v]) {
					vertexColour[v] = cliqueColour;
					--cliqueSize;
				}
		}	
	}
	if(cliqueSize < n)
		++cliqueSize;
	return cliqueSize;
}

int main() {
	readGraph();
	printf("%d\n", solve());
	return 0;
}

