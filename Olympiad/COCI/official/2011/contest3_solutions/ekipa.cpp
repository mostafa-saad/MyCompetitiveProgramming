#include <cstdio>
#include <algorithm>
#include <iostream>
#include <cassert>
#define MAXN 101

using namespace std;

double best[MAXN];

int main() {
	int n, m, k;
	
	scanf("%d%d%d", &n, &m, &k);
	
	for(int i = 0; i < m; ++i) {
		for(int j = 0; j < n; ++j) {	
			int s;
			double o;
			
			scanf("%d%lf", &s, &o);
			best[s-1] = max(best[s-1], o);
		}
	}
		
	sort(best, best+n, greater<double>());
	
	double sol = 0.0;
	for(int i = 0; i < k; ++i)
		sol += best[i];
		
	printf("%.1lf\n", sol);
	
	return 0;
}
