/*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kon5.cpp                                                   *}
{*   Autor:   Bartosz Górski                                             *}
{*   Opis:    Rozwiązanie alternatywne                                   *}
{*            Złożoność: O(n ^ 2)                                        *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************/

#include<cstdio>
#include<assert.h>

#define MAX_N 5000

int n, m, k, a, order[2 * MAX_N], io;
bool graf[2 * MAX_N][2 * MAX_N], visit[2 * MAX_N];
char edgeColour[MAX_N][MAX_N], vertexColour[MAX_N], colour[2 * MAX_N];

void init(int n) {
	m = 2 * n;
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

void reverseDfs(int a) {
	visit[a] = true;
	for(int i = 0; i < m; ++i)
		if(graf[i][a] && !visit[i])
			reverseDfs(i);
	order[io++] = a;
}

void paintDfs(int a) {
	visit[a] = true;
	if(colour[a ^ 1] == '?')
		colour[a] = 'R';
	else
		colour[a] = 'B';
	for(int i = 0; i < m; ++i)
		if(graf[a][i] && !visit[i])
			paintDfs(i);
}

bool findSolution() {
	for(int i = 0; i < m; ++i)
		for(int j = 0; j < m; ++j)
			graf[i][j] = false;
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j)
			if(edgeColour[i][j] == 'R')
				graf[2 * i + 1][2 * j] = graf[2 * j + 1][2 * i] = true;
			else
				graf[2 * i][2 * j + 1] = graf[2 * j][2 * i + 1] = true;				
	for(int i = 0; i < m; ++i) {
		visit[i] = false;
		colour[i] = '?';
	}
	for(int i = 0; i < m; ++i)
		if(!visit[i])
			reverseDfs(i);
	for(int i = 0; i < m; ++i)
		visit[i] = false;
	for(int i = m - 1; i >= 0; --i)
		if(!visit[order[i]])
			paintDfs(order[i]);
	for(int i = 0; i < m; ++i)
		for(int j = 0; j < m; ++j)
			if(graf[i][j] && colour[i] == 'R' && colour[j] == 'B')
				return false;
	for(int i = 0; i < n; ++i)
		vertexColour[i] = colour[2 * i];
	return true;
}

char oppositeColour(char colour) {
	if(colour == 'R')
		return 'B';
	return 'R';
}

int solve() {
	if(!findSolution())
		return 0;
	int  red[MAX_N], blue[MAX_N], ir = 0, ib = 0;
	for(int i = 0; i < n; ++i)
		if(vertexColour[i] == 'R')
			red[ir++] = i;
		else
			blue[ib++] = i;
	int res = 1, deg[MAX_N];
	for(int i = 0; i < ir; ++i) {
		deg[red[i]] = 0;
		for(int j = 0; j < ib; ++j)
			if(edgeColour[red[i]][blue[j]] == 'R')
				++deg[red[i]];
	}
	for(int i = 0; i < ib; ++i) {
		deg[blue[i]] = 0;
		for(int j = 0; j < ir; ++j)
			if(edgeColour[blue[i]][red[j]] == 'B')
				++deg[blue[i]];
	}
	for(int i = 0; i < ir; ++i)
		for(int j = 0; j < ib; ++j)
			if(edgeColour[red[i]][blue[j]] == 'R') {
				if(deg[red[i]] == 1 && deg[blue[j]] == 0)
					++res;
			}
			else {
				if(deg[red[i]] == 0 && deg[blue[j]] == 1)
					++res;
			}
	for(int i = 0; i < n; ++i)
		if(deg[i] == 0)
			++res;
	if(res > n)
		--res;
	return res;
}

int main() {
	readGraph();	
	printf("%d\n", solve());
	return 0;
}

