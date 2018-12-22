#include <cstdio>
using namespace std;

int s[1001][1001];

int main () {
	int n;
	scanf ("%d", &n);
	if (n == 2) {
		printf ("1 1\n");
		return 0;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			scanf ("%d", &s[i][j]);
	int suma_prva_tri = (s[0][1] + s[0][2] + s[1][2]) / 2;
	int a = suma_prva_tri - s[1][2];
	printf("%d", a);
	for (int i = 1; i < n; i++)
		printf(" %d", s[0][i] - a);
	printf("\n");
}
