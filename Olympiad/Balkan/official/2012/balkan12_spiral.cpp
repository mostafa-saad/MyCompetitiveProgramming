#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 1005;
const int inf = 1e9;

int n, k;
pi a[2005];
int ok[1005][1005];
int ly[1005][1005], hy[1005][1005], lx[1005][1005], hx[1005][1005];
 
struct seg{
	struct node{
		int ret, l, r;
	}tree[2050];
	int lim;
	node base;
	node merge(node &l, node &r){
		node ret;
		ret.ret = max(l.ret, r.ret);
		ret.ret = max(ret.ret, r.r - l.l);
		ret.r = max(r.r, l.r);
		ret.l = min(l.l, r.l);
		return ret;
	}
	void init(int n){
		base = (node){-inf, inf, -inf};
		fill(tree, tree + 2050, base);
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void add(int x, int f1, int f2){
		node v;
		v.ret = -inf, v.l = f1, v.r = f2;
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = merge(tree[2*x], tree[2*x+1]);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		node lv = base, rv = base;
		while(s < e){
			if(s%2 == 1) lv = merge(lv, tree[s++]);
			if(e%2 == 0) rv = merge(tree[e--], rv);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) lv = merge(lv, tree[s]);
		return merge(lv, rv).ret;
	}
}seg;
 
vector<int> swp[MAXN];
int aux1[MAXN];
pi aux2[MAXN];

int solve(){
	memset(ok, 0, sizeof(ok));
	for(int i=0; i<k; i++){
		ok[a[i].first][a[i].second] = 1;
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(ok[i][j]) ly[i][j] = j;
			else ly[i][j] = ly[i][j-1];
		}
		hy[i][n+1] = inf;
		for(int j=n; j; j--){
			if(ok[i][j]) hy[i][j] = j;
			else hy[i][j] = hy[i][j+1]; 
		}
		for(int j=1; j<=n; j++){
			if(ok[i][j]) lx[i][j] = i;
			else lx[i][j] = lx[i-1][j];
		}
	}
	memset(hx[n+1], 0x3f, sizeof(hx[n+1]));
	for(int i=n; i; i--){
		for(int j=1; j<=n; j++){
			if(ok[i][j]) hx[i][j] = i;
			else hx[i][j] = hx[i+1][j];
		}
	}
	int ret = 0;
	for(int i=1; i<=n; i++){
		set<int> s;
		fill(aux1, aux1 + n + 1, -1e9);
		for(int j=0; j<=n; j++) swp[j].clear();
		for(int j=1; j<=n; j++){
			if(i - 1 > lx[i][j]) aux1[j] = -lx[i][j] - j;
			swp[min(i-1, lx[i][j])].push_back(j);
			aux2[j] = pi(2 * j + lx[i][j], 2 * j);
		}
		seg.init(n);
		for(int j=1; j<=n; j++){
			if(ly[i][j] + 1 < j) aux1[j] = max(aux1[j], aux1[j-1]);
		}
		for(int j=1; j<i; j++){
			for(auto &k : swp[j - 1]){
				s.insert(k);
				seg.add(k, 2 * k + lx[i][k], 2 * k);
			}
			vector<int> v;
			int p1 = hy[i][1], p2 = hy[j][1];
			int prv = 0;
			while(p1 <= n || p2 <= n){
				if(p1 <= p2){
					if(prv + 1 <= p1 - 1){
						ret = max(ret, i + i - j - 1 + seg.query(prv + 1, p1 - 1));
					}
					prv = p1;
					p1 = hy[i][p1+1];
				}
				else{
					if(prv + 1 <= p2 - 1){
						ret = max(ret, i + i - j - 1 + seg.query(prv + 1, p2 - 1));
					}
					prv = p2;
					p2 = hy[j][p2+1];
				}
			}
			if(prv + 1 <= n){
				ret = max(ret, i + i - j - 1 + seg.query(prv + 1, n));
			}
			for(int k=1; k<=n; k=hy[j][k] + 1){
				if(ok[j][k-1]){
					int bound = min(hy[j][k], hy[i][k]);
					auto t = s.lower_bound(bound);
					if(t != s.begin()){
						t = prev(t);
						if(*t > k && ly[i][k] + 1 < k){
							ret = max(ret, i + *t + aux1[k-1] + i - j + *t - k);
						}
					}
				}
			}
		}
	}
	return ret;
}
 
int main(){
	scanf("%d %d",&n,&k);
	for(int i=0; i<k; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
	}
	int ret = 0;
	for(int i=0; i<4; i++){
		ret = max(ret, solve());
		for(int j=0; j<k; j++){
			a[j].second = n + 1 - a[j].second;
		}
		ret = max(ret, solve());
		for(int j=0; j<k; j++){
			a[j].second = n + 1 - a[j].second;
		}
		for(int j=0; j<k; j++){
			a[j] = pi(a[j].second, n + 1 - a[j].first);
		}
	}
	printf("%d",ret);
}

