#include <cstdio>
#include <algorithm>
#include <set>

using namespace std;

typedef long long llint;

const int MAXN = 300100;

int N, K;
pair<int, int> nakit[MAXN];
multiset<int> M;

bool cmp(const pair<int, int> &A, const pair<int, int> &B) {
	if(A.second != B.second) return A.second > B.second;
	return A.first < B.first;
}

int main(void) {
	
	scanf("%d%d", &N, &K);
	
	for(int i = 0; i < N; ++i)
		scanf("%d%d", &nakit[i].first, &nakit[i].second);
		
	sort(nakit, nakit + N, cmp);
		
	for(int i = 0; i < K; ++i) {
		int x; scanf("%d", &x);
		M.insert(x);
	}
	
	llint ans = 0;
	
	for(int i = 0; i < N; ++i) {
		if(M.empty()) break;
		if(M.lower_bound(nakit[i].first) != M.end()) {
			ans += nakit[i].second;
			M.erase(M.lower_bound(nakit[i].first));
		}
	}
	
	printf("%lld\n", ans);
	
	return 0;
	
}
