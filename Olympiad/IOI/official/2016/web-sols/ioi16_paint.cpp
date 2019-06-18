#include "paint.h"
#include <bits/stdc++.h>
using namespace std;

int n, k;
bool L[205][200005];
bool R[205][200005];
char t[200005];

int ok_empty[200005], ok_full[200005];
int psum[200005];

bool has_white(int s, int e){
	return psum[e] != psum[s-1];
}

string solve_puzzle(string s, vector<int> c) {
	n = s.size();
	k = c.size();
	for(int i=1; i<=n; i++){
		t[i] = s[i-1];
	}
	t[n+1] = '_';
	n++;
	for(int i=1; i<=n; i++){
		psum[i] = psum[i-1] + (t[i] == '_');
	}
	L[0][0] = 1;
	for(int i=0; i<=k; i++){
		for(int j=1; j<=n; j++){
			if(t[j] == 'X') continue;
			L[i][j] = L[i][j-1];
			if(i > 0 && j >= c[i-1] + 1 && !has_white(j - c[i-1], j - 1)){
				L[i][j] |= L[i-1][j - c[i-1] - 1];
			}
		}
	}
	R[k][n+1] = 1;
	for(int i=k; i>=0; i--){
		for(int j=n; j; j--){
			if(t[j] != 'X') R[i][j] = R[i][j+1];
			if(i < k && j + c[i] <= n && t[j + c[i]] != 'X' && !has_white(j, j + c[i] - 1)){
				R[i][j] |= R[i+1][j + c[i] + 1];
			}
		}
	}
	for(int i=1; i<n; i++){
		for(int j=0; j<=k; j++){
			if(L[j][i] && R[j][i+1] && t[i] != 'X'){
				ok_empty[i] = 1;
			}
		}
	}
	for(int i=1; i<=k; i++){
		for(int j=0; j<=n-1-c[i-1]; j++){
			if(L[i-1][j] && R[i][j + c[i-1] + 2] && !has_white(j+1, j+c[i-1]) && t[j] != 'X' && t[j + c[i-1] + 1] != 'X'){
				ok_full[j+1]++;
				ok_full[j+c[i-1]+1]--;
			}
		}
	}
	for(int i=1; i<=n; i++){
		ok_full[i] += ok_full[i-1];
	}
	string dap;
	for(int i=1; i<n; i++){
		if(ok_empty[i] && ok_full[i]) dap.push_back('?');
		else if(ok_empty[i]) dap.push_back('_');
		else if(ok_full[i]) dap.push_back('X');
		else assert(0);
	}
	return dap;
}