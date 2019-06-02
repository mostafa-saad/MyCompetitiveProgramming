/*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    konb3.cpp                                                  *}
{*   Autor:   Bartosz Górski                                             *}
{*   Opis:    Rozwiązanie nieefektywne czasowo i niestabilne numerycznie *}
{*            Złożoność: O(n ^ 2 * 2 ^ n)                                *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************/

#include<cstdio>
#include<algorithm>
#include<assert.h>
using namespace std;

#define MAX_N 5000

int n, k, a;
char edgeColour[MAX_N][MAX_N], vertexColour[MAX_N];

void init(int n) {
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

bool findSolution() {
	for(int i = 0; i < (1 << n); ++i) {
		for(int j = 0; j < n; ++j)
			if((i & (1 << j)) == (1 << j))
				vertexColour[j] = 'R';
			else
				vertexColour[j] = 'B';
		if(check())
			return true;
	}
	return false;
}

char oppositeColour(char colour) {
	if(colour == 'R')
		return 'B';
	return 'R';
}

int solve() {
	if(!findSolution())
		return 0;
	int res = 1;
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j) {
			if(vertexColour[i] == vertexColour[j])
				continue;
			swap(vertexColour[i], vertexColour[j]);
			if(check())
				++res;
			swap(vertexColour[i], vertexColour[j]);
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

