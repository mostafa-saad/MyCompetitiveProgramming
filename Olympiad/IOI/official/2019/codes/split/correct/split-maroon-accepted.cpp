#include "split.h"
#include <bits/stdc++.h>
using namespace std;

using ll=long long;
//#define int ll

#define rng(i,a,b) for(int i=int(a);i<int(b);i++)
#define rep(i,b) rng(i,0,b)
#define gnr(i,a,b) for(int i=int(b)-1;i>=a;i--)
#define per(i,b) gnr(i,0,b)
#define pb push_back
#define eb emplace_back
#define a first
#define b second
#define bg begin()
#define ed end()
#define all(x) x.bg,x.ed
#ifdef LOCAL
#define dmp(x) cerr<<__LINE__<<" "<<#x<<" "<<x<<endl
#else
#define dmp(x) void(0)
#endif

template<class t,class u> void chmax(t&a,u b){if(a<b)a=b;}
template<class t,class u> void chmin(t&a,u b){if(b<a)a=b;}

template<class t> using vc=vector<t>;
template<class t> using vvc=vc<vc<t>>;

using pi=pair<int,int>;
using vi=vc<int>;

template<class t,class u>
ostream& operator<<(ostream& os,const pair<t,u>& p){
	return os<<"{"<<p.a<<","<<p.b<<"}";
}

template<class t> ostream& operator<<(ostream& os,const vc<t>& v){
	os<<"{";
	for(auto e:v)os<<e<<",";
	return os<<"}";
}

const int nmmax=200010;

vc<pi> g[nmmax];
int ans[nmmax];
bool us[nmmax];

void puti(int v,int i,int&rem){
	if(ans[v]||rem==0)return;
	ans[v]=i;
	rem--;
	for(auto e:g[v])if(us[e.b])
		puti(e.a,i,rem);
}

bool vis[nmmax];
//find any spanning tree
void dfs1(int v,int pe){
	if(vis[v])return;
	vis[v]=1;
	if(pe!=-1)
		us[pe]=1;
	for(auto e:g[v])
		dfs1(e.a,e.b);
}

//find a centroid
int dfs2(int v,int p,int n){
	int s=1,mx=0;
	for(auto e:g[v])if(us[e.b]&&p!=e.a){
		int f=dfs2(e.a,v,n);
		if(f<=0)return f;
		chmax(mx,f);
		s+=f;
	}
	chmax(mx,n-s);
	if(mx*2<=n)return -v;
	return s;
}

void dfs3(int v,int p,vi&w){
	w.pb(v);
	for(auto e:g[v])if(us[e.b]&&p!=e.a)
		dfs3(e.a,v,w);
}

vector<int> find_split(int n, int a, int b, int c, vector<int> p, vector<int> q) {
	vc<pi> si{pi(a,1),pi(b,2),pi(c,3)};
	sort(all(si));
	
	int m=p.size();
	rep(i,m){
		g[p[i]].eb(q[i],i);
		g[q[i]].eb(p[i],i);
	}
	
	dfs1(0,-1);
	
	int r=-dfs2(0,-1,n);
	
	vvc<int> cmps;
	for(auto e:g[r])if(us[e.b]){
		vi w;
		dfs3(e.a,r,w);
		cmps.pb(w);
	}
	
	bool fd=false;
	for(auto w:cmps){
		if(int(w.size())>=si[0].a){
			ans[r]=-1;
			puti(w[0],si[0].b,si[0].a);
			ans[r]=0;
			puti(r,si[1].b,si[1].a);
			fd=true;
			break;
		}
	}
	if(!fd){
		vi idx(n,-1);
		rep(i,cmps.size())
			for(auto v:cmps[i])
				idx[v]=i;
		int z=idx[0];
		if(z==-1)return vi(n,0);
		int cur=cmps[z].size();
		vi ad(cmps.size());
		ad[z]=1;
		rep(i,m){
			int x=idx[p[i]],y=idx[q[i]];
			if(y==z)swap(x,y);
			if(x==z&&y!=-1&&!ad[y]){
				ad[y]=1;
				cur+=cmps[y].size();
				us[i]=1;
				if(cur>=si[0].a){
					ans[r]=-1;
					puti(0,si[0].b,si[0].a);
					ans[r]=0;
					puti(r,si[1].b,si[1].a);
					fd=true;
					break;
				}
			}
		}
	}
	if(!fd)return vi(n,0);
	
	assert(si[0].a==0);
	assert(si[1].a==0);
	rep(i,n)if(ans[i]==0)ans[i]=si[2].b;
	return vi(ans,ans+n);
}
