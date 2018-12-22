#include <cstdio>
#include <cstring>
using namespace std;

char a[2505][16], buff[16];
int p[2505];

int main() {
	int n;
	scanf("%d", &n);
	for (int i = 0; i < n; ++i)
		scanf("%s", a[i]);
	int sol = 0;
	for (int i = 0; i < n; ++i) {
		scanf("%s", buff);
		for (int j = 0; j < n; ++j)
			if (strcmp(buff, a[j]) == 0) {
				p[i] = j;
				for (int k = 0; k < i; ++k)
					sol += (p[k] < p[i]);
				break;
			}
	}
	printf("%d/%d\n", sol, n * (n - 1) / 2);
}
