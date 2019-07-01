/*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kon8.cpp                                                   *}
{*   Autor:   Bartosz Górski                                             *}
{*   Opis:    Rozwiązanie alternatywne                                   *}
{*            Złożoność: O(n ^ 2)                                        *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************/

#include<cstdio>
#include<algorithm>
#include<assert.h>
using namespace std;

#define MAX_N 5000

int n, m, k, a, degree[MAX_N], redDegree[MAX_N], counter;
char edgeColour[MAX_N][MAX_N], vertexColour[MAX_N], chosenColour;

void init(int n) {
	for(int i = 0; i < n; ++i) {
		redDegree[i] = 0;
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

bool paint(int v, char colour) {
	if(vertexColour[v] != '?')
		return vertexColour[v] == colour;
	vertexColour[v] = colour;
	--m;
	if(vertexColour[v] == chosenColour)
		--counter;
	if(counter < 0)
		return false;
	degree[v] = 0;
	for(int i = 0; i < n; ++i)
		if(edgeColour[v][i] == chosenColour && vertexColour[i] == '?')
			--degree[i];
	bool res = true;
	for(int i = 0; i < n && res; ++i)
		if(i != v && edgeColour[v][i] == oppositeColour(vertexColour[v]))
				res &= paint(i, edgeColour[v][i]);
	return res;
}

int getVertex(int gr, int gb, int n, int m) {
	for(int i = 0; i < n; ++i)
		if(vertexColour[i] == '?' && ((m - 1 - degree[i]) >= gb || degree[i] >= gr))
			return i;
	return -1;
}

int countSolutions(int k) {
	if(k <= 0 || k >= n)
		return 0;
	for(int i = 0; i < n; ++i) {
		vertexColour[i] = '?';
		degree[i] = redDegree[i];
	}
	int v = -1, gr = -1, gb = -1;
	chosenColour = 'R';
	counter = k;
	m = n;
	while(counter > 2) {
		gr = counter + 1;
		gb = (m - counter + 1);
		if(counter >= m - 2) {
			counter = m - counter;
			chosenColour = 'B';
			for(int i = 0; i < n; ++i)
				degree[i] = m - 1 - degree[i];
			gr = counter + 1;
			gb = (m - counter + 1);
			break;
		}
		else
			v = getVertex(gr, gb, n, m);
		if(v == -1)
			break;
		if(degree[v] >= gr) {
			if(!paint(v, 'R'))
				return 0;
		}
		else
			if(!paint(v, 'B'))
				return 0;
	}
	for(int i = 0; i < n; ++i)
		if(vertexColour[i] == '?') {
			if(degree[i] > counter) {
				if(!paint(i, chosenColour))
					return 0;
			}
			else
				if(degree[i] < (counter - 1) && counter > 2)
					if(!paint(i, oppositeColour(chosenColour)))
						return 0;
		}
	if(counter == 0)
		return 1;
	int d[3], left = 0;
	d[0] = d[1] = d[2] = 0;
	for(int i = 0; i < n; ++i)
		if(vertexColour[i] == '?') {
			++d[degree[i]];
			++left;
		}
	if(counter == 1) {
		if(d[1] == 0)
			return left;
		if(d[1] == 2)
			return 2;
		return 0;
	}
	if(counter == 2) {
		if((d[1] == 2 && d[2] == 0) || (d[1] == 2 && d[2] == 2))
			return 1;
		if(d[1] == 2 && d[2] == 1)
			return 2;
		if(d[1] == 0 && d[2] == 3)
			return 3;
		return 0;
	}
	return 0;
}

int solve() {
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			if(edgeColour[i][j] == 'R')
				++redDegree[i];
	for(int i = 0; i < n; ++i)
		degree[i] = redDegree[i];
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < i; ++j)
			if(degree[j] < degree[i])
				swap(degree[j], degree[i]);
	k = 0;
	while(k < n && (degree[k] >= k))
		++k;
	return countSolutions(k - 1) + countSolutions(k);
}

int main() {
	readGraph();	
	printf("%d\n", solve());
	return 0;
}
