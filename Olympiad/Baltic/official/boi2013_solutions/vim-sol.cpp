#include <stdio.h>
#include <algorithm>
using namespace std;

const int NMAX = 70000;
const int S = 11;

char line[NMAX+10]; // the input
int Nin, N = 0, rewritecost = 0;
// input with characters converted to numbers from 0 to S-1 and 'e' removed
int text[NMAX+2];
bool must[NMAX+2]; // whether we have to reach this character

int dp1[NMAX][S];
int dp2[NMAX][S][S];

int main() {
	scanf("%d %s", &Nin, line);
	bool nextmust = false;
	for (int i = 0; i < Nin; i++) {
		if (line[i] == 'e') {
			rewritecost++;
			if (N) {
				rewritecost++;
				nextmust = true;
			}
		} else {
			must[N] = nextmust;
			nextmust = false;
			text[N] = line[i]-'a';
			N++;
		}
	}
	for (int s = 0; s < S; s++) {
		dp1[0][s] = 1E9;
		for (int t = 0; t < S; t++)
			dp2[0][s][t] = 1E9;
	}
	dp1[0][text[0]] = 0;
	for (int i = 1; i <= N; i++) {
		for (int s = 0; s < S; s++) {
			int h = 1E9;
			int p = text[i-1];
			if (p != s && !must[i-1])
				h = min(h, dp1[i-1][s]);
			h = min(h, dp1[i-1][p]+2);
			if (p != s)
				h = min(h, dp2[i-1][p][s]);
			h = min(h, dp2[i-1][p][p]+2);
			dp1[i][s] = h;
			for (int t = 0; t < S; t++) {
				h = 1E9;
				if (p != s)
					h = min(h, dp1[i-1][s]+3);
				h = min(h, dp1[i-1][p]+5);
				if (p != s && p != t)
					h = min(h, dp2[i-1][s][t]+1);
				if (p != s)
					h = min(h, dp2[i-1][s][p]+3);
				if (p != t)
					h = min(h, dp2[i-1][p][t]+3);
				h = min(h, dp2[i-1][p][p]+5);
				dp2[i][s][t] = h;
			}
		}
	}
	printf("%d\n", dp1[N][S-1]+rewritecost-2);
	return 0;
}
