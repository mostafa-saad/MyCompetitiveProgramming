#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int MAXN = 110;

int n, a[MAXN], ans[MAXN];
vector<int> v;

int main(void) {

	scanf("%d", &n);
	for(int i = 0; i < n; ++i)
		scanf("%d", a + i);

	for(int i = 0; i < n; ++i) {
		int t = 1;
		while(1) {
			v.push_back(t);
			if(a[i] / t == 0) break;
			t = a[i] / (a[i] / t) + 1;
		}
	}

	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());

	int tmp[110];

	memset(ans, -1, sizeof ans);

	for(int i = 0; i < v.size(); ++i) {
		for(int j = 0; j < n; ++j) 
			tmp[j] = a[j] / v[i];
		sort(tmp, tmp + n);
		for(int j = 0; j < n; ) {
			int t = j;
			while(t < n && tmp[t] == tmp[j]) ++t;
			if(ans[t - j] == -1) ans[t - j] = v[i];
			j = t;
		}
	}

	for(int i = 1; i <= n; ++i) 
		printf("%d\n", ans[i]);
	
	return 0;
		
}
