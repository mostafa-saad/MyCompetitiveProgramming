#include<cstdio>
#include<algorithm>

#include "Memory2_lib.h"

using namespace std;

const int MAX_N = 50;

int N;

int memo[MAX_N * 2][MAX_N * 2];

int flip(int i, int j){
	if(memo[i][j] != -1) return memo[i][j];
	int x = Flip(i, j);
	memo[i][j] = x;
	memo[j][i] = x;
	return x;
}

bool answered[MAX_N];

void answer(int i, int j,int x){
	if(answered[x]) return;
	answered[x] = true;
	Answer(i, j, x);
}

int a, b, c;

int vals[MAX_N * 2];

void add(int k){
	flip(a, k);
	flip(b, k);
	flip(c, k);
	int ids[] = {a, b, c, k};
	for(int i = 0; i < 4; ++i){
		bool flg = true;
		for(int j = 0; j < 4; ++j){
			if(i == j) continue;
			if(flip(ids[i], ids[i ^ 1]) != flip(ids[i], ids[j])){
				flg = false;
			}
		}
		if(flg){
			vals[ids[i]] = flip(ids[i], ids[i ^ 1]);
			if(i == 0) a = k;
			if(i == 1) b = k;
			if(i == 2) c = k;
			break;
		}
	}
}

void init(int N_){
	N = N_;
	for(int i = 0; i < N * 2; ++i){
		vals[i] = -1;
		for(int j = 0; j < N * 2; ++j){
			memo[i][j] = -1;
		}
	}
}

void Solve(int T, int N){
	init(N);
	a = 0;
	b = 1;
	c = 2;
	flip(a, b);
	flip(b, c);
	flip(c, a);
	for(int i = 3; i < N * 2; ++i){
		add(i);
	}
	int a2 = flip(b, c);
	int b2 = flip(c, a);
	int c2 = flip(a, b);
	if(a2 == b2){
		vals[c] = a2;
		vals[a] = c2;
		vals[b] = c2;
	}else if(b2 == c2){
		vals[a] = b2;
		vals[b] = a2;
		vals[c] = a2;
	}else{
		vals[b] = a2;
		vals[c] = b2;
		vals[a] = b2;
	}
	for(int i = 0; i < N; ++i){
		int a = -1, b = -1;
		for(int j = 0; j < N * 2; ++j){
			if(vals[j] == i){
				if(a == -1) a = j;
				else b = j;
			}
		}
		Answer(a, b, i);
	}
}
