#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXM = 1000000;
const int MAXK = 50000;

struct query {
	long long row;
	int id;
	query(long long row = 0, int id = 0):
		row(row), id(id) {}
};

int n, m, k;
char w[MAXM+1];
int p[MAXM];
long long ans[MAXK];
vector<query> Q[26];

long long calc_pos(long long row) {
	long long a, b;
	if(row & 1) { 
		a = row; 
		b = (row+1)/2; 
	} else {
		a = row/2;
		b = row+1;
	}
	a %= m;
	b %= m;
	return a * b % m;
}

int f(int p1, int p2) {
	return p[p2] - (p1 != 0 ? p[p1-1] : 0);
}

long long solve(long long r) {
	int p = calc_pos(r-1);
	long long ans = 0;
	long long len = r-(m-p);
	if(p+r <= m) return f(p, p+r-1);
		else ans = f(p, m-1);
	ans += (long long)f(0, m-1) * (len/m);
	if(len%m) ans += f(0, len%m-1);
	return ans;
}

int main(void) {

	scanf("%d", &n);
	scanf("%s", w);

	m = strlen(w);

	scanf("%d", &k);
	for(int i = 0; i < k; ++i) {
		char c; long long a;
		scanf("%lld %c", &a, &c);
		Q[c-'A'].push_back(query(a, i));
	}

	for(int i = 0; i < 26; ++i) {
		for(int j = 0; j < m; ++j) {
			if(w[j]-'A' == i) p[j] = 1; else p[j] = 0;
			if(j > 0) p[j] += p[j-1];
		}
		for(int j = 0; j < Q[i].size(); ++j) 
			ans[Q[i][j].id] = solve(Q[i][j].row);
	}	

	for(int i = 0; i < k; ++i) printf("%lld\n", ans[i]);

	return 0;

}
