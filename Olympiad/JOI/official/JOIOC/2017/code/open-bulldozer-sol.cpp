#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;

typedef long long ll;

const int MAX_N = 4002;
const int seg_siz = 1<<13;
const ll INF = 10000000000000;

struct SEG{
	ll s[seg_siz],t[seg_siz],u[seg_siz];
	int siz = seg_siz>>1;
	void init(){
		for(int i = 0 ; i < siz*2-1 ; i ++){
			s[i] = -INF;
			t[i] = INF;
			u[i] = 0;
		}
	}
	void update(int k,ll x){
		k += siz-1;
		s[k] = x;
		t[k] = x;
		while(k > 0){
			k = (k-1)/2;
			s[k] = max(s[2*k+1],s[2*k+2]);
			t[k] = min(t[2*k+1],t[2*k+2]);
			u[k] = max(u[2*k+1],u[2*k+2]);
			u[k] = max(u[k],s[2*k+2]-t[2*k+1]);
		}
	}
}seg;

int main(){
	int n;
	ll x[MAX_N],y[MAX_N],w[MAX_N];
	scanf("%d",&n);
	for(int i = 0 ; i < n ; i ++){
		scanf("%lld%lld%lld",&x[i],&y[i],&w[i]);
	}
	
	vector<pair<pair<ll,ll>,ll>> Points;
	for(int i = 0 ; i < n ; i ++){
		Points.push_back(pair<pair<ll,ll>,ll>(pair<ll,ll>(x[i],y[i]),w[i]));
	}
	sort(Points.begin(),Points.end());
	for(int i = 0 ; i < n ; i ++){
		x[i] = Points[i].first.first;
		y[i] = Points[i].first.second;
		w[i] = Points[i].second;
	}
	
	vector<pair<pair<ll,ll>,pair<int,int>>> Swap;
	for(int i = 0 ; i < n ; i ++){
		for(int j = 0 ; j < n ; j ++){
			if(x[i] < x[j])Swap.push_back(pair<pair<ll,ll>,pair<int,int>>(pair<ll,ll>(y[i]-y[j],x[j]-x[i]),pair<int,int>(min(i,j),max(i,j))));
		}
	}
	sort(Swap.begin(),Swap.end(),
		[](pair<pair<ll,ll>,pair<int,int>> a,pair<pair<ll,ll>,pair<int,int>> b){
			if(a.first.first*b.first.second == a.first.second*b.first.first){
				return a.second > b.second;
			}
			else return a.first.first*b.first.second > a.first.second*b.first.first;
		}
	);
	
	ll s[MAX_N] = {};
	s[0] = 0;
	for(int i = 1 ; i <= n ; i ++){
		s[i] = s[i-1]+w[i-1];
	}
	int t[MAX_N] = {};
	for(int i = 0 ; i < n ; i ++){
		t[i] = i+1;
	}
	
	seg.init();
	for(int i = 0 ; i <= n ; i ++){
		seg.update(i,s[i]);
	}
	ll ret = seg.u[0];
	
	for(int i = 0 ; i < Swap.size() ; i ++){
		pair<int,int> p = Swap[i].second;
		s[t[p.first]] += s[t[p.first]+1] - 2*s[t[p.first]] + s[t[p.first]-1];
		seg.update(t[p.first],s[t[p.first]]);
		swap(t[p.first],t[p.second]);
		
		if(i == Swap.size()-1){
			ret = max( ret , seg.u[0] );
			break;
		}
		pair<ll,ll> q = Swap[i].first , r = Swap[i+1].first;
		if(q.first*r.second != q.second*r.first){
			ret = max( ret , seg.u[0] );
		}
	}
	
	cout << ret << endl;
}
