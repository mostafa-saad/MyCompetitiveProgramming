#include "bubblesort2.h"

#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=int(a);i<int(b);i++)
#define REP(i,b) FOR(i,0,b)
#define ALL(x) x.begin(),x.end()
#define PB push_back

using vi=vector<int>;
using pi=pair<int,int>;
const int inf=INT_MAX/2;

struct SegTree{
	vi mx,lz;
	int s;
	SegTree(int n){
		s=1;
		while(s<n)s*=2;
		mx.resize(s*2,0);
		lz.resize(s*2,0);
	}
	void Propagate(int i){
		mx[i]+=lz[i];
		lz[i*2]+=lz[i];
		lz[i*2+1]+=lz[i];
		lz[i]=0;
	}
	int Get(int i){
		return mx[i]+lz[i];
	}
	void Add(int b,int e,int v,int l,int r,int i){
		if(e<=l||r<=b)return;
		if(b<=l&&r<=e){
			lz[i]+=v;
			return;
		}
		Propagate(i);
		Add(b,e,v,l,(l+r)/2,i*2);
		Add(b,e,v,(l+r)/2,r,i*2+1);
		mx[i]=max(Get(i*2),Get(i*2+1));
	}
	void Add(int b,int e,int v){
		if(b<e)
			Add(b,e,v,0,s,1);
	}
	int Get(){
		return Get(1);
	}
};

vector<int> countScans(vector<int> a,vector<int> x,vector<int> v){
	int n=a.size(),q=x.size();
	
	vector<pi> crd;
	REP(i,n)crd.PB(pi(a[i],i));
	REP(i,q)crd.PB(pi(v[i],x[i]));
	sort(ALL(crd));
	crd.erase(unique(ALL(crd)),crd.end());
	
	int s=crd.size();
	SegTree seg(s);
	seg.Add(0,s,-inf);
	
	const auto Ins=[&](int p,int r){
		int i=lower_bound(ALL(crd),pi(p,r))-crd.begin();
		seg.Add(i,i+1,inf+r);
		seg.Add(i+1,s,-1);
	};
	const auto Ers=[&](int p,int r){
		int i=lower_bound(ALL(crd),pi(p,r))-crd.begin();
		seg.Add(i,i+1,-(inf+r));
		seg.Add(i+1,s,1);
	};
	
	REP(i,n)
		Ins(a[i],i);
	
	vi res(q);
	REP(i,q){
		Ers(a[x[i]],x[i]);
		Ins(v[i],x[i]);
		a[x[i]]=v[i];
		res[i]=seg.Get();
	}
	
	return res;
}
