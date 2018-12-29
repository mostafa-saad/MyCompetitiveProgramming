/*************************************************************************}
{*                                                                       *}
{*   Zadanie: Konspiracja (KON)                                          *}
{*   Plik:    kons11.cpp                                                 *}
{*   Autor:   Bartosz Górski                                             *}
{*   Opis:    Rozwiązanie nieefektywne czasowo                           *}
{*            Złożoność: O(3 ^ (log n) * n ^ 2)                          *}
{*            Kodowanie znaków: UTF-8                                    *}
{*                                                                       *}
{*************************************************************************/

#include<cstdio>
#include<algorithm>
#include<assert.h>
using namespace std;

#define MAX_N 5000

int n, m, k, a, degree[MAX_N], redDegree[MAX_N];
char edgeColour[MAX_N][MAX_N], vertexColour[MAX_N];

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

bool paint(int v, char colour, char chosenColour, char * vertexColour, int * degree, int & counter) {
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
		if(i != v && edgeColour[v][i] == chosenColour && vertexColour[i] == '?')
			--degree[i];
	bool res = true;
	for(int i = 0; i < n && res; ++i)
		if(i != v && edgeColour[v][i] == oppositeColour(vertexColour[v]))
				res &= paint(i, edgeColour[v][i], chosenColour, vertexColour, degree, counter);
	return res;
}

int isClique(int m, char colour, char chosenColour, int & u, int & v, int * nr) {
	u = -1;
	v = -1;
	int deg[MAX_N];
	for(int i = 0; i < m; ++i)
		deg[i] = 0;
	for(int i = 0; i < m; ++i)
		for(int j = i + 1; j < m; ++j)
			if(edgeColour[nr[i]][nr[j]] != colour) {
				u = i;
				v = j;
				++deg[i];
				++deg[j];
			}
	int maxD = 0, equal1 = 0, higher = 0;
	for(int i = 0; i < m; ++i) {
		maxD = max(deg[i], maxD);
		if(deg[i] == 1)
			++equal1;
		if(deg[i] > 1)
			++higher;
	}
	if(u != -1 && v != -1) {
		if(deg[u] < deg[v])
			swap(u, v);
		if(colour != chosenColour && deg[u] > deg[v]) {
				u = nr[u];
				v = -1;
		}
		else {
			u = nr[u];
			v = nr[v];
		}
	}
	int badVertexCounter = n;
	if(maxD == 0)
		badVertexCounter = 0;
	else
		if(higher <= 1 && maxD == (equal1 + higher - 1))
			badVertexCounter = 2;
	return badVertexCounter;
}

bool swapVertex(int ic, int in, int v, char chosenColour, int *clique, int * noClique) {
	if(v == -1)
		return false;
	int edgeFromV = 0, tmp, edgeFromI, u = -1;
	for(int i = 0; i < ic; ++i)
		if(edgeColour[v][clique[i]] == chosenColour)
			++edgeFromV;
	for(int i = 0; i < ic; ++i) {
		edgeFromI = 0; 
		for(int j = 0; j < in; ++j)
			if(edgeColour[clique[i]][noClique[j]] == chosenColour && noClique[j] != v)
				++edgeFromI;
		tmp = edgeFromV;
		if(edgeColour[clique[i]][v] == chosenColour)
			--tmp;
		if(tmp == ic - 1 && edgeFromI == 0) {
			u = clique[i];
			break;
		}
	}
	if(u == -1)
		return false;
	for(int i = 0; i < ic; ++i)
		if(clique[i] == u) {
			clique[i] = v;
			break;
		}
	for(int i = 0; i < in; ++i)
		if(noClique[i] == v) {
			noClique[i] = u;
			break;
		}
	return true;
}

int countSwaps(int ic, int in, char chosenColour, int * clique, int * noClique) {
	int degree[MAX_N];
	for(int i = 0; i < ic; ++i)
		degree[clique[i]] = 0;
	for(int i = 0; i < in; ++i)
		degree[noClique[i]] = 0;
	for(int i = 0; i < ic; ++i)
		for(int j = 0; j < in; ++j)
			if(edgeColour[clique[i]][noClique[j]] == chosenColour) {
				++degree[clique[i]];
				++degree[noClique[j]];
			}
	int tmp1, tmp2, res = 0;
	for(int i = 0; i < ic; ++i)
		for(int j = 0; j < in; ++j) {
			tmp1 = degree[clique[i]];
			tmp2 = degree[noClique[j]];
			if(edgeColour[clique[i]][noClique[j]] == chosenColour) {
				--tmp1;
				--tmp2;
			}
			if(tmp1 == 0 && tmp2 == (ic - 1))
				++res;
		}
	return res;
}

void copyColours(char * vertexColour, char * newVertexColour) {
	for(int i = 0; i < n; ++i)
		newVertexColour[i] = vertexColour[i];
}

void copyDegrees(int * degree, int * newDegree) {
	for(int i = 0; i < n; ++i)
		newDegree[i] = degree[i];
}

int getUncolour(int m, char * vertexColour, int * nr, int * newNr) {
	int in = 0;
	for(int i = 0; i < m; ++i)
		if(vertexColour[i] == '?')
			newNr[in++] = i;
	return in;
}

int countSolutions(int k, int m, char chosenColour, int * nr, char * vertexColour, int * degree) {
	if(k < 0 || k > m)
		return 0;
	int copyDegree[MAX_N];
	copyDegrees(degree, copyDegree);
	if(k < (m + 1) / 2) {
		chosenColour = oppositeColour(chosenColour);
		for(int i = 0; i < m; ++i)
			copyDegree[nr[i]] = m - 1 - copyDegree[nr[i]];
		k = m - k;
	}
	int clique[MAX_N], noClique[MAX_N], lic = k, ic = 0, in = 0, u = -1, v = -1;
	for(int i = 0; i < m; ++i)
		if(copyDegree[nr[i]] >= k - 1 && lic > 0) {
			clique[ic++] = nr[i];
			--lic;
		}
		else
			noClique[in++] = nr[i];
	if(lic > 0)
		return 0;
	if(isClique(ic, chosenColour, chosenColour, u, v, clique) == 0) {
		int bad = isClique(in, oppositeColour(chosenColour), chosenColour, u, v, noClique);
		if(bad > 2)
			return 0;
		if(bad > 0) 
			if(!swapVertex(ic, in, u, chosenColour, clique, noClique))
				if(!swapVertex(ic, in, v, chosenColour, clique, noClique))
					return 0;
		return 1 + countSwaps(ic, in, chosenColour, clique, noClique);
	}
	else {
		int newNr[MAX_N], newDegree[MAX_N], newM, newK, res = 0;
		char newVertexColour[MAX_N];
		copyColours(vertexColour, newVertexColour);
		copyDegrees(copyDegree, newDegree);
		newK = k;
		if(paint(v, chosenColour, chosenColour, newVertexColour, newDegree, newK)) {
			newM = getUncolour(m, newVertexColour, nr, newNr);
			res += countSolutions(newK, newM, chosenColour, newNr, newVertexColour, newDegree);
		}
		copyColours(vertexColour, newVertexColour);
		copyDegrees(copyDegree, newDegree);
		newK = k;
		if(paint(u, chosenColour, chosenColour, newVertexColour, newDegree, newK)) {
			newM = getUncolour(m, newVertexColour, nr, newNr);
			res += countSolutions(newK, newM, chosenColour, newNr, newVertexColour, newDegree);
		}
		copyColours(vertexColour, newVertexColour);
		copyDegrees(copyDegree, newDegree);
		newK = k;
		if(paint(u, oppositeColour(chosenColour), chosenColour, newVertexColour, newDegree, newK) &&
			paint(v, oppositeColour(chosenColour), chosenColour, newVertexColour, newDegree, newK)) {
			newM = getUncolour(m, newVertexColour, nr, newNr);
			res += countSolutions(newK, newM, chosenColour, newNr, newVertexColour, newDegree);
		}
		return res;
	}
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
	int nr[MAX_N];
	for(int i = 0; i < n; ++i) {
		nr[i] = i;
		vertexColour[i] = '?';
	}
	int res = 0;
	if(k > 1)
		res += countSolutions(k - 1, n, 'R', nr, vertexColour, redDegree);
	if(k < n)
		res += countSolutions(k, n, 'R', nr, vertexColour, redDegree);
	return res;
}

int main() {
	readGraph();	
	printf("%d\n", solve());
	return 0;
}
