// NOT YET CORRECT ON SAMPLE INPUT

#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>

#define llint long long 

using namespace std;

int N,D;
vector<vector<int> > T;
vector<llint> vert, mytime, pen, K;

bool compare (pair<llint, llint> a, pair<llint, llint> b) {
	llint comp = a.first*b.second - b.first*a.second;
	if(comp != 0) return comp >= 0;
	return a.first < b.first;
}

void DFS(int pos) {
	// account for pos vertex
	mytime[pos] = pen[pos] = 1 + K[pos];
	vert[pos] = 1;
	
	// Base case: pos is a leaf
	if(T[pos].size() == 0) return;
	
	// Recursions
	// Corectly computes vert and mytime, and prepares for pen computation.
	vector<pair<llint, llint> > children;
	for(int i = 0; i < T[pos].size(); ++i) {
		int v = T[pos][i];
		DFS(v);
		vert[pos] += vert[v];
		pen[pos] += pen[v];
		mytime[pos] += mytime[v];
		children.push_back(pair<llint, llint> (vert[v], mytime[v]));
	}
	
	sort(children.begin(), children.end(), compare);
	
	int offset = 1;
	for(int i = 0; i < children.size(); ++i) {
		pen[pos] += offset * children[i].first;
		offset += children[i].second;
	}
	pen[pos] += offset; // for the root vertex
}

int main() {
	scanf("%d", &N);
	N++;
	T = vector<vector<int> > (N);
	vert = vector<llint> (N, 0);
	mytime = vector<llint> (N, 0);
	pen = vector<llint> (N, 0);
	K = vector<llint> (N,0);
	for(int i = 1; i < N; ++i) {
		int Fi;
		scanf("%lld%d", &(K[i]), &Fi);
		T[i] = vector<int> (Fi, 0);
		for(int j = 0; j < Fi; ++j)	scanf("%d", &(T[i][j]));
	}

	DFS(1);
	printf("%d", pen[1]);
	return 0;
}