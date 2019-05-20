#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct disj{
	int pa[600005];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int n, m, cnt[300005], sum;
int s[300005], e[300005], vis[300005];
vector<pi> gph[300005];
vector<int> v;
vector<tuple<int, int, int>> ans;

int dfs(int x, int p){
	vis[x] = 1;
	int ret = cnt[x];
	for(auto &i : gph[x]){
		if(i.second != p && dfs(i.second, x)){
			ans.emplace_back(1, s[i.first], e[i.first]);
			swap(s[i.first], e[i.first]);
			ret ^= 1;
		}
	}
	return ret;
}

int main(){
	scanf("%d %d",&n,&m);
	disj.init(n);
	for(int i=0; i<m; i++){
		scanf("%d %d",&s[i],&e[i]); 
		cnt[s[i]] ^= 1;
		if(disj.uni(s[i], e[i])){
			gph[s[i]].push_back(pi(i, e[i]));
			gph[e[i]].push_back(pi(i, s[i]));
		}
	}
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			if(dfs(i, -1)){
				puts("-1");
				return 0;
			}
		}
	}
	memset(cnt, 0, sizeof(cnt));
	disj.init(2*n);
	for(int i=0; i<m; i++){
		disj.uni(s[i] + n, e[i]);
		cnt[e[i]] ^= 1;
	}
	for(int i=2; i<=n; i++){
		if(disj.uni(1, i)){
			ans.emplace_back(2, 1, i);
			cnt[1] ^= 1;
			cnt[i] ^= 1;
		}
	}
	v.clear();
	for(int i=1; i<=n; i++) if(cnt[i]) v.push_back(i);
	for(int i=0; i<v.size(); i+=2) ans.emplace_back(2, v[i], v[i+1]);
	cout << ans.size() << endl;
	for(auto &i : ans) printf("%d %d %d\n", get<0>(i), get<1>(i), get<2>(i));
}
