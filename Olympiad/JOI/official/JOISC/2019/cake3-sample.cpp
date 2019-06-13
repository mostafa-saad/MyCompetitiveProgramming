#include <cstdio>
#include <cstdlib>
#include <algorithm>
#include <vector>
#include <cstring>
#include <queue>
#include <set>
#include <map>
#define SIZE 200005
#define BT 256*1024*2
#define INF 1000000000000000LL

using namespace std;
typedef long long int ll;
typedef pair <int,int> P;
typedef pair <P,P> PP;

vector <P> vx;
struct segtree
{
	ll seg[BT];
	int cnt[BT];
	int mum;
	
	void init(int n)
	{
		mum=1;
		while(mum<n) mum<<=1;
		for(int i=0;i<mum*2;i++) seg[i]=0,cnt[i]=0;
	}
	void add(int k,int v)
	{
		k+=mum-1;
		cnt[k]+=v;
		seg[k]+=vx[k-mum+1].first*v;
		while(k>0)
		{
			k=(k-1)/2;
			seg[k]=seg[k*2+1]+seg[k*2+2];
			cnt[k]=cnt[k*2+1]+cnt[k*2+2];
		}
	}
	ll get(int X)
	{
		if(cnt[0]<X) return -1;
		if(cnt[0]==X) return seg[0];
		ll ret=0;
		int l=0,r=mum,k=0;
		while(r-l>1)
		{
			if(cnt[k*2+2]>X)
			{
				l=(l+r)/2;
				k=k*2+2;
			}
			else
			{
				ret+=seg[k*2+2];
				X-=cnt[k*2+2];
				r=(l+r)/2;
				k=k*2+1;
			}
		}
		return ret;
	}
}seg;
P pos[SIZE];
int id[SIZE],to[SIZE];

int main()
{
	int n,m;
	scanf("%d %d",&n,&m);
	for(int i=0;i<n;i++)
	{
		int v,c;
		scanf("%d %d",&v,&c);
		pos[i]=P(c,v);
	}
	sort(pos,pos+n);
	for(int i=0;i<n;i++) vx.push_back(P(pos[i].second,i));
	sort(vx.begin(),vx.end());
	for(int i=0;i<n;i++) id[vx[i].second]=i;
	seg.init(n+2);
	ll ans=-INF;
	vector <PP> query;
	query.push_back(PP(P(0,n-m+1),P(0,n-1)));
	while(!query.empty())
	{
		vector <PP> nxt;
		seg.init(n+2);
		int s=0,e=0;
		for(int i=0;i<query.size();i++)
		{
			P p=query[i].first,q=query[i].second;
			int d=(p.first+p.second)/2;
			while(e<max(d,q.first)) seg.add(id[e++],1);
			while(s<d) seg.add(id[s++],-1);
			ll mx=-INF;
			int to=-1;
			for(int j=max(d,q.first);j<=q.second;j++)
			{
				if(e==j)
				{
					seg.add(id[j],1);
					e++;
				}
				ll vl=seg.get(m);
				if(vl!=-1)
				{
					vl-=2LL*(pos[j].first-pos[d].first);
					if(mx<vl)
					{
						mx=vl;
						to=j;
					}
				}
			}
			ans=max(ans,mx);
			if(p.first<d) nxt.push_back(PP(P(p.first,d),P(q.first,to)));
			if(d+1<p.second) nxt.push_back(PP(P(d+1,p.second),P(to,q.second)));
		}
		query=nxt;
	}
	printf("%lld\n",ans);
	return 0;
}
