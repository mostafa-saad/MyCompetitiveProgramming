#include <cstdio>
#include <algorithm>
using namespace std;
long long rsq[1000005], m[1000005], ans;
int n, k, fw[1000005], p;
void add(int x) { for (;x<=p;x+=x&(-x)) ++fw[x]; }
int val(int x) {
	int o = 0;
	for (;x;x-=x&(-x)) o+=fw[x];
	return o;
}
int main () {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; ++i) {
		scanf("%lld", &rsq[i]);
		rsq[i] += rsq[i-1];
		m[i] = rsq[i];
	}
	
	/* Discretization */
	sort(m, m+n+1);
	p = unique(m, m+n+1)-m;
	
	for (int i = 0; i <= n; ++i) {
		int it = upper_bound(m, m+p, rsq[i]-k)-m-1+1; //discretized value of rsq[i]-k then +1 (for 1-indexed fenwick)
		ans += val(it); 
		add(lower_bound(m, m+p, rsq[i])-m+1); //discretized value of rsq[i] then +1 (for 1-indexed fenwick)
	}
	printf("%lld\n", ans);
}
