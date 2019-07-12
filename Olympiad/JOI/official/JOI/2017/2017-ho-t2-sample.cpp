#include<cstdio>
#include<vector>
#include<algorithm>

using namespace std;

const int MAX_M = 3000;

int N, M, K;
long long A, B, C;
long long T;
int s[MAX_M];

int nums[3000 * 3000];
int c = 0;

int getNums(int l, int r){
	int res = 0;
	long long t = B * l;
	int id = l;
	int cnt = 0;
	while(id < r){
		long long x = T - t;
		if(x < 0) break;
		x /= A;
		long long nxt = id + x + 1;
		nxt = min((long long)r, nxt);
		if(id == l) res = nxt - id;
		else nums[c++] = nxt - id;
		t += C * (nxt - id);
		id = nxt;
		cnt++;
		if(cnt > K - M) break;
	}
	return res;
}


int solve(){
	int ans = B * s[M - 1] <= T ? 1 : 0;
	for(int i = 0; i < M - 1; ++i){
		ans += getNums(s[i], s[i + 1]);
	}
	sort(nums, nums + c);
	reverse(nums, nums + c);
	for(int i = 0; i < K - M; ++i){
		ans += nums[i];
	}
	return ans - 1;
}

void input(){
	scanf("%d%d%d", &N, &M, &K);
	scanf("%lld%lld%lld", &A, &B, &C);
	scanf("%lld", &T);
	for(int i = 0; i < M; ++i){
		scanf("%d", s + i);
		s[i]--;
	}
}

int main(){
	input();
	int ans = solve();
	printf("%d\n", ans);
	return 0;
}
