#include "xylophone.h"

void solve(int N) {
	int A[N];
	A[0] = 0;
	int D[N - 1];
	int T[N - 2];
	for(int i = 1; i < N; i++) {
		D[i - 1] = query(i, i + 1);
	}
	for(int i = 2; i < N; i++) {
		T[i - 2] = query(i - 1, i + 1);
	}
	A[1] = D[0];
	bool up = true;
	for(int i = 2; i < N; i++) {
		if(D[i - 2] + D[i - 1] != T[i - 2]) {
			up = !up;
		}
		A[i] = A[i - 1] + D[i - 1] * ((int)up * 2 - 1);
	}
	int mx = 0, mn = 0;
	int mxp = 0, mnp = 0;
	for(int i = 1; i < N; i++) {
		if(A[i] > mx) {
			mx = A[i];
			mxp = i;
		}
		if(A[i] < mn) {
			mn = A[i];
			mnp = i;
		}
	}
	if(mnp < mxp) {
		for(int i = 0; i < N; i++) {
			answer(i + 1, A[i] - mn + 1);
		}
	} else {
		for(int i = 0; i < N; i++) {
			answer(i + 1, mx - A[i] + 1);
		}
	}
	
	return;
}
