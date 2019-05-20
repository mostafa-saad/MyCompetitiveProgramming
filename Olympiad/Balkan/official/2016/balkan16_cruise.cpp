#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n;
struct pnt{
	int x, y, p, idx;
}a[2005];

int ccw(pnt a, pnt b, pnt c){
	int dx1 = b.x - a.x;
	int dy1 = b.y - a.y;
	int dx2 = c.x - a.x;
	int dy2 = c.y - a.y;
	return dx1 * dy2 - dy1 * dx2;
}

int dist(pnt a, pnt b){
	int dx = b.x - a.x;
	int dy = b.y - a.y;
	return dx * dx + dy * dy;
}

double dp[2005], dis[2005][2005];
int sum[2005][2005];

pnt low[2005][2005], high[2005][2005];
int sz1[2005], sz2[2005];

bool trial(double k){
	for(int i=n; i>=0; i--){
		dp[i] = -k * dis[0][i] + a[i].p;
		for(int j=i+1; j<=n; j++){
			dp[i] = max(dp[i], dp[j] + sum[i][j] - k * dis[i][j] + a[i].p);
		}
	}
	double ret = -1e9;
	for(int i=1; i<=n; i++){
		ret = max(ret, dp[i] - k * dis[0][i]);
	}
	return (ret >= 0);
}

struct bit{
	int tree[2005];
	void init(){ memset(tree, 0, sizeof(tree)); }
	void add(int x, int v){
		while(x <= n){
			tree[x] += v;
			x += x & -x;
		}
	}
	int sum(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

int main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		cin >> a[i].x >> a[i].y >> a[i].p;
	}
	sort(a+1, a+n+1, [&](const pnt &p, const pnt &q){
		int t = ccw(a[0], p, q);
		if(t != 0) return t > 0;
		return dist(a[0], p) < dist(a[0], q);
	});
	for(int i=0; i<=n; i++){
		for(int j=i+1; j<=n; j++){
			dis[i][j] = sqrt(dist(a[i], a[j]));
		}
		a[i].idx = i;
	}
	for(int i=0; i<=n; i++){
		for(int j=0; j<i; j++){
			low[i][sz1[i]] = a[j];
			sz1[i]++;
		}
		for(int j=i+1; j<=n; j++){
			high[i][sz2[i]] = a[j];
			sz2[i]++;
		}
		sort(low[i], low[i] + sz1[i], [&](const pnt &p, const pnt &q){
			return ccw(a[i], p, q) < 0;
		});
		sort(high[i], high[i] + sz2[i], [&](const pnt &p, const pnt &q){
			return ccw(a[i], p, q) < 0;
		});
		int st = i+1;
		while(st <= n && ccw(a[0], a[i], a[st]) == 0) st++;
		int p = 0;
		bit.init();
		for(int j=0; j<sz2[i]; j++){
			while(p < sz2[i] && ccw(a[i], high[i][j], high[i][p]) >= 0){
				if(high[i][p].idx >= st){
					bit.add(high[i][p].idx, high[i][p].p);
				}
				p++;
			}
			sum[i][high[i][j].idx] = bit.sum(high[i][j].idx - 1);
		}
	}
	double s = 0, e = 8000;
	for(int i=0; i<45; i++){
		double m = (s+e)/2;
		if(trial(m)) s = m;
		else e = m;
	}
	printf("%.9f", s);
}

