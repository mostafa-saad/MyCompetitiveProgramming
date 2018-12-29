/*
  O(N*logN) solution for City.

  Author: Giovanni Paolini
*/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Point {
	int x;
	int y;
	
	Point() {}
	
	Point(int _x, int _y) {
		x = _x;
		y = _y;
	}
};

bool operator< (const Point &a, const Point &b) {
	if ( a.x != b.x ) return ( a.x < b.x );
	return ( a.y < b.y );
}

int const MAXN = 1000005;

int n;
Point squares[MAXN];

void read(int N, int *X, int *Y) {
	
	n = N;
	
	for (int i=0; i<n; ++i) {
	  squares[i] = Point(X[i], Y[i]);
	}
	
}

void exchange() { // Exchanges the x and y coordinates of all the points.
	for (int i=0; i<n; ++i) {
		squares[i] = Point( squares[i].y, squares[i].x );
	}
}

struct Node {
	int x;
	int ymin;
	int ymax;
	vector<int> neighbours;
	
	Node () {}
	
	Node (int _x, int _ymin, int _ymax) {
		x = _x;
		ymin = _ymin;
		ymax = _ymax;
	}
};

vector<Node> nodes;


void make_tree() { // Builds the tree of vertically/horizontally-collapsed nodes
	
	sort( squares, squares + n );
	nodes.clear();
	
	// Create nodes
	
	int cont = 0;
	while ( cont < n ) {
		int x = squares[cont].x;
		int ymin = squares[cont].y;
		
		int y = ymin;
		
		int i;
		for (i=cont+1; i<n; ++i) {
			if ( squares[i].y == y+1 ) y++;
			else break;
		}
		
		int ymax = y;
		cont = i;
		
		nodes.push_back( Node( x, ymin, ymax ) );
	}
	
	// Create edges
	
	int cont1,cont2;
	
	cont1 = 0;
	for ( cont2 = 1; cont2 < nodes.size(); cont2++ ) {
		while ( ( nodes[cont1].x + 1 < nodes[cont2].x ) || ( nodes[cont1].x + 1 == nodes[cont2].x && nodes[cont1].ymax < nodes[cont2].ymin ) ) cont1++;
		
		int numedges = 0;
		while ( nodes[cont1].x + 1 == nodes[cont2].x && nodes[cont1].ymin <= nodes[cont2].ymax ) {
			numedges++;
			nodes[cont1].neighbours.push_back(cont2);
			nodes[cont2].neighbours.push_back(cont1);
			cont1++;
		}
		if ( numedges > 0 ) cont1--;
	}
	
}

int weight (int i) {
	return nodes[i].ymax - nodes[i].ymin + 1;
}

bool visited[MAXN];
long long int s; // sum of all weights
long long int tot; // required total
long long int const MOD = 1000000000;

long long int dfs (int k) {
	if ( visited[k] ) return 0;
	
	visited[k] = 1;
	
	long long int w = weight(k);
	for (int i=0; i<nodes[k].neighbours.size(); ++i) {
		w += dfs( nodes[k].neighbours[i] );
		w %= MOD;
	}
	
	tot += w * (s - w);
	tot %= MOD;
	
	return w;
}

long long int sum () {
	make_tree();
	
	s = 0;
	tot = 0;
	for (int i=0; i<nodes.size(); ++i) {
		s += weight(i);
		s %= MOD;
		visited[i] = 0;
	}
	
	dfs(0);
	
	return tot;
}

int DistanceSum(int N, int *X, int *Y) {
	
	read(N, X, Y);
	
	// Find the horizontal sum
	long long int first = sum();
	
	exchange();
	
	// Find the vertical sum
	long long int second = sum();
	
	long long int sol = first + second;
	sol %= MOD;
	
	return sol;
	
}
