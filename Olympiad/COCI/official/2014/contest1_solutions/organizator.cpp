#include <cstdio>
#include <algorithm>

using namespace std;

const int MAXV = 2000010;

int N, num[MAXV];

int main(void) {

	scanf("%d", &N);
	
	for(int i = 0; i < N; ++i) {
		int x; scanf("%d", &x);
		++num[x];
	}
	
	long long sol = N;
	
	for(int i = 1; i <= 2000000; ++i) {
		int curr = 0;
		for(int j = i; j <= 2000000; j += i)
			curr += num[j];
		if(curr > 1) sol = max(sol, (long long)curr * i);
	}
	
	printf("%lld\n", sol);

  return 0;

}
