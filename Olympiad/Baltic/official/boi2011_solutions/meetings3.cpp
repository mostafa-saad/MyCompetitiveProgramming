// BOI 2011
// Task MEETINGS
// Konstantin Tretyakov, konstantin.tretjakov@ut.ee

#include <iostream>
#include <cmath>
using namespace std;

// Computes N^k
long long power(long long N, int k) {
	// k is so small we don't need anything complicated here,
	// but the floating-point pow() could introduce rounding errors
	long long result = 1;
	for (int i = 0; i < k; i++) {
		result *= N;
	}
	return result;
}

// Computes the best possible time with k divisors
long long solve(long long N, int P, int V, int k) {
	long long divisor = (long long) pow(N, 1.0 / k);
	// since the divisors were rounded down above, we now increase
	// some of them by 1 to have them multiply to at least N
	int increased = 0;
	while (power(divisor + 1, increased) * power(divisor, k - increased) < N) {
		++increased;
	}
	// the answer is \sum(divisors)*P + k*V
	return (k * divisor + increased) * P + k * V;
}

int main() {
	long long N, P, V;
	cin >> N >> P >> V;
	if (N == 1) {
		cout << 0 << endl;
	} else {
		long long result = solve(N, P, V, 1);
		for (int i = 2; 2LL << i <= N; i++) {
			long long r = solve(N, P, V, i);
			if (result > r) {
				result = r;
			}
		}
		cout << result << endl;
	}
	return 0;
}
