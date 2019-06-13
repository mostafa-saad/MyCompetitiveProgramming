#include <cstdio>
#include <vector>
#include <cstring>
#include <functional>
#include <algorithm>
#include <math.h>
#include <bitset>
#include <set>
#include <queue>
#include <assert.h>
#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <complex>
#include <numeric>
#include <map>
#include <time.h>
#include "library.h"
using namespace std;
typedef long double ld;
typedef long long ll;
typedef unsigned long long ull;
typedef unsigned int uint;
typedef pair<int,int> pii;
typedef pair<int,ll> pil;
typedef pair<int,ull> piu;
typedef pair<ull,ull> puu;
typedef pair<ll,int> pli;
typedef pair<ll,ll> pll;
typedef pair<pii,ll> ppl;
typedef pair<ll,pii> plp;
typedef pair<ll,pll> plP;
typedef pair<int,pii> pip;
typedef pair<pii,int> ppi;
typedef pair<pii,pii> ppp;
typedef pair<double,int> pdi;
typedef pair<int,double> pid;
typedef pair<double,pii> pdp;
typedef pair<double,double> pdd;
typedef pair<pdd,double> pd3;
typedef vector<ll> vec;
typedef vector<vec> mat;
#define rep(i,n) for (int (i) = 0; (i) < (n); (i)++)
#define repn(i,a,n) for (int (i) = (a); (i) < (n); (i)++)
#define ALL(x) (x).begin(),(x).end()
#define pb push_back
#define SORT(x) sort((x).begin(),(x).end())
#define SORTN(x,n) sort((x),(x)+(n))
#define ERASE(x) (x).erase(unique((x).begin(),(x).end()),(x).end())
#define COUNT(x,c) count((x).begin(),(x).end(),(c))
#define REMOVE(x,c) (x).erase(remove((x).begin(),(x).end(),(c)),(x).end())
#define REVERSE(x) reverse((x).begin(),(x).end())
#define FORIT(it,v) for(__typeof((v).begin()) it=(v).begin();it!=(v).end();it++)
#define LB(x,a) lower_bound((x).begin(),(x).end(),(a))-(x).begin()
#define lb(x,a) lower_bound((x).begin(),(x).end(),(a))
#define LBN(x,a,n) lower_bound((x),(x)+(n),(a))-(x)
#define lbN(x,a,n) lower_bound((x),(x)+(n),(a))
#define UB(x,a) upper_bound((x).begin(),(x).end(),(a))-(x).begin()
#define ub(x,a) upper_bound((x).begin(),(x).end(),(a))
#define BS(x,a) binary_search((x).begin(),(x).end(),(a))
#define BS2(x,n,a) binary_search((x),(x)+(n),(a))
#define NB(x) (((x)&~((x)+((x)&-(x))))/((x)&-(x))>>1)|((x)+((x)&-(x)))
#define NP(x) next_permutation((x).begin(),(x).end())
#define MM(x,p) memset((x),(p),sizeof(x))
#define SQ(x) (x)*(x)
#define SC(c1,c2) strcmp(c1,c2)==0
#define mp make_pair
#define INF (1<<29)
#define INFL (1LL<<61)
#define fi first
#define se second
#define EPS 1e-9
#define MOD 1000000007
#define MIN(x,a) x=min(x,a)
#define MAX(x,a) x=max(x,a)
#define madd(x,a) x=(x+a)%MOD
#define msub(x,a) x=(x+MOD-a)%MOD
#define OUTPUT(x) rep(__,x.size())printf("%d%c",x[__],__+1==x.size()?'\n':' ')

int N_;

int res[1001];
bool used[1001];

int calc(vector<int> h)
{
	vector<int> hh(N_,0);
	for(int i=0;i<h.size();i++)hh[h[i]-1]=1;
	return Query(hh);
}

pair<int,int> jud_s(vector<int> f)
{
	vector<int> fv;
	bitset<1001> bt;
	rep(i,f.size())bt.set(f[i]);
	rep(i,N_)if(res[i]>0)bt.set(res[i]);
	repn(i,1,N_+1)if(!bt.test(i))fv.pb(i);
	return mp(calc(f),calc(fv));
}
vector<pii> pending;
void sol_pos(int v,vector<int> f)
{
	if(f.size()==1)
	{
		pending.pb(mp(v,f[0]));
		return;
	}
	vector<int> h1,h2;
	rep(i,f.size()/2)h1.pb(f[i]);
	repn(i,f.size()/2,f.size())h2.pb(f[i]);
	pii c1=jud_s(h1);
	if((c1.fi+c1.se)%2==1)sol_pos(v,h2);
	else sol_pos(v,h1);
}

void sol(int l,int r,vector<int> f)
{
	if(l==r)
	{
		res[l]=f[0];
		used[f[0]]=true;
		return;
	}
	vector<int> h1,h2;
	rep(i,f.size()/2)h1.pb(f[i]);
	repn(i,f.size()/2,f.size())h2.pb(f[i]);
	pii c1=jud_s(h1);
	if((c1.fi+c1.se)%2==1)
	{
		if(c1.fi>c1.se)sol(l,r,h1);
		else sol(l,r,h2);
	}
	else
	{
		if(l==0&&r==N_-1)sol_pos(l,h1),sol_pos(r,h2);
		else
		{
			h1.pb(res[l-1]);
			int c1n=calc(h1);
			h1.pop_back();
			if(c1.fi==c1n)sol_pos(l,h1),sol_pos(r,h2);
			else sol_pos(l,h2),sol_pos(r,h1);
		}
	}
}

void Solve(int N)
{
	N_=N;
	MM(res,-1);
	int l=0,r=N-1;
	while(l<=r)
	{
		pending.clear();
		vector<int> h;
		bitset<1001> bt;
		rep(i,N)if(res[i]>0)bt.set(res[i]);
		repn(i,1,N+1)if(!bt.test(i))h.pb(i);
		sol(l,r,h);
		l++;r--;
		rep(_,pending.size())
		{
			int v=pending[_].fi;
			int val=pending[_].se;
			res[v]=val;
			used[val]=true;
		}
	}
	vector<int> rr;
	rep(i,N)rr.pb(res[i]);
	Answer(rr);
}
