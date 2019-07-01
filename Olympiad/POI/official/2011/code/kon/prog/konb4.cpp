/*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    konb4.cpp                                                  *}
{*   Autor:   Bartosz Górski                                             *}
{*   Opis:    Rozwiązanie niepoprawne                                    *}
{*            Złożoność: O(n ^ 2)                                        *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************/

#include<cstdio>
#include<algorithm>
#include<assert.h>
using namespace std;

#define MAX_N 5000

int n, k, a, xRedEdge, yRedEdge, xBlueEdge, yBlueEdge;
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

bool check(int a, int b) {
	if(vertexColour[a] != '?' && edgeColour[a][b] == vertexColour[a])
		return true;
	if(vertexColour[b] != '?' && edgeColour[a][b] == vertexColour[b])
		return true;
	return false;
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

bool paint(int a, int b, int c) {
	if(edgeColour[a][b] == 'R' && edgeColour[b][c] == 'R')
		return go(b, edgeColour[a][b]);
	return go(c, edgeColour[a][c]);
}

bool triangle(int a, int b, int c, int d) {
	if(a == c)
		return paint(a, b, d);
	if(a == d)
		return paint(a, b, c);
	if(b == c)
		return paint(b, a, d);
	if(b == d)
		return paint(b, a, c);
	if(edgeColour[a][c] == 'R')
		return paint(c, a, d);
	return paint(a, b, c);
}

void next(int & x, int & y) {
	++x;
	if(x < n)
		return;
	x = 0;
	++y;
}

int solve() {
	while(1) {
		while(yRedEdge < n && (xRedEdge == yRedEdge ||
				edgeColour[xRedEdge][yRedEdge] == 'B' || check(xRedEdge, yRedEdge)))
			next(xRedEdge, yRedEdge);
		while(yBlueEdge < n && (xBlueEdge == yBlueEdge || 
				edgeColour[xBlueEdge][yBlueEdge] == 'R' || check(xBlueEdge, yBlueEdge)))
			next(xBlueEdge, yBlueEdge);
		if(yRedEdge >= n || yBlueEdge >= n)
			break;
		if(!triangle(xRedEdge, yRedEdge, xBlueEdge, yBlueEdge))
			return 0;
	}
	int res = 0;
	for(int i = 0; i < n; ++i)
		if(vertexColour[i] == '?')
			++res;
	return res + 1;
}

int main()
{
	readGraph();
	printf("%d\n", solve());
	return 0;
}

