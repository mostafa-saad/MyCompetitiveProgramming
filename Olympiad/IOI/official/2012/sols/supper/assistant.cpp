/*
	O(N) assistant program for Supper.
	
	Author: Giovanni Paolini
*/

#include <cstdio>
#include <queue>
#include <cassert>
#include <stack>

#include "assistant.h"

using namespace std;

int const MAXN = 100000;

bool in_the_scaffold[MAXN];
queue<int> passive; // queue of passive colors

void Assist (unsigned char *real_advice, int n, int k, int l) {
	
	for (int i=0; i<k; ++i) {
		in_the_scaffold[i] = 1;
		if ( real_advice[i] == 0 ) passive.push(i);
	}
	
	for (int i=0; i<n; ++i) {
		int color = GetRequest();
		
		if ( !in_the_scaffold[color] ) {
		    
			in_the_scaffold[ passive.front() ] = 0;
			in_the_scaffold[ color ] = 1;
			
			PutBack( passive.front() );
			passive.pop();
			
		}
		
		if ( real_advice[k+i] == 0 ) passive.push(color);
	}
	
}

