#include <cstdio>

using namespace std;

const int MAXK = 10;

int k, v[1 << MAXK];
int ans[1 << MAXK];

int pos = 0;

void solve(int t) {
	if(t >= 1 << k) return;
	solve(2 * t);
	ans[t] = v[pos++];
	solve(2 * t + 1);
}

int main(void) {

	scanf("%d", &k);
	for(int i = 0; i < (1 << k) - 1; ++i)
		scanf("%d", v + i);

	solve(1);

	int start = 1;
	for(int i = 0; i < k; ++i) {
		for(int j = start; j < 2 * start; ++j)
			printf("%d ", ans[j]);
		printf("\n");
		start *= 2;
	}

	return 0;

}
