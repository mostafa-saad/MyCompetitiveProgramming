#include<cstdio>
#include<iostream>
#include<vector>
#include<algorithm>

#define llint long long 

using namespace std;

int N,D;
llint pen = 0, curTime = 0;
vector<vector<int> > T;
vector<llint> vert, mytime, K;

bool compare (int i, int j) {
	llint n1 = vert[i], t1 = mytime[i], n2 = vert[j], t2 = mytime[j], comp;
	comp = n1*t2 - n2*t1;
	if(comp != 0) return comp > 0;
	return n1 < n2;
}

void DFS1(int pos) {
	mytime[pos] = 1 + K[pos];
	vert[pos] = 1;
	for(int i = 0; i < T[pos].size(); ++i) {
		DFS1(T[pos][i]);
		mytime[pos] += mytime[T[pos][i]];
		vert[pos] += vert[T[pos][i]];
}}

void DFS2(int pos) {
	curTime++;
	for(int i = 0; i < T[pos].size(); ++i) {DFS2(T[pos][i]);}
	curTime += K[pos];
	pen += curTime;
}

int main() {
	scanf("%d", &N);
	N++;
	T = vector<vector<int> > (N);
	vert = vector<llint> (N, 0);
	mytime = vector<llint> (N, 0);
	K = vector<llint> (N,0);
	for(int i = 1; i < N; ++i) {
		int Fi;
		scanf("%lld%d", &(K[i]), &Fi);
		T[i] = vector<int> (Fi, 0);
		for(int j = 0; j < Fi; ++j)	scanf("%d", &(T[i][j]));
	}

	DFS1(1);
	
	for(int i = 1; i < N; ++i) {sort(T[i].begin(), T[i].end(), compare);}
	
	DFS2(1);
	
	printf("%lld\n", pen);
	return 0;
}
