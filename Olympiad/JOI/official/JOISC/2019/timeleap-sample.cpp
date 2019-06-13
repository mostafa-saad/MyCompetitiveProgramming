#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#define SIZE 300005
#define BT 512*1024*2
#define MX 10000000000LL

using namespace std;
typedef long long int ll;

struct DT
{
	ll l,s,t;
	ll cost;
	DT(ll l=-MX,ll s=-MX,ll t=MX,ll cost=0):l(l),s(s),t(t),cost(cost){}
	ll f(ll x)
	{
		if(x<=l) return s;
		return min(t,s+x-l);
	}
	ll g(ll x)
	{
		return cost+max(0LL,x-l-(t-s));
	}
};
DT merge(DT l,DT r)
{
	DT ret;
	ret.s=r.f(l.s);
	ret.t=r.f(l.t);
	ret.l=min(l.l+l.t-l.s,l.l+max(0LL,r.l-l.s));
	ret.cost=l.cost+r.g(l.s);
	return ret;
}
struct segtree
{
	DT seg[BT];
	int mum;
	
	void init(int n)
	{
		mum=1;
		while(mum<n) mum<<=1;
		for(int i=0;i<mum*2;i++) seg[i]=DT();
	}
	void add(int k,int L,int R)
	{
		k+=mum-1;
		seg[k]=DT(L,L,R,0);
		while(k>0)
		{
			k=(k-1)/2;
			seg[k]=merge(seg[k*2+1],seg[k*2+2]);
		}
	}
	DT get(int a,int b,int k,int l,int r)
	{
		if(b<=l||r<=a) return DT();
		if(a<=l&&r<=b) return seg[k];
		else
		{
			DT vl=get(a,b,k*2+1,l,(l+r)/2);
			DT vr=get(a,b,k*2+2,(l+r)/2,r);
			return merge(vl,vr);
		}
	}
	DT get(int a,int b)
	{
		if(a==b) return DT();
		return get(a,b,0,0,mum);
	}
}seg;
struct Query
{
	int T;
	int P,S,E;
	int A,B,C,D;
	Query(){}
	void type1(int P_,int S_,int E_)
	{
		T=1;
		P=P_,S=S_,E=E_;
	}
	void type2(int A_,int B_,int C_,int D_)
	{
		T=2;
		A=A_,B=B_,C=C_,D=D_;
	}
};
Query query[SIZE];
int L[SIZE],R[SIZE];
ll ans[SIZE];
int n,q;

void solve()
{
	seg.init(n+2);
	for(int i=0;i<n-1;i++) seg.add(i,L[i]-i,R[i]-i-1);
	for(int i=0;i<q;i++)
	{
		if(query[i].T==1)
		{
			int v=query[i].P;
			seg.add(v,query[i].S-v,query[i].E-v-1);
		}
		else if(query[i].A<=query[i].C)
		{
			DT d=seg.get(query[i].A,query[i].C);
			ans[i]=d.g(query[i].B-query[i].A)+max(0LL,d.f(query[i].B-query[i].A)-(query[i].D-query[i].C));
		}
	}
}
int main()
{
	scanf("%d %d",&n,&q);
	for(int i=0;i<n-1;i++) scanf("%d %d",&L[i],&R[i]);
	for(int i=0;i<q;i++)
	{
		int T;
		scanf("%d",&T);
		if(T==1)
		{
			int P,S,E;
			scanf("%d %d %d",&P,&S,&E);P--;
			query[i].type1(P,S,E);
		}
		else
		{
			int A,B,C,D;
			scanf("%d %d %d %d",&A,&B,&C,&D);A--,C--;
			query[i].type2(A,B,C,D);
		}
	}
	solve();
	for(int l=0,r=n-2;l<r;l++,r--) swap(L[l],L[r]),swap(R[l],R[r]);
	for(int i=0;i<q;i++)
	{
		if(query[i].T==1)
		{
			query[i].P=n-query[i].P-2;
		}
		else
		{
			query[i].A=n-query[i].A-1;
			query[i].C=n-query[i].C-1;
		}
	}
	solve();
	for(int i=0;i<q;i++)
	{
		if(query[i].T==2)
		{
			printf("%lld\n",ans[i]);
		}
	}
	return 0;
}
