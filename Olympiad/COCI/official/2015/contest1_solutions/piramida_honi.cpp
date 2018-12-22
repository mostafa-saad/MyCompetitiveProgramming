#include <cstdio>
#include <cassert>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXM = 100000;

int n, m, k;
char w[MAXM+1];
int p[26][MAXM];

int calc_pos(long long r) {
	long long a, b;
	if(r & 1) { 
		a = r; 
		b = (r+1)/2; 
	} else {
		a = r/2;
		b = r+1;
	}
	a %= m;
	b %= m;
	return a * b % m;
}

int f(int c, int p1, int p2) {
	return p[c][p2] - (p1 != 0 ? p[c][p1-1] : 0);
}

long long solve(long long r, int c) {
	int p = calc_pos(r-1);
	long long ans = 0;
	long long len = r-(m-p);
	if(p+r <= m) return f(c, p, p+r-1);
		else ans = f(c, p, m-1);
	ans += (long long)f(c, 0, m-1) * (len/m);
	if(len%m > 0) ans += f(c, 0, len%m-1);
	return ans;
}

int main(void) {

	scanf("%d", &n);
	scanf("%s", w);

	m = strlen(w);
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < 26; ++j) {
			if(w[i]-'A' == j) p[j][i] = 1;
			if(i > 0) p[j][i] += p[j][i-1];
		}
	}

	scanf("%d", &k);
	for(int i = 0; i < k; ++i) {
		char c; long long a;
		scanf("%lld %c", &a, &c);
		printf("%lld\n", solve(a, c-'A'));
	}

	return 0;

}
