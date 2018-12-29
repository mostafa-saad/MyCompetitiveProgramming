/*
	O(N*logN) advisor program for Supper, with advice of length N+K.
	
	Author: Giovanni Paolini
*/

#include <cstdio>
#include <queue>
#include <cassert>

#include "advisor.h"

using namespace std;

int const MAXN = 100000;

struct Color {
	int id;
	int np; // next position
	
	Color () {}
	
	Color (int _id, int _np) {
		id = _id;
		np = _np;
	}
};

bool operator< (Color const &a, Color const &b) {
	return ( a.np < b.np );
}


int next[MAXN]; // next[i] = index of next occurrence of d[i] in array d (n if it is the last occurrence)
int position[MAXN]; // position[j] = index of the next occurrence of color j in array d (n if it is the last occurrence)

bool in_scaffold[MAXN]; // whether color j is in the scaffold or not
priority_queue<Color> coda;

int solution[MAXN]; // -1 if no change is necessary, otherwise the color to be removed

queue<int> events[MAXN]; // events[j] is the queue of the events of color j: 1 = used; 0 = removed.


int accumulated = 0;
int counter = 0;

void ComputeAdvice (int *d, int n, int k, int m) {
	
	// Finding the next occurrence of each color
	for (int i=0; i<n; ++i) {
		position[i] = n;
	}
	
	for (int i=n-1; i>=0; --i) {
		next[i] = position[d[i]];
		position[d[i]] = i;
	}
	
	// Initial settings: inserting colors 0,...,k in the player
	for (int j=0; j<k; ++j) {
		in_scaffold[j] = 1;
		coda.push( Color( j, position[j] ) );
	}
	
	// Finding the solution
	for (int i=0; i<n; ++i) {
	
		int color = d[i];
		if ( in_scaffold[color] ) {
			
			coda.push( Color( color, next[i] ) );
			
			solution[i] = -1;
			events[ color ].push( 1 );
			
			continue;
			
		}
		
		// Removing useless color in scaffold
		Color useless = coda.top();
		coda.pop();
		in_scaffold[ useless.id ] = 0;
		
		// Inserting new color in scaffold
		coda.push( Color( color, next[i] ) );
		in_scaffold[ color ] = 1;
		
		// Writing the solution
		solution[i] = useless.id;
		events[ useless.id ].push( 0 );
		events[ color ].push( 1 );
	}
	
	// Writing the advice
	for (int j=0; j<k; ++j) {
		
		if ( events[j].empty() ) {
			WriteAdvice(0);
			continue;
		}
		
		if ( events[j].front() == 0 ) {
			events[j].pop();
			WriteAdvice(0);
		}
		else {
			WriteAdvice(1);
		}
		
	}
	
	for (int i=0; i<n; ++i) {
		
		int color = d[i];
		assert( events[ color ].front() == 1 );
		events[ color ].pop();
		
		if ( events[ color ].empty() ) {
			// The color will not be used or removed any more
			WriteAdvice(0);
			continue;
		}
		
		if ( events[ color ].front() == 0 ) {
			events[ color ].pop();
		    // The color is now inactive
			WriteAdvice(0);
		}
		else {
			// The color is now active
			WriteAdvice(1);
		}
		
	}
}

