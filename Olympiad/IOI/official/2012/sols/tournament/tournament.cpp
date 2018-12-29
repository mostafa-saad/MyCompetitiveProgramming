/*
	O(N*logN) solution for Tournament.
	
	Author: Giovanni Paolini
*/

#include <cstdio>
#include <iostream>
#include <cassert>
#include <vector>
#include <queue>

using namespace std;

int const MAXN = 2000000;
int const MAXLOGN = 22;

struct Node {
	int start;
	int end;
	
	bool all_white; // True if the interval contains good knights only
	bool almost_all_white; // True if the interval contains good knights only, except at most the first knight
	
	int best_result; // The maximum length of a victory-path finishing in that node
	int where_best; // Where is the best_result achieved
	
	Node() {}
	
	Node(int _start, int _end) {
		start = _start;
		end = _end;
		best_result = 0;
	}
};

int n,c,o;

bool rank[MAXN];

// Range tree
int range_tree[MAXLOGN][MAXN];
int size; // the size of the range tree

void make_range_tree() {
	
	int m = n;
	int step = 0;
	
	while ( m > 0 ) {
		for (int i=0; i<m; ++i) {
			if ( step == 0 ) range_tree[step][i] = 1;
			else {
				range_tree[step][i] = range_tree[step-1][2*i] + range_tree[step-1][2*i+1];
			}
		}
		
		if ( m > 1 ) m = (m+1)/2;
		else m = 0;
		step++;
	}
	
	size = step;
	
}

void change (int k, int delta) { // Change the value of position k by delta
	int m = k;
	for (int step = 0; step < size; ++step) {
		
		range_tree[step][m] += delta;
		m /= 2;
		
	}
}

int find_knight (int k, int step, int m) { // Find the (initial) position of the k-th living knight, starting from a given node (step,m) of the range tree
	if ( k > range_tree[step][m] ) return n;
	
	if ( step == 0 ) {
		assert(k == 1);
		return m;
	}
	
	if ( range_tree[step-1][2*m] >= k ) return find_knight( k, step-1, 2*m );
	else return find_knight( k - range_tree[step-1][2*m], step-1, 2*m+1 );
}


// Calls tree

vector<Node> calls_tree;
int father[MAXN]; // The index of current interval of the knight

int GetBestPosition(int N, int C, int R, int *K, int *S, int *E) {
	
	n = N;
	c = C;
	int o = R;
	
	make_range_tree();
	
	rank[0] = 1;
	Node nodo = Node( 0, 0 );
	nodo.all_white = 1;
	nodo.almost_all_white = 1;
	nodo.where_best = 0;
	calls_tree.push_back( nodo );
	father[0] = 0;
	
	for (int i=1; i<n; ++i) {
		int r = K[i-1];
		rank[i] = (r > o);
		father[i] = i;
		
		Node nodo = Node( i, i );
		nodo.all_white = !rank[i];
		nodo.almost_all_white = 1;
		nodo.where_best = i;
		calls_tree.push_back( nodo );
	}
	
	for (int i=0; i<c; ++i) {
		
		int s = S[i]+1;
		int e = E[i]+1;
		
		int first = find_knight( s, size-1, 0 );
		int last = find_knight( e+1, size-1, 0 ) - 1;
		
		Node interval = Node( first, last ); // The new interval
		
		bool all_white = 1;
		bool almost_all_white = 1;
		
		int best_child = -1;
		int the_best = -1;
		
		queue<int> to_change;
		
		for (int j=s; j<=e; ++j) {
		
			int knight = find_knight( j, size-1, 0 );
			if ( j > s ) to_change.push( knight );
			int old_int = father[knight];
			
			father[knight] = calls_tree.size();
			
			if ( calls_tree[old_int].all_white == 0 ) {
				all_white = 0;
				
				if ( j > s ) almost_all_white = 0;
				else if ( calls_tree[old_int].almost_all_white == 0 ) almost_all_white = 0;
			}
			
			if ( calls_tree[old_int].best_result > the_best ) {
				the_best = calls_tree[old_int].best_result;
				best_child = old_int;
			}
		}
		
		while ( !(to_change.empty()) ) {
			int knight = to_change.front();
			to_change.pop();
			change( knight, -1 );
		}
		
		interval.all_white = all_white;
		interval.almost_all_white = almost_all_white;
		
		if ( almost_all_white ) {
			interval.best_result = the_best + 1;
			interval.where_best = calls_tree[ best_child ].where_best;
			// Found an interval for which it is possible to win interval.best_result times by starting in position interval.where_best
		}
		else {
			interval.best_result = the_best;
			interval.where_best = calls_tree[ best_child ].where_best;
		}
		
		calls_tree.push_back(interval);
	}
	
	int t = calls_tree.size();
	
	return calls_tree[t-1].where_best;
}

