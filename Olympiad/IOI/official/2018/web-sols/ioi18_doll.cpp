#include "doll.h"
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 400005;

int vtx_number, total_leaf;
int X[MAXN], Y[MAXN], mp[MAXN];

void dfs(int s, int e, int v, int d){
	vtx_number++;
	if(e - s == 1){
		if(s < total_leaf) X[vtx_number - 1] = -1;
		else X[vtx_number - 1] = v;
		Y[vtx_number - 1] = v ^ (1 << d);
		return;
	}
	int cur_vtx = vtx_number - 1;
	int m = (s + e) / 2;
	if(m < total_leaf){
		X[cur_vtx] = -1;
	}
	else{
		X[cur_vtx] = -vtx_number - 1;
		dfs(s, m, v, d + 1);
	}
	Y[cur_vtx] = -vtx_number - 1;
	dfs(m+1, e, v ^ (1 << d), d + 1);
}

void create_circuit(int M, std::vector<int> A) {
	if(A.size() == 1){
		vector<int> C(M + 1, 0), X, Y;
		C[0] = A[0];
		answer(C, X, Y);
		return;
	}
	vector<int> C(M + 1, -1);
	C[0] = A[0];
	int K = 0;
	while((1 << K) < A.size()) K++;
	total_leaf = (1 << K) - A.size();
	A.erase(A.begin());
	A.push_back(0);
	dfs(0, (1 << K) - 1, 0, 0);
	for(int i=0; i<vtx_number; i++){
		if(X[i] >= 0) mp[X[i]] = 1;
		if(Y[i] >= 0) mp[Y[i]] = 1;
	}
	int ptr = 0;
	for(int i=0; i<(1<<K); i++){
		if(mp[i]){
			mp[i] = A[ptr++];
		}
	}
	for(int i=0; i<vtx_number; i++){
		if(X[i] >= 0) X[i] = mp[X[i]];
		if(Y[i] >= 0) Y[i] = mp[Y[i]];
	}
	vector<int> vx(X, X + vtx_number);
	vector<int> vy(Y, Y + vtx_number);
	answer(C, vx, vy);
}