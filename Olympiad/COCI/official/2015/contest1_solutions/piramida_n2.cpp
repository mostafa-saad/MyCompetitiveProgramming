#include <cstdio>
#include <cstring>

using namespace std;

const int MAXN = 1000;
const int MAXLEN = 100000;

int n, m, k;
char w[MAXLEN];
int broj[26][MAXN];

int main(void) {

	scanf("%d", &n);
	scanf("%s", w);
	m = strlen(w);

	int pos = 0;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= i; ++j) {
			broj[w[pos]-'A'][i-1]++;
			pos = (pos+1) % m;
		}
	}	

	scanf("%d", &k);
	for(int i = 0; i < k; ++i) {
		int a; char c;
		scanf("%d %c", &a, &c);
		printf("%d\n", broj[c-'A'][a-1]);
	}

	return 0;

}
