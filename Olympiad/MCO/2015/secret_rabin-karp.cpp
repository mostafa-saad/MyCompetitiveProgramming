#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>
#include <bitset>
#include <queue>

using namespace std;


long long MOD = 100000007LL;
long long HASH1 = 10000003LL;

long long seq1[200005];
long long seq2[100005];

int main () {
	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		int tmp;
	    scanf("%d", &tmp);
		seq1[i] = tmp;
	}
	for (int i = 0; i < N; i++) {
		seq1[i + N] = seq1[i];
	}

	for (int i = 0; i < N; i++) {
		int tmp;
		scanf("%d", &tmp);
		seq2[i] = tmp;
	}

	bool success = false;

	// Is seq2 a contiguous subsequence of seq1?
	long long seq2hash = 0;
	for (int i = 0; i < N; i++) {
		seq2hash += seq2[i];
		seq2hash *= HASH1;
		seq2hash %= MOD;
	}

	long long rollingHash = 0;
	for (int i = 0; i < N; i++) {
		rollingHash += seq1[i];
		rollingHash *= HASH1;
		rollingHash %= MOD;
	}

	long long base = 1;
	for (int i = 0; i < N+1; i++) {
		base *= HASH1;
		base %= MOD;
	}

	for (int i = N; i < 2*N; i++) {
		if (rollingHash == seq2hash) {
			bool good = true;
			for (int j = 0; j < N; j++) {
				if (seq2[j] != seq1[i-N+j]) {
					good = false;
					break;
				}
			}

			if (good) {
				success = true;
				break;
			}
		}

		rollingHash += seq1[i];
		rollingHash *= HASH1;
		rollingHash %= MOD;
		rollingHash += (MOD - (seq1[i - N] * base) % MOD);
		rollingHash %= MOD;
	}

    if (success) cout << "YES\n";
    else cout << "NO\n";
}
