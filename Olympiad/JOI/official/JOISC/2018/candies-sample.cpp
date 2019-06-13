#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define mp make_pair
#define fi first
#define sc second
int n;
ll a[200005];
multiset<pair<ll,int> >M;
multiset<pair<int,ll> >rM;
ll ans[200005];
int main(){
	cin >> n;
	for(int i=1;i<=n;i++){
		cin >> a[i];
		M.insert(mp(-a[i],i));
		rM.insert(mp(i,-a[i]));
	}
	M.insert(mp(1e18,0)); M.insert(mp(1e18,n+1));
	rM.insert(mp(0,1e18)); rM.insert(mp(n+1,1e18));
	ans[0] = 0;
	for(int num=1;num<=(n+1)/2;num++){
		pair<ll,int> p = *M.begin();
		ans[num] = ans[num-1] - p.first;
		cout << ans[num] << endl;
		multiset<pair<int,ll> >::iterator it = rM.lower_bound(mp(p.sc,-1e18));
		it--;
		pair<int,ll>a = *it;
		M.erase(M.find(mp(a.sc,a.fi)));
		rM.erase(it++);
		pair<int,ll>b = *it;
		M.erase(M.find(mp(b.sc,b.fi)));
		rM.erase(it++);
		pair<int,ll>c = *it;
		M.erase(M.find(mp(c.sc,c.fi)));
		rM.erase(it++);
		rM.insert(mp(b.fi,a.sc+c.sc-b.sc));
		M.insert(mp(a.sc+c.sc-b.sc,b.fi));
	}
}