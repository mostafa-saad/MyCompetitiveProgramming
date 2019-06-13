#include<cstdio>
#include<vector>
#include<set>
#include<map>
#include<algorithm>
#define fi first
#define se second
#define rep(i,n) for(int i = 0; i < n; ++i)
using namespace std;
typedef pair<int,int> P;
typedef long long ll;

const int MX = 200005, INF = 2000020000;

ll ans;
P in[MX];

struct bit {
	vector<int> d;
	bit(int n):d(n+5,0){}
	void add(int i){ while(i < d.size()) ++d[i], i += i&-i;}
	int sum(int i){ int res = 0; while(i) res += d[i], i -= i&-i; return res;}
};

void f(P p[], int n){
	if(n <= 1) return;
	int c = n/2;
	f(p,c); f(p+c,n-c);
	set<int> s;
	vector<P> l, r; // cover range
	
	s.insert(INF);
	for(int i = c-1; i >= 0; --i){
		int x = *(s.lower_bound(p[i].se));
		l.push_back(P(p[i].se,x-1));
		s.insert(p[i].se);
	}
	s.clear(); s.insert(INF);
	for(int i = c; i < n; ++i){
		int x = -(*(s.lower_bound(-p[i].se)));
		r.push_back(P(x+1,p[i].se));
		s.insert(-p[i].se);
	}
	sort(l.begin(),l.end());
	sort(r.begin(),r.end());
	
	map<int,int> z; // compress axis
	rep(i,l.size()){
		z.insert(P(l[i].fi,0));
		z.insert(P(l[i].se,0));
	}
	rep(i,r.size()){
		z.insert(P(r[i].fi,0));
		z.insert(P(r[i].se,0));
	}
	int k = 1;
	for(map<int,int>::iterator it = z.begin(); it != z.end(); ++it) it->se = k++;
	
	bit d(k);
	
	// valid pair : R.first <= L.first <= R.second <= L.second
	k = 0;
	rep(i,l.size()){
		while(k < r.size() && r[k].fi <= l[i].fi) d.add(z[r[k++].se]);
		ans += d.sum(z[l[i].se])-d.sum(z[l[i].fi]-1);
	}
}

int main(){
	int n;
	scanf("%d",&n);
	rep(i,n) scanf("%d%d",&in[i].fi,&in[i].se);
	sort(in,in+n);
	
	f(in,n);
	
	printf("%lld\n",ans);
	
	return 0;
}
