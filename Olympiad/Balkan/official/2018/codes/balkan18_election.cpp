#include<bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 500005;
const int MAXT = 1050000;
 
int a[MAXN], nxt[19][MAXN], edg[19][MAXN];
char str[MAXN];
vector<pi> v;
 
struct seg{
	int tree[MAXT], lim;
	void init(int n, int *a){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + MAXT, -1e9);
		for(int i=0; i<n; i++) tree[i + lim] = a[i];
		for(int i=lim-1; i; i--) tree[i] = max(tree[2*i], tree[2*i+1]);
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = -1e9;
		while(s < e){
			if(s % 2 == 1) ret = max(ret, tree[s++]);
			if(e % 2 == 0) ret = max(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = max(ret, tree[s]);
		return ret;
	}
}seg;
 
int main(){
	int n; scanf("%d",&n);
	scanf("%s", str + 1);
	for(int i=1; i<=n; i++){
		if(str[i] == 'C') a[i] = a[i-1] + 1;
		else a[i] = a[i-1] - 1;
	}
	seg.init(n + 1, a);
	for(int i=0; i<=n; i++) v.push_back(pi(a[i], i));
	sort(v.begin(), v.end());
	for(int i=0; i<=n; i++){
		auto k = lower_bound(v.begin(), v.end(), pi(a[i] - 1, i));
		if(k == v.end() || k->first != a[i] - 1){
			nxt[0][i] = n + 1;
			edg[0][i] = -1e9;
		}
		else{
			nxt[0][i] = k->second;
			edg[0][i] = seg.query(i, nxt[0][i] - 1);
		}
	}
	nxt[0][n+1] = n+1;
	edg[0][n+1] = -1e9;
	for(int i=1; i<19; i++){
		for(int j=n+1; j>=0; j--){
			nxt[i][j] = nxt[i-1][nxt[i-1][j]];
			edg[i][j] = max(edg[i-1][j] - (1<<(i-1)), edg[i-1][nxt[i-1][j]]);
		}
	}
	int q; scanf("%d",&q);
	while(q--){
		int l, r;
		scanf("%d %d",&l,&r);
		l--;
		int dap = -1e9;
		int cnt = 0;
		for(int i=18; i>=0; i--){
			if(nxt[i][l] <= r){
				cnt += (1<<i);
				dap = max(dap - (1<<i), edg[i][l]);
				l = nxt[i][l];
			}
		}
		dap = max(dap - 1, seg.query(l, r));
		printf("%d\n", cnt + dap - a[r]);
	}
}