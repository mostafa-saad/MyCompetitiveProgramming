#include <cstdio>
#include <algorithm>
using namespace std;

const int M = 1000000;
int lijevo[2][M+2], desno[2][M+2];

int main() {
	int n;
	scanf("%d", &n);
	for(int i=0; i<n; ++i) {
		int a, b, c, d, e, f;
		scanf("%d%d%d%d%d%d", &a, &b, &c, &d, &e, &f);
		int lox = min(a, min(c, e));
		int loy = min(b, min(d, f));
		int hix = max(a, max(c, e));
		int hiy = max(b, max(d, f));
		lijevo[0][hix]++;
		lijevo[1][hiy]++;
		desno[0][lox]++;
		desno[1][loy]++;
	}
	for(int i=1; i<=M; i++)
		for(int k=0; k<2; ++k)
			lijevo[k][i] += lijevo[k][i-1];
	for(int i=M-1; i>=0; i--)
		for(int k=0; k<2; ++k)
			desno[k][i] += desno[k][i+1];
	int q;
	scanf("%d", &q);
	while(q--) {
		char c;
		int x;
		scanf(" %c = %d", &c, &x);
		int k = (c == 'y');
		//printf("k=%d, x=%d, n=%d, lijevo[k][x]=%d, desno[k][x]=%d sol=",k,x,n,lijevo[k][x],desno[k][x]);
		printf("%d\n", n - lijevo[k][x] - desno[k][x]);
	}
	return 0;
}
