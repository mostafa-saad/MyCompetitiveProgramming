#include<stdio.h>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
ll s1,s2;
ll dif[300001];
ll get(ll t)
{
	if(t>0)return -s1*t;
	else return -s2*t;
}
int main()
{
	int num,query;
	scanf("%d%d%lld%lld",&num,&query,&s1,&s2);
	vector<int>v;
	for(int i=0;i<=num;i++)
	{
		int z;
		scanf("%d",&z);
		v.push_back(z);
	}
	ll ans=0;
	for(int i=0;i<num;i++)
	{
		dif[i]=v[i+1]-v[i];
		ans+=get(dif[i]);
	}
	for(int i=0;i<query;i++)
	{
		int za,zb,zc;
		scanf("%d%d%d",&za,&zb,&zc);
		ans-=get(dif[za-1]);
		dif[za-1]+=zc;
		ans+=get(dif[za-1]);
		if(zb!=num)
		{
			ans-=get(dif[zb]);
			dif[zb]-=zc;
			ans+=get(dif[zb]);
		}
		printf("%lld\n",ans);
	}
}

