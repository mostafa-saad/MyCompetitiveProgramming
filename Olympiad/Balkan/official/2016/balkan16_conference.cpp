#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, m, k, s[1000005], e[1000005];
int ok[1000005];
int ans1[1000005], ans2[1000005], ans3[1000005], ans4[1000005], ans5[1000005];
int main(){
	cin >> n >> m >> k;
	for(int i=0; i<m; i++) scanf("%d %d",&s[i],&e[i]);
	memset(ans1, -1, sizeof(ans1));
	memset(ans3, -1, sizeof(ans3));
	memset(ans4, -1, sizeof(ans4));
	memset(ans5, 0x3f, sizeof(ans5));
	for(int i=k+1; i<=n; i++){
		ok[i] = 1;
	}
	for(int i=m-1; i>=0; i--){
		if(ok[s[i]] == ok[e[i]]) continue;
		if(!ok[s[i]]) swap(s[i], e[i]);
		ok[e[i]] = 1;
		ans1[e[i]] = i + 1;
	}
	for(int i=1; i<=k; i++) printf("%d ", ans1[i]);
	puts("");
	memset(ok, 0, sizeof(ok));
	for(int i=0; i<m; i++){
		if(ans1[s[i]] == i + 1) ok[s[i]] = 1;
		if(ans1[e[i]] == i + 1) ok[e[i]] = 1;
		if(ok[s[i]]) ok[e[i]] = 1;
		if(ok[e[i]]) ok[s[i]] = 1;
	}
	printf("%d ", count(ok + k + 1, ok + n + 1, true));
	for(int i=k+1; i<=n; i++) if(ok[i]) printf("%d ", i);
	puts("");
	for(int i=m-1; i>=0; i--){
		if(s[i] > k && e[i] > k) continue;
		if(s[i] > k) swap(s[i], e[i]);
		if(e[i] > k){
			ans4[s[i]] = e[i];
			ans5[s[i]] = i;
		}
		else{
			if(ans5[s[i]] < ans5[e[i]]) swap(s[i], e[i]);
			ans4[s[i]] = ans4[e[i]];
			ans5[s[i]] = ans5[e[i]];
		}
		if(ans1[s[i]] == i + 1){
			ans3[s[i]] = ans4[s[i]];
		}
		if(ans1[e[i]] == i + 1){
			ans3[e[i]] = ans4[e[i]];
		}
	}
	for(int i=1; i<=k; i++) printf("%d ", ans3[i]);
}
