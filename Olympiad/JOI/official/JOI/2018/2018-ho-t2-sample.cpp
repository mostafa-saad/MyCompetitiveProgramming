#include <cstdio>
#include <algorithm>
using namespace std;

int N;
pair<long long, int> X[505050];

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; ++i) {
		long long A; int B;
		scanf("%lld%d", &A, &B);
		X[i] = make_pair(A, B);
	}
	sort(X, X + N);
	long long ret = 0, acc = 0, lo = 0;
	for (int i = 0; i < N; ++i) {
		lo = min(lo, acc - X[i].first);
		acc += X[i].second;
		ret = max(ret, acc - X[i].first - lo);
	}
	printf("%lld\n", ret);
	return 0;
}
