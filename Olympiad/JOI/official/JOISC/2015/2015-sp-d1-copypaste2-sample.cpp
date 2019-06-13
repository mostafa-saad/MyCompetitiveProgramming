#include <stdio.h>

const int LIM_LENGTH = 200000;
const int LIM_N = 200000;
const int LIM_K = 200;

int K, M;
char S[LIM_LENGTH + 10];
int N;
int A[LIM_N + 10], B[LIM_N + 10], C[LIM_N + 10];

char ans[LIM_K + 10];

int main() {
	scanf("%d%d", &K, &M);
	scanf("%s", S);
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		scanf("%d%d%d", &A[i], &B[i], &C[i]);
	}
	
	for (int k = 0; k < K; ++k) {
		int x = k;
		for (int i = N - 1; i >= 0; --i) {
			if (x < C[i]) {
				x = x;
			} else if (x < C[i] + (B[i] - A[i])) {
				x = A[i] + (x - C[i]);
			} else {
				x = x - (B[i] - A[i]);
			}
		}
		ans[k] = S[x];
	}
	ans[K] = '\0';
	puts(ans);
	
	return 0;
}
