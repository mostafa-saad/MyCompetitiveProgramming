#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int N, X;
char s[1010];
char tmp[1010];
int perm[1010], perm2[1010];

bool visited[1010];
int go(int x) {
	int ret = 0;
	while(!visited[x]) {
		++ret;
		visited[x] = 1;
		x = perm[x];
	}
	return ret;
}


int main(void) {

	scanf("%d%s", &X, s);
	N = strlen(s);

	if(N <= 2) { 
		printf("%s\n", s);
		return 0;
	}

	for(int i = 0; i < N; ++i) perm2[i] = i;
	for(int i = 0; i < N / 2; ++i) {
		perm[2 * i] = perm2[i];
		perm[2 * i + 1] = perm2[N - i - 1];
	}
	if(N & 1) perm[N - 1] = perm2[N / 2];


	int ciklus = 1;
	for(int i = 0; i < N; ++i) {
		if(visited[i]) continue;
		int t = go(i);
		ciklus = ciklus * t / __gcd(ciklus, t);
	}

	X %= ciklus;
	X = ciklus - X;

	for(int i = 0; i < X; ++i) {
		for(int j = 0; j < N / 2; ++j) {
			tmp[2 * j] = s[j];
			tmp[2 * j + 1] = s[N - j - 1];
		}
		if(N & 1) tmp[N - 1] = s[N / 2];
		memcpy(s, tmp, sizeof s);
	}

	printf("%s\n", s);

	return 0;

}
