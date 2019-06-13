#include "alicelib.h"
#include <cassert>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

void Alice( int N, int M, int A[], int B[] ){
	vector<pair<int,int>> G;
	for(int i = 0 ; i < M ; i ++){
		G.push_back(pair<int,int>(A[i],B[i]));
	}
	for(int i = 0 ; i < 10 ; i ++){
		for(int j = 0 ; j < N ; j ++){
			if((j>>i)&1)G.push_back(pair<int,int>(N+i,j));
		}
		G.push_back(pair<int,int>(N+i,N+10));
		if(i < 9)G.push_back(pair<int,int>(N+i,N+i+1));
	}
	for(int i = 0 ; i < N+10 ; i ++){
		G.push_back(pair<int,int>(i,N+11));
	}
	InitG( N+12, G.size() );
	for(int i = 0 ; i < G.size() ; i ++){
		MakeG( i, G[i].first, G[i].second );
	}
}

