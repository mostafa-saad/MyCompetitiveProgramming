#include "catdog.h"
#include <bits/stdc++.h>
using namespace std;

using ll=long long;

#define FOR(i,a,b) for(int i=int(a);i<int(b);i++)
#define REP(i,b) FOR(i,0,b)

using vi=vector<int>;
#define PB push_back
using pi=pair<int,int>;

const ll inf64=LLONG_MAX/3;

template<class T,class U>
void chmin(T&t,const U&u){
	if(t>u)t=u;
}
template<class T,class U>
void chmax(T&t,const U&u){
	if(t<u)t=u;
}

struct SegTree{
	struct Node{
		ll cost[2][2];
	};
	vector<Node> buf;
	int s;
	void Init(int n){
		s=1;
		while(s<n)s*=2;
		buf.resize(s*2);
		FOR(i,s,s*2){
			buf[i].cost[0][0]=0;
			buf[i].cost[1][1]=0;
			buf[i].cost[0][1]=inf64;
			buf[i].cost[1][0]=inf64;
		}
		for(int i=s-1;i>=1;i--)
			Update(i);
	}
	void Update(int i){
		REP(a,2)REP(b,2)
			buf[i].cost[a][b]=inf64;
		REP(a,2)REP(b,2)REP(c,2)REP(d,2)
			chmin(buf[i].cost[a][d],buf[i*2].cost[a][b]+(b^c)+buf[i*2+1].cost[c][d]);
	}
	void Add(int i,int v0,int v1){
		i+=s;
		buf[i].cost[0][0]+=v0;
		buf[i].cost[1][1]+=v1;
		while(i>>=1)
			Update(i);
	}
	void Get(int&v0,int&v1){
		int a=min(buf[1].cost[0][0],buf[1].cost[0][1]);
		int b=min(buf[1].cost[1][0],buf[1].cost[1][1]);
		v0=min(a,b+1);
		v1=min(a+1,b);
	}
};
const int Nmax=100010;
int n,par[Nmax],sub[Nmax],grp[Nmax],pos[Nmax],gsz[Nmax],gpar[Nmax],gord,state[Nmax];
vi tr[Nmax];
SegTree segs[Nmax];
int dfs1(int v,int p){
	par[v]=p;
	sub[v]=1;
	for(auto to:tr[v])if(to!=p)
		sub[v]+=dfs1(to,v);
	return sub[v];
}
void dfs2(int v,int p,int g){
	grp[v]=g;
	if(gsz[g]==0)
		gpar[g]=p;
	pos[v]=gsz[g]++;
	pi si(0,-1);
	for(auto to:tr[v])if(to!=p)
		chmax(si,pi(sub[to],to));
	for(auto to:tr[v])if(to!=p){
		if(to==si.second)
			dfs2(to,v,g);
		else
			dfs2(to,v,gord++);
	}
}
void initialize(int N,vi A,vi B){
	n=N;
	REP(i,n-1){
		tr[A[i]-1].PB(B[i]-1);
		tr[B[i]-1].PB(A[i]-1);
	}
	dfs1(0,-1);
	dfs2(0,-1,gord++);
	REP(i,gord)
		segs[i].Init(gsz[i]);
}
int update(int v,int v0,int v1){
	while(v!=-1){
		int g=grp[v],cur0,cur1,nx0,nx1;
		segs[g].Get(cur0,cur1);
		segs[g].Add(pos[v],v0,v1);
		segs[g].Get(nx0,nx1);
		v0=nx0-cur0;
		v1=nx1-cur1;
		v=gpar[g];
	}
	int a,b;
	segs[0].Get(a,b);
	return min(a,b);
}
int cat(int v){
	v--;
	int ret=update(v,Nmax,0);
	state[v]=1;
	return ret;
}
int dog(int v){
	v--;
	int ret=update(v,0,Nmax);
	state[v]=2;
	return ret;
}
int neighbor(int v){
	v--;
	int ret;
	if(state[v]==1)
		ret=update(v,-Nmax,0);
	else
		ret=update(v,0,-Nmax);
	state[v]=0;
	return ret;
}
