#include <cstdio>
#include <algorithm>
using namespace std;

int main() {
	int N, M, S, V;
	scanf("%d%d", &N, &M);
	int C[M];
	pair<int, int> paints[N];  //first V, second S
	for(int i = 0; i < N; i++) {
		scanf("%d%d", &S, &V);
		paints[i] = make_pair(V, S);
	}
	for(int i = 0; i < M; i++) {
		scanf("%d", C + i);
	}
	sort(paints, paints + N);
	sort(C, C + M);
	int ans = 0;
	for(int i = N - 1; i >= 0 && ans < M; i--) {
		if(C[M - ans - 1] >= paints[i].second) {
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}
