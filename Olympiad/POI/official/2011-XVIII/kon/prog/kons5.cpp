/*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kons5.cpp                                                  *}
{*   Autor:   Bartosz Górski                                             *}
{*   Opis:    Rozwiązanie nieefektywne czasowo                           *}
{*            Złożoność: O(n ^ 4)                                        *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************/

#include<cstdio>
#include<algorithm>
#include<assert.h>
using namespace std;

#define MAX_N 5000

int n, m, k, a, order[2 * MAX_N], io;
bool graph[2 * MAX_N][2 * MAX_N], visit[2 * MAX_N];
char edgeColour[MAX_N][MAX_N], vertexColour[MAX_N], colour[2 * MAX_N];

void init(int n) {
	m = 2 * n;
	for(int i = 0; i < n; ++i) {
		vertexColour[i] = '?';
		for(int j = 0; j < n; ++j)
			edgeColour[i][j] = 'B';
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

bool check() {
	bool res = true;
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j)
			if(edgeColour[i][j] != vertexColour[i] && edgeColour[i][j] != vertexColour[j])
				res = false;
	return res;
}

void reverseDfs(int a) {
	visit[a] = true;
	for(int i = 0; i < m; ++i)
		if(graph[i][a] && !visit[i])
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
		if(graph[a][i] && !visit[i])
			paintDfs(i);
}

bool findSolution() {
	for(int i = 0; i < m; ++i)
		for(int j = 0; j < m; ++j)
			graph[i][j] = false;
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j)
			if(edgeColour[i][j] == 'R')
				graph[2 * i + 1][2 * j] = graph[2 * j + 1][2 * i] = true;
			else
				graph[2 * i][2 * j + 1] = graph[2 * j][2 * i + 1] = true;				
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
			if(graph[i][j] && colour[i] == 'R' && colour[j] == 'B')
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
	int res = 1;
	for(int i = 0; i < ir; ++i)
		for(int j = 0; j < ib; ++j) {
			swap(vertexColour[red[i]], vertexColour[blue[j]]);
			if(check())
				++res;
			swap(vertexColour[red[i]], vertexColour[blue[j]]);
		}
	for(int i = 0; i < n; ++i) {
		vertexColour[i] = oppositeColour(vertexColour[i]);
		if(check())
			++res;
		vertexColour[i] = oppositeColour(vertexColour[i]);
	}
	if(res > n)
		--res;
	return res;
}

int main() {
	readGraph();	
	printf("%d\n", solve());
	return 0;
}

