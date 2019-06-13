#include <cstdio>
#include <vector>
using namespace std;

void dfs(const vector<int> *E, int *P, int *D, int N) {
	for(int e: E[N]) {
		if(P[e] < 0) {
			P[e] = N;
			D[e] = D[N] + 1;
			dfs(E, P, D, e);
		}
	}
}

int getU(int *P, int N) {
	if(P[N] >= 0) return N;
	P[N] = -getU(P, -P[N]);
	return -P[N];
}

int main() {
	int N, K;
	scanf("%d%d", &N, &K);
	vector<int> E[N + 1];
	for(int i = 1; i < N; i++) {
		int A, B;
		scanf("%d%d", &A, &B);
		E[A].push_back(B);
		E[B].push_back(A);
	}
	vector<int> C[K];
	for(int i = 1; i <= N; i++) {
		int S;
		scanf("%d", &S);
		S--;
		C[S].push_back(i);
	}

	int P[N + 1];
	int D[N + 1];
	fill(P, P + N + 1, -1);
	int R = 1;
	P[R] = 0;
	D[R] = 0;
	dfs(E, P, D, R);
	for(int i = 0; i < K; i++) {
		int U = getU(P, C[i][0]);
		for(unsigned j = 1; j < C[i].size(); j++) {
			int V = getU(P, C[i][j]);
			for(; U != V;) {
				if(D[V] > D[U]) {
					P[V] *= -1;
					V = getU(P, V);
				} else {
					P[U] *= -1;
					U = getU(P, U);
				}
			}
		}
	}

	int deg[N + 1];
	fill(deg, deg + N + 1, 0);
	for(int i = 1; i <= N; i++) if(P[i] > 0) {
		deg[i]++;
		deg[getU(P, P[i])]++;
	}
	int ans = 0;
	for(int i = 1; i <= N; i++) {
		if(deg[i] == 1) ans++;
	}
	printf("%d\n", (ans + 1) / 2);
	return 0;
}
